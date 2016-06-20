#pragma once
#include "afxwin.h"


// CDNSSet �Ի���

class CDNSSet : public CDialog
{
	DECLARE_DYNAMIC(CDNSSet)

public:
	CDNSSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDNSSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_DNS_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton			m_StartDDNS;
	CComboBox		m_DdnsType;
	CEdit			m_UserName;
	CEdit			m_PassWord;
	CEdit			m_Area;
	CEdit			m_Port;
	CComboBox		m_UpdateTime;


	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEditArea();
	afx_msg void OnCbnSelchangeComboDdnstype();

	int ReFreshWindow();


private:
	JDdnsConfig		m_dnsconfig;
};
