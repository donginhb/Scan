// HideScreenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HideScreenDlg.h"
#include "Pub_Data.h"


#define  DRAWCOLOR RGB(255,0,0)


IMPLEMENT_DYNAMIC(CHideScreenDlg, CDialog)

CHideScreenDlg::CHideScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHideScreenDlg::IDD, pParent)
{
	for(int i= 0; i< 4; i++)
	{
		m_StartPoint[i] = FALSE;
		m_EndPoint[i] = 0;
		m_bStart[i] = 0;
	}

	m_bStartPaint = FALSE;
	
}

CHideScreenDlg::~CHideScreenDlg()
{
	DestroyWindow();
}

void CHideScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHideScreenDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CHideScreenDlg ��Ϣ�������

BOOL CHideScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for(int i =0; i < 4; i++)
	{
		m_cBorderDlg[i].Create(IDD_DIALOG_BORDERDLG, this);
		m_cBorderDlg[i].SetOwner(this);
	}
	return TRUE;
}

void CHideScreenDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] >= 4 || !m_bStartPaint)
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = TRUE;
	m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;
	m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;

	CDialog::OnLButtonDown(nFlags, point);
}

void CHideScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] >= 4 || !m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = FALSE;

	//��������һ�����Σ���ԭ����϶�ʱ���ο����ԭ����ͬ��
	CClientDC dc(this);
	dc.SetROP2(R2_BLACK); 
	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
	,m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]));

	int x = m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x;
	int y = m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y;


	DrawHideAlarmBorder(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng],
		m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x,
		m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y,
		point.x - m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].x,
		point.y - m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]].y);

	g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] ++;

	CDialog::OnLButtonUp(nFlags, point);
}

void CHideScreenDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClientDC dc(this);   //��ȡ�豸���

	//SetRop2 Specifies the new drawing mode.(MSDN)
	//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
	//�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ
	//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£�
	//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ�
	//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ������ˣ�
	dc.SetROP2(R2_BLACK);   //��Ϊ�ؼ�!!!
	dc.SelectStockObject(BLACK_BRUSH ); //ʹ�û�ˢ
	if (TRUE == m_bStart[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])   //�����Ƿ��е����ж��Ƿ���Ի�����
	{
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
		,m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]])); 
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]]
		,point));
		m_EndPoint[g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]] = point;
	}



	CDialog::OnMouseMove(nFlags, point);
}



void CHideScreenDlg::DrawHideAlarmBorder(int i, int iX, int iY, int iW, int iH)
{
	//m_cBorderDlg[i]->MoveWindow(iX, iY, iW, iH, TRUE);
	CRect cRect;
	this->GetClientRect(cRect);
	ClientToScreen(cRect);

	m_cBorderDlg[i].MoveWindow(cRect.left + iX, cRect.top + iY, iW, iH, TRUE);
	m_cBorderDlg[i].ShowWindow(SW_SHOW);
}


void CHideScreenDlg::RegDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), DrawCB, this);
}

void CHideScreenDlg::ExitDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), NULL, this);
}




void CALLBACK CHideScreenDlg::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
// 	CRect cRect;
// 	gHideScreen->GetWindowRect(cRect);
// 	CPoint maxPoint(cRect.Width(), cRect.Height());
// 	if(g_PubData.g_iCountHide[g_PubData.g_iAttributeIng] > 0)
// 	{
// 		
// 		for(int i = 0; i< g_PubData.g_iCountHide[g_PubData.g_iAttributeIng]; i++)
// 		{
// 			CPoint point1(gHideScreen->m_StartPoint[i].x, gHideScreen->m_StartPoint[i].y);
// 			CPoint point2(gHideScreen->m_EndPoint[i].x, gHideScreen->m_StartPoint[i].y);
// 			CPoint point3(gHideScreen->m_EndPoint[i].x, gHideScreen->m_EndPoint[i].y);
// 			CPoint point4(gHideScreen->m_StartPoint[i].x, gHideScreen->m_EndPoint[i].y);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point1, &point2, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point2, &point3, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point3, &point4, &maxPoint);
// 			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point4, &point1, &maxPoint);
// 		}
// 	}
}