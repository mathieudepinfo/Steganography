#include "Steganograph.h"



Steganograph::Steganograph()
{
}

Steganograph::Steganograph(const char* pwd)
{
	password = pwd;

}


Steganograph::~Steganograph()
{
}

Steganograph& Steganograph::setPwd(const char * newPwd)
{
	password = newPwd;
	return (*this);
}

cv::Mat Steganograph::encodeMat(const cv::Mat & carrier, const cv::Mat & message, int flags, const char* filedst)
{
	//copy the carrier 
	cv::Mat encoded_image = carrier.clone();
	cv::Mat cmessage;
	if (message.isContinuous()) cmessage = message;
	else cmessage = message.clone();

	//getting useful information on the carrier
	uint nRows = carrier.rows;
	uint nCols = carrier.cols;
	uint nChannels = carrier.channels();
	uint messageChannels = message.channels();
	//Initializing random number generator
	cv::RNG rng(hash(password));
	
	//Applying noise for unique carrier
	if(flags & SG_NOISE) addNoise(rng, encoded_image);

	uint l = 0;
	uint size = nRows * nCols*messageChannels;
	cv::Mat used = cv::Mat::zeros(carrier.size(), carrier.type());	
	uchar LSBmask = 1;	//mask used to change value of least significant bit

	//Encoded(l) = Carrier(l) + Message(k), signal is scrambled
	for (uint k = 0; k < size ; ++k)
	{

		if (SG_SCRAMBLE & flags) {
			//Select a random location
			while (used.data[l] == 1) {
				l = rng.uniform(0, size);
			};
			
			//Updating used positions
			used.data[l] = 1;
		}
		else {
			l = k;
		}

		//if message(k) is 0, changing least significant bit
		if (cmessage.data[k] == 0) encoded_image.data[l] ^= LSBmask;
	}

	//writing result in an image file if required
	if (filedst != nullptr) {
		try {
			cv::imwrite(filedst,encoded_image);
		}
		catch (std::exception e) {
			throw e;
		}

	}

	return encoded_image;
}

cv::Mat Steganograph::encodeFile(const cv::Mat & carrier, const char * message,int flags, const char* filedst)
{
	//opening the stream
	std::ifstream file(message, std::ios::binary);

	//vector which will contain the binary data , first bits are reserved for filesize(in bits)
	std::vector<uchar> bvec(BITS_PER_INT);	

	uchar mask = 0; //mask used to select a specific bit in a char
	char c;		//character read by file.get
	uchar uc;	//cast of c into an uc
	uchar b;	//bit value, 8 for each uc

	while (file.get(c)) {// read char by char (8bits)
		uc = reinterpret_cast<uchar&>(c);

		/*
		for each char, storing the value of each bit in an element of bvec
		the most significant bit is on the left
		bvec(0:64) = size bits
		Kth char = bvec(64+k*8:64+(k+1)*8), bvec(64+k*8) = MSB*/
		for (int i = BITS_PER_BYTE-1; i >= 0; --i) {
			mask = 1 << i;
			b = (uc & mask) >> i;

			//Storing 255 instead of 1 (data prepared for binary image)
			bvec.push_back(b * UCHAR_MAX); 
		}

	}
	file.close();

	size_t sizeMask = 0;

	//Now that all bytes have been read => storing the size (nob for number of bits) in bvec
	size_t nob = (bvec.size() - BITS_PER_INT);
	for (int i = BITS_PER_INT - 1; i >= 0; --i) {
		sizeMask = 1l << i;
		b = static_cast<uchar>((nob & sizeMask) >> i);
		bvec[BITS_PER_INT - 1-i] = (b * UCHAR_MAX);
	}

	//If the carrier capacity is too small throwing an error
	uint maxInfo = carrier.cols*carrier.rows*carrier.channels();
	if (maxInfo < bvec.size()) throw "Not enough space";

	//Creating a binary image of the same size than the carrier to store the data
	cv::Mat binaryImage = cv::Mat::zeros(carrier.size(), carrier.type());


	for (int i = 0; i < bvec.size(); ++i) {
		binaryImage.data[i] = bvec[i];
	}

	if(SG_SHOWBINARY & flags)cv::imshow("binaryfile", binaryImage);
	std::cout << "Information stored :" << bvec.size() / BITS_PER_BYTE << " bytes, \nMaximum capacity : " << maxInfo / BITS_PER_BYTE << "bytes\n";

	return encodeMat(carrier,binaryImage,flags,filedst);
}

cv::Mat Steganograph::decodeMat(const cv::Mat & carrier, const cv::Mat & message, int flags,const char* filedst)
{

	if (carrier.rows*carrier.cols != message.rows*message.cols) throw "Invalid dimensions";

	//getting useful information on the carrier
	uint nRows = carrier.rows;
	uint nCols = carrier.cols;
	uint nChannels = carrier.channels();
	uint messageChannels;
	
	//assert that message is continuous for easier access
	cv::Mat cmessage;
	if (!message.isContinuous()) cmessage = message.clone();
	else cmessage = message;

	//empty decoded image to store the result, 
	//if the message was a multi channel image (basically call to encodeFile), it needs 3 channels
	cv::Mat decoded_image;
	if (SG_COLOR_MESSAGE & flags) {
		decoded_image = cv::Mat::zeros(carrier.size(), CV_8UC3);
		messageChannels = 3;
	}
	else {
		decoded_image = cv::Mat::zeros(carrier.size(), CV_8UC1);
		messageChannels = 1;
	}

	//Applying noise for unique carrier
	cv::RNG rng(hash(password));
	cv::Mat carrier_noise = carrier.clone();
	if(SG_NOISE & flags) addNoise(rng,carrier_noise);

	uint l = 0;	//index for scrambling
	cv::Mat used = cv::Mat::zeros(carrier.size(), carrier.type()); //used positions, initialized with zeros
	uint size = nRows * nCols*messageChannels;	//number of char in the message

	//Decoding loop, reverse the operations made in encodeMat
	for (uint k = 0; k < size; ++k)
	{
		if (SG_SCRAMBLE & flags) {
			//Select a random location
			while (used.data[l] == 1) {
				l = rng.uniform(0,size );
			};

			//Updating used positions
			used.data[l] = 1;
		}
		else {
			l = k;
		}

		//Reverse operation of XOR is XOR
		decoded_image.data[k] = (1 - (message.data[l] ^ carrier_noise.data[l])) * 255;
	}

	if (filedst!=nullptr) {
		//writing can fail if filedst is not image format
		try {
			cv::imwrite(filedst, decoded_image);
		}
		catch (std::exception e) {
			throw e;
		}
		
	}

	return decoded_image;
}

void Steganograph::decodeFile(const cv::Mat & carrier, const cv::Mat & message, const char* filedst,int flags)
{
	//decoding the message to get a binary image representing the file
	cv::Mat decoded = decodeMat(carrier, message,flags|SG_COLOR_MESSAGE, nullptr);
	if (SG_SHOWBINARY & flags)cv::imshow("binaryfile",decoded);

	//converting binary data to a vector
	std::vector<uchar> bitvec;

	if(!decoded.isContinuous()) decoded = decoded.clone();
	bitvec.assign(decoded.datastart, decoded.dataend);
	
	//Retrieving number of bits from 64 first bits
	size_t nob = 0;
	for (int i = 0; i < BITS_PER_INT; ++i) {
		nob += (bitvec[i]/255)  << (BITS_PER_INT - 1 - i);
	}

	if (nob%BITS_PER_BYTE != 0) throw "Invalid bit size";

	size_t nbytes = nob / BITS_PER_BYTE;	

	std::ofstream decoded_file(filedst, std::ios::out | std::ios::binary);
	
	std::vector<uchar> charvec(nbytes,0);

	//Converting packs of 8bits into unsigned chars
	for (int i = 0; i < nbytes; ++i) {
		for (int b = 0; b < BITS_PER_BYTE; ++b) {
			charvec[i] += (bitvec[i*BITS_PER_BYTE+BITS_PER_INT+b] / 255) << (BITS_PER_BYTE-1-b);
		}
	}

	//Writing the result in the file
	decoded_file.write(reinterpret_cast<char*>(&charvec[0]), nbytes);

	decoded_file.close();
}


uint Steganograph::hash(const char *str)
{
	uint hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


void Steganograph::addNoise(cv::RNG & rng, cv::Mat & m)
{
	cv::Mat noise = cv::Mat(m.size(), m.type());
	rng.fill(noise, cv::RNG::NORMAL, 0, 5);
	add(m, noise, m);
}
