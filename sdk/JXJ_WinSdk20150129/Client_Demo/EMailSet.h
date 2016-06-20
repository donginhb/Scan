#pragma once
#include "afxwin.h"


// CEMailSet �Ի���

class CEMailSet : public CDialog
{
	DECLARE_DYNAMIC(CEMailSet)

public:
	CEMailSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEMailSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_EMAIL_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit		m_SmtpServer;
	CEdit		m_EmailAddr;
	CEdit		m_SmtpUser;
	CEdit		m_SmtpPassword;
	CEdit		m_SmtpPort;
	CEdit		m_EmailResive1;
	CEdit		m_EmailResive2;
	CEdit		m_EmailResive3;
	CButton		m_SSL;
	

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();


	int ReFreshWindow();
private:
	JSMTPParameter  m_smtpParam;
};
