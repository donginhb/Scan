// CpcScreen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "CpcScreen.h"
#include "Pub_Data.h"

// CCpcScreen �Ի���

#define  DRAWCOLOR RGB(255,0,0)
IMPLEMENT_DYNAMIC(CCpcScreen, CDialog)

CCpcScreen::CCpcScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CCpcScreen::IDD, pParent)
{

	
}

CCpcScreen::~CCpcScreen()
{
}

void CCpcScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCpcScreen, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCpcScreen ��Ϣ�������
BOOL CCpcScreen::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

void CCpcScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	m_bDraw = TRUE;
	m_cpcPoint[m_iCountPoint] = point;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CCpcScreen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	m_iCountPoint ++;
	m_cpcPoint[m_iCountPoint] = point;

	pdc->MoveTo(m_cpcPoint[m_iCountPoint -1]);
	pdc->LineTo(point);
	if(m_bDraw)
	{
		m_bDraw = FALSE;
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CCpcScreen::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_bDraw)
	{
		return;
	}

	CClientDC dc(this);   //��ȡ�豸���

	//SetRop2 Specifies the new drawing mode.(MSDN)
	//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
	//�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ
	//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£�
	//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ�
	//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ������ˣ�
	dc.SetROP2(R2_BLACK);   //��Ϊ�ؼ�!!!
	dc.SelectStockObject(NULL_BRUSH ); //ʹ�û�ˢ

	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	pdc->MoveTo(m_cpcPoint[m_iCountPoint]);
	pdc->LineTo(point);
	CDialog::OnMouseMove(nFlags, point);
}


void CCpcScreen::RegDrawCallBack()
{
	
}

void CCpcScreen::ExitDrawCallBack()
{
	
}


void CALLBACK CCpcScreen::DrawCB(int nPort, HWND hwnd, HDC hdc, int nWidth, int nHeight, unsigned long long u64TimeStamp, void *pUser)
{
	CRect cRect;
	
	
}
