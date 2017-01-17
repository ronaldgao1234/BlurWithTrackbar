#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
using namespace std;

//OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int blurAmount = 15;
//trackbar call back function
static void onChange(int pos, void* userInput);
//Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput);

Mat img;
bool applyGray = false;
bool applyBlur = false;
bool applySobel = false;
void grayCallback(int state, void * userData) {
	applyGray = true;
	applyFilters();
}
void bgrCallback(int state, void* userData) {
	applyGray = false;
	applyFilters();
}
void blurCallback(int state, void* userData) {
	applyBlur = (bool)state;
	applyFilters();
}
void sobelCallback(int state, void* userData) {
	applySobel = !applySobel;
	applyFilters();
}
void applyFilters() {
	Mat result;
	img.copyTo(result);
	if (applyGray) {
		cvtColor(result, result, COLOR_BGR2GRAY);
	}
	if (applyBlur) {
		blur(result, result, Size(5, 5));
	}
	if (applySobel) {
		Sobel(result, result, CV_8U, 1, 1);
	}
	imshow("Lena", result);
}

int main(int argc, const char** argv) {
	//Read images
	Mat iu = imread("iu.jpg");
	Mat lena = imread("lena.jpg");

	//create windows
	namedWindow("lenaI", CV_GUI_NORMAL);
	//namedWindow("iuI", 0);

	//window name, parent window name, pointer to variable that reflects position of slider,
	//max value of the slider position, pointer to function to be called everytime the slider changes
	//position,user data that is passed as callback
	setMouseCallback("lenaI", onMouse, &lena);
	createTrackbar("lenaI", "lenaI", &blurAmount, 30, onChange, &lena);
	onChange(blurAmount, &lena);

	img = imread("lena.jpg");

	//create buttons
	createButton("Blur", blurCallback, NULL, QT_CHECKBOX, 0);
	createButton("Gray", grayCallback, NULL, QT_RADIOBOX, 0);
	createButton("RGB", bgrCallback, NULL, QT_RADIOBOX, 1);
	createButton("Sobel", sobelCallback, NULL, QT_PUSH_BUTTON, 0);
	namedWindow("lena");
	//move window
	//moveWindow("lenaI", 10, 10);
	//moveWindow("iuI", 520, 10);
	//show images
	//imshow("lenaI", lena);
	//imshow("iuI", iu);
	//resize windows
	//resizeWindow("lenaI", 512, 512);
	//wait for key press
	waitKey(0);

	//destroy the windows
	destroyWindow("lenaI");
	//destroyWindow("iuI");
	destroyWindow("lena");

	//create 10 windows
	//for(int i = 0; i < 10; i++) {
	//	ostringstream ss;
	//	ss << "iuI " << i;
	//	namedWindow(ss.str());
	//	moveWindow(ss.str(), 20 * i, 20 * i);
	//	imshow(ss.str(), lena);
	//}

	//waitKey(0);
	////Destroy all windowes
	//destroyAllWindows();
	return 0;
}

//trackbar callback function
static void onChange(int pos, void* userInput) {
	//cannot do  0 pixels blur
	if (pos <= 0)
		return;
	//Aux variable for result
	Mat imgBlur;

	//get the pointer input image	
	Mat* img = (Mat*)userInput;

	//Apply a blur filter
	blur(*img, imgBlur, Size(pos, pos));

	//Show the result
	imshow("lenaI", imgBlur);
}

//Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput) {
	if (event != EVENT_LBUTTONDOWN)
		return;

	//Get the pointer input image
	Mat* img = (Mat*)userInput;

	//Draw a circle
	circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);
	//imshow("Lena", imgBkur)
	//call onChange to get blurred image
	onChange(blurAmount, img);
}
