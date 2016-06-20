#pragma once
#include "afxwin.h"
#include "MainStream.h"
#include "SecondStreamDlg.h"
#include "ThirdStreamDlg.h"
#include "Pub_Data.h"
#include "afxcmn.h"


// CEncodeDlg �Ի���

class CEncodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CEncodeDlg)

public:
	CEncodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncodeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ENCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_comChooseChannel;
	CButton				m_bStartVoice;
	CComboBox			m_eInVoice;
	CMainStream			m_MainStream;
	CSecondStreamDlg	m_SecondStream;
	CThirdStreamDlg		m_ThirdStream;
	CTabCtrl			m_TabStream;
	
	
	afx_msg void OnClose();
	afx_msg void OnTcnSelchangingTabstream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabstream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();


	void		InitResalutionWnd();//��ʼ���ֱ����б�
	CString		GetComReasolution(int iText);  //�õ�iText������
	int			GetIndexOfString(CString strText);  //�õ�strText��ֵ
	void		SaveMainStream();
	void		SaveSecondStream();
	void		SaveThirdStream();
	int			ReFreshMainStream();
	int			ReFreshSecondStream();
	int			ReFreshThirdStream();

private:
	JEncodeParameter	m_encodeParamer1;
	JEncodeParameter	m_encodeParamer2;
	JEncodeParameter	m_encodeParamer3;
	int					m_StreamId;
}; 
