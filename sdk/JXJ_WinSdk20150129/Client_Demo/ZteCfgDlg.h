#pragma once
#include "afxwin.h"


// CZteCfgDlg �Ի���

class CZteCfgDlg : public CDialog
{
	DECLARE_DYNAMIC(CZteCfgDlg)

public:
	CZteCfgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZteCfgDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ZTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton			m_enableZTE;
	CEdit			m_id;
	CEdit			m_userName;
	CEdit			m_password;
	CEdit			m_ip;
	CEdit			m_port;

	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonSave();

	int				ReFreshWindow();
private:
	JZtePfCfg		m_ztePfCfg;

};
