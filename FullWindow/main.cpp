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

	//-�摜�����[�h-
	image = imread(image_name,1);

	//�E�B���h�E�쐬
	namedWindow(windowname,0);

	//�w��̃E�B���h�E���t���X�N���[���ɐݒ�
	/*****�d�l��*****
	DISP_NUMBER:�\���������f�o�C�X�̔ԍ����w��D
		�f�B�X�v���C�̂ݐڑ����Ă�����
			0=�f�B�X�v���C
		�f�B�X�v���C+�v���W�F�N�^���ڑ����Ă�����
			0=�f�B�X�v���C
			1=�v���W�F�N�^
	windowname:�\���������E�B���h�E�̖��O
	*****************/
	Projection::MySetFullScrean(DISP_NUMBER,windowname);

	//��ʕ\��
	imshow(windowname,image);

	//�J����������
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