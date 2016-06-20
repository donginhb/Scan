// DeviceState.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "DeviceState.h"
#include "Pub_Data.h"


// CDeviceState �Ի���


IMPLEMENT_DYNAMIC(CDeviceState, CDialog)

CDeviceState::CDeviceState(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceState::IDD, pParent)
{
	ZeroMemory(&m_DevWorkState, sizeof(m_DevWorkState));
}

CDeviceState::~CDeviceState()
{
	DestroyWindow();
}

void CDeviceState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE_STATE, m_DeviceState);
	DDX_Control(pDX, IDC_COMBO_LOCOLSHOW, m_LocalShow);
	DDX_Control(pDX, IDC_LIST_DISKSTATE, m_ListDiskState);
	DDX_Control(pDX, IDC_LIST_CHANNELSTATE, m_ListChannelState);
}


BEGIN_MESSAGE_MAP(CDeviceState, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CDeviceState::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDeviceState::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDeviceState ��Ϣ�������
BOOL CDeviceState::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_DeviceState.AddString(_T("����"));
		m_DeviceState.AddString(_T("CPUʹ���ʹ���"));

		m_LocalShow.AddString(_T("����"));
		m_LocalShow.AddString(_T("������"));

		m_ListDiskState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListDiskState.InsertColumn(0 , _T("Ӳ������"), 2, 100, -1);
		m_ListDiskState.InsertColumn(1 , _T("Ӳ��ʣ��ռ�"), 2, 100,-1);
		m_ListDiskState.InsertColumn(2 , _T("Ӳ��״̬"), 2, 200,-1);

		m_ListChannelState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListChannelState.InsertColumn(0 , _T("�Ƿ�¼��"), 2, 80, -1);
		m_ListChannelState.InsertColumn(1 , _T("�ź�״̬"), 2, 80,-1);
		m_ListChannelState.InsertColumn(2 , _T("ͨ��Ӳ��״̬"), 2, 80,-1);
		m_ListChannelState.InsertColumn(3 , _T("ʵ������"), 2, 80, -1);
		m_ListChannelState.InsertColumn(4 , _T("����ͨ��״̬"), 2, 80, -1);
		m_ListChannelState.InsertColumn(5 , _T("���������״̬"), 2, 80, -1);
		m_ListChannelState.InsertColumn(6 , _T("���������״̬"), 2, 80, -1);
	}
	else
	{
		m_DeviceState.AddString(_T("Normal"));
		m_DeviceState.AddString(_T("High CPU usage"));

		m_LocalShow.AddString(_T("Normal"));
		m_LocalShow.AddString(_T("Not normal"));

		m_ListDiskState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListDiskState.InsertColumn(0 , _T("Hard disk capacity"), 2, 100, -1);
		m_ListDiskState.InsertColumn(1 , _T("Hard disk space"), 2, 100,-1);
		m_ListDiskState.InsertColumn(2 , _T("The hard state"), 2, 200,-1);

		m_ListChannelState.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
		m_ListChannelState.InsertColumn(0 , _T("Whether the video"), 2, 80, -1);
		m_ListChannelState.InsertColumn(1 , _T("Channel state"), 2, 80,-1);
		m_ListChannelState.InsertColumn(2 , _T("Channel hardware status"), 2, 80,-1);
		m_ListChannelState.InsertColumn(3 , _T("The actual rate"), 2, 80, -1);
		m_ListChannelState.InsertColumn(4 , _T("Voice channel state"), 2, 80, -1);
		m_ListChannelState.InsertColumn(5 , _T("Alarm input state"), 2, 80, -1);
		m_ListChannelState.InsertColumn(6 , _T("Alarm output status"), 2, 80, -1);
	}


	return TRUE;
}


void CDeviceState::ShowWndData()
{
	m_DeviceState.SetCurSel(m_DevWorkState.device_static);

	int iIndex = -1;
	CString strText = _T("");
	m_LocalShow.SetCurSel(m_DevWorkState.local_display);



	strText = _T("");
	m_ListDiskState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_DISK_NUMBER; i++)
	{
		if(m_DevWorkState.hd_static[i].volume <= 0)
		{
			break;
		}
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].volume);
		m_ListDiskState.InsertItem(i, strText);
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].free_space);
		m_ListDiskState.SetItemText(i, 1, strText);

		if(m_DevWorkState.hd_static[i].hd_static == 0)
		{
			strText = _T("����ʹ��");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 1)
		{
			strText = _T("δ����");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 2)
		{
			strText = _T("�ѹ���δʹ��");
		}
		m_ListDiskState.SetItemText(i, 2, strText);
	}
	/*uint8_t  record_static;						//ͨ���Ƿ���¼��0����¼��1��¼�� 
	uint8_t  signal_static;						//���ӵ��ź�״̬��0��������  1���źŶ�ʧ  
	uint8_t  hardware_static;					//ͨ��Ӳ��״̬��  0��������  1���쳣������DSP�쳣�� 
	uint8_t  res1;
	uint32_t bit_rate[J_SDK_MAX_STREAM_SIZE];	//ʵ������ */
	m_ListChannelState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_CHN_SIZE; i++)
	{
		if(i > 0)
		{
			break;
		}
		if(m_DevWorkState.chn_static[i].record_static == 0)
		{
			strText = _T("��");
		}
		else if(m_DevWorkState.chn_static[i].record_static == 1)
		{
			strText = _T("��");
		}
		m_ListChannelState.InsertItem(i, strText);
		//strText.Format(_T("%d"), m_DevWorkState.chn_static[i].signal_static);
		if(m_DevWorkState.chn_static[i].signal_static == 0)
		{
			strText = _T("����");
		}
		else if(m_DevWorkState.chn_static[i].signal_static == 1)
		{
			strText = _T("�źŶ�ʧ");
		}
		m_ListChannelState.SetItemText(i, 1, strText);
		if(m_DevWorkState.chn_static[i].hardware_static == 0)
		{
			strText = _T("����");
		}
		else if(m_DevWorkState.chn_static[i].hardware_static == 1)
		{
			strText = _T("�쳣");
		}
		m_ListChannelState.SetItemText(i, 2, strText);

		int iIndex = g_PubData.g_iStreamType[g_PubData.g_iAttributeIng];
		strText.Format(_T("%d"), m_DevWorkState.chn_static[i].bit_rate[iIndex-1]);
		m_ListChannelState.SetItemText(i, 3, strText);

		strText.Format(_T("%d"), m_DevWorkState.audio_chn_status[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("δʹ��");
		}
		else if(iIndex == 1)
		{
			strText = _T("ʹ����");
		}
		else if(iIndex == 0xff)
		{
			strText = _T("��Ч");
		}
		m_ListChannelState.SetItemText(i, 4, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_in_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("û�б���");
		}
		else if(iIndex == 1)
		{
			strText = _T("�б���");
		}
		m_ListChannelState.SetItemText(i, 5, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_out_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("û�б���");
		}
		else if(iIndex == 1)
		{
			strText = _T("�б���");
		}
		m_ListChannelState.SetItemText(i, 6, strText);

	}
}

void CDeviceState::ShowWndDataEnglish()
{
	m_DeviceState.SetCurSel(m_DevWorkState.device_static);

	int iIndex = -1;
	CString strText = _T("");
	m_LocalShow.SetCurSel(m_DevWorkState.local_display);



	strText = _T("");
	m_ListDiskState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_DISK_NUMBER; i++)
	{
		if(m_DevWorkState.hd_static[i].volume <= 0)
		{
			break;
		}
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].volume);
		m_ListDiskState.InsertItem(i, strText);
		strText.Format(_T("%d"),m_DevWorkState.hd_static[i].free_space);
		m_ListDiskState.SetItemText(i, 1, strText);

		if(m_DevWorkState.hd_static[i].hd_static == 0)
		{
			strText = _T("Is in use");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 1)
		{
			strText = _T("Unmounted");
		}
		else if(m_DevWorkState.hd_static[i].hd_static == 2)
		{
			strText = _T("The unused");
		}
		m_ListDiskState.SetItemText(i, 2, strText);
	}
	/*uint8_t  record_static;						//ͨ���Ƿ���¼��0����¼��1��¼�� 
	uint8_t  signal_static;						//���ӵ��ź�״̬��0��������  1���źŶ�ʧ  
	uint8_t  hardware_static;					//ͨ��Ӳ��״̬��  0��������  1���쳣������DSP�쳣�� 
	uint8_t  res1;
	uint32_t bit_rate[J_SDK_MAX_STREAM_SIZE];	//ʵ������ */
	m_ListChannelState.DeleteAllItems();
	for(int i = 0; i< J_SDK_MAX_CHN_SIZE; i++)
	{
		if(i > 0)
		{
			break;
		}
		if(m_DevWorkState.chn_static[i].record_static == 0)
		{
			strText = _T("No");
		}
		else if(m_DevWorkState.chn_static[i].record_static == 1)
		{
			strText = _T("Yes");
		}
		m_ListChannelState.InsertItem(i, strText);
		//strText.Format(_T("%d"), m_DevWorkState.chn_static[i].signal_static);
		if(m_DevWorkState.chn_static[i].signal_static == 0)
		{
			strText = _T("Normal");
		}
		else if(m_DevWorkState.chn_static[i].signal_static == 1)
		{
			strText = _T("Loss of signal");
		}
		m_ListChannelState.SetItemText(i, 1, strText);
		if(m_DevWorkState.chn_static[i].hardware_static == 0)
		{
			strText = _T("Normal");
		}
		else if(m_DevWorkState.chn_static[i].hardware_static == 1)
		{
			strText = _T("Abnormal");
		}
		m_ListChannelState.SetItemText(i, 2, strText);

		int iIndex = g_PubData.g_iStreamType[g_PubData.g_iAttributeIng];
		strText.Format(_T("%d"), m_DevWorkState.chn_static[i].bit_rate[iIndex-1]);
		m_ListChannelState.SetItemText(i, 3, strText);

		strText.Format(_T("%d"), m_DevWorkState.audio_chn_status[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("Not used");
		}
		else if(iIndex == 1)
		{
			strText = _T("In use");
		}
		else if(iIndex == 0xff)
		{
			strText = _T("Invalid");
		}
		m_ListChannelState.SetItemText(i, 4, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_in_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("No alarm");
		}
		else if(iIndex == 1)
		{
			strText = _T("Alarm");
		}
		m_ListChannelState.SetItemText(i, 5, strText);

		strText.Format(_T("%d"), m_DevWorkState.alarm_out_static[i]);
		iIndex = _ttoi(strText);
		if(iIndex == 0)
		{
			strText = _T("No alarm");
		}
		else if(iIndex == 1)
		{
			strText = _T("Alarm");
		}
		m_ListChannelState.SetItemText(i, 6, strText);

	}
}
void CDeviceState::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������

	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEV_WORK_STATE, (char *)&m_DevWorkState, sizeof(m_DevWorkState),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	if(g_PubData.g_iLanguageFlag == 0)
	{
		ShowWndData();
	}
	else
	{
		ShowWndDataEnglish();
	}
	
}

void CDeviceState::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDeviceState::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}
