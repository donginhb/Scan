
// testFindDevices.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtestFindDevicesApp: 
// �йش����ʵ�֣������ testFindDevices.cpp
//

class CtestFindDevicesApp : public CWinApp
{
public:
	CtestFindDevicesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestFindDevicesApp theApp;