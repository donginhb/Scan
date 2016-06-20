// RecodeScreenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "RecodeScreenDlg.h"
#include "Pub_Data.h"
#include "Client_DemoDlg.h"
#include "VideoPlayBack.h"


// CRecodeScreenDlg �Ի���

IMPLEMENT_DYNAMIC(CRecodeScreenDlg, CDialog)

CRecodeScreenDlg::CRecodeScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecodeScreenDlg::IDD, pParent)
{
	m_bPlayFileProgress = FALSE;
}

CRecodeScreenDlg::~CRecodeScreenDlg()
{
}

void CRecodeScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_PLAYPROGRESS, m_PlayProgress);
}


BEGIN_MESSAGE_MAP(CRecodeScreenDlg, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CRecodeScreenDlg ��Ϣ�������

BOOL CRecodeScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bDbclk = FALSE;

	return TRUE;
}
void CRecodeScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)AfxGetMainWnd();
	if(!m_bDbclk)
	{
		this->MoveWindow(28,0,g_PubData.g_iStaticScreenWidth-28,g_PubData.g_iStaticScreenHeight - 32,TRUE);
		this->ShowWindow(SW_SHOW);
		m_bDbclk = TRUE;
		pDlg->m_videoPlayBack.m_VideoPlayBack.ShowWindow(SW_HIDE);
	}
	else
	{
		this->MoveWindow(30,270,650,255, TRUE);
		this->ShowWindow(SW_SHOW);
		m_bDbclk = FALSE;
		pDlg->m_videoPlayBack.m_VideoPlayBack.ShowWindow(SW_SHOW);
	}
	
	CRect cRect;
	this->GetClientRect(&cRect);
	this->GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->MoveWindow(0,0,cRect.Width(), cRect.Height() - 25, TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->MoveWindow(50, cRect.Height()-18, cRect.Width()- 50,20, TRUE);
	this->GetDlgItem(IDC_SLIDER_PLAYPROGRESS)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->MoveWindow(0, cRect.Height()-15, 50, 20, TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWPLAYTIME)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->MoveWindow(0, cRect.Height()-25, cRect.Width(),25, TRUE);
	this->GetDlgItem(IDC_STATIC_GROPU_PROGRESS)->ShowWindow(SW_SHOW);
		

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CRecodeScreenDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������


}

BOOL CRecodeScreenDlg::PreTranslateMessage(MSG* pMsg) 
{

	CVideoPlayBack *pDlg = (CVideoPlayBack *)AfxGetMainWnd();
	int buID;
	buID= GetWindowLong(pMsg->hwnd,GWL_ID);//�ɴ��ھ�����ID�ţ�GetWindowLongΪ��ô��ڵ�ID�š�
	if(pMsg->message==WM_LBUTTONDOWN)   //���� 
	{	
		
	}
	if(pMsg->message==WM_LBUTTONUP)  //�ɿ�
	{  
		if(buID == IDC_SLIDER_PLAYPROGRESS)
		{
			m_bPlayFileProgress = TRUE;
			pDlg->m_PlayFiletime = m_PlayProgress.GetPos();
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CRecodeScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	CBrush   brush(RGB(255,255,255)); 
	if(pWnd-> GetDlgCtrlID() == IDC_STATIC_SHOWRECODEVIDEO)
	{
		CRect   rect;  
		pDC->SelectObject(&brush);  
		CWnd   *p_staticwnd=GetDlgItem(IDC_STATIC_SHOWRECODEVIDEO); 
		p_staticwnd-> GetWindowRect(&rect);  
		pDC-> Rectangle(&rect); 
		pDC->SetBkMode(TRANSPARENT); 
	}

	return   (HBRUSH)brush;
	//return hbr;
}

void CRecodeScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonUp(nFlags, point);
}

//void CRecodeScreenDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialog::OnMouseMove(nFlags, point);
//}
