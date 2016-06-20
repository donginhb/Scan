#pragma once
#include "afxwin.h"


// CSerialSet �Ի���

class CSerialSet : public CDialog
{
	DECLARE_DYNAMIC(CSerialSet)

public:
	CSerialSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerialSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERIAL_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit				m_DataBit;
	CEdit				m_StopBit;
	CEdit				m_BaudRate;
	CComboBox			m_SerialType;
	CComboBox			m_CheckBit;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();



	int					ReFreshWindow();
private:

	JSerialParameter			m_serialParam;
};
