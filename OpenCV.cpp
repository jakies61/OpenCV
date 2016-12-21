#include "stdafx.h"
#include <iostream>
#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

int Camera() {
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
		cout << "Nie odnaleziono pliku!\n";
	};

	VideoCapture captureDevice;
	captureDevice.open(0);

	if (!captureDevice.isOpened()) {
		cout << "Kamera nie zosta³a wykryta\n";
	};

	Mat captureFrame;
	Mat grayscaleFrame;

	namedWindow("Kamera", 1);

	while(true) {
		captureDevice.read(captureFrame);

		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		vector<Rect> faces;

		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (int i = 0; i < faces.size(); i++) {
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		};

		imshow("Kamera", captureFrame);

		waitKey(0);
	};
	return 0;
}

int Picture() {
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
		cout << "Nie odnaleziono pliku!\n";
	};
	Mat picture;
	picture = imread("1.jpg", 1);
	if (!picture.data) {
		cout << "Nie odnaleziono pliku w folderze glownym!\n";
	};
	namedWindow("Zdjecie", CV_WINDOW_AUTOSIZE);

	vector<Rect> faces;
	Mat picture_gray;

	cvtColor(picture, picture_gray, CV_BGR2GRAY);
	equalizeHist(picture_gray, picture_gray);

	face_cascade.detectMultiScale(picture_gray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50));
	for (int i = 0; i < faces.size(); i++) {
		Rect rect_face(faces[i]);
		rectangle(picture, rect_face, Scalar(120, 5, 86), 2, 2, 0);
	};
	imshow("Zdjecie", picture);
	waitKey(0);
	return 0;
}

int WebCamera() {
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
		cout << "Nie odnaleziono pliku!\n";
	};
	VideoCapture captureMovie;
	captureMovie.open("http://130.215.73.77/mjpg/video.mjpg");
	if (!captureMovie.open("http://130.215.73.77/mjpg/video.mjpg")) {
		cout << "Kamera nie jest polaczona!\n";
	};
	Mat captureFrame;
	Mat grayscaleFrame;
	namedWindow("WebCamera", 1);
	while (true) {
		captureMovie.read(captureFrame);
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);
		vector<Rect> faces;
		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		for (int i = 0; i < faces.size(); i++) {
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);
			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		};
		imshow("WebCamera", captureFrame);
		waitKey(33);
	};
}

int Video() {
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt2.xml");
	if (!face_cascade.load("haarcascade_frontalface_alt2.xml")) {
		cout << "Nie odnaleziono pliku!\n";
	};

	VideoCapture captureMovie;
	captureMovie.open("1.avi");
	if (!captureMovie.open("1.avi")) {
		cout << "Nie odnaleziono pliku!\n";
		//return -1;
	};

	Mat captureFrame;
	Mat grayscaleFrame;

	namedWindow("Nagranie", 1);

	while (true) {
		captureMovie.read(captureFrame);

		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		vector<Rect> faces;

		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (int i = 0; i < faces.size(); i++) {
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		};

		imshow("Nagranie", captureFrame);
		waitKey(0);
	};
	return 0;
}

int main() {
	int wybor;
	cout << "Za pomoca czego chcesz wykryc twarz?  \n";
	cout << "1. Kamera\n";
	cout << "2. Zdjecie\n";
	cout << "3. Nagranie\n";
	cout << "4. WebCamera\n";
	cout << "0. Wyjscie\n";

	while (scanf_s("%d", &wybor) != 1 || wybor > 4)
	{
		cout << "Podany przez Ciebie znak nie jest cyfra z zakresu 1-4!\n Sprobuj jeszcze raz: ";
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	if (wybor == 1) {
		Camera();
	}else if (wybor == 2) {
		Picture();
	}else if (wybor == 3) {
		Video();
	}else if (wybor == 4) {
		WebCamera();
	}else if (wybor == 0) {
		return 0;
	};
}