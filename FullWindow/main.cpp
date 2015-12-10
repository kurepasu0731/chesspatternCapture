#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <opencv2\opencv.hpp>

#include "Projection.hpp"

#define DISP_NUMBER (2)

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480


using namespace cv;

const string image_name("./image/chess_pattern_1280_800.jpg");
const char* windowname = "Window";

VideoCapture vc;
Mat camera_img;
std::string winName = "Camera Image";

int capNum = 0;

void initCamera(){
	vc = VideoCapture(0);
	Size captureSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	vc.set(CV_CAP_PROP_FRAME_WIDTH, captureSize.width);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, captureSize.height);
	namedWindow(winName);
}

std::string get_capImgFileName(int num){
	std::string str1 = "./capture_image/cap";
	std::string str2 = std::to_string(num);
	std::string str3 = ".jpg";
	std::string filename = str1 + str2 + str3;

	return filename;
}


void idle(){
	vc >> camera_img;
	imshow(winName, camera_img);
}


int main(void){

	Mat image;

	//-画像をロード-
	image = imread(image_name,1);

	//ウィンドウ作成
	namedWindow(windowname,0);

	//指定のウィンドウをフルスクリーンに設定
	/*****仕様書*****
	DISP_NUMBER:表示したいデバイスの番号を指定．
		ディスプレイのみ接続している状態
			0=ディスプレイ
		ディスプレイ+プロジェクタが接続している状態
			0=ディスプレイ
			1=プロジェクタ
	windowname:表示したいウィンドウの名前
	*****************/
	Projection::MySetFullScrean(DISP_NUMBER,windowname);

	//画面表示
	imshow(windowname,image);

	//カメラ初期化
	//initCamera();

	while(true){
		//idle();
		std::string filename = get_capImgFileName(capNum);
		if(waitKey(30) == 'c') {
			imwrite(filename, camera_img);
			capNum++;
		}

	}

	return 0;
}