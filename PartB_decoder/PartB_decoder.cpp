// PartB_decoder.cpp : Second example of use of the Steganograph class for decoding. No noise added to carrier, but signal is scrambled, no colour carrier 
//


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <cassert>
#include "Steganograph.h"

using namespace cv;


int main(int argc, char** argv)
{

	Mat encoded, carrier, result;
	

	std::string 
		pathencoded = "../ImagesB/PartBencoded.png", 
		pathcarrier = "../ImageSrc/grayscale_carrier.png", 
		pathoutput = "../ImagesB/PartBdecoded.png",
		password = "scrambling";

	std::cout << "Part B Decoder\n";
	std::cout << "Enter password\n";
	std::cin >> password;
	std::cout << "Enter encoded file path:\n";
	std::cin >> pathencoded;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	Steganograph sg(password.c_str());

	encoded = imread(pathencoded, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_GRAYSCALE);

	//assert that the file has been read
	assert(encoded.rows != 0 && carrier.rows != 0);

	result = sg.decodeMat(carrier, encoded, SG_SCRAMBLE, pathoutput.c_str());
	imshow("partBdecoded", result);
	waitKey(0);
}
