
// DaHuaFindDevicesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DaHuaFindDevices.h"
#include "DaHuaFindDevicesDlg.h"
#include "afxdialogex.h"

#include "DHVideoServer/dhnetsdk.h"

#pragma comment(lib, "JNetSDK.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// TODO:  �ڴ���ӿؼ�֪ͨ����������
typedef BOOL(CALL_METHOD *pCLIENT_Init)(DH::fDisConnect cbDisConnect, LDWORD dwUser);

// �첽������������IPC��NVS���豸
typedef LLONG(CALL_METHOD *pCLIENT_StartSearchDevices)(DH::fSearchDevicesCB cbSearchDevices, void* pUserData, char* szLocalIp);
//typedef BOOL (CALL_METHOD *pCLIENT_SearchDevicesByIPs)(DEVICE_IP_SEARCH_INFO* pIpSearchInfo, fSearchDevicesCB cbSearchDevices, LDWORD dwUserData, char* szLocalIp, DWORD dwWaitTime);
// ֹͣ�첽������������IPC��NVS���豸
typedef BOOL(CALL_METHOD *pCLIENT_StopSearchDevices)(LLONG lSearchHandle);

// ������������IPC��NVS���豸
typedef BOOL (CALL_METHOD *pCLIENT_SearchDevices)(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime, char* szLocalIp );


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


// CDaHuaFindDevicesDlg �Ի���



CDaHuaFindDevicesDlg::CDaHuaFindDevicesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDaHuaFindDevicesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDaHuaFindDevicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CDaHuaFindDevicesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDaHuaFindDevicesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDaHuaFindDevicesDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDaHuaFindDevicesDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDaHuaFindDevicesDlg ��Ϣ�������

BOOL CDaHuaFindDevicesDlg::OnInitDialog()
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

	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T(""));
	m_list.InsertColumn(1, _T("����"));
	m_list.InsertColumn(2, _T("IP"));
	m_list.InsertColumn(3, _T("�˿�"));
	m_list.InsertColumn(4, _T("��������"));
	m_list.InsertColumn(5, _T("����"));
	m_list.InsertColumn(6, _T("MAC"));
	m_list.InsertColumn(7, _T("ID"));
	m_list.SetColumnWidth(0, 20);
	m_list.SetColumnWidth(1, 150);
	m_list.SetColumnWidth(2, 150);
	m_list.SetColumnWidth(3, 100);
	m_list.SetColumnWidth(4, 150);
	m_list.SetColumnWidth(5, 150);
	m_list.SetColumnWidth(6, 150);
	m_list.SetColumnWidth(7, 150);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDaHuaFindDevicesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDaHuaFindDevicesDlg::OnPaint()
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
HCURSOR CDaHuaFindDevicesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LLONG CDaHuaFindDevicesDlg::SearchDevicesCB1(DH::DEVICE_NET_INFO_EX *pDevNetInfo, void *pUserData)
{
	CDaHuaFindDevicesDlg* pWnd = (CDaHuaFindDevicesDlg*)pUserData;
	
	pWnd->m_list.SetRedraw(FALSE);	
	int nTotalIndex = pWnd->m_list.GetItemCount();
	int j = nTotalIndex;
	//�Ƚ�ip��ַ,ȥ��
	while (j >= 0)
	{
	j--;
	CString strTmp = pWnd->m_list.GetItemText(j, 2);
	char *szIp = strTmp.GetBuffer(0);
	if (strncmp(szIp, pDevNetInfo->szIP, strlen(pDevNetInfo->szIP)) == 0)
	{
	Sleep(12);
	return 0;
	}
	}

	char sTmp[20] = { 0 };
	sprintf_s(sTmp, "%d", nTotalIndex + 1);
	int nIndex = pWnd->m_list.InsertItem(nTotalIndex, sTmp);

	pWnd->m_list.SetItemText(nIndex, 1, pDevNetInfo->szDeviceType);
	
	pWnd->m_list.SetItemText(nIndex, 2, pDevNetInfo->szIP);

	memset(sTmp, 0, 20);
	sprintf_s(sTmp, "%d", pDevNetInfo->nPort);
	pWnd->m_list.SetItemText(nIndex, 3, sTmp);

	pWnd->m_list.SetItemText(nIndex, 4, pDevNetInfo->szSubmask);
	pWnd->m_list.SetItemText(nIndex, 5, pDevNetInfo->szGateway);
	pWnd->m_list.SetItemText(nIndex, 6, pDevNetInfo->szMac);
	
	//m_list.SetItemText(nIndex, 6, m_Device[i].sSn);
		
	pWnd->m_list.SetRedraw(TRUE);
	//
	Sleep(12);
	return 0;
}


void CDaHuaFindDevicesDlg::OnBnClickedButton1()
{
	

	HINSTANCE hNetlib = NULL;
	pCLIENT_Init pInit = NULL;
	pCLIENT_StartSearchDevices pSearch = NULL;
	pCLIENT_StopSearchDevices pStop = NULL;
	BOOL bInit, bSearch = FALSE;
	LLONG nSearch = 0;

	DH::DEVICE_IP_SEARCH_INFO IpSearchInfo = { 0 };
	if (NULL == hNetlib)
	{
		hNetlib = LoadLibrary("dhnetsdk.dll");
	}	

	if (NULL != hNetlib && !pInit && !pSearch)
	{
		pInit = (pCLIENT_Init)GetProcAddress(hNetlib, "CLIENT_Init");
		pSearch = (pCLIENT_StartSearchDevices)GetProcAddress(hNetlib, "CLIENT_StartSearchDevices");
		pStop = (pCLIENT_StopSearchDevices)GetProcAddress(hNetlib, "CLIENT_StopSearchDevices");
	}

	
	m_list.DeleteAllItems();

	if (pInit && pSearch)
	{
		bInit = pInit(NULL, NULL);
		if (bInit)
		{						
			nSearch = pSearch((DH::fSearchDevicesCB)SearchDevicesCB1, this, NULL);
		}
	}
	
}


void CDaHuaFindDevicesDlg::OnBnClickedButton2()
{
	
	HINSTANCE hNetlib = NULL;
	pCLIENT_Init pInit = NULL;
	pCLIENT_SearchDevices pSearch = NULL;
	BOOL bInit, bSearch = FALSE;

	DH::DEVICE_NET_INFO pDev[100] = { 0 };
	int nBufLen = 0;

	if (NULL == hNetlib)
	{
		hNetlib = LoadLibrary("dhnetsdk.dll");
	}

	if (NULL != hNetlib && !pSearch && !pInit)
	{
		pInit = (pCLIENT_Init)GetProcAddress(hNetlib, "CLIENT_Init");
		pSearch = (pCLIENT_SearchDevices)GetProcAddress(hNetlib, "CLIENT_SearchDevices");
	}
	
	m_list.DeleteAllItems();

	if (pInit && pSearch)
	{
		bInit = pInit(NULL, NULL);
		if (bInit)
		{
			pSearch((char *)pDev, sizeof(DH::DEVICE_NET_INFO)*100, &nBufLen, 3000, NULL);
		}
	}
	if (nBufLen > 0)
	{
		int i;
		m_list.SetRedraw(FALSE);
		for (i = 0; i < nBufLen / sizeof(DH::DEVICE_NET_INFO); i++)
		{
			int nTotalIndex = m_list.GetItemCount();
			char sTmp[20] = { 0 };
			sprintf_s(sTmp, "%d", nTotalIndex + 1);
			int nIndex = m_list.InsertItem(nTotalIndex, sTmp);

			m_list.SetItemText(nIndex, 1, pDev[i].szDeviceType);

			m_list.SetItemText(nIndex, 2, pDev[i].szIP);

			memset(sTmp, 0, 20);
			sprintf_s(sTmp, "%d", pDev[i].nPort);
			m_list.SetItemText(nIndex, 3, sTmp);

			m_list.SetItemText(nIndex, 4, pDev[i].szSubmask);
			m_list.SetItemText(nIndex, 5, pDev[i].szGateway);
			m_list.SetItemText(nIndex, 6, pDev[i].szMac);

			//m_list.SetItemText(nIndex, 6, m_Device[i].sSn);

			
		}
		m_list.SetRedraw(TRUE);
	}
}

int CALLBACK CDaHuaFindDevicesDlg::fcbJMBNotify(long lHandle, DWORD dwPortocol, int iErr, int iMsgID, LPCTSTR lpszDstID, void* pData, int iDataLen, void* pUserParam)
{
	if (NULL == lpszDstID || NULL == pData || NULL == pUserParam)
	{
		return -1;
	}

	CDaHuaFindDevicesDlg*		pDlg = (CDaHuaFindDevicesDlg*)(pUserParam);
	ZeroMemory(&pDlg->m_devConfig, sizeof(pDlg->m_devConfig));
	try
	{
		j_Device_T *pDev = (j_Device_T *)(pData);
		int copy_size = 0;

		ZeroMemory(&pDlg->m_devConfig.stDev, sizeof(j_Device_T));

		if (iDataLen != sizeof(j_Device_T))
		{
			copy_size = sizeof(J_SysCfg_T);
			if (pDev->SysSize < sizeof(J_SysCfg_T))
			{
				copy_size = pDev->SysSize;

			}
			pDlg->m_devConfig.stDev.SysSize = sizeof(J_SysCfg_T);
			memcpy(&pDlg->m_devConfig.stDev.SysCfg, &pDev->SysCfg, copy_size);

			copy_size = sizeof(JNetworkInfo);
			if (pDev->NetSize < sizeof(JNetworkInfo))
			{
				copy_size = pDev->NetSize;

			}
			pDlg->m_devConfig.stDev.NetSize = sizeof(JNetworkInfo);
			memcpy(&pDlg->m_devConfig.stDev.NetworkInfo, &pDev->NetworkInfo, copy_size);
		}
		else
		{
			memcpy(&pDlg->m_devConfig.stDev, pData, sizeof(j_Device_T));
		}

		pDlg->m_list.SetRedraw(FALSE);
		
		int nTotalIndex = pDlg->m_list.GetItemCount();
		char sTmp[20] = { 0 };
		sprintf_s(sTmp, "%d", nTotalIndex + 1);
		int nIndex = pDlg->m_list.InsertItem(nTotalIndex, sTmp);

		//Get device type
		CString strDevType;
		//�豸�����޷���ȡ���Ӧ���ͺţ�����device_type
		//strDevType = pDlg->GetDeviceType((int)&pDlg->m_devConfig.stDev.SysCfg.dev_type);	
		strDevType.Format("%s", pDlg->m_devConfig.stDev.SysCfg.device_type);
		pDlg->m_list.SetItemText(nIndex, 1, strDevType);

		CString strIP;
		strIP.Format("%s", pDlg->m_devConfig.stDev.NetworkInfo.network[0].ip);
		pDlg->m_list.SetItemText(nIndex, 2, strIP);

		CString strPort;
		//uint32_t uPort = ;
		strPort.Format("%u", pDlg->m_devConfig.stDev.NetworkInfo.cmd_port);
		pDlg->m_list.SetItemText(nIndex, 3, strPort);

		CString strNetMask;
		strNetMask.Format("%s", pDlg->m_devConfig.stDev.NetworkInfo.network[0].netmask);
		pDlg->m_list.SetItemText(nIndex, 4, strNetMask);

		CString strGateWay;
		strGateWay.Format("%s", pDlg->m_devConfig.stDev.NetworkInfo.network[0].gateway);
		pDlg->m_list.SetItemText(nIndex, 5, strGateWay);

		CString strMac;
		strMac.Format("%s", pDlg->m_devConfig.stDev.NetworkInfo.network[0].mac);
		pDlg->m_list.SetItemText(nIndex, 6, strMac);

		CString strID;
		strID.Format("%s", pDlg->m_devConfig.stDev.SysCfg.serial_no);
		pDlg->m_list.SetItemText(nIndex, 7, strID);


		
		pDlg->m_list.SetRedraw(TRUE);
		
	}
	catch (...)
	{
		return 0;
	}

	return 0;
}

void CDaHuaFindDevicesDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char szIp[11] = "224.0.0.99";
	int nPort = 40086;
	long lReturn = 0;
	int nInit = JNetInit(0);

	m_list.DeleteAllItems();

	long lResult = JNetMBOpen(szIp, nPort, fcbJMBNotify, this, JNET_PRO_T_JPF, lReturn);
	lResult = JNetMBSearch(lReturn, 5);
	//lResult = JNetMBClose(lReturn);

}

CString CDaHuaFindDevicesDlg::GetDeviceType(int i)
{
	CString strType = _T("");
	switch (i)
	{
	case J_DEV_IPC_6001:
		strType = _T("3516��ͨǹ��");
		break;
	case J_DEV_IPC_6002:
		strType = _T("3516���⻤��");
		break;
	case J_DEV_IPC_6003:
		strType = _T("3516�������");
		break;
	case J_DEV_IPC_6004:
		strType = _T("3516��������");
		break;
	case J_DEV_IPC_6005:
		strType = _T("3516����");
		break;
	case J_DEV_IPC_8001:
		strType = _T("3518A��ͨǹ��");
		break;
	case J_DEV_IPC_8002:
		strType = _T("3518A���⻤��");
		break;
	case J_DEV_IPC_8003:
		strType = _T("3518A�������");
		break;
	case J_DEV_IPC_8004:
		strType = _T("3518A��������");
		break;
	case J_DEV_IPC_8005:
		strType = _T("3518A����");
		break;
	case J_DEV_IPC_8101:
		strType = _T("3518C��ͨǹ��");
		break;
	case J_DEV_IPC_8102:
		strType = _T("3518C���⻤��");
		break;
	case J_DEV_IPC_8103:
		strType = _T("3518C�������");
		break;
	case J_DEV_IPC_8104:
		strType = _T("3518C��������");
		break;
	case J_DEV_IPC_8105:
		strType = _T("3518C����");
		break;
	case J_Dev_IPNC_:
		strType = _T("IPNC");
		break;
	case J_Dev_DVR_2_3520:
		strType = _T("DVR 3520 16-D1");
		break;
	case J_Dev_DVR_16_3531:
		strType = _T("DVR 3531 16-D1(960)");
		break;
	case J_Dev_DVR_4_3531:
		strType = _T("DVR 3531 04-HD-SDI");
		break;
	case J_Dev_NVR_1_3520:
		strType = _T("NVR 3520 08-720P");
		break;
	case J_Dev_NVR_16_3531:
		strType = _T("NVR 3531 16-720P");
		break;
	case J_Dev_NVR_9_3531:
		strType = _T("NVR 3531 09-1080P");
		break;
	case J_Dev_DECC_10_3531:
		strType = _T("DEC CARD 720P 10in, 2out");
		break;
	case J_Dev_DECB_13_3531:
		strType = _T("DEC BOX  720P 13in, 2out");
		break;

	default:
		strType = _T("NONE");
		break;
	}

	return strType;
}