// WifiConnect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "WifiConnect.h"


// CWifiConnect �Ի���

IMPLEMENT_DYNAMIC(CWifiConnect, CDialog)

CWifiConnect::CWifiConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CWifiConnect::IDD, pParent)
{

}

CWifiConnect::~CWifiConnect()
{

}

void CWifiConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WIFIPASSWORD, m_WifiPassword);
}


BEGIN_MESSAGE_MAP(CWifiConnect, CDialog)
	ON_BN_CLICKED(IDOK, &CWifiConnect::OnBnClickedOk)
END_MESSAGE_MAP()


// CWifiConnect ��Ϣ�������
BOOL CWifiConnect::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

void CWifiConnect::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_WifiPassword.GetWindowText(m_StrPassword);
	OnOK();
}
