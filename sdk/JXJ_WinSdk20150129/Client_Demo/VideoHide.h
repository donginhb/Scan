#pragma once
#include "afxwin.h"
#include "HideScreenDlg.h"

// CVideoHide �Ի���

class CVideoHide : public CDialog
{
	DECLARE_DYNAMIC(CVideoHide)

public:
	CVideoHide(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoHide();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIDEO_HIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_comChannel;
	CButton				m_bStartHide;
	CButton				m_bStartPaint;
	
	

	
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedCheckStartpaint();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();
	afx_msg void OnDestroy();

	int					ReFreshWindow();
	CHideScreenDlg		m_HideScreen;
private:
	JHideParameter		m_hideParam;
	bool				m_bClear;
	int					m_iLeft;
	int					m_iTop;
	int					m_iRight;
	int					m_iBottom;

};
