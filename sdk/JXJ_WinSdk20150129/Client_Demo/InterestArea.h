#pragma once
#include "afxwin.h"
#include "Pub_Data.h"
#include "InterestScreen.h"

// CInterestArea �Ի���

class CInterestArea : public CDialog
{
	DECLARE_DYNAMIC(CInterestArea)

public:
	CInterestArea(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInterestArea();

// �Ի�������
	enum { IDD = IDD_DIALOG_INTERSET_AREA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_comChannel;
	CComboBox			m_VideoQuality;
	CButton				m_StartInterest;
	CButton				m_bStartPaint;


	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCheckStartpaint();
	int		ReFreshWindow();
	CInterestScreen			m_interestScreen;
private:

	JRegionConfig			m_jRegion;
	bool					m_bClear;
	
};
