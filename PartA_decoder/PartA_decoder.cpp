// PartA_decoder.cpp : First example of use of the Steganograph class for decoding. No noise added to carrier, no scrambling, no colour carrier 
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
	Steganograph sg("pwd");

	std::string 
		pathencoded = "../ImagesA/PartAencoded.png", 
		pathcarrier = "../ImageSrc/grayscale_carrier.png", 
		pathoutput = "../ImagesA/PartAdecoded.png";

	std::cout << "Part A Decoder\n";
	std::cout << "Enter encoded file path:\n";
	std::cin >> pathencoded;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	encoded = imread(pathencoded, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_GRAYSCALE);

	//assert that the files have been read
	assert(encoded.rows != 0 && carrier.rows != 0);

	//flags = 0 means no scrambling, no noise 
	result = sg.decodeMat(carrier, encoded, 0, pathoutput.c_str());
	imshow("partAdecoded", result);
	waitKey(0);
}
