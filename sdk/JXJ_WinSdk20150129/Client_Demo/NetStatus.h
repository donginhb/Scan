#pragma once
#include "afxwin.h"


// CNetStatus �Ի���

class CNetStatus : public CDialog
{
	DECLARE_DYNAMIC(CNetStatus)

public:
	CNetStatus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetStatus();

// �Ի�������
	enum { IDD = IDD_DIALOG_NET_CONNECT_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_LimitStatus;
	CComboBox m_WireLessStatus;
	CComboBox m_PppoeStatus;
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();

	int		ReFreshWindow();


private:
	JNetworkStatus		m_netStatus;
};
