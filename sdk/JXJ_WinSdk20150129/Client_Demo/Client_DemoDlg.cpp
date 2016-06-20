// Client_DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <stdlib.h>
#include "Client_Demo.h"
#include "Client_DemoDlg.h"
#include "SerchDevice.h"
#include "FullUpDlg.h"
#include "Pub_Data.h"
#include "CAttributeDlg.h"
#include "SerachNote.h"
#include "SrcSet.h"
#include "IniFile.h"
#include <math.h>
#include "direct.h"     //mkdir ͷ�ļ�


#define  DRAWCOLOR RGB(255,0,0)
#define  DRAWTROUGHCOLOR RGB(0,0,255)
#define  DRAWRECTCOLOR  RGB(0,128,64)
#define  DRAWPERCENT	RGB(255,0,0)


#define  MAX_BITMAP 5
#define  BTREE      0
#define  BSUCCESS   1
#define  BFAIL      2
#define  BSERVERSUCCESS      3
#define  BSERVERFAIL      4
#define  MAX_SEND_SIZE 1024


#define MIN(a, b) ((a > b) ? (b) : (a))

#define MAX(a, b) ((a > b) ? (a) : (b))


CTreeCtrl *gMainTree = NULL;
long	g_lMainWnd  = NULL;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClient_DemoDlg �Ի���




CClient_DemoDlg::CClient_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClient_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDragFile = FALSE;
	m_vSnapHandle = -1;
	g_lMainWnd = (LONG)this;
	
}

void CClient_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MAIN, m_MainTree);
	DDX_Control(pDX, IDC_STATIC_SHOWTIME, m_ShowTime);
	DDX_Control(pDX, IDC_COMBO_SCREEN_NUM, m_comScreenNum);
	DDX_Control(pDX, IDC_LIST_WARNING, m_ListWarning);
	DDX_Control(pDX, IDC_COMBO_PTZJD, m_combJD);
	DDX_Control(pDX, IDC_CHECK_STARTLIGHT, m_StartLight);
	DDX_Control(pDX, IDC_CHECK_STARTBRUSH, m_StartBrush);
	DDX_Control(pDX, IDC_BUTTON_PTZUP, m_bUp);
	DDX_Control(pDX, IDC_BUTTON_PTZLEFT, m_bLeft);
	DDX_Control(pDX, IDC_BUTTON_PTZRIGHT, m_bRight);
	DDX_Control(pDX, IDC_BUTTON_PTZDOWN, m_bDown);
	DDX_Control(pDX, IDC_BUTTOn_PTZAUTO, m_bAuto);
	DDX_Control(pDX, IDC_BUTTON_PTZSCANJIA, m_ScanJIa);
	DDX_Control(pDX, IDC_BUTTON_PTZSCANJIAN, m_ScanJian);
}

BEGIN_MESSAGE_MAP(CClient_DemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_STATIC_TEXT2, &CClient_DemoDlg::OnBnClickedStaticText2)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_TREE_MAIN, &CClient_DemoDlg::OnNMRClickTreeMain)
	ON_CBN_SELCHANGE(IDC_COMBO_SCREEN_NUM, &CClient_DemoDlg::OnCbnSelchangeComboScreenNum)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_MAIN, &CClient_DemoDlg::OnNMDblclkTreeMain)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &CClient_DemoDlg::OnBnClickedButtonPlayback)
	ON_BN_CLICKED(IDC_BUTTON_WATCH, &CClient_DemoDlg::OnBnClickedButtonWatch)
	ON_BN_CLICKED(IDC_CHECK_STARTLIGHT, &CClient_DemoDlg::OnBnClickedCheckStartlight)
	ON_BN_CLICKED(IDC_CHECK_STARTBRUSH, &CClient_DemoDlg::OnBnClickedCheckStartbrush)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_WARNING, &CClient_DemoDlg::OnLvnColumnclickListWarning)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MAIN, &CClient_DemoDlg::OnTvnSelchangedTreeMain)
	ON_COMMAND(ID_MENU_DELETE, &CClient_DemoDlg::OnMenuDelete)
	ON_BN_CLICKED(IDC_BUTTON_RECODE, &CClient_DemoDlg::OnBnClickedButtonRecode)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE_MAIN, &CClient_DemoDlg::OnTvnBegindragTreeMain)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CLOSEALLVIDEO, &CClient_DemoDlg::OnBnClickedButtonCloseallvideo)
	ON_COMMAND(ID_MENU_ATTRIBUTE, &CClient_DemoDlg::OnMenuAttribute)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_WARNING, &CClient_DemoDlg::OnNMRClickListWarning)
	ON_COMMAND(ID_MENU_DelList, &CClient_DemoDlg::OnMenuDellist)
	ON_BN_CLICKED(IDC_BUTTON_CLEARWARNING, &CClient_DemoDlg::OnBnClickedButtonClearwarning)
	ON_BN_CLICKED(IDC_BUTTON_ALLFULLUP, &CClient_DemoDlg::OnBnClickedButtonAllfullup)
	ON_NOTIFY(NM_CLICK, IDC_TREE_MAIN, &CClient_DemoDlg::OnNMClickTreeMain)
	ON_BN_CLICKED(IDC_BUTTON_ELSE, &CClient_DemoDlg::OnBnClickedButtonElse)
	ON_COMMAND(IDM_LOCALATTRIBUTE, &CClient_DemoDlg::OnLocalattribute)
	ON_WM_ERASEBKGND()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MENU_DEVICE_SNAP, &CClient_DemoDlg::OnMenuDeviceSnap)
END_MESSAGE_MAP()


// CClient_DemoDlg ��Ϣ�������

BOOL CClient_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CenterWindow();
	CRect cRect;
	GetWindowRect(cRect);
	g_PubData.g_iMainWindowX = cRect.left;
	g_PubData.g_iMainWindowY = cRect.top;
	g_PubData.g_iMainWindowW = cRect.Width();
	g_PubData.g_iMainWindowH = cRect.Height();

	//this->MoveWindow(cRect.left,cRect.top, cRect.Width(), cRect.Height(), TRUE);
	//this->ShowWindow(SW_SHOW);

	// 	LONG style = GetWindowLong(this->GetSafeHwnd(),GWL_STYLE); 
	// 	style = style | WS_CLIPSIBLINGS ; 
	// 	SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,style);

	m_strSelItemText = _T("");
	m_bWarningMax = FALSE;
	m_bDragDown = FALSE;
	m_bDrag = FALSE;
	gMainTree = &m_MainTree;
	SetTimer(1, 1000 , NULL);   //ʱ�䴥����
	

	for(int i = 0;i < 101; i++)
	{
		CString strText = _T("");
		strText.Format(_T("%d"), i);
		m_combJD.AddString(strText);
	}
	m_combJD.SetCurSel(50);

	m_MainTree.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);

	SetTreeIcon();
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_hRoot = m_MainTree.InsertItem(_T("�豸�б�(�һ�������豸)"), 0, 0);
	}
	else
	{
		m_hRoot = m_MainTree.InsertItem(_T("Device Tree"), 0, 0);
	}

	initComboxScreenNum();   //��ʼ���������������б�

	m_ListWarning.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE|WS_CLIPSIBLINGS);
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_ListWarning.InsertColumn(0 , _T("IP"), 2, 100, -1);
		m_ListWarning.InsertColumn(1 , _T("����ʱ��"), 2, 150,-1);
		m_ListWarning.InsertColumn(2 , _T("ͨ����"), 2, 100,-1);
		m_ListWarning.InsertColumn(3 , _T("����"), 2, 100,-1);
		m_ListWarning.InsertColumn(4 , _T("״̬"), 2, 100,-1);
		m_ListWarning.InsertColumn(5 , _T("��ע"), 2, 220,-1);
	}
	else
	{
		m_ListWarning.InsertColumn(0 , _T("IP"), 2, 100, -1);
		m_ListWarning.InsertColumn(1 , _T("AlarmTime"), 2, 150,-1);
		m_ListWarning.InsertColumn(2 , _T("Channel"), 2, 100,-1);
		m_ListWarning.InsertColumn(3 , _T("Type"), 2, 100,-1);
		m_ListWarning.InsertColumn(4 , _T("Status"), 2, 100,-1);
		m_ListWarning.InsertColumn(5 , _T("Remark"), 2, 220,-1);
	}
	
// 	LONG style = GetWindowLong(this->GetSafeHwnd(),GWL_STYLE); 
// 	style = style | WS_CLIPSIBLINGS ; 
// 	SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,style);


	m_ListWarning.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY + g_PubData.g_iStaticScreenHeight, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight,TRUE);
	m_ListWarning.ShowWindow(SW_SHOW);

	m_videoPlayBack.Create(IDD_DIALOG_VIDEO_PLAYBACK, this);

	double iii2 = pow((DOUBLE)8,1.0/(DOUBLE)2);
	double iii3 = pow((DOUBLE)16,1.0/(DOUBLE)2);
	double iii1 = pow((DOUBLE)4,1.0/(DOUBLE)2);
	double iii4 = pow((DOUBLE)2,1.0/(DOUBLE)2);

	DWORD dd = 40 / iii2;

	// ��ʼ�����������
	int iRet = -1;

// 	iRet = JNetInit(NULL);
// 	if( 0 != iRet )
// 	{
// 		AfxMessageBox(_T("JNetInit error!"));
// 		return FALSE;
// 	}
	InitINIfile();
	GetDlgItem(IDC_STATIC_SHOWMODE)->SetWindowText(_T("Client"));


		
	iRet = JNetInit(NULL);
	if( 0 != iRet )
	{
		AfxMessageBox(_T("jcu_net_init error!"));
		return FALSE;
	}
	iRet = AVP_Init();
	if ( iRet!=AVPErrSuccess )
	{
		return FALSE;
	}


	AVP_InitRecMng(128, 8);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CClient_DemoDlg::InitINIfile()
{
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
	m_iDemoMode = _ttoi(strArrKeyValue.GetAt(0));


}
/*
int CClient_DemoDlg::LoginExNotify(_jcu_event_cb_s *handle,jcu_cb_parm_t *parm)
{
	CClient_DemoDlg *pDlg = (CClient_DemoDlg*)AfxGetMainWnd();

 	if(parm->id == JCU_EVENT_REGISTER)
	{	

		jcu_client_t *cliData = (jcu_client_t *)parm->data;
		CString strIP;
		strIP.Format(_T("%s"), cliData->ip);

		CString strTest = strIP;
		strTest +=  _T("-�ѵ���");
		int iFlag = -1;
		for(int i = 0; i < g_PubData.g_strArrayPlaySuccessIp.GetCount(); i++)
		{
			if(strTest == g_PubData.g_strArrayPlaySuccessIp.GetAt(i))
			{
				iFlag = i;
				break;
			}
		}
		if(iFlag < 0)
		{
			g_PubData.g_vLoginHandle[g_PubData.g_iIsPlayNum] = cliData->handle;

			g_PubData.g_hTreeItem[g_PubData.g_iIsPlayNum] = gMainTree->InsertItem(strIP, BSUCCESS, BSUCCESS);
			g_PubData.g_strArrayPlaySuccessIp.Add(strIP);
			handle->user_arg = (int *)g_PubData.g_iIsPlayNum;
			g_PubData.g_iServerFlag[g_PubData.g_iIsPlayNum] = 1;
			g_PubData.g_iIsPlayNum ++;
			pDlg->GetDevCap();// ��½�ɹ���ȡ�豸������
		}
		else  //����������
		{
			g_PubData.g_bUpgDeviceClose = TRUE;
			g_PubData.g_vLoginHandle[iFlag] = cliData->handle;
			g_PubData.g_strArrayPlaySuccessIp.SetAt(iFlag, strIP);
			gMainTree->SetItemImage(g_PubData.g_hTreeItem[iFlag], BSUCCESS, BSUCCESS);
			g_PubData.g_iServerFlag[iFlag] = 1;
			g_PubData.g_DeviceClose[iFlag] = FALSE;
		}
	}
	else if(parm->id == JCU_EVENT_UNREGISTER)
	{
		int iIndex = (int)handle->user_arg;

		CString strShowSuccessIp = _T("");
		strShowSuccessIp += g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
		strShowSuccessIp += _T("-�ѵ���");
		g_PubData.g_strArrayPlaySuccessIp.SetAt(iIndex, strShowSuccessIp);
		g_PubData.g_iServerFlag[iIndex] = -1;
		
		gMainTree->SetItemImage(g_PubData.g_hTreeItem[iIndex], BFAIL, BFAIL);
		g_PubData.g_DeviceClose[iIndex] = TRUE;

		for(int i = 0; i< GET_MAX_DEV_NUM; i++)  //�ѵ��ߵ��豸���ڲ��ŵĴ�����Ч
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == iIndex)
			{
				AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[i].m_iPlayWndIndex],
					g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
				g_cFullUpDlg[i].m_iPlayWndIndex = -1;
				g_cFullUpDlg[i].m_iPlayWndNum = -1;
				g_cFullUpDlg[i].m_iPlayFlag = -1;

				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);
				g_cFullUpDlg[i].Invalidate(TRUE);
			}
		}
		if(g_PubData.g_iChancel[iIndex] >= 0)
		{
			AVP_Stop(g_PubData.g_iChancel[iIndex]);
			AVP_ReleasePort(g_PubData.g_iChancel[iIndex]);	
			g_PubData.g_iChancel[iIndex] =-1;
		}

		if(g_PubData.g_vStreamHandle[iIndex] != NULL)
		{
			jcu_net_stream_close(g_PubData.g_vStreamHandle[iIndex]);
			g_PubData.g_vStreamHandle[iIndex] = NULL;
		}

	}
	else if(parm->id == PARAM_SUBMINT_ALARM)
	{
		JSubmitAlarm *alarm = (JSubmitAlarm*)parm->data;
		
		///////////////////////////�Ӿ���Ϣ////////////////////////////
		CString strTime = _T("");
		strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), alarm->alarm_time.year + 1900
			, alarm->alarm_time.month
			, alarm->alarm_time.date
			, alarm->alarm_time.hour
			, alarm->alarm_time.minute
			, alarm->alarm_time.second);

		CString strChannel = _T("");
		strChannel.Format(_T("%d"), alarm->channel);

		CStringArray strArrayAlarm;
		pDlg->GetAlarmData(alarm->alarm_type, alarm->action_type, strArrayAlarm);
		
		CString strRemark = _T("");
		strRemark.Format(_T("%s"), alarm->data);

		int iIndex = (int)handle->user_arg;
		CString alarmIp = _T("");
		alarmIp = g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
	
		ListWarning->InsertItem(g_PubData.g_iWarningCount,alarmIp);
		ListWarning->SetItemText(g_PubData.g_iWarningCount, 1, strTime);
		ListWarning->SetItemText(g_PubData.g_iWarningCount, 2, strChannel);
		ListWarning->SetItemText(g_PubData.g_iWarningCount, 3, strArrayAlarm.GetAt(0));
		ListWarning->SetItemText(g_PubData.g_iWarningCount, 4, strArrayAlarm.GetAt(1));
		ListWarning->SetItemText(g_PubData.g_iWarningCount, 5, strRemark);
		g_PubData.g_iWarningCount ++ ;
	}
	else if(parm->id == PARAM_FORMAT_DISK)
	{
		if(-1 != parm->args)
		{
			JFormatDisk *prs = (JFormatDisk *)parm->data;
			g_PubData.g_iFormatProgress = prs->progress;

		}
	}
	else if(parm->id == PARAM_FIRMWARE_UPGRADE)
	{
		if (-1 == parm->args)
		{
			//TRACE("upgrade failed\n");        
		}
		else 
		{
			JUpgradeProgress *prs = (JUpgradeProgress *)parm->data;
			upDev.percent = prs->percent;
			//TRACE("upgrade callback percent: %d\n", parm->args);
		}
	}
	else if(parm->id == PARAM_CONTROL_DEV)
	{	
		JSubmitDeviceStatus *deviceStatus = (JSubmitDeviceStatus*)parm->data;
		g_PubData.g_iControlDevRet = deviceStatus->ddp_status;	
	}

	return 0;
}*/


void CClient_DemoDlg::GetAlarmData(int iAlarm, int iAction, CStringArray &strArray, int iIndex)
{
	CString strType = _T("");
	CString strAction = _T("");

	if(iAlarm == 4)
	{
		strType = _T("���ܷ���AVD�澯");

		if(iAction & AVD_BRIGHT_ABMNL)
		{
			strAction += _T(",�����쳣");
		}
		if(iAction & AVD_BRIGHT_NORMAL)
		{
			strAction += _T(",��������");
		}
		if(iAction & AVD_CLARITY_ABMNL)
		{
			strAction += _T(",�������쳣");
		}
		if(iAction & AVD_CLARITY_NORMAL)
		{
			strAction += _T(",����������");
		}
		if(iAction & AVD_NOISE_ABMNL)
		{
			strAction += _T(",�����쳣");
		}
		if(iAction & AVD_NOISE_NORMAL)
		{
			strAction += _T(",��������");
		}
		if(iAction & AVD_COLOR_ABMNL)
		{
			strAction += _T(",ƫɫ�쳣");
		}
		if(iAction & AVD_COLOR_NORMAL)
		{
			strAction += _T(",ƫɫ����");
		}
		if(iAction & AVD_SCENE_ABMNL)
		{
			strAction += _T(",�����任����");
		}
		if(iAction & AVD_SCENE_NORMAL)
		{
			strAction += _T(",��������");
		}
		strAction = strAction.Right(strAction.GetLength() - 1);

	}
	else if(iAlarm == J_SDK_NETWORK_FAULT_ALARM)
	{
		strType = _T("������ϸ澯");
		if(iAction & NETWORK_DISCONNECT)
		{
			strAction += (_T(",�������ӶϿ�"));
		}
		if(iAction & NETWORK_RECONNECT)
		{
			strAction += (_T(",�����ָ�����"));
		}
		strAction = strAction.Right(strAction.GetLength() - 1);
	}
	else if(iAlarm == J_SDK_PEA_OSC_ALARM)
	{
// 		strType = _T("���ܷ�������");
// 		if(iAction & J_TGT_NONE_EVENT)
// 		{
// 			strAction += (_T(",δ�����¼�"));
// 		}
// 		if(iAction & J_TGT_UNKNOWN_EVENT)
// 		{
// 			strAction += (_T(",δ֪�¼�"));
// 		}
// 		if(iAction & J_TGT_TRIPWIRE_EVENT)
// 		{
// 			strAction += (_T(",������"));
// 			g_PubData.g_iCountPerson[iIndex] ++;
// 		}
// 		if(iAction & J_TGT_MUTITRIPWIRE_EVENT)
// 		{
// 			strAction += (_T(",˫����"));
// 			g_PubData.g_iCountPerson[iIndex] ++;
// 		}
// 		if(iAction & J_TGT_PERI_METER_EVENT)
// 		{
// 			strAction += (_T(",����������"));
// 		}
// 		if(iAction & J_TGT_LOITER_EVENT)
// 		{
// 			strAction += (_T(",�ǻ�"));
// 		}
// 		if(iAction & J_TGT_LEFT_EVENT)
// 		{
// 			strAction += (_T(",��Ʒ����"));
// 		}
// 		if(iAction & J_TGT_TAKE_EVENT)
// 		{
// 			strAction += (_T(",��Ʒ��ʧ"));
// 		}
// 		strAction = strAction.Right(strAction.GetLength() - 1);
	}
	else
	{
		if(iAlarm == J_SDK_MOVE_ALARM)
		{
			strType = _T("�ƶ�����");
		}
		else if(iAlarm == J_SDK_LOST_ALARM)
		{
			strType = _T("��ʧ����");
		}
		else if(iAlarm == J_SDK_HIDE_ALARM)
		{
			strType = _T("�ڵ�����");
		}
		else if(iAlarm == J_SDK_IO_ALARM)
		{
			strType = _T("IO����");
		}
		else if(iAlarm == J_SDK_PIR_ALARM)
		{
			strType = _T("��������ⱨ��");
		}
		// ����״̬
		if (iAction ==  0)
		{
			strAction = _T("������ʼ");
		}
		else if(iAction == 1)
		{
			strAction = _T("��������");
		}
	}

	strArray.Add(strType);
	strArray.Add(strAction);
}

void CClient_DemoDlg::GetAlarmDataEnglish(int iAlarm, int iAction, CStringArray &strArray)
{
	CString strType = _T("");
	CString strAction = _T("");

	if(iAlarm == 4)
	{
		strType = _T("AVD ALARM");

		if(iAction & AVD_BRIGHT_ABMNL)
		{
			strAction += _T(",AVD_BRIGHT_ABMNL");
		}
		if(iAction & AVD_BRIGHT_NORMAL)
		{
			strAction += _T(",AVD_BRIGHT_NORMAL");
		}
		if(iAction & AVD_CLARITY_ABMNL)
		{
			strAction += _T(",AVD_CLARITY_ABMNL");
		}
		if(iAction & AVD_CLARITY_NORMAL)
		{
			strAction += _T(",AVD_CLARITY_NORMAL");
		}
		if(iAction & AVD_NOISE_ABMNL)
		{
			strAction += _T(",AVD_NOISE_ABMNL");
		}
		if(iAction & AVD_NOISE_NORMAL)
		{
			strAction += _T(",AVD_NOISE_NORMAL");
		}
		if(iAction & AVD_COLOR_ABMNL)
		{
			strAction += _T(",AVD_COLOR_ABMNL");
		}
		if(iAction & AVD_COLOR_NORMAL)
		{
			strAction += _T(",AVD_COLOR_NORMAL");
		}
		if(iAction & AVD_SCENE_ABMNL)
		{
			strAction += _T(",AVD_SCENE_ABMNL");
		}
		if(iAction & AVD_SCENE_NORMAL)
		{
			strAction += _T(",AVD_SCENE_NORMAL");
		}
		strAction = strAction.Right(strAction.GetLength() - 1);

	}
	else if(iAlarm == J_SDK_NETWORK_FAULT_ALARM)
	{
		strType = _T("NETWORK_FAULT_ALARM");
		if(iAction & NETWORK_DISCONNECT)
		{
			strAction += (_T(",NETWORK_DISCONNECT"));
		}
		if(iAction & NETWORK_RECONNECT)
		{
			strAction += (_T(",NETWORK_RECONNECT"));
		}
		strAction = strAction.Right(strAction.GetLength() - 1);
	}
	else if(iAlarm == J_SDK_PEA_OSC_ALARM)
	{
// 		strType = _T("PEA_OSC_ALARM");
// 		if(iAction & J_TGT_NONE_EVENT)
// 		{
// 			strAction += (_T(",NONE_EVENT"));
// 		}
// 		if(iAction & J_TGT_UNKNOWN_EVENT)
// 		{
// 			strAction += (_T(",UNKNOWN_EVENT"));
// 		}
// 		if(iAction & J_TGT_TRIPWIRE_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_TRIPWIRE_EVENT"));
// 		}
// 		if(iAction & J_TGT_MUTITRIPWIRE_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_MUTITRIPWIRE_EVENT"));
// 		}
// 		if(iAction & J_TGT_PERI_METER_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_PERI_METER_EVENT"));
// 		}
// 		if(iAction & J_TGT_LOITER_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_LOITER_EVENT"));
// 		}
// 		if(iAction & J_TGT_LEFT_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_LEFT_EVENT"));
// 		}
// 		if(iAction & J_TGT_TAKE_EVENT)
// 		{
// 			strAction += (_T(",J_TGT_TAKE_EVENT"));
// 		}
// 		strAction = strAction.Right(strAction.GetLength() - 1);
	}
	else
	{
		if(iAlarm == 0)
		{
			strType = _T("MOVE ALARM");
		}
		else if(iAlarm == 1)
		{
			strType = _T("LOST ALARM");
		}
		else if(iAlarm == 2)
		{
			strType = _T("HIDE ALARM");
		}
		else if(iAlarm == 3)
		{
			strType = _T("IO ALARM");
		}
		// ����״̬
		if (iAction ==  0)
		{
			strAction = _T("START ALARM");
		}
		else if(iAction == 1)
		{
			strAction = _T("Alarm over");
		}
	}

	strArray.Add(strType);
	strArray.Add(strAction);
}

//��������ͼ���б�
void CClient_DemoDlg::SetTreeIcon()
{
	CBitmap bmp[MAX_BITMAP];
	m_imageList.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);

	bmp[BTREE].LoadBitmap(IDB_BITMAP_TREE);
	m_imageList.Add(&bmp[BTREE],RGB(1,1,1));

 	bmp[BSUCCESS].LoadBitmap(IDB_BITMAP_CAMERA);
 	m_imageList.Add(&bmp[BSUCCESS],RGB(1,1,1));
 
 	bmp[BFAIL].LoadBitmap(IDB_BITMAP_LOGINFAIL);
 	m_imageList.Add(&bmp[BFAIL],RGB(1,1,1));

	bmp[BSERVERSUCCESS].LoadBitmap(IDB_BITMAP_SERVERC);
	m_imageList.Add(&bmp[BSERVERSUCCESS],RGB(1,1,1));

	bmp[BSERVERFAIL].LoadBitmap(IDB_BITMAP_SERVERFAIL);
	m_imageList.Add(&bmp[BSERVERFAIL],RGB(1,1,1));

	m_MainTree.SetImageList( &m_imageList,TVSIL_NORMAL);
}

void CClient_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClient_DemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
	m_ListWarning.Invalidate();
	UpdateWindow();
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClient_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClient_DemoDlg::OnBnClickedStaticText2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void CClient_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strTime(_T(""));
	m_cTime = COleDateTime::GetCurrentTime();
	strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), m_cTime.GetYear(), m_cTime.GetMonth(), m_cTime.GetDay(),
		m_cTime.GetHour(),m_cTime.GetMinute(),m_cTime.GetSecond());
	GetDlgItem(IDC_STATIC_SHOWTIME)->SetWindowText(strTime);
	CDialog::OnTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}


//�����б�����¼�
void CClient_DemoDlg::OnCbnSelchangeComboScreenNum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_comScreenNum.GetCurSel();
	m_iCurWndNum = (int)pow(double(iIndex+1), 2);//current window number
	m_iCurWndIndex = 0;//initialize current window index while switch window
	ArrangeOutputs(m_iCurWndNum);
	GetDlgItem(IDC_STATIC_SCREEN)->Invalidate(TRUE);
}

void CClient_DemoDlg::initComboxScreenNum()
{
	m_comScreenNum.AddString(_T("1"));
	m_comScreenNum.AddString(_T("4"));
	m_comScreenNum.AddString(_T("9"));
	m_comScreenNum.AddString(_T("16"));
	m_comScreenNum.AddString(_T("25"));
	m_comScreenNum.AddString(_T("36"));
	m_comScreenNum.AddString(_T("49"));
	m_comScreenNum.AddString(_T("64"));
	m_comScreenNum.AddString(_T("81"));

	m_comScreenNum.SetCurSel(1);

	for(int i = 0; i< GET_MAX_DEV_NUM; i++)
	{
		g_cFullUpDlg[i].Create(IDD_DIALOG_FULLUP_SCREEN,this);
	}

	ArrangeOutputs(4);
}

//��ʾ iNumber ������
void CClient_DemoDlg::Show_Window(int iNumber)
{
	for(int i = 0; i< iNumber; i++)
	{
		g_cFullUpDlg[i].ShowWindow(SW_SHOW);
	}
}

//���س��� index �Ĵ��� 
void CClient_DemoDlg::Hide_Window(int index)
{
	for (int i = 0;i < GET_MAX_DEV_NUM;i++)
	{
		if( index == i )
		{
			continue;
		}
		g_cFullUpDlg[i].ShowWindow(SW_HIDE);	
	}
}
// �ھ�̬��������dialog  ���ָ̬��
void CClient_DemoDlg::ArrangeOutputs(int iNumber)
{
	g_PubData.g_iCutScreenNum = iNumber;
	int i = 0;
	CRect crect;

	int iSqrtNum = 0;//sqrt value of window number
	int iWidth = 0;//window width
	int iHeight = 0;//window height

	iSqrtNum = (int)sqrt((double)iNumber);

	for (i = 0;i < GET_MAX_DEV_NUM;i++)
	{
		g_cFullUpDlg[i].ShowWindow(SW_HIDE);	
	}
	CRect rect; //�����õ���̬��Ŀ��

	GetDlgItem(IDC_STATIC_SCREEN)->GetClientRect(&rect);

	CRect rectStatic;	   
	CWnd *pWnd=GetDlgItem(IDC_STATIC_SCREEN);//����ı���ָ��   
	pWnd->GetClientRect(rectStatic);		//����ı������,���Ͻ�����(0,0)   
	pWnd->ClientToScreen(rectStatic);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������  
	g_PubData.g_iStaticToScreenX = rectStatic.left;
	g_PubData.g_iStaticToScreenY = rectStatic.top;

	GetClientRect(g_PubData.g_RectDlg);//��öԻ������,���Ͻ�����(0,0)   
	ClientToScreen(g_PubData.g_RectDlg);//ת������Ļ����,���Ͻ�����Ϊ�Ի�������Ļ������   

	int x = rectStatic.left-g_PubData.g_RectDlg.left;//���ǵĲΪ�ı����ڶԻ����е�X����   
	int y = rectStatic.top-g_PubData.g_RectDlg.top;//���ǵĲΪ�ı����ڶԻ����е�Y���� 

	m_iCurScreenWidth = rect.Width();//GetSystemMetrics(0);
	m_iCurScreenHeight = rect.Height();//GetSystemMetrics(1);

	//�þ�̬��Ļ�������������꼰��� ֻ��ֵһ�� ��Ϊ���˳��໭��ȫ��
	if(g_PubData.g_iMoveX <= 0 || g_PubData.g_iMoveY <=0 ||g_PubData.g_iStaticScreenWidth <=0 || g_PubData.g_iStaticScreenHeight <= 0)
	{
		g_PubData.g_iMoveX = x;
		g_PubData.g_iMoveY = y;
		g_PubData.g_iStaticScreenWidth = m_iCurScreenWidth;
		g_PubData.g_iStaticScreenHeight = m_iCurScreenHeight;
	}
	
	iWidth = (m_iCurScreenWidth - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
	iHeight = (m_iCurScreenHeight - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
	g_PubData.g_iCutScreenWidth = iWidth;
	g_PubData.g_iCutScreenHeight = iHeight;
	for (i = 0; i < iNumber; i++)
	{
		g_cFullUpDlg[i].MoveWindow((i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL)+x,(i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL)+y,iWidth,iHeight,TRUE);

		CRect cRect;
		g_cFullUpDlg[i].GetClientRect(&cRect);
		g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_SHOWVIDEO)->MoveWindow(0,0,cRect.Width(),cRect.Height()-22,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_SHOW);

		g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_GROUP)->MoveWindow(0,cRect.Height()-30,cRect.Width(),30,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_GROUP)->ShowWindow(SW_SHOW);

		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->MoveWindow(0,cRect.Height()-22,30,20,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->ShowWindow(SW_SHOW);

		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->MoveWindow(31,cRect.Height()-22,30,20,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->ShowWindow(SW_SHOW);
		
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->MoveWindow(62,cRect.Height()-22,30,20,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->ShowWindow(SW_SHOW);

		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->MoveWindow(93,cRect.Height()-22,30,20,TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->ShowWindow(SW_SHOW);

		if(g_PubData.g_iLanguageFlag == 0)
		{
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,30,20,TRUE);
		}
		else
		{
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,40,20,TRUE);
		}
		
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->ShowWindow(SW_SHOW);

		g_cFullUpDlg[i].m_iWndX = (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL)+x;
		g_cFullUpDlg[i].m_iWndY = (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL)+y;
		g_cFullUpDlg[i].m_iWndWidth = iWidth;
		g_cFullUpDlg[i].m_iWndHeight = iHeight;
		g_cFullUpDlg[i].m_iHideIndex = i;
		g_cFullUpDlg[i].ShowWindow(SW_SHOW);
	}
}


HBRUSH CClient_DemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	/*
	CBrush   brush(RGB(22,14,177)); 
	if(pWnd-> GetDlgCtrlID()==IDC_STATIC_SCREEN)
	{
		CRect   rect;  
		pDC-> SelectObject(&brush);  
		CWnd   *p_staticwnd=GetDlgItem(IDC_STATIC_SCREEN); 
		p_staticwnd-> GetWindowRect(&rect);  
		pDC-> Rectangle(&rect); 
		pDC->SetBkMode(TRANSPARENT); 
	}
	return   (HBRUSH)brush;
	*/
	return hbr;

}

void CClient_DemoDlg::OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
///////////////////////////////////////////////////////////////////////

	CPoint pt;
	HTREEITEM selDevhItem = NULL;
	::GetCursorPos(&pt);
	m_MainTree.ScreenToClient(&pt);
	selDevhItem = m_MainTree.HitTest(pt);

	CMenu cMenu;
	CPoint point;  
	GetCursorPos(&point);  
	if(selDevhItem != NULL)   
	{  
		m_MainTree.SelectItem(selDevhItem);

		m_strSelItemText = m_MainTree.GetItemText(selDevhItem);
		CString strText = _T("");
		if(g_PubData.g_iLanguageFlag == 0)
		{
			strText = _T("�豸�б�(�һ�������豸)");
		}
		else
		{
			strText = _T("Device Tree");
		}
		if(m_strSelItemText == strText)
		{
			if(m_iDemoMode != 0)
			{
				AfxMessageBox( _T("Server.........."));
				return;
			}
			CSerchDevice cSerchDlg;
			cSerchDlg.DoModal();
		
			if( cSerchDlg.m_bIsAdd )
			{
				for(int i = 0; i < g_PubData.g_strArrayLoginIp.GetCount(); i++)
				{
					g_PubData.g_strLoginIp = g_PubData.g_strArrayLoginIp.GetAt(i);
					g_PubData.g_hAddItem[i] = m_MainTree.InsertItem(g_PubData.g_strLoginIp, BFAIL, BFAIL);
					g_PubData.g_strArraySavedIp.Add(g_PubData.g_strLoginIp);
					g_PubData.g_iCountDevice ++;
				}
				SaveLoginDevice();
				cSerchDlg.m_bIsAdd = false;
			}
		}
		else
		{
			cMenu.LoadMenu(IDR_MENU2);
			CMenu* pPopup=cMenu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
			m_MainTree.Select(selDevhItem, TVGN_CARET);
			m_hDeleteItem = selDevhItem;
			
		}
	}

	
	*pResult = 0;
}

void CClient_DemoDlg::OnNMDblclkTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{

}
void CClient_DemoDlg::SaveLoginDevice()
{
	
	HANDLE hThread = CreateThread(NULL, 0 , (LPTHREAD_START_ROUTINE)LoginDevice, this, 0, NULL);
	CloseHandle(hThread);
}

void CClient_DemoDlg::LoginDevice(LPVOID DBClickIp)
{
	CClient_DemoDlg *pDlg = (CClient_DemoDlg*)DBClickIp;
	int iCountLogin = 0;
loopLogin:	
	g_PubData.g_strLoginIp = g_PubData.g_strArrayLoginIp.GetAt(iCountLogin);

	int nTimeOut = 10;
	
	//��½�豸
	g_PubData.g_hTreeItem[g_PubData.g_iIsPlayNum] = g_PubData.g_hAddItem[iCountLogin];
	JNetLogin(g_PubData.g_strLoginIp.GetBuffer(0), g_PubData.g_iDevicePort, g_PubData.g_strUser.GetBuffer(0), g_PubData.g_strPassword.GetBuffer(0), nTimeOut, ConnEventCB, pDlg, JNET_PRO_T_JPF, g_PubData.g_vLoginHandle[g_PubData.g_iIsPlayNum], NULL);
	
	g_PubData.g_strArrayPlaySuccessIp.Add(g_PubData.g_strLoginIp);
	
	
	g_PubData.g_iIsPlayNum ++;	

	
	if(iCountLogin < g_PubData.g_strArrayLoginIp.GetCount()-1)//��̨�豸��½
	{
		iCountLogin ++;
		goto loopLogin;
	}
	return;
}

int CClient_DemoDlg::GetDevIndex(long lHandle)
{
	for(int i = 0; i < g_PubData.g_iIsPlayNum; i++)
	{
		if(lHandle == g_PubData.g_vLoginHandle[i])
		{
			return i;
		}
	}

	return -1;
}

int CClient_DemoDlg::ConnEventCB(long lHandle, eJNetEvent eType,int iDataType,void* pEventData,int iDataLen,void* pUserParam)
{
	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)pUserParam;
	int nIndex = pDlg->GetDevIndex(lHandle);
	if(nIndex < 0)
	{
		return 0;
	}
	//TRACE("etype = %d,  idataType = %d\r\n",eType,  iDataType);
	switch(eType)
	{
		case JNET_EET_LOGIN_OK:		 //��¼�ɹ�
			{
				gMainTree->SetItemImage(g_PubData.g_hTreeItem[nIndex], BSUCCESS, BSUCCESS);
				pDlg->GetDevCap(nIndex);
			}
			break;
		case JNET_EET_LOGIN_ERROR:   //��¼ʧ��
			{
				gMainTree->SetItemImage(g_PubData.g_hTreeItem[nIndex], BFAIL, BFAIL);
			}
			break;
		case JNET_EET_EVENT_NOTIFY:  //�����¼�
		{
			if(NULL == pEventData)
				return 0;

			//  �ϱ��澯
			if(PARAM_SUBMINT_ALARM == iDataType)
			{
				pDlg->SubmitAlarm(nIndex, pEventData);	
			}
			if(PARAM_FIRMWARE_UPGRADE == iDataType)
			{
				JFirmwareUpgrade *prs = (JFirmwareUpgrade *)pEventData;
				upDev.percent = prs->percent;
			}
			if(PARAM_FORMAT_DISK == iDataType)
			{
				JFormatDisk *prs = (JFormatDisk *)pEventData;
				g_PubData.g_iFormatProgress = prs->progress;
			}
		}
			break;
		case JNET_EET_UPG_OK:   //�����ɹ�
			{
			}
			break;
		case JNET_EET_UPG_ERR:  //����ʧ��
			{
				upDev.percent = -100;
			}
			break;
	}

	return 0;
}

// int CClient_DemoDlg::EventNotify(_jcu_event_cb_s *handle,jcu_cb_parm_t *parm)
// {
//TRACE("================================================ id %d, args %d, size %d\n", parm->id, parm->args, parm->size);
// 	CClient_DemoDlg *pDlg = (CClient_DemoDlg*)AfxGetMainWnd();
// 
// 	switch(parm->id)
// 	{
// 	case JCU_EVNET_OPEN:
// 		{
// 
// 			int iIndex = (int)handle->user_arg;
// 			if(g_PubData.g_DeviceClose[iIndex])
// 			{	
// 				g_PubData.g_bUpgDeviceClose = TRUE;
// 				g_PubData.g_DeviceClose[iIndex] = FALSE;
// 				gMainTree->SetItemImage(g_PubData.g_hTreeItem[iIndex], 1, 1);
// 				CString strText = g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
// 				CString strShowSuccessIp = strText.Left(strText.GetLength() - 7);
// 				g_PubData.g_strArrayPlaySuccessIp.SetAt(iIndex, strShowSuccessIp);
// 
// 			}
// 		}
// 		break;
// 	case JCU_EVENT_CLOSE:  //�豸�Ͽ�����ʱ�ر����ڲ��ŵ�¼�񣬲�����ʧ��ͼ��
// 		{	
// 
// 			int iIndex = (int)handle->user_arg;
// 			CString strText = _T("");
// 			CString strShowSuccessIp = _T("");
// 			strText += g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
// 			strShowSuccessIp += g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
// 			strText += _T("--�豸�Ͽ����ӣ����ڵȴ�����......");
// 			strShowSuccessIp += _T("-�ѵ���");
// 			g_PubData.g_strArrayPlaySuccessIp.SetAt(iIndex, strShowSuccessIp);
// 
// 			gMainTree->SetItemImage(g_PubData.g_hTreeItem[iIndex], 2, 2);
// 			g_PubData.g_DeviceClose[iIndex] = TRUE;
// 			//AfxMessageBox(strText);
// 			//TRACE(_T("conn close\n"));
// 		}
// 		break;
// 	case JCU_EVENT_PARAM:
// 		break;
// 	case PARAM_CONTROL_DEV:
// 		{
// 			JSubmitDeviceStatus *deviceStatus = (JSubmitDeviceStatus*)parm->data;
// 			g_PubData.g_iControlDevRet = deviceStatus->ddp_status;
// 		}
// 		break;
// 	case PARAM_SUBMINT_ALARM:
// 		{
// 			int iIndex = (int)handle->user_arg;
// 			if(iIndex < 0 || iIndex > (g_PubData.g_strArrayPlaySuccessIp.GetCount() - 1))
// 			{
// 				return 0;
// 			}
// 			CString strIP = g_PubData.g_strArrayPlaySuccessIp.GetAt(iIndex);
// 	
// 			JSubmitAlarm *alarm = (JSubmitAlarm*)parm->data;
// 
// 			///////////////////////////�Ӿ���Ϣ////////////////////////////
// 			CString strTime = _T("");
// 			strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), alarm->alarm_time.year + 1900
// 				, alarm->alarm_time.month
// 				, alarm->alarm_time.date
// 				, alarm->alarm_time.hour
// 				, alarm->alarm_time.minute
// 				, alarm->alarm_time.second
// 				);
// 
// 			CString strChannel = _T("");
// 			strChannel.Format(_T("%d"), alarm->channel);
// 
// 			CStringArray strArrayAlarm;
// 			if(g_PubData.g_iLanguageFlag == 0)
// 				pDlg->GetAlarmData(alarm->alarm_type, alarm->action_type, strArrayAlarm, iIndex);
// 			else
// 				pDlg->GetAlarmDataEnglish(alarm->alarm_type, alarm->action_type, strArrayAlarm);
// 	
// 			
// 			CString strRemark = _T("");
// 			strRemark.Format(_T("%s"), alarm->data);
// 
// 
// 			ListWarning->InsertItem(g_PubData.g_iWarningCount,strIP);
// 			ListWarning->SetItemText(g_PubData.g_iWarningCount, 1, strTime);
// 			ListWarning->SetItemText(g_PubData.g_iWarningCount, 2, strChannel);
// 			ListWarning->SetItemText(g_PubData.g_iWarningCount, 3, strArrayAlarm.GetAt(0));
// 			ListWarning->SetItemText(g_PubData.g_iWarningCount, 4, strArrayAlarm.GetAt(1));
// 			ListWarning->SetItemText(g_PubData.g_iWarningCount, 5, strRemark);
// 			g_PubData.g_iWarningCount ++;
// 			///////////////////////////////////////////////////////////////
// 
// 
// 		}
// 		break;
// 	case  PARAM_FORMAT_DISK:
// 		if(-1 == parm->args)
// 		{
// 
// 		}
// 		else 
// 		{
// 			JFormatDisk *prs = (JFormatDisk *)parm->data;
// 			g_PubData.g_iFormatProgress = prs->progress;
// 			
// 		}
// 	case  PARAM_FIRMWARE_UPGRADE:
// 		
// 		if (-1 == parm->args)
// 		{
// 			//TRACE("upgrade failed\n");        
// 		}
// 		else 
// 		{
// 			JUpgradeProgress *prs = (JUpgradeProgress *)parm->data;
// 			upDev.percent = prs->percent;
// 			//TRACE("upgrade callback percent: %d\n", parm->args);
// 		}
// 	case JCU_EVENT_RECORD:
// 		if (-1 == parm->args)
// 		{
// 			//TRACE("record stream failed\n");        
// 		}
// 		else 
// 		{
// 			//TRACE("record stream ok\n");        
// 		}
// 		break;
// 	}
// 
// 	//�����豸�����Ľ���,ֻ���豸����ʱ���õ���
//  	return 0;
// }


void CClient_DemoDlg::SubmitAlarm(int nIndex, void *pData)
{
	JSubmitAlarm *alarm = (JSubmitAlarm*)pData;
	CString strIP = g_PubData.g_strArrayPlaySuccessIp.GetAt(nIndex);
	///////////////////////////�Ӿ���Ϣ////////////////////////////
	CString strTime = _T("");
	strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), alarm->alarm_time.year + 1900
		, alarm->alarm_time.month
		, alarm->alarm_time.date
		, alarm->alarm_time.hour
		, alarm->alarm_time.minute
		, alarm->alarm_time.second
		);

	CString strChannel = _T("");
	strChannel.Format(_T("%d"), alarm->channel);
	CStringArray strArrayAlarm;
	if(g_PubData.g_iLanguageFlag == 0)
		GetAlarmData(alarm->alarm_type, alarm->action_type, strArrayAlarm, nIndex);
	else
		GetAlarmDataEnglish(alarm->alarm_type, alarm->action_type, strArrayAlarm);

	CString strRemark = _T("");
	strRemark.Format(_T("%s"), alarm->data);
	m_ListWarning.InsertItem(g_PubData.g_iWarningCount,strIP);
	m_ListWarning.SetItemText(g_PubData.g_iWarningCount, 1, strTime);
	m_ListWarning.SetItemText(g_PubData.g_iWarningCount, 2, strChannel);
	m_ListWarning.SetItemText(g_PubData.g_iWarningCount, 3, strArrayAlarm.GetAt(0));
	m_ListWarning.SetItemText(g_PubData.g_iWarningCount, 4, strArrayAlarm.GetAt(1));
	m_ListWarning.SetItemText(g_PubData.g_iWarningCount, 5, strRemark);
	g_PubData.g_iWarningCount ++;
}


//��ȡ�豸������
void CClient_DemoDlg::GetDevCap(int nIndex)
{
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[nIndex],0,PARAM_DEVICE_CAP, (char *)&g_PubData.g_jDevCap[g_PubData.g_iIsPlayNum - 1], sizeof(JDevCap),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
}


// int CClient_DemoDlg::StreamCallBack(_jcu_stream_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	//TRACE("parm->id  =======================      %d\n", parm->id );
// 	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)g_lMainWnd;
// 	if(parm->id == JCU_STREAM_EV_OPEN)
// 	{
// 		//TRACE(_T("stream open=========\n"));
// 	}
// 
// 	else if(parm->id == JCU_STREAM_EV_RECV)
// 	{
// 		j_frame_t* pBufFrame = (j_frame_t*)parm->data;
// 
// 		if(pBufFrame == NULL)
// 		{
// 			return 0;
// 		}
// 
// 		int port= (int)handle->user_arg;
// 		int iRet = -1;
// 
// 		long len = 0;
// 		if(g_PubData.g_iRecFileID[port] >= 0)
// 		{
// 			len = AVP_WriteRecFile(g_PubData.g_iRecFileID[port], parm->data, parm->size, NULL, 0);
// 			TRACE("write file len = %ld, data size = %d\r\n", len, parm->size);
// 		}
// 		if(g_PubData.g_bTalk[port] &&  pBufFrame->frame_type == j_audio_frame)
// 		{
// 			//���Խ�ʱ ������Ƶ֡
// 		}
// 		else if(pBufFrame->frame_type == j_pic_frame)
// 		{
// 			CStringArray strArrallSecons;
// 			CStringArray strArrKey;
// 			CStringArray strArrKeyValue;
// 			g_PubData.g_iniFile.GetAllSections(strArrallSecons);
// 
// 			if(strArrallSecons.GetAt(0) == _T(""))
// 			{
// 				return -1;
// 			}
// 			g_PubData.g_iniFile.GetAllKeysAndValues(strArrallSecons.GetAt(0),strArrKey,strArrKeyValue);
// 			CString strPath = _T("");
// 			strPath = strArrKeyValue.GetAt(0);
// 			if(strPath == _T(""))
// 			{
// 				//AfxMessageBox(_T("��������ͼƬ����·��"));
// 				if(g_PubData.g_iLanguageFlag == 0)
// 					AfxMessageBox(_T("��������ͼƬ����·��"));
// 				else
// 					AfxMessageBox(_T("Upgrade"),_T("Please set the picture placed path!"));
// 				return -1;
// 			}
// 
// 
// 			if(!PathFileExists(strPath))
// 			{
// 				::_mkdir(strPath); 
// 			}
// 
// 			//��Ƭ������ = ip + ץ�Ŀ�ʼʱ�� + ��׺
// 			COleDateTime cTime;
// 			cTime = COleDateTime::GetCurrentTime();	
// 			CString strPictureName = g_PubData.g_strArrayPlaySuccessIp.GetAt(port);
// 			CString strPictureTime = _T("");
// 			strPictureTime.Format(_T("_%d%02d%02d%02d%02d%02d"),cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),
// 				cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
// 			strPictureName += strPictureTime;
// 			strPictureName += _T(".bmp");
// 			strPath += _T("\\");
// 			strPath += strPictureName;
// 
// 			
// 			FILE *fp = NULL;
// 			errno_t iErr = fopen_s(&fp, strPath.GetBuffer(0),_T("wb"));
// 			strPath.ReleaseBuffer();
// 			if(iErr != 0)
// 			{
// 				//AfxMessageBox(_T("�ļ���ʧ��"));
// 				return -1;	
// 			}
// 			iRet = fwrite(pBufFrame->data, pBufFrame->size,1,fp);
// 			TRACE(_T("size ==================================%ld\n"), pBufFrame->size);
// 			if(iRet != 1)
// 			{
// 				//AfxMessageBox(_T("ץͼ����"));
// 				return -1;
// 			}
// 
// 			fclose(fp);
// 
// 
// 			CClient_DemoDlg *pDlg = (CClient_DemoDlg *)g_lMainWnd;
// 			
// 			if(pDlg->m_vSnapHandle != NULL)
// 			{
// 				jcu_net_stream_close(pDlg->m_vSnapHandle);
// 				pDlg->m_vSnapHandle = NULL;
// 			}
// 
// 
// 		}
// 		else if(pBufFrame->frame_type != j_va_frame)
// 		{
// 			AVP_PutFrame(port,parm->data);	
// 		}
// 
// 	}
// 	else if(parm->id == JCU_STREAM_EV_CLOSE)
// 	{
// 		return 0;
// 	}
// 
// 	return 0;
// }




BOOL CClient_DemoDlg::HiPlayerOpenVideoStream(int iIndex)
{
	
	return TRUE;
}

BOOL CClient_DemoDlg::OpenVideoStream(int iIndex)
{
	int iRet = -1;

	// ��ȡ����ͨ��
	if( g_PubData.g_vStreamHandle[iIndex] != NULL)   //�Ѿ��򿪹���Ƶ��
	{
		return TRUE;
	}

	g_PubData.g_iChancel[iIndex] = AVP_GetFreePort();
	if ( g_PubData.g_iChancel[iIndex] < 0 )
	{
		AfxMessageBox(_T("AVP_GetFreePort error!"));
		return FALSE;
	}
	
	//��������
	int ch_no = 0;  
	int st_type = j_primary_stream; //��������
	int protocol = j_rtp_over_tcp;  //����Э��
	g_PubData.g_iStreamType[iIndex] = st_type;

	JNetStreamOpen(g_PubData.g_vLoginHandle[iIndex], ch_no,st_type, protocol,StreamCB,  (int *)iIndex, g_PubData.g_vStreamHandle[iIndex]);

	// ֡��ʽ
	iRet = AVP_SetDataProtocol(g_PubData.g_iChancel[iIndex],AVP_PROTOCOL_JPF);	
	if(iRet != AVPErrSuccess)
	{
		AfxMessageBox(_T("AVPErrSuccess  error\n"));
		return FALSE;
	}
	
	// ����ͨ��ʹ�õĽ�����
	iRet = AVP_SetCoder(g_PubData.g_iChancel[iIndex],AVP_CODER_JXJ);
	if ( iRet!=AVPErrSuccess )
	{
		AfxMessageBox(_T("AVP_SetCoder  error\n"));
		return FALSE;
	}

	// ��������
	iRet = AVP_Play(g_PubData.g_iChancel[iIndex]);
	if ( iRet!=AVPErrSuccess )
	{
		AfxMessageBox(_T("AVP_Play  error!"));
		return FALSE;
	}
	return TRUE;
}


// ��Ƶ�ص�
int CClient_DemoDlg::StreamCB(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam)
{
	int nIndex = (int)pUserParam;
	j_frame_t *pFrame = (j_frame_t *)pBuff;
	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)g_lMainWnd;
	if(g_PubData.g_iRecFileID[nIndex] >= 0)
	{
		AVP_WriteRecFile(g_PubData.g_iRecFileID[nIndex], pBuff, dwRevLen, NULL, 0); //¼��
	}
	if(pFrame->frame_type == j_pic_frame)  //ͼƬ֡
	{
		TRACE("NoVideoSnap......\r\n");
		pDlg->NoVideoSnap(nIndex, pFrame->data, pFrame->size);
	}
	else
	{
		int iRet = AVP_PutFrame(g_PubData.g_iChancel[nIndex],pBuff);
		TRACE("iret = %d\r\n",iRet );
	}
		
	return 0;
}


int CClient_DemoDlg::NoVideoSnap(int nIndex, char *pBuff, DWORD dwRevLen)
{
	int iRet = -1;
	CStringArray strArrallSecons;
	CStringArray strArrKey;
	CStringArray strArrKeyValue;


	g_PubData.g_iniFile.GetAllSections(strArrallSecons);

	if(strArrallSecons.GetAt(0) == _T(""))
	{
		return -1;
	}
	g_PubData.g_iniFile.GetAllKeysAndValues(strArrallSecons.GetAt(0),strArrKey,strArrKeyValue);
	CString strPath = _T("");
	strPath = strArrKeyValue.GetAt(0);
	if(strPath == _T(""))
	{	
		AfxMessageBox(_T("��������ͼƬ����·��"));
		return -1;
	}


	if(!PathFileExists(strPath))
	{
		::_mkdir(strPath); 
	}

	//��Ƭ������ = ip + ץ�Ŀ�ʼʱ�� + ��׺
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();	
	CString strPictureName = g_PubData.g_strArrayPlaySuccessIp.GetAt(nIndex);
	CString strPictureTime = _T("");
	strPictureTime.Format(_T("_%d%02d%02d%02d%02d%02d"),cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),
		cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	strPictureName += strPictureTime;
	strPictureName += _T(".bmp");
	strPath += _T("\\");
	strPath += strPictureName;


	FILE *fp = NULL;
	errno_t iErr = fopen_s(&fp, strPath.GetBuffer(0),_T("wb"));
	strPath.ReleaseBuffer();
	if(iErr != 0)
	{
		//AfxMessageBox(_T("�ļ���ʧ��"));
		return -1;	
	}
	
	iRet = fwrite(pBuff, dwRevLen,1,fp);
	if(iRet != 1)
	{
		//AfxMessageBox(_T("ץͼ����"));
		return -1;
	}

	fclose(fp);

	if(m_vSnapHandle >= 0)
	{
		JNetStreamClose(m_vSnapHandle);
		m_vSnapHandle = -1;
	}

	return 0;

}


//�˳�����
void CClient_DemoDlg::OnDestroy()
{
	CDialog::OnDestroy();
	int iRet = -1;
	// TODO: �ڴ˴������Ϣ����������
	for(int i = 0; i < g_PubData.g_iIsPlayNum; i++)
	{

		if(g_PubData.g_vTalkHandle[i] != NULL)
		{
			AVP_StopPickAudio();
			JNetTalkClose(g_PubData.g_vTalkHandle[i]);
			g_PubData.g_vTalkHandle[i] = NULL;	
		}
		if(g_PubData.g_iChancel[i] >= 0)
		{

			AVP_Stop(g_PubData.g_iChancel[i]);
			AVP_ReleasePort(g_PubData.g_iChancel[i]);	
			g_PubData.g_iChancel[i] =-1;
		}
	
		if(g_PubData.g_vStreamHandle[i] != NULL)
		{
			JNetStreamClose(g_PubData.g_vStreamHandle[i]);
			g_PubData.g_vStreamHandle[i] = NULL;
		}
		
		if(g_PubData.g_vLoginHandle[i] != NULL)
		{
			if(g_PubData.g_iServerFlag[i] == 1)
			{
				continue;
			}
			JNetLogout(g_PubData.g_vLoginHandle[i]);
			g_PubData.g_vLoginHandle[i] = NULL;
		}
		
	}			
	
	AVP_Cleanup();
	JNetCleanup();
	

}/*
CString CClient_DemoDlg::ASCIIToHex(CString strASCII)
{//��ASCii���ַ���ת���Կո񻮷ֵ�ʮ�������ַ���
	//"X0201014" ->"58 30 32 30 31 30 31 34"
	int i,iLen;
	CString strHex;
	char chTemp;
	iLen=strASCII.GetLength();
	strHex="";
	for (i=0;i<iLen;i++)
	{
		chTemp=strASCII[i];
		strHex+=CharToStr(chTemp)+" ";
	}
	return strHex;

}
*/

void CClient_DemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for(int i = 0; i< GET_MAX_DEV_NUM; i++)
	{
		CString strRecode(_T(""));
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->GetWindowText(strRecode);
		if(strRecode == _T("ֹͣ"))
		{
			if(g_PubData.g_iLanguageFlag == 0)
				AfxMessageBox( _T("���ȹر�¼��"));
			else
				AfxMessageBox( _T("Please turn off the video"));
			return;
		}
	}
// 	if(g_PubData.g_iLanguageFlag == 0)
// 	{
// 		int iRet = ::MessageBox(NULL,_T("ȷ���˳�?"),_T("�˳�ѯ��"),MB_YESNO|MB_ICONQUESTION); 
// 		if(iRet == IDYES)
// 		{
// 			CDialog::OnClose();
// 		}
// 	}
// 	else
// 	{
// 		int iRet = ::MessageBox(NULL,_T("Exit?"),_T("Q"),MB_YESNO|MB_ICONQUESTION); 
// 		if(iRet == IDYES)
// 		{
// 			CDialog::OnClose();
// 		}
// 	}
	CDialog::OnClose();
	
}

/*
	���������� index Ҫ���������Ĵ���
			   streamType Ҫ���õ���������

	�������ͣ� j_unknown_stream = 0,
			   j_primary_stream,
			   j_secondary_stream,
			   j_third_stream,
			   j_fourth_stream
*/
void CClient_DemoDlg::Set_StreamType(int index , int streamType)
{
	int ret=-1;

	if(g_PubData.g_vStreamHandle[index] != NULL)
	{
		ret=JNetStreamClose(g_PubData.g_vStreamHandle[index]);
		if (ret!=0)
		{	
			//AfxMessageBox(_T("�����ر�ʧ��"));
			return;
		}
		g_PubData.g_vStreamHandle[index] = NULL;
	}
	
	
	int ch_no = 0;  
	int st_type = streamType; //��������
	int protocol = j_rtp_over_tcp;  //����Э��
	JNetStreamOpen(g_PubData.g_vLoginHandle[index], ch_no,st_type, protocol,StreamCB,(int *)index,  g_PubData.g_vStreamHandle[index]);

}


BOOL CClient_DemoDlg::VideoTalk(int index)
{
	g_PubData.g_bTalk[index] = TRUE;
	AVP_EnableAudio(g_PubData.g_iChancel[index], TRUE);

	// iSamples		: 0--8k 1--16k 2-32k
    // iEncodeType	: 0--pcm 1-g711a 2-g711u 3--g726
    // iChannels	: 1
    // iBits		: 16bit
	//������
	JNetTalkOpen(g_PubData.g_vLoginHandle[index], 0, 1, 1, 16, OnTalkStream, (int *)index, g_PubData.g_vTalkHandle[index]);
	
	bool bRet = FALSE;
	bRet = AVP_StartPickAudio(8000,TRUE,PickAudioCallBack, (void *)index);
	if(bRet != TRUE)
	{
		AfxMessageBox(_T("�ɼ���Ƶʧ��"));
		return FALSE;
	}
	
	return TRUE;
}

BOOL CClient_DemoDlg::OnTalkStream(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam)
{
	_j_frame*	pstFrame	= (_j_frame*)(pBuff);
	int iIndex = (int)pUserParam;
	
	if ( pstFrame->frame_type==j_audio_frame)
	{
		AVP_PutFrame(g_PubData.g_iChancel[iIndex],pBuff);
	}

	return FALSE;
}

void CALLBACK CClient_DemoDlg::PickAudioCallBack(const BYTE* pBuffer, DWORD dwBufSize, void* pUserData)
{

	j_frame_t* pBufFrame = (j_frame_t*)pBuffer;

	int index = (int)pUserData;
	if(pBuffer == NULL)
	{
		AfxMessageBox(_T("��ȡ����ʧ��"));
		return;
	}

	int iRet = -1;
	iRet = JNetTalkSend(g_PubData.g_vTalkHandle[index], pBufFrame->data, dwBufSize - sizeof(j_frame_t) );
	if( iRet != 0 )
	{
		AfxMessageBox(_T("jcu_talk_send ʧ��"));
		return;
	}
}



void CClient_DemoDlg::OnBnClickedButtonPlayback()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_HIDE);
	
	m_bDragFile = TRUE;
	this->GetDlgItem(IDC_BUTTON_ALLFULLUP)->EnableWindow(FALSE);
	m_comScreenNum.EnableWindow(FALSE);
	int iCountDevice = g_PubData.g_strArrayPlaySuccessIp.GetCount();
	m_videoPlayBack.m_ComDevice.ResetContent();
	if(iCountDevice > 0)
	{
		for(int i =0 ;i < iCountDevice; i++)
		{
			m_videoPlayBack.m_ComDevice.AddString(g_PubData.g_strArrayPlaySuccessIp.GetAt(i));
		}
		g_PubData.g_iPlayBack = 0;
		m_videoPlayBack.m_ComDevice.SetCurSel(0);
	}
	else
	{
		//m_videoPlayBack.m_PlayBackIp.EnableWindow(FALSE);
		//m_videoPlayBack.m_PlayBackIp.SetWindowText(_T("û���豸"));
	}
	

	m_videoPlayBack.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight, TRUE);
	m_videoPlayBack.ShowWindow(SW_SHOW);
	Hide_Window(-1);


	m_ListWarning.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY + g_PubData.g_iStaticScreenHeight, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight,TRUE);
	m_ListWarning.ShowWindow(SW_SHOW);
	m_bWarningMax = FALSE;
	UpdateWindow();

	//Invalidate();
}

void CClient_DemoDlg::OnBnClickedButtonWatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDragFile = FALSE;
	this->GetDlgItem(IDC_BUTTON_ALLFULLUP)->EnableWindow(TRUE);
	m_comScreenNum.EnableWindow(TRUE);
	m_videoPlayBack.ShowWindow(SW_HIDE);
	//this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_SHOW);
	int iFlag = 0;
	for(int i = 0; i < GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iFlag == 1)  //��һ����ģʽ�У�ֻ��һ�����Ĵ�����ʾ����
		{
			iFlag = 1;
			g_cFullUpDlg[i].ShowWindow(SW_SHOW);
			break;
		}
	}
	if(iFlag != 1)
	{
		Show_Window(g_PubData.g_iCutScreenNum);
	}
	

	m_ListWarning.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY + g_PubData.g_iStaticScreenHeight, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight,TRUE);
	m_ListWarning.ShowWindow(SW_SHOW);
	m_bWarningMax = FALSE;
	UpdateWindow();
	//Invalidate();
}

//��̨����
void CClient_DemoDlg::ControlPtz(int iCmd)
{
	if(g_PubData.g_iPlayBack < 0 )
	{
		return;
	}
	if(g_PubData.g_vLoginHandle[g_PubData.g_iPlayBack] == NULL)
	{
		return;
	}
	int ptzValue = m_combJD.GetCurSel();

	int iRet = -1;
	
	m_domeCtrlPtz.u16PtzCmd = iCmd;
	m_domeCtrlPtz.u8Speed = ptzValue;

	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DOME_CTRL, (char *)&m_domeCtrlPtz, sizeof(m_domeCtrlPtz),TRUE );
	if( iRet != 0)
	{
		AfxMessageBox( _T("PTZ error!"));
	}

}


BOOL CClient_DemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	int buID;
	buID= GetWindowLong(pMsg->hwnd,GWL_ID);//�ɴ��ھ�����ID�ţ�GetWindowLongΪ��ô��ڵ�ID�š�
	if(pMsg->message==WM_LBUTTONDOWN)   //���� 
	{	
		if(buID== IDC_BUTTON_PTZUP)
		{  
			ControlPtz(PTZ_DOME_UP);
		}
		if(buID== IDC_BUTTON_PTZDOWN)
		{  
			ControlPtz(PTZ_DOME_DOWN);
		}  
		if(buID== IDC_BUTTON_PTZLEFT)
		{  
			ControlPtz(PTZ_DOME_LEFT);
		}  
		if(buID== IDC_BUTTON_PTZRIGHT)
		{  
			ControlPtz(PTZ_DOME_RIGHT);
		}  
		if(buID== IDC_BUTTOn_PTZAUTO)
		{  
			ControlPtz(PTZ_DOME_AUTOSCAN);
		}  
		if(buID == IDC_BUTTON_PTZSCANJIA)
		{
			ControlPtz(PTZ_DOME_FOCUS_NEAR);
		}
		if(buID == IDC_BUTTON_PTZSCANJIAN)
		{
			ControlPtz(PTZ_DOME_FOCUS_FAR);
		}
	}
	if(pMsg->message==WM_LBUTTONUP)  //�ɿ�
	{  
		if(buID==IDC_BUTTON_PTZUP)
		{  
			ControlPtz(PTZ_DOME_STOP);
		}  
		if(buID== IDC_BUTTON_PTZDOWN)
		{  
			ControlPtz(PTZ_DOME_STOP);
		}  
		if(buID== IDC_BUTTON_PTZLEFT)
		{  
			ControlPtz(PTZ_DOME_STOP);
		}  
		if(buID== IDC_BUTTON_PTZRIGHT)
		{  
			ControlPtz(PTZ_DOME_STOP);
		}  
		if(buID== IDC_BUTTOn_PTZAUTO)
		{  
			ControlPtz(PTZ_DOME_STOP);
		}  
		if(buID == IDC_BUTTON_PTZSCANJIA)
		{
			ControlPtz(PTZ_DOME_STOP);
		}
		if(buID == IDC_BUTTON_PTZSCANJIAN)
		{
			ControlPtz(PTZ_DOME_STOP);
		}
	}
	//ESC27,Enter13
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 27 )
	{

		if(g_PubData.g_bAllFullScreen)
		{
			RecoverToOldScreen();
		}

		if(g_PubData.g_iFullScreenId < 0 )
		{
			return FALSE;
		}
		
		if(g_cFullUpDlg[g_PubData.g_iFullScreenId].m_iFlag == 2)
		{
			g_cFullUpDlg[g_PubData.g_iFullScreenId].EscEvent();
		}	

		
		return FALSE;
	}
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 13 )
	{
		return FALSE;
	}

	
	return CDialog::PreTranslateMessage(pMsg);
}
void CClient_DemoDlg::OnBnClickedCheckStartlight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iCheck = m_StartLight.GetCheck();
	if(iCheck == 1)
	{
		ControlPtz(PTZ_TURN_ON);
	}
	else
	{
		ControlPtz(PTZ_TURN_OFF);
	}
}

void CClient_DemoDlg::OnBnClickedCheckStartbrush()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iCheck = m_StartBrush.GetCheck();
	if(iCheck == 1)
	{
		ControlPtz(PTZ_WIPERS_ON);
	}
	else
	{
		ControlPtz(PTZ_WIPERS_OFF);
	}
}

void CClient_DemoDlg::EnablePTZ()
{
	m_combJD.EnableWindow(FALSE);
	m_bUp.EnableWindow(FALSE);
	m_bLeft.EnableWindow(FALSE);
	m_bRight.EnableWindow(FALSE);
	m_bDown.EnableWindow(FALSE);
	m_bAuto.EnableWindow(FALSE);
	m_ScanJIa.EnableWindow(FALSE);
	m_ScanJian.EnableWindow(FALSE);
	m_StartLight.EnableWindow(FALSE);
	m_StartBrush.EnableWindow(FALSE);
}

void CClient_DemoDlg::ShowPtz()
{
	m_combJD.EnableWindow(TRUE);
	m_bUp.EnableWindow(TRUE);
	m_bLeft.EnableWindow(TRUE);
	m_bRight.EnableWindow(TRUE);
	m_bDown.EnableWindow(TRUE);
	m_bAuto.EnableWindow(TRUE);
	m_ScanJIa.EnableWindow(TRUE);
	m_ScanJian.EnableWindow(TRUE);
	m_StartLight.EnableWindow(TRUE);
	m_StartBrush.EnableWindow(TRUE);
}

void CClient_DemoDlg::OnLvnColumnclickListWarning(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect cRect;
	GetDlgItem(IDC_LIST_WARNING)->GetWindowRect(cRect);

	if(!m_bWarningMax)
	{
		m_ListWarning.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight, TRUE);
		m_ListWarning.ShowWindow(SW_SHOW);

 		m_videoPlayBack.ShowWindow(SW_HIDE);
 		Hide_Window(-1);
		m_bWarningMax = TRUE;
		m_comScreenNum.EnableWindow(FALSE);
		UpdateWindow();
	}
	else
	{
		m_ListWarning.MoveWindow(g_PubData.g_iMoveX, g_PubData.g_iMoveY + g_PubData.g_iStaticScreenHeight, g_PubData.g_iStaticScreenWidth, g_PubData.g_iStaticScreenHeight,TRUE);
		m_ListWarning.ShowWindow(SW_SHOW);
		int iFlag = 0;
		for(int i = 0; i < GET_MAX_DEV_NUM; i++)
		{
			if(g_cFullUpDlg[i].m_iFlag == 1)  //��һ����ģʽ�У�ֻ��һ�����Ĵ�����ʾ����
			{
				iFlag = 1;
				g_cFullUpDlg[i].ShowWindow(SW_SHOW);
				break;
			}
		}
		if(iFlag != 1 )
		{
			Show_Window(g_PubData.g_iCutScreenNum);
		}
		
		m_bWarningMax = FALSE;
		m_comScreenNum.EnableWindow(TRUE);
		UpdateWindow();
	}
	
	//this->Invalidate();

	*pResult = 0;
}

void CClient_DemoDlg::OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	HTREEITEM ht = m_MainTree.GetSelectedItem();
	if(ht)
	{    
		CString str;
		str = m_MainTree.GetItemText(ht);    
		AfxMessageBox(str);
	}*/

	*pResult = 0;
}

void CClient_DemoDlg::OnMenuAttribute()
{
	// TODO: �ڴ���������������
	g_PubData.g_iAttributeIng = GetDragItemIndex(m_strSelItemText);
	if(g_PubData.g_iAttributeIng < 0)
	{
		//AfxMessageBox(_T("��ѡ��Ҫ���õĴ���"));
		return;
	}
	if(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		//AfxMessageBox(_T("û���豸"));
		return;
	}
	if(g_PubData.g_vStreamHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		OpenVideoStream(g_PubData.g_iAttributeIng); // ���û�д���Ƶ��������Ƶ��
		g_PubData.g_bOpenStreamInAttribute = TRUE;
	}
	m_bDragFile = FALSE;
	g_PubData.g_iPlayWndFlag = -1;
	CCAttributeDlg dlg;
	dlg.DoModal();
}


void CClient_DemoDlg::OnMenuDelete()
{
	// TODO: �ڴ���������������
	int iRet = -1;
	if(g_PubData.g_iLanguageFlag == 0)
		iRet = ::MessageBox(NULL,_T("ȷ��ɾ��?"),_T("ɾ��ѯ��"),MB_YESNO|MB_ICONQUESTION); 
	else
		iRet = AfxMessageBox(_T("Sure to delete?")); 
	if(iRet == IDYES || iRet == 1)
	{
		
		for(int i = 0; i< g_PubData.g_iCountDevice; i++)
		{
			if(g_PubData.g_strArraySavedIp.GetAt(i) == m_strSelItemText)
			{
				g_PubData.g_strArraySavedIp.SetAt(i, _T(""));
				g_PubData.g_iCountPerson[i] = 0;
			}
		}

		for(int j = 0; j< g_PubData.g_strArrayPlaySuccessIp.GetCount(); j++)
		{
			if(g_PubData.g_strArrayPlaySuccessIp.GetAt(j) == m_strSelItemText)
			{
				if(g_PubData.g_iServerFlag[j] == 1)
				{
					AfxMessageBox(_T("����ɾ��������½���豸"));
					return;
				}
				CString strText = _T("");
				strText = g_PubData.g_strArrayPlaySuccessIp.GetAt(j);
				if(g_PubData.g_iLanguageFlag == 0)
					strText += _T("(��ɾ��)");
				else
					strText += _T("Deleted");
				g_PubData.g_strArrayPlaySuccessIp.SetAt(j, strText);
				DeleteDevice(j);
			}
		}
		m_MainTree.DeleteItem(m_hDeleteItem);
	}
}


void CClient_DemoDlg::DeleteDevice(int index)
{
	int iRet = -1;
	// TODO: �ڴ˴������Ϣ����������
	
	g_PubData.g_DeviceClose[index] = FALSE;
	if(g_PubData.g_vTalkHandle[index] != NULL)
	{
		AVP_StopPickAudio();
		JNetTalkClose(g_PubData.g_vTalkHandle[index]);
		g_PubData.g_vTalkHandle[index] = NULL;	
	}

	if(g_PubData.g_iChancel[index] >= 0)
	{
		AVP_Stop(g_PubData.g_iChancel[index]);
		AVP_ReleasePort(g_PubData.g_iChancel[index]);		
		g_PubData.g_iChancel[index] =-1;
	}

	if(g_PubData.g_vStreamHandle[index] != NULL)
	{
		JNetStreamClose(g_PubData.g_vStreamHandle[index]);
		g_PubData.g_vStreamHandle[index] = NULL;
	}

	if(g_PubData.g_vLoginHandle[index] != NULL)
	{
		JNetLogout(g_PubData.g_vLoginHandle[index]);
		g_PubData.g_vLoginHandle[index] = NULL;
	}
	for(int i = 0; i< GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iPlayWndIndex == index)
		{
			g_cFullUpDlg[i].m_iPlayWndIndex = -1;
			g_cFullUpDlg[i].m_iPlayWndNum = -1;
			g_cFullUpDlg[i].m_iPlayFlag = -1;

			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
			g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);
			g_cFullUpDlg[i].Invalidate(TRUE);
		}
	}
}

void CClient_DemoDlg::OnBnClickedButtonRecode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDragFile = FALSE;
	CSerachNote serachNote;
	serachNote.DoModal();
	
}
void CClient_DemoDlg::OnNMClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint pt;
	HTREEITEM selDevhItem = NULL;
	::GetCursorPos(&pt);
	m_MainTree.ScreenToClient(&pt);
	selDevhItem = m_MainTree.HitTest(pt);
	int iIndex = -2;
	CString strItemText = m_MainTree.GetItemText(selDevhItem);
	for(int i = 0; i < g_PubData.g_strArrayPlaySuccessIp.GetCount(); i++)
	{
		if(strItemText == g_PubData.g_strArrayPlaySuccessIp.GetAt(i))
		{
			iIndex = i;
			break;
		}
	}

	for(int i = 0; i < GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iPlayWndIndex == iIndex)
		{
			g_cFullUpDlg[i].DrewWinBorder();
		}
		else
		{
			g_cFullUpDlg[i].ResetBorder();
		}
	}


	*pResult = 0;
}

void CClient_DemoDlg::OnTvnBegindragTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_hDragItem = pNMTreeView->itemNew.hItem;  //��ȡ��ʼ�϶��Ľڵ�
	m_strDragItemText = _T("");
	if(m_hDragItem != NULL) 
	{		
		TVITEM item;
		CHAR szText[20];
		item.hItem = m_hDragItem;
		item.mask = TVIF_TEXT | TVIF_HANDLE;
		item.pszText = szText;
		item.cchTextMax = 20;

		BOOL bWorked = m_MainTree.GetItem(&item);
		m_strDragItemText.Format(_T("%s"), szText);
	}

	m_iLoginOk = -1;
	m_iLoginOk = GetDragItemIndex(m_strDragItemText);
	if(m_iLoginOk < 0)//˵����δ��½�ɹ�
	{
		*pResult = 0;
		return ;
	}

	if (m_hDragItem == m_MainTree.GetRootItem())       //�������϶����ڵ�
	{
		*pResult = 0;
		return;
	}
	
	if(g_PubData.g_DeviceClose[m_iLoginOk])     //��;���ߵ�
	{
		*pResult = 0;
		return ;
	}


	m_hBeginDrag = m_hDragItem;        //��¼��ʼ�϶�����Ŀ
	m_pDragImage = m_MainTree.CreateDragImage(m_hDragItem);    //�����϶���ͼ���б�

	CPoint dragPT;          //��¼��ʼ��
	dragPT.x = pNMTreeView->ptDrag.x;
	dragPT.y = pNMTreeView->ptDrag.y;
	if (m_pDragImage != NULL)
	{
		m_pDragImage->BeginDrag(0, CPoint(0,-10));  //��ʼ�϶�ͼ��

		ClientToScreen(&dragPT);      //ת���ͻ����굽��Ļ����
		m_pDragImage->DragEnter(this, dragPT);   //�������ڸ��£����϶��Ĺ�������ʾ�϶���ͼ��
		SetCapture();         //��ʼ��겶׽
		m_bDrag = TRUE;
	}


	*pResult = 0;
}

void CClient_DemoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);
}

void CClient_DemoDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bDrag)
	{
		m_MainTree.SelectItem(m_hDragItem);
		CPoint  pt = point;
		CImageList::DragMove( pt );

		CRect  clientRC;
		GetClientRect(&clientRC);      //��ȡ�ͻ�����
		m_pDragImage->DragMove(point);     //�����϶���ͼ��λ��
		
		//m_MainTree.SelectDropTarget(m_hDragItem);     //����ѡ�е���Ŀ
		CImageList::DragShowNolock(TRUE);   //��ʾ�϶���ͼ��
		
	}


	CDialog::OnMouseMove(nFlags, point);
}
void CClient_DemoDlg::RegDrawCallBackEx(int iChannel, HWND hwnd)
{
	
}

void CClient_DemoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (m_bDrag)          //Tree�����϶�״̬
	{
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;

		int iDragIndex = -1;
		iDragIndex = GetDragItemIndex(m_strDragItemText);
		if(iDragIndex < 0 )
		{
			return;
		}

		int iWndIndex = -1;
		iWndIndex = GetDragToScreenNum(point.x, point.y);
		if(iWndIndex < 0 )
		{
			return;
		}

		if(!OpenVideoStream(iDragIndex))   //����Ƶ��
		{
			return;
		}
		// ������ʾ����
		if(g_cFullUpDlg[iWndIndex].m_iPlayWndIndex >= 0)
		{
			AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[iWndIndex].m_iPlayWndIndex], g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			g_cFullUpDlg[iWndIndex].Invalidate(TRUE);
		}

	
		
		AVP_AddPlayWnd(g_PubData.g_iChancel[iDragIndex],NULL, g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd(),NULL, NULL);
		
		g_cFullUpDlg[iWndIndex].m_iPlayWndIndex = iDragIndex;
		g_cFullUpDlg[iWndIndex].m_iPlayWndNum = iWndIndex;
		g_cFullUpDlg[iWndIndex].m_iPlayFlag = 1;
		g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(TRUE);
		g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(TRUE);
		g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
		g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(TRUE);
		g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(TRUE);

		for(int i = 0; i < GET_MAX_DEV_NUM; i++)    //�жϸ��豸�Ƿ��Ѿ��ڲ�����Ƶ�����Ѿ����˶Խ�����������¼��
		{

			if(i == iWndIndex  || g_cFullUpDlg[i].m_iPlayFlag != 1)
			{
				continue;
			}

			if((g_cFullUpDlg[i].m_iPlayWndIndex == iDragIndex))
			{
				if(g_cFullUpDlg[i].m_bTalk)
				{
					g_cFullUpDlg[iWndIndex].m_bTalk = TRUE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkE);
				}
				else
				{
					g_cFullUpDlg[iWndIndex].m_bTalk = FALSE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
				}

				if(g_cFullUpDlg[i].m_bListen)
				{
					g_cFullUpDlg[iWndIndex].m_bListen = TRUE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListemE);
				}
				else
				{
					g_cFullUpDlg[iWndIndex].m_bListen = FALSE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
				}

				if(g_cFullUpDlg[i].m_bRecode)
				{
					g_cFullUpDlg[iWndIndex].m_bRecode = TRUE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordE);
				}
				else
				{
					g_cFullUpDlg[iWndIndex].m_bRecode = FALSE;
					g_cFullUpDlg[iWndIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);
				}

			}
			
		}
		

		m_bDrag = FALSE;

	}

	CDialog::OnLButtonUp(nFlags, point);
}
int CClient_DemoDlg::GetDragItemIndex(CString strNode)
{
	for(int i= 0; i< g_PubData.g_strArrayPlaySuccessIp.GetCount(); i++)
	{
		if(strNode == g_PubData.g_strArrayPlaySuccessIp.GetAt(i))
		{
			return i;
		}
	}
	return -1;
}

int CClient_DemoDlg::GetDragToScreenNum(int iX, int iY)
{
	int iSqrtNum = (int)sqrt((double)g_PubData.g_iCutScreenNum);

	int iStaticX = g_PubData.g_iMoveX;
	int iStaticY = g_PubData.g_iMoveY;
	if(g_PubData.g_bAllFullScreen)  //�໭��ȫ��ģʽ
	{
		iStaticX = 0;
		iStaticY = 0;
	}
	else
	{
		if(iX < g_PubData.g_iMoveX || iY < g_PubData.g_iMoveY)//���ھ�̬����
		{
			return -1;
		}
	}

	int	iRowNum = (( iX- iStaticX ) - OUTPUT_INTERVAL*(iSqrtNum - 1)) / g_PubData.g_iCutScreenWidth;
	int	iColNum = (( iY- iStaticY ) - OUTPUT_INTERVAL*(iSqrtNum - 1)) / g_PubData.g_iCutScreenHeight;
	if(iRowNum >= iSqrtNum || iColNum >= iSqrtNum)
	{
		return -1;
	}

	return iColNum * iSqrtNum + iRowNum;
}

//�ر����д򿪵Ĵ��ڲ��ر���Ƶ��
void CClient_DemoDlg::OnBnClickedButtonCloseallvideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i= 0; i< GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iPlayFlag < 0)  //�Ĵ���û�в�����Ƶ
		{
			continue;
		}
// 		AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[i].m_iPlayWndIndex],
// 						g_cFullUpDlg[i].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
// 
// 
// 		if(g_PubData.g_vStreamHandle[g_cFullUpDlg[i].m_iPlayWndIndex] != NULL)
// 		{
// 			AVP_Stop(g_PubData.g_iChancel[g_cFullUpDlg[i].m_iPlayWndIndex]);
// 			AVP_ReleasePort(g_PubData.g_iChancel[g_cFullUpDlg[i].m_iPlayWndIndex]);	
// 			g_PubData.g_iChancel[g_cFullUpDlg[i].m_iPlayWndIndex] =-1;
// 			jcu_net_stream_close(g_PubData.g_vStreamHandle[g_cFullUpDlg[i].m_iPlayWndIndex]);
// 			g_PubData.g_vStreamHandle[g_cFullUpDlg[i].m_iPlayWndIndex] = NULL;
// 		}
// 
// 		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
// 		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
// 		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
// 		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
// 		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);
// 
// 		g_cFullUpDlg[i].m_iPlayWndIndex = -1;
// 		g_cFullUpDlg[i].m_iPlayWndNum = -1;
// 		g_cFullUpDlg[i].m_iPlayFlag = -1;
		g_cFullUpDlg[i].OnMenuClose();
		g_cFullUpDlg[i].Invalidate();
	}
	Invalidate();
}


void CClient_DemoDlg::OnNMRClickListWarning(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
}

void CClient_DemoDlg::OnMenuDellist()
{

}

void CClient_DemoDlg::OnBnClickedButtonClearwarning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListWarning.DeleteAllItems();
	g_PubData.g_iWarningCount = 0;
}

//�໭��ȫ��
void CClient_DemoDlg::OnBnClickedButtonAllfullup()
{
	ModifyStyle(WS_CAPTION,0,0); 
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	this->MoveWindow(0,0,iScreenWidth,iScreenHeight,TRUE);
	this->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_STATIC_SCREEN)->MoveWindow(0,0,iScreenWidth,iScreenHeight,TRUE);
	this->GetDlgItem(IDC_STATIC_SCREEN)->ShowWindow(SW_SHOW);
	ArrangeOutputs(g_PubData.g_iCutScreenNum);
	g_PubData.g_bAllFullScreen = TRUE;	

	GetDlgItem(IDC_STATIC_SHOWTIME)->ShowWindow(SW_HIDE);
	for(int i= 0; i< GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iPlayFlag < 0)
		{
			continue;
		}
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);
		g_cFullUpDlg[i].Invalidate(TRUE);
	}
	
	HideButton(SW_HIDE);
}

//���ض໭��ȫ��֮ǰ��״̬
void CClient_DemoDlg::RecoverToOldScreen()
{
	/*int g_iMainWindowX;         //�����������Ļ������X
	int g_iMainWindowY;			//�����������Ļ������Y
	int g_iMainWindowW;         //�����������Ļ������width
	int g_iMainWindowH;			//�����������Ļ������height

	int g_iMoveX;        //��̬����ڶԻ��� x λ��
	int g_iMoveY;       //��̬����ڶԻ��� y λ��
	int g_iStaticScreenWidth;       //��̬���ڵĿ�
	int g_iStaticScreenHeight;		//��̬���ڵĸ�
	int g_iCutScreenNum;          //�ָ�Ĵ�����*/

	//��ԭ������
	SetWindowLong(this-> GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_hWnd,GWL_STYLE) + (WS_CAPTION|WS_BORDER) ); 

	this->MoveWindow(g_PubData.g_iMainWindowX,g_PubData.g_iMainWindowY,
		g_PubData.g_iMainWindowW,g_PubData.g_iMainWindowH,TRUE);
	this->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_STATIC_SCREEN)->MoveWindow(g_PubData.g_iMoveX,g_PubData.g_iMoveY,g_PubData.g_iStaticScreenWidth,g_PubData.g_iStaticScreenHeight,TRUE);
	this->GetDlgItem(IDC_STATIC_SCREEN)->ShowWindow(SW_SHOW);
	ArrangeOutputs(g_PubData.g_iCutScreenNum);
	g_PubData.g_bAllFullScreen = FALSE;
	GetDlgItem(IDC_STATIC_SHOWTIME)->ShowWindow(SW_SHOW);
	for(int i= 0; i< GET_MAX_DEV_NUM; i++)
	{
		if(g_cFullUpDlg[i].m_iPlayFlag < 0)
		{
			continue;
		}
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(TRUE);
		g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(TRUE);
		g_cFullUpDlg[i].Invalidate(TRUE);
	}
	HideButton(SW_SHOW);
}


//�໭��ȫ��ʱ�����������ϵĿؼ�
void CClient_DemoDlg::HideButton(int iFlag)
{
	this->GetDlgItem(IDC_BUTTON_WATCH)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PLAYBACK)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_RECODE)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_CLOSEALLVIDEO)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_CLEARWARNING)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_ALLFULLUP)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZUP)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZDOWN)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZLEFT)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZRIGHT)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTOn_PTZAUTO)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZSCANJIA)->ShowWindow(iFlag);
	this->GetDlgItem(IDC_BUTTON_PTZSCANJIAN)->ShowWindow(iFlag);
	m_StartLight.ShowWindow(iFlag);
	m_StartBrush.ShowWindow(iFlag);
	m_ListWarning.ShowWindow(iFlag);
	m_MainTree.ShowWindow(iFlag);
	m_comScreenNum.ShowWindow(iFlag);
}


void CClient_DemoDlg::OnBnClickedButtonElse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint point1;
	GetCursorPos(&point1);
	CMenu pMenu;
	if (!pMenu.LoadMenu(IDR_MENU4))
	{
			return;
	}
	CMenu* pPopup=pMenu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point1.x,point1.y,this);
}


//����ץ�ġ�¼��·��
void CClient_DemoDlg::OnLocalattribute()
{
	// TODO: �ڴ���������������
	CSrcSet srcSet;

	int id = srcSet.DoModal();
	if(id == IDOK)
	{

		CString strMode;
		strMode.Format(_T("%d"), srcSet.m_iMode);
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("ץ��·��"),srcSet.m_strTakeApictureSrc);
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("¼��·��"),srcSet.m_strRecodeSrc);
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("����·��"),srcSet.m_strDownLoadSrc);

		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("ģʽ"), strMode);     //0 �ͻ���  1 �����
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("����˿�"), srcSet.m_strPort);
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("���˿�"), srcSet.m_strSPort);
		CString strLanguage;
		strLanguage.Format(_T("%d"), srcSet.m_iLanguageFlag);
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("����"), strLanguage);




		if(srcSet.m_iLanguageFlag != g_PubData.g_iLanguageFlag)
		{
			if(g_PubData.g_iLanguageFlag == 0)
				AfxMessageBox(_T("Ҫʹ������Ч������������������!")); 
			else
				AfxMessageBox(_T("To make the preservation effect, you must restart the program"));
		
		}

	}
}




BOOL CClient_DemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return CDialog::OnEraseBkgnd(pDC);
}


void CClient_DemoDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!m_bDragFile)
	{
		return;
	}

	CPoint ptCurrent;
	GetCursorPos(&ptCurrent); 
	CRect cRect;
	m_videoPlayBack.m_recodeScreenDlg.GetWindowRect(cRect);

	if(ptCurrent.x > cRect.left && ptCurrent.x < cRect.right && ptCurrent.y > cRect.top && ptCurrent.y < cRect.bottom)
	{
		UINT count;
		char filePath[200];

		count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
		if(count)
		{        
			// 		for(UINT i=0; i<count; i++)  //�϶���ļ�ʱ  ���ŵ�һ��
			// 		{
			int pathLen = DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));
			CString strFile = _T("");
			strFile.Format(_T("%s"), filePath);
			m_videoPlayBack.PlayVideoFile(strFile);
			//}
		}

		DragFinish(hDropInfo);

	}

	CDialog::OnDropFiles(hDropInfo);
}


void CClient_DemoDlg::OnMenuDeviceSnap()
{
	// TODO: �ڴ���������������
	int nDeviceIndex = GetDragItemIndex(m_strSelItemText);

	if(g_PubData.g_vLoginHandle[nDeviceIndex] == NULL)
	{
		return;
	}
	
	int ch_no = 0;  
	int st_type = j_picture; //��������
	int protocol = j_rtp_over_tcp;  //����Э��
	if(m_vSnapHandle >= 0)
	{
		JNetStreamClose(m_vSnapHandle);
		m_vSnapHandle = -1;
	}
	JNetStreamOpen(g_PubData.g_vLoginHandle[nDeviceIndex], ch_no,st_type, protocol,StreamCB,  (int *)nDeviceIndex, m_vSnapHandle);
	if(m_vSnapHandle < 0)
	{
		AfxMessageBox(_T("JNetStreamOpen error!"));
		return; 
	}
}



///region��һ����Ԫ�ص�����ָ�룬��ʾһ���ı��Σ�pos��ʾ���жϵĵ�
///����ж�������С�����Ƿ��ڲ������ı����ڣ��ǲ����ж�С�������ĵ�ķ����������������λ������С����(��6*6����)�������С��������ϵ���Ϊ���ĵ�
bool CClient_DemoDlg::area_cross(JPoint region[], JPoint pos)
{	
	int temp1, temp2;

	/// ��1
	if (region[1].x != region[0].x)
	{
		/// (x-x1)*(y2-y1)/(x2-x1) - y + y1
		temp1 = (pos.x-region[0].x)*(region[1].y-region[0].y)/(region[1].x - region[0].x) - pos.y +region[0].y;	
		/// (x3-x1)*(y2-y1)/(x2-x1) - y3 + y1
		temp2 = (region[2].x-region[0].x)*(region[1].y-region[0].y)/(region[1].x - region[0].x) - region[2].y +region[0].y;	
	}
	else
	{
		/// x1 - x
		temp1 = region[0].x - pos.x;
		/// x1 - x3
		temp2 = region[0].x - region[2].x ;	
	}
	if (temp1*temp2 >0)
	{
		/// ��2
		if (region[2].x != region[1].x)
		{
			/// (x-x2)*(y3-y2)/(x3-x2) - y + y2
			temp1 = (pos.x-region[1].x)*(region[2].y-region[1].y)/(region[2].x - region[1].x) - pos.y +region[1].y;	
			/// (x4-x2)*(y3-y2)/(x3-x2) - y4 + y2
			temp2 = (region[3].x-region[1].x)*(region[2].y-region[1].y)/(region[2].x - region[1].x) - region[3].y +region[1].y;	
		}
		else
		{
			/// y2 - y
			temp1 = region[1].x - pos.x;
			/// y2 - y4
			temp2 = region[1].x - region[3].x ;	
		}
		if (temp1*temp2 >0)
		{
			/// ��3
			if (region[3].x != region[2].x)
			{
				/// (x-x3)*(y4-y3)/(x4-x3) - y + y3
				temp1 = (pos.x-region[2].x)*(region[3].y-region[2].y)/(region[3].x - region[2].x) - pos.y +region[2].y;		
				/// (x1-x3)*(y4-y3)/(x4-x3) - y1 + y3
				temp2 = (region[0].x-region[2].x)*(region[3].y-region[2].y)/(region[3].x - region[2].x) - region[0].y +region[2].y;	
			}
			else
			{
				/// y3 - y
				temp1 = region[2].x - pos.x;	
				/// y3 - y1
				temp2 =  region[2].x - region[0].x;	
			}
			if (temp1*temp2 >0)
			{
				/// ��4
				if (region[0].x != region[3].x)
				{
					/// (x-x4)*(y1-y4)/(x1-x4) - y + y4
					temp1 = (pos.x-region[3].x)*(region[0].y-region[3].y)/(region[0].x - region[3].x) - pos.y +region[3].y;	
					/// (x2-x4)*(y1-y4)/(x1-x4) - y2 + y4
					temp2 = (region[1].x-region[3].x)*(region[0].y-region[3].y)/(region[0].x - region[3].x) - region[1].y +region[3].y;	
				}
				else
				{
					/// y4 - y 
					temp1 = region[3].x - pos.x;
					/// y4 - y2 
					temp2 = region[3].x - region[1].x ;	
				}
				if (temp1*temp2 >0){
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

int CClient_DemoDlg::getBlockValue(char *data, int len, int isBit, int blockIndex)
{
	int i, j;

	if (isBit == 0)
	{
		i = blockIndex / 8;
		j = blockIndex % 8;
		if (i >= len)
			return -1;
		return (data[i]&(0x80>>j));
	}
	else
	{
		if (blockIndex >= len)
			return -1;
		return (data[blockIndex]);
	}
}
