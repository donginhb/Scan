
// Client_Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClient_DemoApp:
// �йش����ʵ�֣������ Client_Demo.cpp
//


class CClient_DemoApp : public CWinAppEx
{
public:
	CClient_DemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClient_DemoApp theApp;