// PartA.cpp : First example of use of the Steganograph class for encoding. No noise added to carrier, no scrambling, no colour carrier 
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

	Mat message, carrier,result;
	Steganograph sg("pwd");

	std::string 
		pathmessage="../ImageSrc/message.png", 
		pathcarrier="../ImageSrc/grayscale_carrier.png",
		pathoutput="../ImagesA/PartAencoded.png";

	std::cout << "Part A Encoder\n";
	std::cout << "Enter message file path:\n";
	std::cin >> pathmessage;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	message = imread(pathmessage, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_GRAYSCALE);

	//assert that the files have been read
	assert(message.rows != 0 && carrier.rows != 0);

	result = sg.encodeMat(carrier, message, 0, pathoutput.c_str());
	imshow("partAencoded",result);
	waitKey(0);
}
