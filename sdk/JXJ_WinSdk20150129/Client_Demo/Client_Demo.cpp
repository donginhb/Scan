
// Client_Demo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "Client_DemoDlg.h"
#include "FullUpDlg.h"
#include "Pub_Data.h"
#include "BorderDlg.h"
#include "direct.h"     //mkdir ͷ�ļ�

#include "Winnls.h"
#include "Windows.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient_DemoApp

BEGIN_MESSAGE_MAP(CClient_DemoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient_DemoApp ����

CClient_DemoApp::CClient_DemoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClient_DemoApp ����

CClient_DemoApp theApp;
CFullUpDlg g_cFullUpDlg[GET_MAX_DEV_NUM];
CPub_Data g_PubData;

// CClient_DemoApp ��ʼ��

BOOL CClient_DemoApp::InitInstance()
{
	
	AfxOleInit();
	
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//=======================================================

	CStringArray strArrKey;
	CStringArray strArrKeyValue;	
	CStringArray strArraySetion;
	CStringArray strArrallSecons;

	//g_PubData.g_iniFile.m_strPath = _T(".\\sdk.ini");
	g_PubData.g_iniFile.SetIniPath(_T(""), _T("sdk.ini"));
	g_PubData.g_iniFile.GetAllSections(strArrallSecons);
	int iCount = strArrallSecons.GetCount();
	if(strArrallSecons.GetAt(0) == _T(""))
	{
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("ץ��·��"),_T("D:\\PICTURE_SRC"));
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("¼��·��"),_T("D:\\VIDEO_SRC"));	
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("����·��"),_T("D:\\DOWNLOAD_SRC"));
		if(!PathFileExists(_T("D:\\PICTURE_SRC")))
		{
			::_mkdir(_T("D:\\PICTURE_SRC")); 
		}
		if(!PathFileExists(_T("D:\\VIDEO_SRC")))
		{
			::_mkdir(_T("D:\\VIDEO_SRC")); 
		}
		if(!PathFileExists(_T("D:\\DOWNLOAD_SRC")))
		{
			::_mkdir(_T("D:\\DOWNLOAD_SRC")); 
		}

	}
	if(iCount< 2)
	{
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("ģʽ"),_T("0"));     //0 �ͻ���  1 �����;
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("����˿�"),_T("5556"));
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("���˿�"),_T("6666"));
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("����"),_T("0"));
	}


	g_PubData.g_iniFile.GetAllSections(strArraySetion);
	g_PubData.g_iniFile.GetAllKeysAndValues(strArraySetion.GetAt(1),strArrKey,strArrKeyValue);
	g_PubData.g_iLanguageFlag = _ttoi(strArrKeyValue.GetAt(3));
	//==============================================================
	LCID lcidThread = 0;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		lcidThread = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),SORT_DEFAULT);
		SetThreadLocale(lcidThread);  

	}
	else
	{
		lcidThread = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT);
		SetThreadUILanguage(lcidThread);
	}


	//SetThreadUILanguage(lcidThread);


	if(g_PubData.g_iLanguageFlag == 0)
	{
		g_PubData.g_strTalkS = _T("�Խ�");
		g_PubData.g_strTalkE = _T("ֹͣ");

		g_PubData.g_strRecordS = _T("¼��");
		g_PubData.g_strRecordE = _T("ֹͣ");

		g_PubData.g_strListenS = _T("����");
		g_PubData.g_strListemE = _T("�ر�");

		g_PubData.g_strSetMessage = _T("����ʧ�ܣ�");
		g_PubData.g_strGetMessage = _T("��ȡʧ�ܣ�");

	}
	else
	{
		g_PubData.g_strTalkS = _T("Talk");
		g_PubData.g_strTalkE = _T("Stop");

		g_PubData.g_strRecordS = _T("Record");
		g_PubData.g_strRecordE = _T("Stop");

		g_PubData.g_strListenS = _T("Listen");
		g_PubData.g_strListemE = _T("Close");

		g_PubData.g_strSetMessage = _T("Set Failed��");
		g_PubData.g_strGetMessage = _T("Get Failed��");

	}











	
	CClient_DemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

	
	return FALSE;
}
