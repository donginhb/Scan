
// DaHuaFindDevicesDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

namespace DH
{
#include "DHVideoServer/dhnetsdk.h"
}


#include "JXJVideoServer/JNetSDK.h"
#include "JXJVideoServer/mb_api.h"


//��ѯ�豸
typedef struct queryDevConfig
{
	char				dst_id[MB_SERIAL_LEN];
	j_Device_T			stDev;
}DevConfig;

// CDaHuaFindDevicesDlg �Ի���
class CDaHuaFindDevicesDlg : public CDialogEx
{
// ����
public:
	CDaHuaFindDevicesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DAHUAFINDDEVICES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();	
	static LLONG  CALLBACK SearchDevicesCB1(DH::DEVICE_NET_INFO_EX *pDevNetInfo, void *pUserData);
	static int CALLBACK CDaHuaFindDevicesDlg::fcbJMBNotify(long lHandle, DWORD dwPortocol, int iErr, int iMsgID, LPCTSTR lpszDstID, void* pData, int iDataLen, void* pUserParam);
	afx_msg void OnBnClickedButton3();

	DevConfig m_devConfig;
	CString GetDeviceType(int i);
};
