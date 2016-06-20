#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSerchDevice �Ի���

class CSerchDevice : public CDialog
{
	DECLARE_DYNAMIC(CSerchDevice)

public:
	CSerchDevice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerchDevice();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERCH_DEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	
	
public:

	long m_hBhandle;
	bool m_bSerachDevice;
	CListCtrl m_listSerchDevice;
	afx_msg void OnBnClickedButtonSerachdevice();
	static  DWORD SerachDeviceClose(LPVOID lpThreadParameter);
	CEdit m_eDeviceName;
	CEdit m_eDeviceIp;
	CEdit m_eDevicePort;
	CEdit m_eUserName;
	CEdit m_eUserPassword;
	bool m_bIsAdd;        //�Ƿ����
	afx_msg void OnNMDblclkListDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnLvnColumnclickListDevice(NMHDR *pNMHDR, LRESULT *pResult);

	void ListSort(int index);   //��ѯ�������豸����
	void IpSort(CString strIp1, CString strIp2);
	void ReplaceCstring(CString &str1, CString &str2);
	CString m_strIp;  //�㱣����豸ip
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	static int __stdcall OnMBNotify(long lHandle,DWORD dwProtocol,int iErr,int iMsgID,LPCTSTR lpszDstID,void* pData,int iDataLen,void* pUserParam);	// �㲥�ص�
	int InsertDevListItem();
	CString GetDeviceType(int i);

	DevConfig m_devConfig;
	afx_msg void OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult);
};
