// HwSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HwSetDlg.h"
#include "Pub_Data.h"

// CHwSetDlg �Ի���

IMPLEMENT_DYNAMIC(CHwSetDlg, CDialog)

CHwSetDlg::CHwSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHwSetDlg::IDD, pParent)
{
	ZeroMemory(&m_hwcfg, sizeof(m_hwcfg));
}

CHwSetDlg::~CHwSetDlg()
{
}

void CHwSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_hwDeviceId);
	DDX_Control(pDX, IDC_EDIT2, m_hwDevicePwd);
	DDX_Control(pDX, IDC_EDIT3, m_localMsgPort);
	DDX_Control(pDX, IDC_EDIT4, m_hwServerIp);
	DDX_Control(pDX, IDC_EDIT5, m_hwServerAddr);
	DDX_Control(pDX, IDC_EDIT6, m_hwServerPort);
	DDX_Control(pDX, IDC_COMBO_SERVERAREA, m_ServerArea);
}


BEGIN_MESSAGE_MAP(CHwSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHwSetDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CHwSetDlg::OnBnClickedButtonFlash)
END_MESSAGE_MAP()


// CHwSetDlg ��Ϣ�������
BOOL CHwSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�㶫"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�ӱ�"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("������"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("���ɹ�"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�ຣ"));
	m_ServerArea.AddString(_T("ɽ��"));
	m_ServerArea.AddString(_T("ɽ��"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�Ϻ�"));
	m_ServerArea.AddString(_T("�Ĵ�"));
	m_ServerArea.AddString(_T("���"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�½�"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("�㽭"));
	m_ServerArea.AddString(_T("���"));
	m_ServerArea.AddString(_T("����"));
	m_ServerArea.AddString(_T("̨��"));
	
	return TRUE;
}

void CHwSetDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strText;

	m_hwDeviceId.GetWindowText(strText);
	memset(m_hwcfg.device_id, 0, sizeof(m_hwcfg.device_id));
	memcpy(m_hwcfg.device_id, strText.GetBuffer(0), strText.GetLength());

	m_hwDevicePwd.GetWindowText(strText);
	memset(m_hwcfg.device_pwd, 0, sizeof(m_hwcfg.device_pwd));
	memcpy(m_hwcfg.device_pwd, strText.GetBuffer(0), strText.GetLength());

	m_localMsgPort.GetWindowText(strText);
	m_hwcfg.msg_port = _ttoi(strText);


	m_hwcfg.server_area = m_ServerArea.GetCurSel() + 1;

	m_hwServerIp.GetWindowText(strText);
	memset(m_hwcfg.server_id, 0, sizeof(m_hwcfg.server_id));
	memcpy(m_hwcfg.server_id, strText.GetBuffer(0), strText.GetLength());

	m_hwServerAddr.GetWindowText(strText);
	memset(m_hwcfg.server_ip, 0, sizeof(m_hwcfg.server_ip));
	memcpy(m_hwcfg.server_ip, strText.GetBuffer(0), strText.GetLength());

	m_hwServerPort.GetWindowText(strText);
	m_hwcfg.server_port = _ttoi(strText);
	
	strText.ReleaseBuffer();


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HW_PF_CFG, (char *)&m_hwcfg, sizeof(m_hwcfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
}

void CHwSetDlg::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_HW_PF_CFG, (char *)&m_hwcfg, sizeof(m_hwcfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}

int CHwSetDlg::ReFreshWindow()
{
	CString strText;
	strText.Format(_T("%s"), m_hwcfg.device_id);
	m_hwDeviceId.SetWindowText(strText);

	strText.Format(_T("%s"), m_hwcfg.device_pwd);
	m_hwDevicePwd.SetWindowText(strText);

	strText.Format(_T("%d"), m_hwcfg.msg_port);
	m_localMsgPort.SetWindowText(strText);

	m_ServerArea.SetCurSel(m_hwcfg.server_area - 1);

	strText.Format(_T("%s"), m_hwcfg.server_id);
	m_hwServerIp.SetWindowText(strText);

	strText.Format(_T("%s"), m_hwcfg.server_ip);
	m_hwServerAddr.SetWindowText(strText);

	strText.Format(_T("%d"), m_hwcfg.server_port);
	m_hwServerPort.SetWindowText(strText);

	return 0;
}

