#pragma once
#include "afxwin.h"


// CFTPSet �Ի���

class CFTPSet : public CDialog
{
	DECLARE_DYNAMIC(CFTPSet)

public:
	CFTPSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFTPSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_FTP_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	
	CEdit	m_FtpIp;
	CEdit	m_FtpPort;
	CEdit	m_FtpPath;
	CEdit	m_FtpUser;
	CEdit	m_FtpPassword;



	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int		ReFreshWindow();


private:
	JFTPParameter	m_ftpParam;
};
