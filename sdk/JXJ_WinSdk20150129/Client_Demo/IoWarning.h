#pragma once
#include "afxwin.h"
#include "VideoTime.h"

// CIoWarning �Ի���

class CIoWarning : public CDialog
{
	DECLARE_DYNAMIC(CIoWarning)

public:
	CIoWarning(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIoWarning();

// �Ի�������
	enum { IDD = IDD_DIALOG_IOWARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox		m_channel;
	CButton			m_StartIo;
	int				m_iSelChannel;
	CComboBox		m_IoType;
	CComboBox		m_Seconds;
	CVideoTime		m_cVideoTime;

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboChannel();
	afx_msg void OnBnClickedButtonSettime();

	void ShowVideoTime(int iIndex);
	int	 ReFreshWindow();


private:
	JIoAlarm	m_ioAlarm[10];
};
