// SerachNote.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SerachNote.h"
#include "Pub_Data.h"
#include <WinSock.h>
// CSerachNote �Ի���


IMPLEMENT_DYNAMIC(CSerachNote, CDialog)

CSerachNote::CSerachNote(CWnd* pParent /*=NULL*/)
	: CDialog(CSerachNote::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CSerachNote::~CSerachNote()
{
}

void CSerachNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_DATE, m_StartDate);
	DDX_Control(pDX, IDC_START_TIME, m_StartTime);
	DDX_Control(pDX, IDC_END_DATE, m_EndDate);
	DDX_Control(pDX, IDC_END_TIME, m_EndTime);
	DDX_Control(pDX, IDC_COMBO_RECODE_TYPE, m_RecodeType);
	DDX_Control(pDX, IDC_LIST_RECODE, m_ListRecode);
	DDX_Control(pDX, IDC_COMBO_RECODEDEVICE, m_RecodeDevice);
}


BEGIN_MESSAGE_MAP(CSerachNote, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERACH, &CSerachNote::OnBnClickedButtonSerach)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_RECODEDEVICE, &CSerachNote::OnCbnSelchangeComboRecodedevice)
END_MESSAGE_MAP()


// CSerachNote ��Ϣ�������
BOOL CSerachNote::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_iBeginNode = 0;
	m_iEndNode = 31;
	m_iSsid = -1;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_RecodeType.AddString(_T("ϵͳ��־"));
		m_RecodeType.AddString(_T("�澯��־"));
		m_RecodeType.AddString(_T("������־"));
		m_RecodeType.AddString(_T("������־"));
		m_RecodeType.AddString(_T("������־"));
		m_RecodeType.AddString(_T("�쳣��־"));
		m_RecodeType.AddString(_T("������־"));

		m_RecodeType.SetCurSel(0);

		m_ListRecode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListRecode.InsertColumn(0 , _T("ʱ��"), 2, 150, -1);
		m_ListRecode.InsertColumn(1 , _T("��������"), 2, 150,-1);
		m_ListRecode.InsertColumn(2 , _T("�����û�"), 2, 150,-1);
		m_ListRecode.InsertColumn(3 , _T("�����û�IP"), 2, 150,-1);
	}
	else
	{
		m_RecodeType.AddString(_T("system log"));
		m_RecodeType.AddString(_T("alarm log"));
		m_RecodeType.AddString(_T("operation log"));
		m_RecodeType.AddString(_T("web log"));
		m_RecodeType.AddString(_T("Parameter log"));
		m_RecodeType.AddString(_T("abnormal log"));
		m_RecodeType.AddString(_T("all log"));

		m_RecodeType.SetCurSel(0);

		m_ListRecode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListRecode.InsertColumn(0 , _T("Time"), 2, 150, -1);
		m_ListRecode.InsertColumn(1 , _T("Operation type"), 2, 150,-1);
		m_ListRecode.InsertColumn(2 , _T("User"), 2, 150,-1);
		m_ListRecode.InsertColumn(3 , _T("Operation IP"), 2, 150,-1);
	}
	

	COleDateTime LimitData(1970,1,1,0,0,0);
	m_StartDate.SetRange(&LimitData, NULL);
	m_EndDate.SetRange(&LimitData, NULL);
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();																	// Сʱ		//����			//��
	COleDateTime startTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(), 0, 0, 0);
	COleDateTime endTime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(), 23, 59, 59);

	m_StartTime.SetTime(startTime);
	m_EndTime.SetTime(endTime);

	int iCountDevice = g_PubData.g_strArrayPlaySuccessIp.GetCount();
	if(iCountDevice > 0)
	{
		for(int i = 0; i< iCountDevice; i++)
		{
			m_RecodeDevice.AddString(g_PubData.g_strArrayPlaySuccessIp.GetAt(i)); //���IP
		}
		m_RecodeDevice.SetCurSel(0);
		g_PubData.g_iAttributeIng = 0;
	}
	else
	{
		//m_RecodeIp.EnableWindow(FALSE);
		//m_RecodeIp.SetWindowText(_T("û���豸"));
	}
	return TRUE;
}

void CSerachNote::OnBnClickedButtonSerach()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_PubData.g_iAttributeIng < 0)
	{
		//AfxMessageBox(_T("û���豸"));
		return;
	}
	if(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		//AfxMessageBox(_T("û���豸"));
		return;
	}
	ZeroMemory(&m_operationLog, sizeof(JOperationLog));
	//��ѯ����
	CTime dateStart;
	CTime dateEnd;
	CTime timeStart;
	CTime timeEnd;

	m_StartDate.GetTime(dateStart);
	m_StartTime.GetTime(timeStart);
	m_EndDate.GetTime(dateEnd);
	m_EndTime.GetTime(timeEnd);
	
	time_t beg_time = LocalToUtc(dateStart, timeStart);//ת��ΪUTCʱ��
	time_t end_time = LocalToUtc(dateEnd, timeEnd);
	
	m_operationLog.cond.beg_time = (LONG)(beg_time + (8 * 3600));
	m_operationLog.cond.end_time = (LONG)end_time + (8 * 3600);
	m_operationLog.cond.beg_node = m_iBeginNode;
	m_operationLog.cond.end_node = m_iEndNode;
	m_operationLog.cond.sess_id = m_iSsid;
	GetRecodeType(m_RecodeType.GetCurSel());

	if(m_iBeginNode == 0)
	{
		m_ListRecode.DeleteAllItems();
	}

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_OPERATION_LOG, (char *)&m_operationLog, sizeof(m_operationLog),NULL, NULL );
	if (iRet!=0)
	{
		MessageBox(_T("��ȡ��־ʧ��"));
		return ;
	}
	ReFreshWindow();
	//AddToList();
}


void CSerachNote::AddToList()
{
	
	//m_ListRecode.DeleteAllItems();

	int j = m_iBeginNode;
	for(int i = 0; i< (int)m_operationLog.node_count; i++)
	{
		//m_operationLog.item[i].times
		CString strText = _T("");
		time_t times = m_operationLog.item[i].times - (8 * 3600);
		tm local_time;
		localtime_s(&local_time, &times);
		CString strTime = _T("");
		strTime.Format(_T("%d-%2d-%2d %2d:%2d:%2d"),local_time.tm_year + 1900, local_time.tm_mon+1, local_time.tm_mday
											,local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
		m_ListRecode.InsertItem(j, strTime);
		strText = _T("");
		if(m_operationLog.item[i].major_type  == J_LOG_MAJOR_SYSTEM)
		{
			if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_STARTUP)
			{
				strText = _T("����");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_SHUTDOWN)
			{
				strText =_T("�ػ�");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_REBOOT)
			{
				strText =_T("����");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_ALL)
			{
				strText =_T("����ϵͳ��־");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALARM)
		{
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_START)
			{
				strText = _T("����澯����");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_STOP)
			{
				strText =_T("����澯ֹͣ");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_START)
			{
				strText =_T("�ƶ����澯����");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_STOP)
			{
				strText =_T("�ƶ����澯ֹͣ");
			}
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_START)
			{
				strText = _T("��Ƶ��ʧ�澯����");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_STOP)
			{
				strText =_T("��Ƶ��ʧ�澯ֹͣ");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_START)
			{
				strText =_T("��Ƶ�ڵ���������");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_STOP)
			{
				strText =_T("��Ƶ�ڵ�����ֹͣ");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_DISCONN)
			{
				strText =_T("��������");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_RECONN)
			{
				strText =_T("�����ָ�����");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_START)
			{
				strText =_T("�������̽��澯����");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_STOP)
			{
				strText =_T("�������̽��澯ֹͣ");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_ALL)
			{
				strText =_T("���и澯��־");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_OPERATE)
		{			
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGIN)
				{
					strText = _T("��½");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGOUT)
				{
					strText =_T("ע��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_ADD)
				{
					strText =_T("�û�����-����");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_DEL)
				{
					strText =_T("�û�����-ɾ�� ");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_MODI)
				{
					strText = _T("�û�����-�޸�");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_SETTIME)
				{
					strText =_T("����ϵͳʱ��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK)
				{
					strText =_T("��ʽ��Ӳ��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DEFAULT)
				{
					strText =_T("�ָ�Ĭ��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_UPGRADE)
				{
					strText =_T("����");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PLAYBACK)
				{
					strText = _T("�ط�");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PTZ)
				{
					strText =_T("��̨����");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_BACKUP)
				{
					strText =_T("����");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_START)
				{
					strText =_T("����¼��");
				}
				if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_STOP)
				{
					strText = _T("ֹͣ¼��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CLR_ALARM)
				{
					strText =_T("�������");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_START)
				{
					strText =_T("�Խ���ʼ");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_STOP)
				{
					strText =_T("�Խ�����");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_DEL)
				{
					strText =_T("ɾ����־");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_EMPTY)
				{
					strText =_T("�����־");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_BACKUP)
				{
					strText =_T("������־");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_START)
				{
					strText =_T("�ֶ�����¼��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_STOP)
				{
					strText =_T("�ֶ�ֹͣ¼��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK_U)
				{
					strText =_T("��ʽ��U��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CTRL_ALARM_OUT)
				{
					strText =_T("�ֶ����Ʊ������U��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_DEAL_PIX)
				{
					strText =_T("������");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_IRIS)
				{
					strText =_T("��ȦУ��");
				}
				else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_ALL)
				{
					strText =_T("���и澯��־");
				}		 
					 
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_NETWORK)
		{
				strText = _T("������־");
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_PARAM)
		{	 
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NETWORK)
				{
					strText = _T("�����������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UART)
				{
					strText =_T("���ڲ�������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PTZ)
				{
					strText =_T("��̨��������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_CHAN)
				{
					strText =_T("ͨ���������� ");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VENC)
				{
					strText = _T("�����������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_TV)
				{
					strText =_T("TV��������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIC_ATTR)
				{
					strText =_T("ͼ����������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RECORD)
				{
					strText =_T("¼���������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_MOTION)
				{
					strText =_T("�ƶ��������");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VIDEOLOST)
				{
					strText = _T("��Ƶ��ʧ����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMIN)
				{
					strText =_T("����澯����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_POLL)
				{
					strText =_T("��Ѳ����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OVERLAY)
				{
					strText =_T("Ԥ������");
				}
				if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OSD)
				{
					strText = _T("OSD����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_COMM)
				{
					strText =_T("DVR ��������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OD)
				{
					strText =_T("��Ƶ�ڵ�����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ROI)
				{
					strText =_T("����Ȥ��������");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_FTP)
				{
					strText =_T("FTP ���� ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UPNP)
				{
					strText =_T("UPNP ����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_SMTP)
				{
					strText =_T("SMTP ����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NTP)
				{
					strText =_T("NTP ����");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_DDNS)
				{
					strText =_T("DDNS ���� ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMUP)
				{
					strText =_T("�����ϴ����� ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIR)
				{
					strText =_T("�������̽������ ");
				}
				else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RTSP)
				{
					strText =_T("RTSP�������� ");
				}
				else if(m_operationLog.item[i].minor_type == J_PRARM_MINOR_ALL)
				{
					strText =_T("���в�����־");
				}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_EXCEPTION)
		{ 
				if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_FULL)
				{
					strText = _T("Ӳ����");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_ERROR)
				{
					strText =_T("Ӳ�̴���");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_NET_DISCONNECT)
				{
					strText =_T("����Ͽ�");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_IP_CONFLICT)
				{
					strText =_T("IP��ͻ ");
				}
				else if(m_operationLog.item[i].minor_type == J_EXCEPTION_MINOR_ALL)
				{
					strText = _T("�����쳣��־");
				}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALL)
		{
			strText = _T("������־");
		}
		m_ListRecode.SetItemText(j, 1, strText);

		strText = _T("");
		strText.Format(_T("%s"), m_operationLog.item[i].user);
		m_ListRecode.SetItemText(j, 2, strText);

		struct in_addr addr1;
		memcpy(&addr1, &m_operationLog.item[i].ip, 4);

		char strIp[20];
		memset(strIp, '\0', sizeof(strIp));
	
		char *strip = inet_ntoa(addr1);
		strText = _T("");
		strText.Format(_T("%s"), strip);
		m_ListRecode.SetItemText(j, 3, strText);
		j++;
	}
}

void CSerachNote::AddToListEnglish()
{

	//m_ListRecode.DeleteAllItems();

	int j = m_iBeginNode;
	for(int i = 0; i< (int)m_operationLog.node_count; i++)
	{
		//m_operationLog.item[i].times
		CString strText = _T("");
		time_t times = m_operationLog.item[i].times - (8 * 3600);
		tm local_time;
		localtime_s(&local_time, &times);
		CString strTime = _T("");
		strTime.Format(_T("%d-%2d-%2d %2d:%2d:%2d"),local_time.tm_year + 1900, local_time.tm_mon+1, local_time.tm_mday
			,local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
		m_ListRecode.InsertItem(j, strTime);
		strText = _T("");
		if(m_operationLog.item[i].major_type  == J_LOG_MAJOR_SYSTEM)
		{
			if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_STARTUP)
			{
				strText = _T("Starting up");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_SHUTDOWN)
			{
				strText =_T("Shut down");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_REBOOT)
			{
				strText =_T("Restar");
			}
			else if(m_operationLog.item[i].minor_type == J_SYSTEM_MINOR_ALL)
			{
				strText =_T("All the system log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALARM)
		{
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_START)
			{
				strText = _T("Input alarm start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_DI_STOP)
			{
				strText =_T("Input alarm end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_START)
			{
				strText =_T("Mobile detection alarm start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_MD_STOP)
			{
				strText =_T("Mobile detection alarm end");
			}
			if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_START)
			{
				strText = _T("Video loss start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_VL_STOP)
			{
				strText =_T("Video loss end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_START)
			{
				strText =_T("Video occlusion start");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_OD_STOP)
			{
				strText =_T("Video occlusion end");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_DISCONN)
			{
				strText =_T("Network disconnection");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_NETCARD_RECONN)
			{
				strText =_T("Card recovery.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_START)
			{
				strText =_T("The human body infrared detection alarm.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_PIR_STOP)
			{
				strText =_T("The human body infrared detection alarm stop.");
			}
			else if(m_operationLog.item[i].minor_type == J_ALARM_MINOR_ALL)
			{
				strText =_T("All alarm log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_OPERATE)
		{			
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGIN)
			{
				strText = _T("Login");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOGOUT)
			{
				strText =_T("Cancellation");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_ADD)
			{
				strText =_T("User management and increase");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_DEL)
			{
				strText =_T("User management and delete ");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_USER_MODI)
			{
				strText = _T("User management and modify");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_SETTIME)
			{
				strText =_T("Set the system time");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK)
			{
				strText =_T("Disk formatting");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DEFAULT)
			{
				strText =_T("Restore default");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_UPGRADE)
			{
				strText =_T("upgrade");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PLAYBACK)
			{
				strText = _T("Playback");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_PTZ)
			{
				strText =_T("PTZ");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_BACKUP)
			{
				strText =_T("Backup");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_START)
			{
				strText =_T("Start recording");
			}
			if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_RECORD_STOP)
			{
				strText = _T("End recording");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CLR_ALARM)
			{
				strText =_T("Claear alarm");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_START)
			{
				strText =_T("Talkback began");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_TALKBACK_STOP)
			{
				strText =_T("Intercom end");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_DEL)
			{
				strText =_T("Delete log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_EMPTY)
			{
				strText =_T("clear log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_LOG_BACKUP)
			{
				strText =_T("Backup log");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_START)
			{
				strText =_T("Manual start the video");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_MANUAL_RECORD_STOP)
			{
				strText =_T("Manual stop recording");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_FORMAT_DISK_U)
			{
				strText =_T("The disk U");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_CTRL_ALARM_OUT)
			{
				strText =_T("Alarm output U wheel for manual control");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_DEAL_PIX)
			{
				strText =_T("Bad pixel detection");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_DETECT_IRIS)
			{
				strText =_T("Aperture correction");
			}
			else if(m_operationLog.item[i].minor_type == J_OPERATE_MINOR_ALL)
			{
				strText =_T("All alarm log");
			}		 

		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_NETWORK)
		{
			strText = _T("Web log");
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_PARAM)
		{	 
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NETWORK)
			{
				strText = _T("Network parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UART)
			{
				strText =_T("Serial port parameter settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PTZ)
			{
				strText =_T("PTZ parameter settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_CHAN)
			{
				strText =_T("Channel parameter setting ");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VENC)
			{
				strText = _T("Encode parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_TV)
			{
				strText =_T("TV parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIC_ATTR)
			{
				strText =_T("Img parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RECORD)
			{
				strText =_T("Record parameter setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_MOTION)
			{
				strText =_T("Mobile detection settings");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_VIDEOLOST)
			{
				strText = _T("Lost video settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMIN)
			{
				strText =_T("Input alarm setting");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_POLL)
			{
				strText =_T("A round robin set");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OVERLAY)
			{
				strText =_T("Preview settings");
			}
			if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OSD)
			{
				strText = _T("OSD settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_COMM)
			{
				strText =_T("DVR settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_OD)
			{
				strText =_T("Video block set");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ROI)
			{
				strText =_T("Interest Area");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_FTP)
			{
				strText =_T("FTP settings ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_UPNP)
			{
				strText =_T("UPNP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_SMTP)
			{
				strText =_T("SMTP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_NTP)
			{
				strText =_T("NTP settings");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_DDNS)
			{
				strText =_T("DDNS settings ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_ALARMUP)
			{
				strText =_T("Upload alarm ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_PIR)
			{
				strText =_T("The human body infrared probe configuration ");
			}
			else if(m_operationLog.item[i].minor_type == J_PARAM_MINOR_PARAM_RTSP)
			{
				strText =_T("The RTSP service configuration");
			}
			else if(m_operationLog.item[i].minor_type == J_PRARM_MINOR_ALL)
			{
				strText =_T("All parameter log ");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_EXCEPTION)
		{ 
			if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_FULL)
			{
				strText = _T("The disk is full");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_HD_ERROR)
			{
				strText =_T("A disk error");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_NET_DISCONNECT)
			{
				strText =_T("Network disconnection");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_IP_CONFLICT)
			{
				strText =_T("IP conflict ");
			}
			else if(m_operationLog.item[i].minor_type == J_EXCEPTION_MINOR_ALL)
			{
				strText = _T("All abnormal log");
			}
		}
		else if(m_operationLog.item[i].major_type == J_LOG_MAJOR_ALL)
		{
			strText = _T("All log");
		}
		m_ListRecode.SetItemText(j, 1, strText);

		strText = _T("");
		strText.Format(_T("%s"), m_operationLog.item[i].user);
		m_ListRecode.SetItemText(j, 2, strText);

		struct in_addr addr1;
		memcpy(&addr1, &m_operationLog.item[i].ip, 4);

		char strIp[20];
		memset(strIp, '\0', sizeof(strIp));

		char *strip = inet_ntoa(addr1);
		strText = _T("");
		strText.Format(_T("%s"), strip);
		m_ListRecode.SetItemText(j, 3, strText);
		j++;
	}
}
time_t CSerachNote::LocalToUtc(CTime dateStart, CTime timeStart)
{
	tm UtcTime;
	dateStart.GetGmtTm(&UtcTime);

	UtcTime.tm_hour = timeStart.GetHour();
	UtcTime.tm_min = timeStart.GetMinute();
	UtcTime.tm_sec = timeStart.GetSecond();
	return mktime(&UtcTime);
}

void CSerachNote::GetRecodeType(int iIndex)
{ 

	if(iIndex == 0)
	{
		m_operationLog.cond.type = J_LOG_MAJOR_SYSTEM;
	}
	else if(iIndex ==1)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_ALARM;
	}
	else if(iIndex ==2)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_OPERATE;
	}
	else if(iIndex ==3)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_NETWORK;
	}
	else if(iIndex ==4)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_PARAM;
	}
	else if(iIndex ==5)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_EXCEPTION;
	}
	else if(iIndex ==6)
	{	
		m_operationLog.cond.type = J_LOG_MAJOR_ALL;
	}
	
}

int CSerachNote::ReFreshWindow()
{
	if(g_PubData.g_iLanguageFlag == 0)
		AddToList();
	else
		AddToListEnglish();
	if(m_iEndNode < (int)m_operationLog.total_count)
	{
		m_iBeginNode += 32;
		m_iEndNode += 32;
		m_iSsid = m_operationLog.cond.sess_id;
		OnBnClickedButtonSerach();
	}
	else
	{
		m_iBeginNode = 0;
		m_iEndNode = 31;
		m_iSsid = -1;
	}
	return 0;
}
void CSerachNote::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CSerachNote::OnCbnSelchangeComboRecodedevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_PubData.g_iAttributeIng = m_RecodeDevice.GetCurSel();
}
