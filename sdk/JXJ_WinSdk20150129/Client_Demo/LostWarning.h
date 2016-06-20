#pragma once
#include "afxwin.h"
#include "VideoTime.h"


// CLostWarning �Ի���

class CLostWarning : public CDialog
{
	DECLARE_DYNAMIC(CLostWarning)

public:
	CLostWarning(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLostWarning();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOST_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox		m_LostTimeInterval;
	CVideoTime		m_cVideoTime;
	CButton			m_StartLostWarning;

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSetlosttime();

	void		 ShowVideoTime(int iIndex);
	int			 ReFreshWindow();
private:
	JLostAlarm			m_lostAlarm;
};
