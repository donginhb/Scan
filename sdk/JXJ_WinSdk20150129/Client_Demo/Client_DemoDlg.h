
// Client_DemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "VideoPlayBack.h"
#include "DeviceUpdateDlg.h"



// CClient_DemoDlg �Ի���
class CClient_DemoDlg : public CDialog
{
// ����
public:
	CClient_DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStaticText2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	static void  LoginDevice(LPVOID DBClickIp);   //��¼�豸
	static int WINAPI ConnEventCB(long lHandle, eJNetEvent eType,int iDataType,void* pEventData,int iDataLen,void* pUserParam);
	static BOOL WINAPI StreamCB(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);
    static BOOL __stdcall OnTalkStream(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);

	BOOL VideoTalk(int index);     //�Խ�����
	static void CALLBACK PickAudioCallBack(const BYTE* pBuffer, DWORD dwBufSize, void* pUserData);
	
	BOOL OpenVideoStream(int iIndex); //��ʵʱ��
	BOOL HiPlayerOpenVideoStream(int iIndex);
	void GetDevCap(int nIndex);       //��ȡ�豸������

	BOOL PreTranslateMessage(MSG* pMsg); //��ť���º��ɿ�
	void ControlPtz(int iCmd);               //������̨

	void EnablePTZ();						//��̨������
	void ShowPtz();                       //��̨����
	void SubmitAlarm(int nIndex, void *pData);

public:
	void initComboxScreenNum();            
	void ArrangeOutputs(int iNumber);     //�ָ��
	void Hide_Window(int index);         //���س��� index �Ĵ��� 
	void Show_Window(int iNumber);      //��ʾ iNumber ������
	void Set_StreamType(int index , int streamType);    //��������


	void GetAlarmData(int iAlarm, int iAction, CStringArray &strArray, int iIndex);
	void GetAlarmDataEnglish(int iAlarm, int iAction, CStringArray &strArray);
	void InitINIfile();
	int m_iDemoMode;

public:

	int m_iCurWndNum;      //������
	int m_iCurWndIndex;   //��������
	int m_iCurScreenWidth;  
	int m_iCurScreenHeight;
	int m_iDownIndex;
	bool m_bDragDown;
	bool m_bWarningMax;
	bool m_bDragFile;  //�Ƿ����϶��ļ�  ֻ���ڻط�ʱ�϶�
	BOOL m_bDrag;
	int m_iLoginOk;
	long m_vSnapHandle;


	HTREEITEM m_hRoot;
	HTREEITEM m_hItem;
	HTREEITEM m_hDeleteItem;
	HTREEITEM     m_hBeginDrag;
	HTREEITEM     m_hDragItem;  //�����϶��Ľڵ�
	
	COleDateTime m_cTime;
	CTreeCtrl m_MainTree;
	CStatic m_ShowTime;
	CComboBox m_comScreenNum;
	CImageList*   m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	CString m_strDragItemText;
	CString m_strSelItemText;
	CListCtrl m_ListWarning;
	CImageList m_imageList;
	CButton m_bUp;
	CButton m_bLeft;
	CButton m_bRight;
	CButton m_bDown;
	CButton m_bAuto;
	CButton m_ScanJIa;
	CButton m_ScanJian;
	CComboBox m_combJD;
	CButton m_StartLight;
	CButton m_StartBrush;

	

	CDeviceUpdateDlg m_upgDlg;
	CVideoPlayBack m_videoPlayBack;

	afx_msg void OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboScreenNum();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonPlayback();
	afx_msg void OnBnClickedButtonWatch();
	afx_msg void OnBnClickedCheckStartlight();
	afx_msg void OnBnClickedCheckStartbrush();
	afx_msg void OnLvnColumnclickListWarning(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuDelete();
	afx_msg void OnBnClickedButtonRecode();
	afx_msg void OnTvnBegindragTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonCloseallvideo();
	afx_msg void OnMenuAttribute();
	afx_msg void OnNMRClickListWarning(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuDellist();
	afx_msg void OnBnClickedButtonClearwarning();
	afx_msg void OnBnClickedButtonAllfullup();
	afx_msg void OnNMClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonElse();
	afx_msg void OnLocalattribute();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDropFiles(HDROP hDropInfo);


	void SetTreeIcon();
	void SaveLoginDevice();
	void DeleteDevice(int index);
	int GetDragItemIndex(CString strNode);   //�õ�������ק�Ľڵ�Ĳ��ųɹ�������
	int GetDragToScreenNum(int iX, int iY);   //�õ���ק��Ŀ�Ĵ���
	void RecoverToOldScreen();
	void HideButton(int iFlag); // �˵�����ť�Ƿ�����
	void RegDrawCallBackEx(int iChannel, HWND hwnd);
	afx_msg void OnMenuDeviceSnap();




	bool area_cross(JPoint region[], JPoint pos);
	int getBlockValue(char *data, int len, int isBit, int blockIndex);
	int	GetDevIndex(long lHandle);
	int	NoVideoSnap(int nIndex, char *pBuff, DWORD dwRevLen);


	

	JDomeCtrlPtz	m_domeCtrlPtz;
	
};
