#pragma once
#include "afxwin.h"


// CCloudSet �Ի���

class CCloudSet : public CDialog
{
	DECLARE_DYNAMIC(CCloudSet)

public:
	CCloudSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCloudSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_CLOUD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CComboBox	m_Channel;
	CComboBox	m_Protocol;
	CComboBox	m_SerialType;
	CComboBox	m_CheckBit;
	CEdit		m_CloudRate;
	CEdit		m_CloudDataBit;
	CEdit		m_CloudStopBit;
	CEdit		m_eAddressStream;



	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	int ReFreshWindow();
	

private:
	JPTZParameter		m_ptzParamer;
};
