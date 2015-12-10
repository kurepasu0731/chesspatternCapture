#pragma once

#include <Windows.h>
#include <opencv2\opencv.hpp>

using namespace std;

namespace Projection{

	typedef struct disp_prop{
		int index;
		int x,y,width,height;
	} Disp_Prop;

	int dispCount=-1;
	vector<Disp_Prop> Disps_Prop;

	//�f�B�X�v���C�̏�����
	BOOL CALLBACK DispEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData ) {
		Disp_Prop di;
		di.index = dispCount++;
		di.x = lprcMonitor->left;
		di.y = lprcMonitor->top;
		di.width = lprcMonitor->right - di.x;
		di.height = lprcMonitor->bottom - di.y;
		Disps_Prop.push_back(di);

		return TRUE; // TRUE�͒T���p���CFALSE�ŏI��
	}

	//�f�B�X�v���C���o
	void SearchDisplay(void) {
		// ��x�������s����
		if (dispCount == -1) {
			dispCount = 0;
			Disps_Prop = vector<Disp_Prop>();
			EnumDisplayMonitors(NULL, NULL, DispEnumProc, 0);
			Sleep(200);
		}
	}

	//�v���W�F�N�V����
	void MySetFullScrean(const int num, const char *windowname){

		HWND windowHandle = ::FindWindowA(NULL, windowname);

		SearchDisplay();

		if (NULL != windowHandle) {

			//-�E�B���h�E�X�^�C���ύX�i���j���[�o�[�Ȃ��A�őO�ʁj-
			SetWindowLongPtr(windowHandle,  GWL_STYLE, WS_POPUP);
			SetWindowLongPtr(windowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);

			//-�ő剻����-
			ShowWindow(windowHandle, SW_MAXIMIZE);
			cv::setWindowProperty(windowname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );

			//-�f�B�X�v���C���w��-
			Disp_Prop di = Disps_Prop[num];

			//-�N���C�A���g�̈���f�B�X�v���[�ɍ��킹��-
			SetWindowPos(windowHandle, NULL, di.x, di.y, di.width, di.height, SWP_FRAMECHANGED | SWP_NOZORDER);
		}
	}
}