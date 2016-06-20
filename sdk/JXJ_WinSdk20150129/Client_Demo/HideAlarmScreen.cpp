// HideAlarmScreen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HideAlarmScreen.h"
#include "Pub_Data.h"

#define  DRAWCOLOR RGB(255,0,0)

CHideAlarmScreen *gHideAlarm = NULL;
// CHideAlarmScreen �Ի���

IMPLEMENT_DYNAMIC(CHideAlarmScreen, CDialog)

CHideAlarmScreen::CHideAlarmScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CHideAlarmScreen::IDD, pParent)
{
	for(int i= 0; i< 4; i++)
	{
		m_StartPoint[i] = FALSE;
		m_EndPoint[i] = 0;
		m_bStart[i] = 0;
	}
	m_bStartPaint = FALSE;
	gHideAlarm = this;
}

CHideAlarmScreen::~CHideAlarmScreen()
{
	DestroyWindow();
}

void CHideAlarmScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHideAlarmScreen, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHideAlarmScreen ��Ϣ�������
BOOL CHideAlarmScreen::OnInitDialog()
{
	CDialog::OnInitDialog();
	for(int i =0; i < 4; i++)
	{
		m_cBorderDlg[i].Create(IDD_DIALOG_BORDERDLG, this);
		m_cBorderDlg[i].SetOwner(this);
	}
	return TRUE;
}



void CHideAlarmScreen::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	//AfxMessageBox(_T("move "));
	// TODO: �ڴ˴������Ϣ����������
}

void CHideAlarmScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//��Ϊ��ͼ��Ϣ����
	CDialog::OnPaint();
}

void CHideAlarmScreen::RegDrawCallBack()
{
	////HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), DrawCB, this);
}

void CHideAlarmScreen::ExitDrawCallBack()
{
	//HIPLAYER_RegDrawCallBackEx(g_PubData.g_iChancel[g_PubData.g_iAttributeIng], this->GetSafeHwnd(), NULL, this);
}


void CALLBACK CHideAlarmScreen::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
	CRect cRect;
	gHideAlarm->GetWindowRect(cRect);
	CPoint maxPoint(cRect.Width(), cRect.Height());
	if(g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] > 0)
	{

		for(int i = 0; i< g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]; i++)
		{
			CPoint point1(gHideAlarm->m_StartPoint[i].x, gHideAlarm->m_StartPoint[i].y);
			CPoint point2(gHideAlarm->m_EndPoint[i].x, gHideAlarm->m_StartPoint[i].y);
			CPoint point3(gHideAlarm->m_EndPoint[i].x, gHideAlarm->m_EndPoint[i].y);
			CPoint point4(gHideAlarm->m_StartPoint[i].x, gHideAlarm->m_EndPoint[i].y);
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point1, &point2, &maxPoint);
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point2, &point3, &maxPoint);
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point3, &point4, &maxPoint);
			//HIPLAYER_DrawLine(nPort, hdc, DRAWCOLOR, &point4, &point1, &maxPoint);
		}
	}
}


void CHideAlarmScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] >= 4 || !m_bStartPaint)
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]] = TRUE;
	m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]] = point;
	m_EndPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]] = point;

	CDialog::OnLButtonDown(nFlags, point);
}

void CHideAlarmScreen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] >= 4  || !m_bStart[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]])
	{
		return;
	}
	m_bStart[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]] = FALSE;

	//��������һ�����Σ���ԭ����϶�ʱ���ο����ԭ����ͬ��
	CClientDC dc(this);
	//dc.SetROP2(R2_BLACK); 
	dc.SelectStockObject(BLACK_PEN);
	dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]]
	,m_EndPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]]));

	DrawHideAlarmBorder(g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng],
		m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]].x,
		m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]].y,
		point.x - m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]].x,
		point.y - m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]].y);

	g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng] ++;

	CDialog::OnLButtonUp(nFlags, point);
}

void CHideAlarmScreen::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClientDC dc(this);   //��ȡ�豸���

	//SetRop2 Specifies the new drawing mode.(MSDN)
	//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
	//�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ
	//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£�
	//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ�
	//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ������ˣ�
	//dc.SetROP2(R2_BLACK);   //��Ϊ�ؼ�!!!
	dc.SelectStockObject(BLACK_PEN ); //ʹ�û�ˢ
	if (TRUE == m_bStart[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]])   //�����Ƿ��е����ж��Ƿ���Ի�����
	{
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]]
		,m_EndPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]])); 
		dc.Rectangle(CRect(m_StartPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]]
		,point));
		m_EndPoint[g_PubData.g_iCountHideAlarm[g_PubData.g_iAttributeIng]] = point;
	}



	CDialog::OnMouseMove(nFlags, point);
}

void CHideAlarmScreen::DrawHideAlarmBorder(int i, int iX, int iY, int iW, int iH)
{
	//m_cBorderDlg[i]->MoveWindow(iX, iY, iW, iH, TRUE);
	CRect cRect;
	this->GetClientRect(cRect);
	ClientToScreen(cRect);

	m_cBorderDlg[i].MoveWindow(cRect.left + iX, cRect.top + iY, iW, iH, TRUE);
	m_cBorderDlg[i].ShowWindow(SW_SHOW);
}