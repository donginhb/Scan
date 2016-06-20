#pragma once
#include "BorderDlg.h"

// CHideScreenDlg �Ի���

class CHideScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(CHideScreenDlg)

public:
	CHideScreenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHideScreenDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_HIDESCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	CPoint m_StartPoint[4];
	CPoint m_EndPoint[4];
	bool m_bStart[4];
	CBorderDlg m_cBorderDlg[4];

	static void CALLBACK DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser);
	void RegDrawCallBack();
	void ExitDrawCallBack();
	void DrawHideAlarmBorder(int i, int iX, int iY, int iW, int iH);
	bool m_bStartPaint;
};
