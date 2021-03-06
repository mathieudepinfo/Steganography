// PartC.cpp : Third example of use of the Steganograph class for encoding. Noise is added to carrier, signal is scrambled, no colour carrier 
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

	Mat message, carrier, resultN,resultSN;
	Steganograph sg("pwd");

	std::string 
		pathmessage = "../ImageSrc/messages/message2.png", 
		pathcarrier = "../ImageSrc/grayscale_carrier.png",
		pathoutputN = "../ImagesC/PartCencodedNoise.png", 
		pathoutputSN = "../ImagesC/PartCencodedWithoutNoise.png";

	std::cout << "Part C Encoder\n";
	std::cout << "Enter message file path:\n";
	std::cin >> pathmessage;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path (Encoded with Noise):\n";
	std::cin >> pathoutputN;
	std::cout << "Enter output file path (Encoded without Noise):\n";
	std::cin >> pathoutputSN;

	message = imread(pathmessage, CV_LOAD_IMAGE_GRAYSCALE);
	carrier = imread(pathcarrier, CV_LOAD_IMAGE_GRAYSCALE);

	//assert that the file has been read
	assert(message.rows != 0 && carrier.rows != 0);

	resultN = sg.encodeMat(carrier, message, SG_NOISE|SG_SCRAMBLE, pathoutputN.c_str());
	imshow("partCencodedWithNoise", resultN);

	resultSN = sg.encodeMat(carrier, message, SG_SCRAMBLE, pathoutputSN.c_str());
	imshow("partCencodedWithoutNoise", resultSN);

	Mat noise;
	absdiff(resultN, resultSN, noise);
	imshow("noise",noise) ;

	waitKey(0);
}