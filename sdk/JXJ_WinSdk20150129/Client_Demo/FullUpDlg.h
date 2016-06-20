#pragma once


// CFullUpDlg �Ի���

class CFullUpDlg : public CDialog
{
	DECLARE_DYNAMIC(CFullUpDlg)

public:
	CFullUpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFullUpDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FULLUP_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	bool m_bMaxofScreen;
	bool m_bIfFullup;
	int m_iWndX;
	int m_iWndY;
	int m_iWndWidth;
	int m_iWndHeight;
	CMenu m_pMenu;
	CRect m_Rect;
	int m_iHideIndex;  
	int m_iPlayWndIndex;  //  �ô��ڲ��ŵ� ��Ƶ����
	int m_iPlayWndNum;		//�ô����������������
	int m_iPlayFlag;			//�ô����Ƿ��Ѿ�������Ƶ��
	int m_iFlag;
	HCURSOR m_hcursor;
	CImageList m_imageList;


	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuFullscreen();
	afx_msg void OnMenuMainstream();
	afx_msg void OnMenuSecondstream();
	afx_msg void OnMenuThirdstream();
	afx_msg void OnMenuClose();
	afx_msg void OnBnClickedButtonTalk();
	afx_msg void OnBnClickedButtonAttribute();
	void DrewWinBorder();   
	void ResetBorder();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	bool m_bTalk;   //�Ƿ����öԽ�
	bool m_bListen; //�Ƿ����ü���
	bool m_bRecode; //�Ƿ�¼��
	CBitmapButton m_TalkButton;
	afx_msg void OnBnClickedButtonTakeapicture();
	afx_msg void OnBnClickedButtonListen();
	afx_msg void OnBnClickedButtonRecode();
	BOOL PreTranslateMessage(MSG* pMsg); //��ť���º��ɿ�

	void DeviceClose();   //�ر���Ƶ
	void ShowMenuState();   //��ʾ�Ҽ��˵���״̬
	void EscEvent();
	void ButtonCloseAll();
};

extern CFullUpDlg g_cFullUpDlg[GET_MAX_DEV_NUM];