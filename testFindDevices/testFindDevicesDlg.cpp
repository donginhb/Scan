
// testFindDevicesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testFindDevices.h"
#include "testFindDevicesDlg.h"
#include "afxdialogex.h"

# include <stdlib.h>
#include "DiZhiPuVideoServer/netsdk.h"
#include "DiZhiPuVideoServer/H264Play.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "netsdk.lib")

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestFindDevicesDlg �Ի���



CtestFindDevicesDlg::CtestFindDevicesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestFindDevicesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestFindDevicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
}

BEGIN_MESSAGE_MAP(CtestFindDevicesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestFindDevicesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestFindDevicesDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtestFindDevicesDlg ��Ϣ�������

BOOL CtestFindDevicesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_wndList.DeleteAllItems(); 
	m_wndList.InsertColumn(0, _T(""));
	m_wndList.InsertColumn(1, _T("�豸���"));
	m_wndList.InsertColumn(2, _T("IP"));
	m_wndList.InsertColumn(3, _T("Э��"));
	m_wndList.InsertColumn(4, _T("PORT"));
	m_wndList.InsertColumn(5, _T("MAC"));
	m_wndList.InsertColumn(6, _T("SN"));
	m_wndList.SetColumnWidth(0, 20);
	m_wndList.SetColumnWidth(1, 150);
	m_wndList.SetColumnWidth(2, 150);
	m_wndList.SetColumnWidth(3, 50);
	m_wndList.SetColumnWidth(4, 50);
	m_wndList.SetColumnWidth(5, 150);
	m_wndList.SetColumnWidth(6, 150);
	
	



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestFindDevicesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestFindDevicesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestFindDevicesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestFindDevicesDlg::OnBnClickedButton1()
{
	
}


void CtestFindDevicesDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int  nInit = 0;
	int nRetLength = 0;

	nInit = H264_DVR_Init(NULL, NULL);
	int j = m_wndList.GetItemCount();
	while(j < 0)
	{
		m_wndList.DeleteItem(j);
		j--;
	}
	
	SDK_CONFIG_NET_COMMON_V2 m_Device[100] = { 0 };
	memset(&m_Device, 0, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100);
	bool bRet = H264_DVR_SearchDevice((char*)m_Device, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100, &nRetLength, 3000);
	
	if (bRet)
	{		
		m_wndList.SetRedraw(FALSE);
		int nTotalIndex = m_wndList.GetItemCount();
		int i=0, ncount = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);
		for (i = 0; i < ncount; i++)		
		{
			char sTmp[20] = { 0 };
			sprintf_s(sTmp, "%d", i+1);
			int nIndex = m_wndList.InsertItem(nTotalIndex + i, sTmp);
			
			m_wndList.SetItemText(nIndex, 1, m_Device[i].HostName);
			struct in_addr in;
			in.s_addr = m_Device[i].HostIP.l;			
			m_wndList.SetItemText(nIndex, 2, inet_ntoa(in));

			m_wndList.SetItemText(nIndex, 6, m_Device[i].sSn);
				
		}
		
		
		m_wndList.SetRedraw(TRUE);
	}
	
}
