// PartB.cpp : Second example of use of the Steganograph class for encoding. No noise added to carrier, signal is scrambled, no colour carrier 
//
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

#include "Steganograph.h"

using namespace cv;


int main(int argc, char** argv)
{

	Mat message, carrier, result;
	
	std::string 
		pathmessage = "../ImageSrc/message.png", 
		pathcarrier = "../ImageSrc/grayscale_carrier.png", 
		pathoutput = "../ImagesB/PartBencoded.png",
		password = "scrambling"
		;
	std::cout << "Part B Encoder\n";

	std::cout << "Enter password\n";
	std::cin >> password;
	std::cout << "Enter message file path:\n";
	std::cin >> pathmessage;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	Steganograph sg(password.c_str());

	message = imread(pathmessage, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_GRAYSCALE);

	//assert that the file has been read
	assert(message.rows != 0 && carrier.rows != 0);

	result = sg.encodeMat(carrier, message, SG_SCRAMBLE, pathoutput.c_str());
	imshow("partBencoded", result);
	waitKey(0);
}
