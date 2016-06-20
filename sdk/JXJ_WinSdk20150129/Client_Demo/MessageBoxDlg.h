#pragma once
#include "resource.h"

// CMessageBoxDlg �Ի���

class CMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CMessageBoxDlg)

public:
	CMessageBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageBoxDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	int m_iRet;
	CString m_strTitle;
	CString m_strMsg;

	void SetWndText(CString strTitle, CString strMsg);
};
