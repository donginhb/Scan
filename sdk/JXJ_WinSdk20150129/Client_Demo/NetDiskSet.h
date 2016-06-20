#pragma once
#include "afxwin.h"


// CNetDiskSet �Ի���

class CNetDiskSet : public CDialog
{
	DECLARE_DYNAMIC(CNetDiskSet)

public:
	CNetDiskSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetDiskSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_NET_DISK_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CButton				m_StartNetDisk;
	CComboBox			m_comProtocol;
	CEdit				m_DiskIp;
	CEdit				m_DiskPort;
	CEdit				m_StartMachineName;
	CEdit				m_DiskName;
	CComboBox			m_RZType;
	CEdit				m_RZuser;
	CEdit				m_RZpass;
	CComboBox			m_LoginRZtype;
	CEdit				m_LoginRZuser;
	CEdit				m_LoginRZpass;



	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();

	int			 ReFreshWindow();


private:
	JNetworkDisk	m_netDisk;
};
