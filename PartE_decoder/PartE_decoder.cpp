// PartE_decoder.cpp :  Fifth example of use of the Steganograph class for decoding. Noise is added to carrier, signal is scrambled, colour carrier, message can be any file 
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


	std::string pathencoded = "../ImagesE/PartEencoded.png",
		pathcarrier = "../ImageSrc/carriers/partE/partE_large_rgb_carrier-3.png",
		pathoutput = "../ImagesE/PartEdecoded.txt",
		password;

	std::cout << "Part E Decoder\n";
	std::cout << "Enter encoded file path:\n";
	std::cin >> pathencoded;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	Steganograph sg("pwd");

	encoded = imread(pathencoded, CV_LOAD_IMAGE_COLOR);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_COLOR);

	//assert that the file has been read
	assert(encoded.rows != 0 && carrier.rows != 0);

	sg.decodeFile(carrier, encoded, pathoutput.c_str(), SG_SCRAMBLE | SG_NOISE);

	std::cout << "Done \n";
	waitKey(0);
}
