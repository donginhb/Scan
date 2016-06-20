// FullUpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "FullUpDlg.h"
#include "Pub_Data.h"
#include "Client_DemoDlg.h"
#include "CAttributeDlg.h"
#include "IniFile.h"
#include <math.h>

#include "direct.h"     //mkdir ͷ�ļ�

// CFullUpDlg �Ի���

#define BITMAP_SIZE (1920 * 1080 * 4 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))

IMPLEMENT_DYNAMIC(CFullUpDlg, CDialog)

CFullUpDlg::CFullUpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullUpDlg::IDD, pParent)
{
	m_iWndX = 0;
	m_iWndY = 0;
	m_iWndWidth = 0;
	m_iWndHeight = 0;
	m_iHideIndex = -1;
	m_iPlayWndIndex = -1;
	m_iPlayWndNum = -1;
	m_iPlayFlag = -1;
	m_bIfFullup = TRUE;
	m_iFlag = 0;
	m_bTalk = FALSE;
	m_bListen = FALSE;
	m_bRecode = FALSE;
}

CFullUpDlg::~CFullUpDlg()
{
	DestroyWindow();
}

void CFullUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFullUpDlg, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_FULLSCREEN, &CFullUpDlg::OnMenuFullscreen)
	ON_COMMAND(ID_MENU_MAINSTREAM, &CFullUpDlg::OnMenuMainstream)
	ON_COMMAND(ID_MENU_SECONDSTREAM, &CFullUpDlg::OnMenuSecondstream)
	ON_COMMAND(ID_MENU_THIRDSTREAM, &CFullUpDlg::OnMenuThirdstream)
	ON_COMMAND(ID_MENU_CLOSE, &CFullUpDlg::OnMenuClose)
	ON_BN_CLICKED(IDC_BUTTON_TALK, &CFullUpDlg::OnBnClickedButtonTalk)
	ON_BN_CLICKED(IDC_BUTTON_ATTRIBUTE, &CFullUpDlg::OnBnClickedButtonAttribute)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_TAKEAPICTURE, &CFullUpDlg::OnBnClickedButtonTakeapicture)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CFullUpDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_RECODE, &CFullUpDlg::OnBnClickedButtonRecode)
END_MESSAGE_MAP()


// CFullUpDlg ��Ϣ�������
BOOL CFullUpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	/*//��þ�̬�ı���ľ�� 
	HWND h_static = GetDlgItem(IDC_STATIC_SHOWVIDEO)->m_hWnd;

	//��þ�̬�ı����DC��� 
	HDC hdc = ::GetDC(h_static);

	//��þ�̬�ı����DCָ�� 
	CDC *pdc = CDC::FromHandle(hdc);

	//��þ�̬�ı���Ĵ�С 
	CRect rect ;
	GetClientRect(h_static,rect);

	//��侲̬�ı�����ɫ 
	pdc->setsolid(rect,RGB(255,0,0));
*/


	if (!m_pMenu.LoadMenu(IDR_MENU1))
	{
		return FALSE;
	}


	m_bMaxofScreen = TRUE;

	GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);

	
	return TRUE;
}
void CFullUpDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnLButtonDblClk(nFlags, point);

	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();

	if(m_bMaxofScreen)  //һ����ģʽ
	{
		if(g_PubData.g_bAllFullScreen)
		{
			int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
			int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

			this->MoveWindow(0,0 ,iScreenWidth,iScreenHeight,TRUE);
			this->ShowWindow(SW_SHOW);
		}
		else
		{
			this->MoveWindow(g_PubData.g_iMoveX,g_PubData.g_iMoveY,g_PubData.g_iStaticScreenWidth,g_PubData.g_iStaticScreenHeight,TRUE);
			this->ShowWindow(SW_SHOW);
		}
		

		CRect cRect;
		this->GetClientRect(&cRect);
		this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->MoveWindow(0,0,cRect.Width(),cRect.Height()-22,TRUE);
		this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_STATIC_GROUP)->MoveWindow(0,cRect.Height()-30,cRect.Width(),30,TRUE);
		this->GetDlgItem(IDC_STATIC_GROUP)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON_TALK)->MoveWindow(0,cRect.Height()-22,30,20,TRUE);
		this->GetDlgItem(IDC_BUTTON_TALK)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->MoveWindow(31,cRect.Height()-22,30,20,TRUE);
		this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON_LISTEN)->MoveWindow(62,cRect.Height()-22,30,20,TRUE);
		this->GetDlgItem(IDC_BUTTON_LISTEN)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->MoveWindow(93,cRect.Height()-22,30,20,TRUE);
		this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->ShowWindow(SW_SHOW);

		if(g_PubData.g_iLanguageFlag)
			this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,40,20,TRUE);
		else
			this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,30,20,TRUE);
		this->GetDlgItem(IDC_BUTTON_RECODE)->ShowWindow(SW_SHOW);

		pDlg->Hide_Window(m_iHideIndex);
		m_bMaxofScreen = FALSE;
		m_iFlag = 1;
		
	}
	else  //�ָ�֮ǰ״̬
	{
		if(g_PubData.g_bAllFullScreen)  //�Ƿ�໭��ȫ��
		{

			pDlg->ArrangeOutputs(g_PubData.g_iCutScreenNum);
			m_bMaxofScreen = TRUE;
			m_bIfFullup = TRUE;
			m_iFlag = 0;
		}
		else
		{
			EscEvent();
		}	
	}

		
}

//�˳�ȫ�� ����һ����  ��Ӧȫ��Esc��
void CFullUpDlg::EscEvent()
{
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
	m_pMenu.CheckMenuItem(ID_MENU_FULLSCREEN,MF_UNCHECKED);
	pDlg->GetDlgItem(IDC_STATIC_SHOWTIME)->ShowWindow(SW_SHOW);
	//ȫ���˳�ʱ
	int iX = g_PubData.g_iMainWindowX;
	int iY = g_PubData.g_iMainWindowY;
	int iW = g_PubData.g_iMainWindowW;
	int iH = g_PubData.g_iMainWindowH;
	if(m_iFlag == 1)   //һ����ģʽ�˳�ʱ
	{
		CRect mainRect;
		pDlg->GetWindowRect(mainRect);
		iX = mainRect.left;//g_PubData.g_iMainWindowX;
		iY = mainRect.top;//g_PubData.g_iMainWindowY;
		iW = mainRect.Width();//g_PubData.g_iMainWindowW;
		iH = mainRect.Height();//g_PubData.g_iMainWindowH;
	}

	pDlg->MoveWindow(iX, iY, iW, iH, TRUE);
	pDlg->ShowWindow(SW_SHOW);
	this->MoveWindow(m_iWndX,m_iWndY,m_iWndWidth,m_iWndHeight,TRUE);
	this->ShowWindow(SW_SHOW);

	pDlg->Show_Window(g_PubData.g_iCutScreenNum);

	CRect cRect;
	this->GetClientRect(&cRect);
	this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->MoveWindow(0,0,cRect.Width(),cRect.Height()-22,TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_GROUP)->MoveWindow(0,cRect.Height()-30,cRect.Width(),30,TRUE);
	this->GetDlgItem(IDC_STATIC_GROUP)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_TALK)->MoveWindow(0,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_TALK)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->MoveWindow(31,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_LISTEN)->MoveWindow(62,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_LISTEN)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->MoveWindow(93,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->ShowWindow(SW_SHOW);

	if(g_PubData.g_iLanguageFlag)
		this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,40,20,TRUE);
	else
		this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_RECODE)->ShowWindow(SW_SHOW);

	m_bMaxofScreen = TRUE;
	m_bIfFullup = TRUE;
	m_iFlag = 0;
}

void CFullUpDlg::DrewWinBorder()
{
	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(75, 215, 40));
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

void CFullUpDlg::ResetBorder()
{
	CDC * pdc = GetWindowDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, GetSystemMetrics(SM_CXDRAG), RGB(165, 165, 165));
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

void CFullUpDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CPoint point1;
	GetCursorPos(&point1);

	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
	CRect cRect;
	pDlg->GetClientRect(cRect);
	pDlg->ClientToScreen(cRect);

	if(m_iPlayWndIndex < 0)  //û����Ƶ����
	{
		return;
	}
	pDlg->m_MainTree.SelectItem(g_PubData.g_hTreeItem[m_iPlayWndIndex]);
	if(m_iFlag > 0)   //һ������ȫ��ģʽ
	{
		return;
	}
	g_PubData.g_iDownIndex = pDlg->GetDragToScreenNum((point1.x - cRect.left), (point1.y - cRect.top));
	if(g_PubData.g_iDownIndex < 0)
	{
		return;
	}

	g_PubData.g_bDragDown = TRUE;
	CDialog::OnLButtonDown(nFlags, point);
}


void CFullUpDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(g_PubData.g_bDragDown)
	{
// 		HCURSOR hCursor=AfxGetApp()->LoadStandardCursor(IDC_WAIT);
// 		SetCursor(hCursor);

		ICONINFO ii;
		ii.fIcon = TRUE;
		ii.xHotspot = 0;
		ii.yHotspot = 0;
		ii.hbmMask = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_DRAG));
		ii.hbmColor =LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_DRAG));
		m_hcursor = (HCURSOR)CreateIconIndirect(&ii);
		SetCursor(m_hcursor);

	}

	CDialog::OnMouseMove(nFlags, point);
}

void CFullUpDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClient_DemoDlg *pDlg = (CClient_DemoDlg *)AfxGetMainWnd();
	DrewWinBorder();
	for(int i=0; i< GET_MAX_DEV_NUM; i++)
	{
		if(m_iHideIndex == i)
		{
			continue;
		}
		g_cFullUpDlg[i].ResetBorder();
	}

	g_PubData.g_iPlayBack = m_iPlayWndIndex;
	g_PubData.g_iAttributeIng = m_iPlayWndIndex;

	if(g_PubData.g_bDragDown)
	{
		DestroyIcon(m_hcursor);
		CPoint point1;
		GetCursorPos(&point1);

		CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
		CRect cRect;
		pDlg->GetClientRect(cRect);
		pDlg->ClientToScreen(cRect);

		int iUpIndex = -1;		
		iUpIndex = pDlg->GetDragToScreenNum((point1.x - cRect.left), (point1.y - cRect.top));
		if(iUpIndex < 0)
		{
			g_PubData.g_bDragDown = FALSE;
			return;
		}
		if(iUpIndex == g_PubData.g_iDownIndex)
		{
			g_PubData.g_bDragDown = FALSE;
			return;
		}
		
		if(g_cFullUpDlg[iUpIndex].m_iPlayFlag < 0)   //�ô���û����Ƶ���ŵ����
		{

			AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex], 
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
	
			pDlg->RegDrawCallBackEx(g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex,
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			AVP_AddPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex],NULL,
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd(), NULL, NULL);
			UpdateWindow();
			Invalidate();
			g_cFullUpDlg[iUpIndex].m_iPlayWndIndex = g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex;
			g_cFullUpDlg[iUpIndex].m_iPlayWndNum = iUpIndex;
			g_cFullUpDlg[iUpIndex].m_iPlayFlag = 1;

			g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex = -1;
			g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndNum = -1;
			g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayFlag = -1;
			
			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bTalk)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
				g_cFullUpDlg[iUpIndex].m_bTalk = TRUE;
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bTalk =  FALSE;
			}
			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bListen)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListemE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
				g_cFullUpDlg[iUpIndex].m_bListen = TRUE;
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bListen =  FALSE;
			}
			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bRecode)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);
				g_cFullUpDlg[iUpIndex].m_bRecode = TRUE;
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bRecode =  FALSE;
			}
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);

			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(TRUE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(TRUE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(TRUE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(TRUE);

		}
		else
		{
			AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex], 
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			AVP_DelPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[iUpIndex].m_iPlayWndIndex], 
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			
			pDlg->RegDrawCallBackEx(g_cFullUpDlg[iUpIndex].m_iPlayWndIndex,
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			AVP_AddPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[iUpIndex].m_iPlayWndIndex],NULL,
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd(),NULL, NULL);

			pDlg->RegDrawCallBackEx(g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex,
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
			AVP_AddPlayWnd(g_PubData.g_iChancel[g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex],NULL, 
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd(),NULL, NULL);

			int iIndex = g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex;
			int iNumber = g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndNum;

			g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndIndex = g_cFullUpDlg[iUpIndex].m_iPlayWndIndex;
			g_cFullUpDlg[g_PubData.g_iDownIndex].m_iPlayWndNum = g_cFullUpDlg[iUpIndex].m_iPlayWndNum;
			
			g_cFullUpDlg[iUpIndex].m_iPlayWndIndex = iIndex;
			g_cFullUpDlg[iUpIndex].m_iPlayWndNum = iNumber;



			bool bTalk = g_cFullUpDlg[iUpIndex].m_bTalk;
			bool bListen = g_cFullUpDlg[iUpIndex].m_bListen;
			bool bRecode = g_cFullUpDlg[iUpIndex].m_bRecode;
			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bTalk)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkE);
				g_cFullUpDlg[iUpIndex].m_bTalk = TRUE;
			}
			else 
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
				g_cFullUpDlg[iUpIndex].m_bTalk = FALSE;
			}

			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bListen)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListemE);
				g_cFullUpDlg[iUpIndex].m_bListen = TRUE;
			}
			else
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
				g_cFullUpDlg[iUpIndex].m_bListen = FALSE;
			}

			if(g_cFullUpDlg[g_PubData.g_iDownIndex].m_bRecode)
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordE);
				g_cFullUpDlg[iUpIndex].m_bRecode = TRUE;
			}
			else
			{
				g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);
				g_cFullUpDlg[iUpIndex].m_bRecode = FALSE;
			}

			if(bTalk)
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bTalk = TRUE;
			}
			else
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bTalk = FALSE;
			}

			if(bListen)
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListemE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bListen = TRUE;
			}
			else
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bListen = FALSE;
			}

			if(bRecode)
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordE);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bRecode = TRUE;
			}
			else
			{
				g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);
				g_cFullUpDlg[g_PubData.g_iDownIndex].m_bRecode = FALSE;
			}


		}
		g_PubData.g_bDragDown = FALSE;
		g_cFullUpDlg[g_PubData.g_iDownIndex].Invalidate();
		g_cFullUpDlg[iUpIndex].Invalidate();

		if(g_PubData.g_bAllFullScreen)//�໭��ȫ��ģʽʱ�Խ����������ò�����
		{
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
			g_cFullUpDlg[g_PubData.g_iDownIndex].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);

			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
			g_cFullUpDlg[iUpIndex].GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);

		}

	}

	CDialog::OnLButtonUp(nFlags, point);
	
}
void CFullUpDlg::ShowMenuState()
{
	if(m_iPlayWndIndex < 0)
	{
		return;
	}
	if(g_PubData.g_iStreamType[m_iPlayWndIndex] == j_primary_stream)
	{
		m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_CHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,TRUE);

		m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,FALSE);

		m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,FALSE);
	}
	else if(g_PubData.g_iStreamType[m_iPlayWndIndex] == j_secondary_stream)
	{
		m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,FALSE);

		m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_CHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,TRUE);

		m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,FALSE);

	}
	else if(g_PubData.g_iStreamType[m_iPlayWndIndex] == j_third_stream)
	{
		m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,FALSE);

		m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_UNCHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,FALSE);

		m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_CHECKED);
		m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,TRUE);
	}
	if(g_PubData.g_jDevCap[m_iPlayWndIndex].chn_cap.stream_count  == 1)
	{
		m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,TRUE);
		m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,TRUE);
	}
	else if(g_PubData.g_jDevCap[m_iPlayWndIndex].chn_cap.stream_count  == 2)
	{
		m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,TRUE);
	}
}

void CFullUpDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnRButtonDown(nFlags, point);

	ShowMenuState();   //��ʾ�˵�״̬

	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
	this->GetWindowRect(&m_Rect);

	int iNumber = (int)sqrt((double)g_PubData.g_iCutScreenNum);	
	CRect cRect;
	this->GetClientRect(cRect);

	CRect rectStatic;	   
	CWnd *pWnd= pDlg->GetDlgItem(IDC_STATIC_SCREEN);//����ı���ָ��   
	pWnd->GetClientRect(rectStatic);		//����ı������,���Ͻ�����(0,0)   
	pWnd->ClientToScreen(rectStatic);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������  

	if(m_iFlag == 0)
	{
		m_pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN, point.x+rectStatic.left+((m_iHideIndex%iNumber)*(cRect.Width()+OUTPUT_INTERVAL))
			,point.y+rectStatic.top+((m_iHideIndex/iNumber)*(cRect.Height()+OUTPUT_INTERVAL)) ,this);
	}
	else if(m_iFlag == 1)
	{
		m_pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN, point.x+rectStatic.left, point.y+rectStatic.top,this);
	}
	else if(m_iFlag == 2)
	{
		m_pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN, point.x, point.y,this);
	}
	
	
}
void CFullUpDlg::OnMenuFullscreen()
{
	// TODO: �ڴ���������������
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();

	if(m_iFlag == 2)
	{
		m_pMenu.CheckMenuItem(ID_MENU_FULLSCREEN,MF_UNCHECKED);
		OnLButtonDblClk(0, 0);
		return;

	}
	m_pMenu.CheckMenuItem(ID_MENU_FULLSCREEN,MF_CHECKED);
	//m_pMenu.EnableMenuItem(ID_MENU_FULLSCREEN,TRUE);

	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	pDlg->MoveWindow(0,0,iScreenWidth,iScreenHeight,TRUE);
	pDlg->ShowWindow(SW_SHOW);
	this->MoveWindow(0,0,iScreenWidth,iScreenHeight,TRUE);
	this->ShowWindow(SW_SHOW);
	CRect cRect;
	this->GetClientRect(&cRect);
	this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->MoveWindow(0,0,cRect.Width(),cRect.Height()-22,TRUE);
	this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_STATIC_GROUP)->MoveWindow(0,cRect.Height()-30,cRect.Width(),30,TRUE);
	this->GetDlgItem(IDC_STATIC_GROUP)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_TALK)->MoveWindow(0,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_TALK)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->MoveWindow(31,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_ATTRIBUTE)->ShowWindow(SW_SHOW);
	
	this->GetDlgItem(IDC_BUTTON_LISTEN)->MoveWindow(62,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_LISTEN)->ShowWindow(SW_SHOW);

	this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->MoveWindow(93,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->ShowWindow(SW_SHOW);

	if(g_PubData.g_iLanguageFlag)
		this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,40,20,TRUE);
	else
		this->GetDlgItem(IDC_BUTTON_RECODE)->MoveWindow(124,cRect.Height()-22,30,20,TRUE);
	this->GetDlgItem(IDC_BUTTON_RECODE)->ShowWindow(SW_SHOW);

	pDlg->Hide_Window(m_iHideIndex);

	pDlg->GetDlgItem(IDC_STATIC_SHOWTIME)->ShowWindow(SW_HIDE);
	//ModifyStyle(WS_CHILD,WS_POPUP,NULL);
	//SetParent(GetDesktopWindow());
	m_bMaxofScreen = FALSE;
	m_bIfFullup = FALSE;
	m_iFlag = 2;
	g_PubData.g_iFullScreenId = m_iHideIndex;
	
}
/*
�������ͣ� j_unknown_stream = 0,
j_primary_stream,
j_secondary_stream,
j_third_stream,
j_fourth_stream
*/
void CFullUpDlg::OnMenuMainstream()
{
	// TODO: �ڴ���������������
	if(m_iPlayWndIndex < 0)
	{
		return;
	}
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();


	m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_CHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,TRUE);

	m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,FALSE);

	pDlg->Set_StreamType(m_iPlayWndIndex , j_primary_stream);
	g_PubData.g_iStreamType[m_iPlayWndIndex] = j_primary_stream;

}
void CFullUpDlg::OnMenuSecondstream()
{
	// TODO: �ڴ���������������
	if(m_iPlayWndIndex < 0)
	{
		return;
	}
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();

	m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_CHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,TRUE);

	m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,FALSE);

	pDlg->Set_StreamType(m_iPlayWndIndex , j_secondary_stream);
	g_PubData.g_iStreamType[m_iPlayWndIndex] = j_secondary_stream;
	
}

void CFullUpDlg::OnMenuThirdstream()
{
	// TODO: �ڴ���������������
	if(m_iPlayWndIndex < 0)
	{
		return;
	}
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();

	m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_CHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,TRUE);

	pDlg->Set_StreamType(m_iPlayWndIndex , j_third_stream);
	g_PubData.g_iStreamType[m_iPlayWndIndex] = j_third_stream;
	
}

void CFullUpDlg::OnMenuClose()
{
	// TODO: �ڴ���������������
	if(m_iPlayWndIndex < 0 || g_PubData.g_vStreamHandle[m_iPlayWndIndex] == NULL)
	{
		return;
	}
	

	int iTest = 0;
	for(int i = 0; i< GET_MAX_DEV_NUM; i ++)
	{
		if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex)
		{
			iTest ++;
		}
	}
	if(iTest == 1)  //ֻ��һ�������ڲ���   ����Ƶ���ص�
	{
		
		
		ButtonCloseAll();

		AVP_Stop(g_PubData.g_iChancel[m_iPlayWndIndex]);

		AVP_ReleasePort(g_PubData.g_iChancel[m_iPlayWndIndex]);	
		g_PubData.g_iChancel[m_iPlayWndIndex] =-1;
		if(g_PubData.g_vStreamHandle[m_iPlayWndIndex] != NULL)
		{
			JNetStreamClose(g_PubData.g_vStreamHandle[m_iPlayWndIndex]);
			g_PubData.g_vStreamHandle[m_iPlayWndIndex] = NULL;
		}


		
	}
	else
	{
		AVP_DelPlayWnd(g_PubData.g_iChancel[m_iPlayWndIndex], this->GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd());
		TRACE(_T("end addr =  %x\n"), this->GetSafeHwnd());
	}

	m_pMenu.CheckMenuItem(ID_MENU_MAINSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_MAINSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_SECONDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_SECONDSTREAM,FALSE);

	m_pMenu.CheckMenuItem(ID_MENU_THIRDSTREAM,MF_UNCHECKED);
	m_pMenu.EnableMenuItem(ID_MENU_THIRDSTREAM,FALSE);

	GetDlgItem(IDC_BUTTON_TALK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
	GetDlgItem(IDC_BUTTON_ATTRIBUTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
	GetDlgItem(IDC_BUTTON_TAKEAPICTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RECODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);

	m_bTalk = FALSE;
	m_bListen = FALSE;
	m_bRecode = FALSE;
	m_iPlayWndIndex = -1;
	m_iPlayWndNum = -1;
	m_iPlayFlag = -1;


	this->Invalidate();
}


//ɾ���豸ʱ
void CFullUpDlg::ButtonCloseAll()
{
	if(m_bTalk)
	{
		AVP_StopPickAudio();
		if(g_PubData.g_vTalkHandle[m_iPlayWndIndex] != NULL)
		{
			JNetTalkClose(g_PubData.g_vTalkHandle[m_iPlayWndIndex]);
			g_PubData.g_vTalkHandle[m_iPlayWndIndex] = NULL;
		}
	}

	if(m_bListen)
	{	
		int iRet = -1;
		iRet = AVP_EnableAudio(g_PubData.g_iChancel[m_iPlayWndIndex], FALSE);
		if(iRet != 0)
		{
			//AfxMessageBox(_T("�رռ���ʧ��"));
			return;
		}
	}

	

}


void CFullUpDlg::OnBnClickedButtonTalk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();

	if( !m_bTalk )
	{
		if( pDlg->VideoTalk(m_iPlayWndIndex) )
		{
	
			for(int i = 0; i< GET_MAX_DEV_NUM; i++) //����ͬһ�豸�Ĵ�����Ϊ�Խ�״̬
			{
				if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
				{
					g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkE);
					g_cFullUpDlg[i].m_bTalk = TRUE;
					g_cFullUpDlg[i].Invalidate();
				}
			}
		}	
	}
	else
	{
		AVP_EnableAudio(g_PubData.g_iChancel[m_iPlayWndIndex], FALSE);
		AVP_StopPickAudio();
		if(g_PubData.g_vTalkHandle[m_iPlayWndIndex] != NULL)
		{
			JNetTalkClose(g_PubData.g_vTalkHandle[m_iPlayWndIndex]);
			g_PubData.g_vTalkHandle[m_iPlayWndIndex] = NULL;
		}
		g_PubData.g_bTalk[m_iPlayWndIndex] = FALSE;
		
		for(int i = 0; i< GET_MAX_DEV_NUM; i++) 
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
			{
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_TALK)->SetWindowText(g_PubData.g_strTalkS);
				g_cFullUpDlg[i].m_bTalk = FALSE;
				g_cFullUpDlg[i].Invalidate();
			}
		}
	}

}

void CFullUpDlg::OnBnClickedButtonAttribute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CCAttributeDlg cAttribute;
	g_PubData.g_iAttributeIng = m_iPlayWndIndex;
	if(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng] == NULL)
	{
		//AfxMessageBox(_T("û���豸"));
		return;
	}
	g_PubData.g_iPlayWndFlag = -1;
	cAttribute.DoModal();

}

HBRUSH CFullUpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	CBrush   brush(RGB(255,255,255)); 
	if(pWnd-> GetDlgCtrlID() == IDC_STATIC_SHOWVIDEO)
	{
		
		CRect   rect;  
		pDC->SelectObject(&brush);  
		CWnd   *p_staticwnd=GetDlgItem(IDC_STATIC_SHOWVIDEO); 
		p_staticwnd-> GetWindowRect(&rect);  
		pDC-> Rectangle(&rect); 
		pDC->SetBkMode(TRANSPARENT); 
	}
	
	return (HBRUSH)brush;
// 	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SHOWVIDEO )
// 	{
// 		pDC->SetTextColor(RGB(255,0,0));  //������ɫ
// 		pDC->SetBkColor(RGB(0, 0, 255));   //���屳��ɫ  
// 		return (HBRUSH)::GetStockObject(WHITE_BRUSH);  
// 
// 	}
// 	else
// 	{
// 		return hbr;
// 	}
	
}


//ץ��
void CFullUpDlg::OnBnClickedButtonTakeapicture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray strArrallSecons;
	CStringArray strArrKey;
	CStringArray strArrKeyValue;
	g_PubData.g_iniFile.GetAllSections(strArrallSecons);

	if(strArrallSecons.GetAt(0) == _T(""))
	{
		return;
	}
	g_PubData.g_iniFile.GetAllKeysAndValues(strArrallSecons.GetAt(0),strArrKey,strArrKeyValue);
	CString strPath = _T("");
	strPath = strArrKeyValue.GetAt(0);
	if(strPath == _T(""))
	{
		//AfxMessageBox(_T("��������ͼƬ����·��"));
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("��������ͼƬ����·��"));
		else
			AfxMessageBox(_T("Please set the picture placed path!"));
		return;
	}


	if(!PathFileExists(strPath))
	{
		::_mkdir(strPath); 
	}

	//��Ƭ������ = ip + ץ�Ŀ�ʼʱ�� + ��׺
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();	
	CString strPictureName = g_PubData.g_strArrayPlaySuccessIp.GetAt(m_iPlayWndIndex);
	CString strPictureTime = _T("");
	strPictureTime.Format(_T("_%d%02d%02d%02d%02d%02d"),cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),
									cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	strPictureName += strPictureTime;
	strPictureName += _T(".bmp");
	strPath += _T("\\");
	strPath += strPictureName;
	int iRet = -1;
	iRet = AVP_Capture(g_PubData.g_iChancel[m_iPlayWndIndex], strPath.GetBuffer(0));
	if(iRet != 0)
	{
		AfxMessageBox(_T("ץͼʧ��"));
		return ;
	}

	strPath.ReleaseBuffer();
}

//����
void CFullUpDlg::OnBnClickedButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;
	if(!m_bListen)
	{
		iRet = AVP_EnableAudio(g_PubData.g_iChancel[m_iPlayWndIndex], TRUE);
		if(iRet != 0)
		{
			//AfxMessageBox(_T("����ʧ��"));
			return;
		}
		for(int i = 0; i< GET_MAX_DEV_NUM; i++) //����ͬһ�豸�Ĵ�����Ϊ¼��״̬
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
			{
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListemE);
				g_cFullUpDlg[i].m_bListen = TRUE;
				g_cFullUpDlg[i].Invalidate();
			}
		}
	}
	else
	{	
		iRet = AVP_EnableAudio(g_PubData.g_iChancel[m_iPlayWndIndex], FALSE);
		if(iRet != 0)
		{
			//AfxMessageBox(_T("�رռ���ʧ��"));
			return;
		}
		for(int i = 0; i< GET_MAX_DEV_NUM; i++) //����ͬһ�豸�Ĵ�����Ϊ¼��״̬
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
			{
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_LISTEN)->SetWindowText(g_PubData.g_strListenS);
				g_cFullUpDlg[i].m_bListen = FALSE;
				g_cFullUpDlg[i].Invalidate();
			}
		}

	}

}

//�ֶ�¼��
void CFullUpDlg::OnBnClickedButtonRecode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CStringArray strArrallSecons;
	CStringArray strArrKey;
	CStringArray strArrKeyValue;
	g_PubData.g_iniFile.GetAllSections(strArrallSecons);

	if(strArrallSecons.GetAt(0) == _T(""))
	{
		return;
	}
	g_PubData.g_iniFile.GetAllKeysAndValues(strArrallSecons.GetAt(0),strArrKey,strArrKeyValue);
	CString strPath = _T("");
	strPath = strArrKeyValue.GetAt(1);
	if(strPath == _T(""))
	{
		//AfxMessageBox(_T("��������¼�����·��"));
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("��������¼�����·��"));
		else
			AfxMessageBox(_T("Please set the video placed path!"));
		return;
	}

	//�ļ��в����ھʹ���
	if(!PathFileExists(strPath))
	{
		::_mkdir(strPath); 
	}
	COleDateTime cTime;
	cTime = COleDateTime::GetCurrentTime();	

	//¼������� = ip + ¼��ʼʱ�� + ��׺
	CString videoTime = _T("");
	CString strVideoName = g_PubData.g_strArrayPlaySuccessIp.GetAt(m_iPlayWndIndex);
	videoTime.Format(_T("_%d%02d%02d%02d%02d%02d"),cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),
		cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	strVideoName += videoTime;
	strVideoName += _T(".jav");
	strPath += _T("\\");
	strPath += strVideoName;

	CClient_DemoDlg *pDlg=(CClient_DemoDlg *)AfxGetMainWnd();
	if( !m_bRecode )
	{
		g_PubData.g_iRecFileID[m_iPlayWndIndex] = AVP_CreateRecFile(strPath, AVP_PROTOCOL_JPF, Encoder_DM365);

		for(int i = 0; i< GET_MAX_DEV_NUM; i++) //����ͬһ�豸�Ĵ�����Ϊ¼��״̬
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
			{
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordE);
				g_cFullUpDlg[i].m_bRecode = TRUE;
				g_cFullUpDlg[i].Invalidate();
			}
		}
		
	}
	else
	{
		if(g_PubData.g_iRecFileID[m_iPlayWndIndex] >= 0)
		{

			int iRet = AVP_CloseRecFile(g_PubData.g_iRecFileID[m_iPlayWndIndex]);
			g_PubData.g_iRecFileID[m_iPlayWndIndex] = -1;
		}
		for(int i = 0; i< GET_MAX_DEV_NUM; i++) 
		{
			if(g_cFullUpDlg[i].m_iPlayWndIndex == m_iPlayWndIndex )
			{
				g_cFullUpDlg[i].GetDlgItem(IDC_BUTTON_RECODE)->SetWindowText(g_PubData.g_strRecordS);
				g_cFullUpDlg[i].m_bRecode = FALSE;
				g_cFullUpDlg[i].Invalidate();
			}
		}	
	}
}


void CFullUpDlg::DeviceClose()
{
	OnBnClickedButtonTalk();
	OnBnClickedButtonListen();
	OnBnClickedButtonRecode();
}


BOOL CFullUpDlg::PreTranslateMessage(MSG* pMsg) 
{
	//ESC27,Enter13
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 27 )
	{	
		return FALSE;
	}
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 13 )
	{
		return FALSE;
	}


	return CDialog::PreTranslateMessage(pMsg);
}