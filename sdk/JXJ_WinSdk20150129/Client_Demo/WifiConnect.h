#pragma once
#include "afxwin.h"


// CWifiConnect �Ի���

class CWifiConnect : public CDialog
{
	DECLARE_DYNAMIC(CWifiConnect)

public:
	CWifiConnect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWifiConnect();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONNECT_WIFI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_WifiPassword;
	int m_WifiState;
	CString m_StrPassword;
	afx_msg void OnBnClickedOk();
};
