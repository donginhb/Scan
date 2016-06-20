#pragma once
#include "afxcmn.h"


// CSerachWifi �Ի���

class CSerachWifi : public CDialog
{
	DECLARE_DYNAMIC(CSerachWifi)

public:
	CSerachWifi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerachWifi();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERACH_WIFI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl				m_WifiList;


	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnNMDblclkListWifi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	int						ReFreshWifiWindow();
	int						ReFreshConnectWindow();
	void					GetWifiState();
	void					ControlWifi(int iIndex, int iState, CString strPassword);
private:
	JWifiSearchRes			m_wifiSerach;
	JWifiConfig				m_wifiConfig;
	int						m_WifiState;  
	CString					m_wifiPassword;
	CString					m_strSid;

};
