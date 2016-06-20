#pragma once
#include "afxwin.h"


// CDeviceUserDlg �Ի���

class CDeviceUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceUserDlg)

public:
	CDeviceUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceUserDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEVICE_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit		m_eUser;
	CEdit		m_ePassword;
	CEdit		m_NewUser;
	CEdit		m_NewPassword;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	
	int				ReFreshWindow();
private:
	JUserConfig		m_userconfig;
};
