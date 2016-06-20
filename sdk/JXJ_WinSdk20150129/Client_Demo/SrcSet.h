#pragma once
#include "afxwin.h"


// CSrcSet �Ի���

class CSrcSet : public CDialog
{
	DECLARE_DYNAMIC(CSrcSet)

public:
	CSrcSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSrcSet();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTakeapicture();
	afx_msg void OnBnClickedButtonRecodesrc();
	CEdit m_TakeAPictureSrc;
	CEdit m_RecodeSrc;

	CString OpenFileSrc();         //���ļ�·��
	void InitWnd();

	CString m_strTakeApictureSrc;
	CString m_strRecodeSrc;
	CString m_strDownLoadSrc;
	int m_iMode;
	int m_iLanguageFlag;
	CString m_strPort;
	CString m_strSPort;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	CButton m_ServerCheck;
	CButton m_ClientCheck;
	CEdit m_EPort;
	CEdit m_eSport;
	afx_msg void OnBnClickedCheckServer();
	afx_msg void OnBnClickedCheckClient();
	CEdit m_downLoadSrc;
	afx_msg void OnBnClickedButtonDownsrc();
	CComboBox m_language;
};
