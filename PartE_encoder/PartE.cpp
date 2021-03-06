// PartE.cpp :  Fifth example of use of the Steganograph class for encoding. Noise is added to carrier, signal is scrambled, colour carrier, message can be any file
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

	Mat carrier, result;
	Steganograph sg("pwd");

	std::string pathmessage = "../ImageSrc/messages/partE_message3.txt", pathcarrier = "../ImageSrc/carriers/partE/partE_large_rgb_carrier-3.png",
		pathoutput = "../ImagesE/PartEencoded.png";

	std::cout << "Part E Encoder\n";
	std::cout << "Enter message file path:\n";
	std::cin >> pathmessage;
	std::cout << "Enter carrier file path:\n";
	std::cin >> pathcarrier;
	std::cout << "Enter output file path:\n";
	std::cin >> pathoutput;

	carrier = imread(pathcarrier, CV_LOAD_IMAGE_COLOR);

	//assert that the file has been read
	assert(carrier.rows != 0);

	result = sg.encodeFile(carrier, pathmessage.c_str(), SG_NOISE | SG_SCRAMBLE, pathoutput.c_str());
	imshow("partEencoded", result);

	waitKey(0);
}