#pragma once


// CBorderDlg �Ի���

class CBorderDlg : public CDialog
{
	DECLARE_DYNAMIC(CBorderDlg)

public:
	CBorderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBorderDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BORDERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void DrewWinBorder();
	afx_msg void OnPaint();
};
