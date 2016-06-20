// ElevatorSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "ElevatorSet.h"
#include "Pub_Data.h"

// CElevatorSet �Ի���



IMPLEMENT_DYNAMIC(CElevatorSet, CDialog)

CElevatorSet::CElevatorSet(CWnd* pParent /*=NULL*/)
	: CDialog(CElevatorSet::IDD, pParent)
	, m_cstrItemTextEdit(_T(""))
{
	ZeroMemory(&m_elevatorCfg, sizeof(m_elevatorCfg));
}

CElevatorSet::~CElevatorSet()
{
}

void CElevatorSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_THETOP, m_editTop);
	DDX_Control(pDX, IDC_EDIT2, m_editCurrent);
	DDX_Control(pDX, IDC_LIST_FLOOR, m_floorList);
	DDX_Control(pDX, IDC_EDIT_LISTEDIT, m_SubItemEdit);
	DDX_Text(pDX, IDC_EDIT_LISTEDIT, m_cstrItemTextEdit);
	DDX_Control(pDX, IDC_EDIT_ADD, m_loopAdd);
	DDX_Control(pDX, IDC_EDIT_TEXTX, m_showTextX);
	DDX_Control(pDX, IDC_EDIT_TEXTY, m_showTextY);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_showTextColor);
}


BEGIN_MESSAGE_MAP(CElevatorSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETTOP, &CElevatorSet::OnBnClickedButtonSettop)
	ON_BN_CLICKED(IDC_BUTTON_SETCURRENT, &CElevatorSet::OnBnClickedButtonSetcurrent)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CElevatorSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CElevatorSet::OnBnClickedButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FLOOR, &CElevatorSet::OnNMDblclkListFloor)
	ON_EN_KILLFOCUS(IDC_EDIT_LISTEDIT, &CElevatorSet::OnEnKillfocusEditListedit)
	ON_BN_CLICKED(IDC_BUTTON_SETLOOPADD, &CElevatorSet::OnBnClickedButtonSetloopadd)
END_MESSAGE_MAP()


// CElevatorSet ��Ϣ�������
BOOL CElevatorSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SubItemEdit.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SETCURRENT)->ShowWindow(SW_HIDE);

	m_floorList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	CRect rc;
	m_floorList.GetWindowRect(&rc);
	int nWidth = rc.Width() / 2;
	

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_floorList.InsertColumn(0 , _T("¥��ID"), 2, 100, -1);
		m_floorList.InsertColumn(1 , _T("¥�����"), 2, 100,-1);

		m_showTextColor.EnableAutomaticButton(_T("Ĭ��ֵ"), RGB(0, 0, 0)); 
		m_showTextColor.EnableOtherButton(_T("������ɫ")); 
		m_showTextColor.SetColor((COLORREF)-1); 
		m_showTextColor.SetColumnsNumber(10);     
	}
	else
	{
		m_floorList.InsertColumn(0 , _T("Floor ID "), 2, 100, -1);
		m_floorList.InsertColumn(1 , _T("Floor alias"), 2, 100,-1);

		m_showTextColor.EnableAutomaticButton(_T("Windows default"), RGB(0, 0, 0)); 
		m_showTextColor.EnableOtherButton(_T("Other colors ")); 
		m_showTextColor.SetColor((COLORREF)-1); 
		m_showTextColor.SetColumnsNumber(10);     
	}

	return TRUE;
}

void CElevatorSet::OnBnClickedButtonSettop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_floorList.DeleteAllItems();

	CString strCount;
	m_editTop.GetWindowText(strCount);
	int iCount = _ttoi(strCount);
	m_elevatorCfg.thetop = iCount;
	CString strID = _T("");
	CString strText = _T("");
	for(int i = 0; i < iCount; i ++)
	{
		strID.Format(_T("%d"), i+1);
		m_floorList.InsertItem(i,strID);
		strText.Format(_T("%s"), m_elevatorCfg.layername[i]);
		m_floorList.SetItemText(i,1, strText);
	}
}

void CElevatorSet::OnBnClickedButtonSetcurrent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CElevatorSet::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ELEVATOR_CFG, (char *)&m_elevatorCfg, sizeof(m_elevatorCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
}

void CElevatorSet::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	CString strText = _T("");

	m_editTop.GetWindowText(strText);
	m_elevatorCfg.thetop = _ttoi(strText);

	
	m_editCurrent.GetWindowText(strText);
	m_elevatorCfg.thecurrent = _ttoi(strText) - 1;


	m_showTextX.GetWindowText(strText);
	m_elevatorCfg.osd_display_x = _ttoi(strText);

	m_showTextY.GetWindowText(strText);
	m_elevatorCfg.osd_display_y =  _ttoi(strText);

	if(m_elevatorCfg.osd_display_x > 704 || m_elevatorCfg.osd_display_y > 576 ||
	   m_elevatorCfg.osd_display_x < 0 || m_elevatorCfg.osd_display_y < 0)
	{
		AfxMessageBox(_T("�����������!"));
		return;
	}
	

	m_elevatorCfg.osd_display_color = m_showTextColor.GetColor();

	for(int i = 0; i < m_elevatorCfg.thetop; i ++)
	{
		strText = m_floorList.GetItemText(i,1);
		if(strText.GetLength() >= 20)
		{
			CString strText;
			strText.Format(_T("�� %d ��¥��������ù�����"), i+1);
			AfxMessageBox(strText);
			return;

		}
		memset(m_elevatorCfg.layername[i], 0, 20);
		memcpy(m_elevatorCfg.layername[i], strText, strText.GetLength());
	}
	strText.ReleaseBuffer();
	
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ELEVATOR_CFG, (char *)&m_elevatorCfg, sizeof(m_elevatorCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
}



int CElevatorSet::RedrawWindow()
{

	CString strText = _T("");
	strText.Format(_T("%d"), m_elevatorCfg.thetop);
	m_editTop.SetWindowText(strText);

	strText.Format(_T("%d"),m_elevatorCfg.thecurrent+1);
	m_editCurrent.SetWindowText(strText);
	
	m_showTextColor.SetColor(m_elevatorCfg.osd_display_color);

	strText.Format(_T("%d"), m_elevatorCfg.osd_display_x);
	m_showTextX.SetWindowText(strText);

	strText.Format(_T("%d"), m_elevatorCfg.osd_display_y);
	m_showTextY.SetWindowText(strText);

	strText.ReleaseBuffer();

	OnBnClickedButtonSettop();

	return 0;
}



void CElevatorSet::OnNMDblclkListFloor(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
	if(pNMListCtrl->iSubItem == 0)
		return;
	if(pNMListCtrl->iItem != -1)  
	{  
		CRect rect,dlgRect;  
		//��õ�ǰ�еĿ������Ӧ����û��������   
		//�˴����û�õ�����rect���ο������ÿ��   
		//�����һ��ʱ���صĿ�������еĿ�ȣ���Ҳ��֪��Ϊɶ   
		int width = m_floorList.GetColumnWidth(pNMListCtrl->iSubItem);  
		m_floorList.GetSubItemRect(pNMListCtrl->iItem,pNMListCtrl->iSubItem,LVIR_BOUNDS,rect);  
		//����ѡ����б�������   
		//�����Ϊ�������������б�ؼ�һ��CEdit   
		//������Ҫ�����б������   
		//�Լ��������Ӧ�����к�����   
		m_listSelFlag[0] = 1;//�б�1   
		m_listSelFlag[1] = pNMListCtrl->iItem;  
		m_listSelFlag[2] = pNMListCtrl->iSubItem;  
	
		//���listctrl���ο�   
		//��ø��Ի����λ���Ե���CEdit����ʾλ�ã�������������   
		m_floorList.GetWindowRect(&dlgRect);  
		//�����븸���ڶ�Ӧ   
		ScreenToClient(&dlgRect);  
		int height = rect.Height();  
		rect.top += (dlgRect.top+1);  
		rect.left += (dlgRect.left+1);  
		rect.bottom = rect.top+height+2;  
		rect.right = rect.left+width+2;  
		m_SubItemEdit.MoveWindow(&rect);  
		m_SubItemEdit.ShowWindow(SW_SHOW);  
		m_SubItemEdit.SetFocus();  
	}  


	//*pResult = 0;
}


void CElevatorSet::SetListItemText(void)  
{  
	UpdateData(TRUE);  
	//AfxMessageBox(cstrItemTextEdit);   
// 	if(m_listSelFlag[0] == 2)//�����б�   
// 	{  
// 		//�˴���m_cstrItemTextEdit��CEdit�ؼ����ַ�����������   
// 		m_ListCtrlNotSell.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
// 		//���ñ༭���ı�   
// 		m_SubItemEdit.SetWindowText("");  
// 		//���ر༭��   
// 		m_SubItemEdit.ShowWindow(SW_HIDE);  
// 	}  
	if(m_listSelFlag[0] == 1)//�����б�   
	{  
		m_floorList.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
		m_SubItemEdit.SetWindowText("");  
		m_SubItemEdit.ShowWindow(SW_HIDE);  
	}  
	//ǿ��ˢ���б�ؼ��������Ӿ����ио��е㲻ˬ����������^_^��   
	//m_ListCtrlNotSell.Invalidate();  
}  

void CElevatorSet::OnEnKillfocusEditListedit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetListItemText();  
}


BOOL CElevatorSet::PreTranslateMessage(MSG* pMsg)  
{  
	// TODO: �ڴ����ר�ô����/����û���   
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
	{     
		if( GetFocus()->GetDlgCtrlID() == IDC_EDIT2)  
		{  
			if(m_cstrItemTextEdit[0] == 1)  
				m_floorList.SetFocus();//ʹ�б�ؼ���ý��㣬��CEdit���Զ�ʧȥ���㣬����EN_KILLFOCUS��Ϣ   
// 			if(m_cstrItemTextEdit[0] == 2)  
// 				m_ListCtrlNotSell.SetFocus();  
		}  
		return TRUE;  
	}  
	return CDialog::PreTranslateMessage(pMsg);  
}  

void CElevatorSet::OnBnClickedButtonSetloopadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString strText = _T("");
	m_loopAdd.GetWindowText(strText);
	int nIndex = _ttoi(strText);
	if(nIndex < 1)
	{
		AfxMessageBox(_T("��������"));
		return;
	}

	CString strIndex = m_floorList.GetItemText(nIndex-1, 1);
	int iValue = _ttoi(strIndex);
	int j = 0;

	for(int i = nIndex-1; i < m_elevatorCfg.thetop; i++)
	{
		strText.Format(_T("%d"), iValue+j);
		m_floorList.SetItemText(i, 1, strText);
		j++;
	}

}
