// BorderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "BorderDlg.h"


// CBorderDlg �Ի���

IMPLEMENT_DYNAMIC(CBorderDlg, CDialog)

CBorderDlg::CBorderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBorderDlg::IDD, pParent)
{

}

CBorderDlg::~CBorderDlg()
{
	DestroyWindow();
}

void CBorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBorderDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBorderDlg ��Ϣ�������

void CBorderDlg::DrewWinBorder()
{
	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(255,0,0));
	CPen *pOldpen = pdc->SelectObject(&pen);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);
	pdc->MoveTo(rect.left, rect.top);
	pdc->LineTo(rect.right, rect.top);
	pdc->LineTo(rect.right, rect.bottom);
	pdc->LineTo(rect.left, rect.bottom);
	pdc->LineTo(rect.left, rect.top);
	pdc->SelectObject(pOldpen);
	ReleaseDC(pdc);
}
void CBorderDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� 
	CRect    rect;     
	GetClientRect(rect);     
	dc.FillSolidRect(rect,    RGB(255,255,0));     
	CDialog::OnPaint();
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE,
		GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	// Make this window 70% alpha
	::SetLayeredWindowAttributes(this->GetSafeHwnd(), RGB(255,255,0),50, /*LWA_ALPHA*/  LWA_COLORKEY);
	DrewWinBorder();
}
