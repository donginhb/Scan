// DNSSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "DNSSet.h"
#include "Pub_Data.h"


// CDNSSet �Ի���


IMPLEMENT_DYNAMIC(CDNSSet, CDialog)

CDNSSet::CDNSSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDNSSet::IDD, pParent)
{
	ZeroMemory(&m_dnsconfig, sizeof(m_dnsconfig));
}

CDNSSet::~CDNSSet()
{
	DestroyWindow();
}

void CDNSSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTDDNS, m_StartDDNS);
	DDX_Control(pDX, IDC_COMBO_DDNSTYPE, m_DdnsType);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_PassWord);
	DDX_Control(pDX, IDC_EDIT_AREA, m_Area);
	DDX_Control(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Control(pDX, IDC_COMBO_UPDATETIME, m_UpdateTime);
}


BEGIN_MESSAGE_MAP(CDNSSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDNSSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CDNSSet::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CDNSSet::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT_AREA, &CDNSSet::OnEnChangeEditArea)
	ON_CBN_SELCHANGE(IDC_COMBO_DDNSTYPE, &CDNSSet::OnCbnSelchangeComboDdnstype)
END_MESSAGE_MAP()


// CDNSSet ��Ϣ�������
BOOL CDNSSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_DdnsType.AddString(_T("dyndns"));
	m_DdnsType.AddString(_T("3322"));
	m_DdnsType.AddString(_T("withcctv.com"));


	for(int i = 1;i< 49; i++)
	{
		CString str;
		str.Format(_T("%d"),i);
		m_UpdateTime.AddString(str);
	}

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	return TRUE;

}

void CDNSSet::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText(_T(""));

	m_dnsconfig.ddns_open = m_StartDDNS.GetCheck();

	m_dnsconfig.ddns_type = m_DdnsType.GetCurSel();

	m_UserName.GetWindowText(strText);
	memset(m_dnsconfig.ddns_usr, '\0', sizeof(m_dnsconfig.ddns_usr));
	memcpy(m_dnsconfig.ddns_usr, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_PassWord.GetWindowText(strText);
	memset(m_dnsconfig.ddns_pwd, '\0', sizeof(m_dnsconfig.ddns_pwd));
	memcpy(m_dnsconfig.ddns_pwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_Area.GetWindowText(strText);
	memset(m_dnsconfig.ddns_account, '\0', sizeof(m_dnsconfig.ddns_account));
	memcpy(m_dnsconfig.ddns_account, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_Port.GetWindowText(strText);
	m_dnsconfig.ddns_port = _ttoi(strText);

	m_dnsconfig.ddns_times = m_UpdateTime.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DDNS_CODING, (char *)&m_dnsconfig, sizeof(m_dnsconfig), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return;
	}
}

void CDNSSet::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, PARAM_DDNS_CODING, (char *)&m_dnsconfig, sizeof(m_dnsconfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}
	
}


int CDNSSet::ReFreshWindow()
{
	CString strText(_T(""));

	m_StartDDNS.SetCheck(m_dnsconfig.ddns_open);

	m_DdnsType.SetCurSel(m_dnsconfig.ddns_type);

	strText.Format(_T("%s"), m_dnsconfig.ddns_usr);
	m_UserName.SetWindowText(strText);

	strText.Format(_T("%s"), m_dnsconfig.ddns_pwd);
	m_PassWord.SetWindowText(strText);
	
	strText.Format(_T("%s"), m_dnsconfig.ddns_account);
	m_Area.SetWindowText(strText);

	strText.Format(_T("%d"), m_dnsconfig.ddns_port);
	m_Port.SetWindowText(strText);

	m_UpdateTime.SetCurSel(m_dnsconfig.ddns_times);

	OnCbnSelchangeComboDdnstype();

	return 0;
}
void CDNSSet::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CDNSSet::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strText;
	m_Area.GetWindowText(strText);
	memset(m_dnsconfig.ddns_account, '\0', sizeof(m_dnsconfig.ddns_account));
	memcpy(m_dnsconfig.ddns_account, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();
	m_dnsconfig.ddns_type = m_DdnsType.GetCurSel();
	m_dnsconfig.check_account = 1;

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, PARAM_DDNS_CODING, (char *)&m_dnsconfig, sizeof(m_dnsconfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}

	ReFreshWindow();
}



void CDNSSet::OnEnChangeEditArea()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDNSSet::OnCbnSelchangeComboDdnstype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_DdnsType.GetCurSel() == 2)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	}
}
