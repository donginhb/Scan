#pragma once
#include "afxcmn.h"


// CRecodeScreenDlg �Ի���

class CRecodeScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecodeScreenDlg)

public:
	CRecodeScreenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecodeScreenDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RECODESCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_PlayProgress;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	bool m_bDbclk;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL PreTranslateMessage(MSG* pMsg); //��ť���º��ɿ�
	bool m_bPlayFileProgress;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
