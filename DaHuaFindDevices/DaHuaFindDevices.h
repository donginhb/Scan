
// DaHuaFindDevices.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDaHuaFindDevicesApp: 
// �йش����ʵ�֣������ DaHuaFindDevices.cpp
//

class CDaHuaFindDevicesApp : public CWinApp
{
public:
	CDaHuaFindDevicesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDaHuaFindDevicesApp theApp;