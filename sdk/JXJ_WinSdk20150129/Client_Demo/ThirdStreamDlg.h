#pragma once
#include "afxwin.h"


// CThirdStreamDlg �Ի���

class CThirdStreamDlg : public CDialog
{
	DECLARE_DYNAMIC(CThirdStreamDlg)

public:
	CThirdStreamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThirdStreamDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_THIRD_STREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_eZl;
	CEdit m_eSpaceZ;
	CComboBox m_comResolution;
	CComboBox m_comQuality;
	CComboBox m_eZs;
	CEdit m_eMlv;
	CComboBox m_comWlv;
	CComboBox m_comEncodeOrder;
	CComboBox m_comEncodeModel;
	CButton m_IfFirst;

	CStringArray m_strArray;
	afx_msg void OnClose();
};
