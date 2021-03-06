// PartD_decoder.cpp :  Fourth example of use of the Steganograph class for decoding. Noise is added to carrier, signal is scrambled, use a colour carrier 
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
		pathencoded = "../ImagesD/PartDencoded.png",
		pathcarrier = "../ImageSrc/colour_carrier.png",
		pathoutput = "../ImagesD/PartDdecoded.png";

	std::cout << "Part D Decoder\n";
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

	result = sg.decodeMat(carrier, encoded, SG_SCRAMBLE|SG_NOISE, pathoutput.c_str());
	imshow("partDdecoded", result);
	waitKey(0);
}
