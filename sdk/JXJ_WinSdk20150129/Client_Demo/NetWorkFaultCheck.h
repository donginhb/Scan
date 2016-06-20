#pragma once
#include "afxwin.h"


// CNetWorkFaultCheck �Ի���

class CNetWorkFaultCheck : public CDialog
{
	DECLARE_DYNAMIC(CNetWorkFaultCheck)

public:
	CNetWorkFaultCheck(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetWorkFaultCheck();

// �Ի�������
	enum { IDD = IDD_DIALOG_NetWorkFaultCheck };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton			m_StartNetWorkFault;
	CButton			m_StartWifi;
	CButton			m_Start3G;
	CComboBox		m_CableNetWork;
	CButton			m_StartCableNetWork;
	CButton			m_StartAllCableNetWork;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedCheckStartnetworkfault();
	afx_msg void OnCbnSelchangeComboCablenetwork();
	afx_msg void OnBnClickedCheckStartallcable();

	int			ReFreshWindow();

private:
	JNetWorkFaultCheck			m_NetWorkFault;
};
