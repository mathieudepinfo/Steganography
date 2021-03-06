// PartD.cpp : Fourth example of use of the Steganograph class for encoding. Noise is added to carrier, signal is scrambled, colour carrier 
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

	Mat message, carrier, result;
	Steganograph sg("pwd");

	std::string 
		pathmessage = "../ImageSrc/messages/message2.png", 
		pathcarrier = "../ImageSrc/colour_carrier.png",
		pathoutput = "../ImagesD/PartDencoded.png";

	std::cout << "Part D Encoder\n";
	std::cout << "Enter message file path:\n";
	std::cin >> pathmessage;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	message = imread(pathmessage, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_COLOR);

	//assert that the file has been read
	assert(message.rows != 0 && carrier.rows != 0);

	result = sg.encodeMat(carrier, message, SG_NOISE | SG_SCRAMBLE, pathoutput.c_str());
	imshow("partDencoded", result);

	waitKey(0);
}