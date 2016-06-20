// GB28181Set.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "GB28181Set.h"
#include "Pub_Data.h"


// CGB28181Set �Ի���


IMPLEMENT_DYNAMIC(CGB28181Set, CDialog)

CGB28181Set::CGB28181Set(CWnd* pParent /*=NULL*/)
	: CDialog(CGB28181Set::IDD, pParent)
	, m_cstrItemTextEdit(_T(""))
{

	ZeroMemory(&m_gb28181, sizeof(m_gb28181));
	ZeroMemory(&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg));
	m_iSelChannel = 0;
}

CGB28181Set::~CGB28181Set()
{
	DestroyWindow();
}

void CGB28181Set::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVICEID, m_DEVid);
	DDX_Control(pDX, IDC_EDIT_DEVICEPASS, m_DEVpass);
	DDX_Control(pDX, IDC_EDITSERVERID, m_SERVERid);
	DDX_Control(pDX, IDC_EDITSERVERIP, m_SERVERip);
	DDX_Control(pDX, IDC_EDITSERVERPORT, m_SERVERport);
	DDX_Control(pDX, IDC_EDITSERVERMSG, m_SERVERmsg);
	DDX_Control(pDX, IDC_EDIT_CHANNELID, m_channelID);
	DDX_Control(pDX, IDC_COMBO_CHANNELNO, m_channelNo);
	DDX_Control(pDX, IDC_LIST_CHANNELID, m_channelIDlist);
	DDX_Control(pDX, IDC_EDIT_EDITCHANNEL, m_SubItemEdit);
	DDX_Text(pDX, IDC_EDIT_EDITCHANNEL, m_cstrItemTextEdit);
}


BEGIN_MESSAGE_MAP(CGB28181Set, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CGB28181Set::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CGB28181Set::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNELNO, &CGB28181Set::OnCbnSelchangeComboChannelno)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CHANNELID, &CGB28181Set::OnNMDblclkListChannelid)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_CHANNELID, &CGB28181Set::OnNMKillfocusListChannelid)
	ON_EN_KILLFOCUS(IDC_EDIT_EDITCHANNEL, &CGB28181Set::OnEnKillfocusEditEditchannel)
END_MESSAGE_MAP()


// CGB28181Set ��Ϣ�������

BOOL CGB28181Set::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_channelID.ShowWindow(SW_HIDE);
	m_channelNo.ShowWindow(SW_HIDE);
	m_SubItemEdit.ShowWindow(SW_HIDE);

	m_channelIDlist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	CRect rc;
	m_channelIDlist.GetWindowRect(&rc);
	int nWidth = rc.Width() / 5;
	m_channelIDlist.InsertColumn(0 , _T("ͨ����"), 2, nWidth-5, -1);
	m_channelIDlist.InsertColumn(1 , _T("ͨ��ID"), 2, nWidth*4-5,-1);

	
	return TRUE;
}


void CGB28181Set::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strText = _T("");
	m_DEVid.GetWindowText(strText);
	memset(m_gb28181.device_id, '\0', sizeof(m_gb28181.device_id));
	memcpy(m_gb28181.device_id, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_DEVpass.GetWindowText(strText);
	memset(m_gb28181.device_pwd, '\0', sizeof(m_gb28181.device_pwd));
	memcpy(m_gb28181.device_pwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SERVERid.GetWindowText(strText);
	memset(m_gb28181.server_id, '\0', sizeof(m_gb28181.server_id));
	memcpy(m_gb28181.server_id, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SERVERip.GetWindowText(strText);
	memset(m_gb28181.server_ip, '\0', sizeof(m_gb28181.server_ip));
	memcpy(m_gb28181.server_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	

	m_SERVERport.GetWindowText(strText);
	m_gb28181.server_port = _ttoi(strText);

	m_SERVERmsg.GetWindowText(strText);
	m_gb28181.msg_port = _ttoi(strText);

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
	

	CString strID;
	for(int i = 0; i < m_channelIDlist.GetItemCount(); i++)
	{
		strID = m_channelIDlist.GetItemText(i, 1);
		memset(m_gb28181ChannelCfg.channel_id[i], '\0', sizeof(m_gb28181ChannelCfg.channel_id[i]));
		memcpy(m_gb28181ChannelCfg.channel_id[i], strID.GetBuffer(0), strID.GetLength());
	}
	strID.ReleaseBuffer();


	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CGB28181Set::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strID;
	if(m_channelNo.GetCurSel() < 0 )
	{
		for(int i = 0; i< g_PubData.g_iChannelNo; i++)
		{
			CString str = _T("");
			str.Format(_T("%d"), i);
			m_channelNo.AddString(str);

			strID.Format(_T("%d"), i+1);
			m_channelIDlist.InsertItem(i,strID);
			m_channelIDlist.SetItemText(i,1, "");
		}
		m_channelNo.SetCurSel(0);
		m_iSelChannel = 0;
	}

	m_iSelChannel = m_channelNo.GetCurSel();
	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
	ReFreshChannelCfgWindow();
}


int CGB28181Set::ReFreshWindow()
{
	CString strText = _T("");
	strText.Format(_T("%s"), m_gb28181.device_id);
	
	m_DEVid.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.device_pwd);
	m_DEVpass.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.server_id);
	m_SERVERid.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.server_ip);
	m_SERVERip.SetWindowText(strText);

	strText.Format(_T("%d"), m_gb28181.server_port);
	m_SERVERport.SetWindowText(strText);

	strText.Format(_T("%d"), m_gb28181.msg_port);
	m_SERVERmsg.SetWindowText(strText);

	return 0;
}



int CGB28181Set::ReFreshChannelCfgWindow()
{
	
	CString strText = _T("");
	for(int i= 0; i < g_PubData.g_iChannelNo; i++)
	{	
		strText.Format(_T("%s"), m_gb28181ChannelCfg.channel_id[i]);
		//gGb28181Set->m_channelID.SetWindowText(strText);

		m_channelIDlist.SetItemText(i, 1, strText);
	}	
	
	return 0;
}


void CGB28181Set::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CGB28181Set::OnCbnSelchangeComboChannelno()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_iSelChannel = m_channelNo.GetCurSel();
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],m_iSelChannel,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}


	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],m_iSelChannel,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
	ReFreshChannelCfgWindow();
}

void CGB28181Set::OnNMDblclkListChannelid(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//*pResult = 0;

	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
	if(pNMListCtrl->iSubItem == 0)
		return;
	if(pNMListCtrl->iItem != -1)  
	{  
		CRect rect,dlgRect;  
		//��õ�ǰ�еĿ������Ӧ����û��������   
		//�˴����û�õ�����rect���ο������ÿ��   
		//�����һ��ʱ���صĿ�������еĿ�ȣ���Ҳ��֪��Ϊɶ   
		int width = m_channelIDlist.GetColumnWidth(pNMListCtrl->iSubItem);  
		m_channelIDlist.GetSubItemRect(pNMListCtrl->iItem,pNMListCtrl->iSubItem,LVIR_BOUNDS,rect);  
		//����ѡ����б�������   
		//�����Ϊ�������������б�ؼ�һ��CEdit   
		//������Ҫ�����б������   
		//�Լ��������Ӧ�����к�����   
		m_listSelFlag[0] = 1;//�б�1   
		m_listSelFlag[1] = pNMListCtrl->iItem;  
		m_listSelFlag[2] = pNMListCtrl->iSubItem;  

		//���listctrl���ο�   
		//��ø��Ի����λ���Ե���CEdit����ʾλ�ã�������������   
		m_channelIDlist.GetWindowRect(&dlgRect);  
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





}


void CGB28181Set::SetListItemText(void)  
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
		m_channelIDlist.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
		m_SubItemEdit.SetWindowText("");  
		m_SubItemEdit.ShowWindow(SW_HIDE);  
	}  
	//ǿ��ˢ���б�ؼ��������Ӿ����ио��е㲻ˬ����������^_^��   
	//m_ListCtrlNotSell.Invalidate();  
}  
void CGB28181Set::OnNMKillfocusListChannelid(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


BOOL CGB28181Set::PreTranslateMessage(MSG* pMsg)  
{  
	// TODO: �ڴ����ר�ô����/����û���   
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
	{     
		if( GetFocus()->GetDlgCtrlID() == IDC_EDIT_EDITCHANNEL)  
		{  
			if(m_listSelFlag[0] == 1)  
				m_channelIDlist.SetFocus();//ʹ�б�ؼ���ý��㣬��CEdit���Զ�ʧȥ���㣬����EN_KILLFOCUS��Ϣ   
			// 			if(m_cstrItemTextEdit[0] == 2)  
			// 				m_ListCtrlNotSell.SetFocus();  
		}  
		return TRUE;  
	}  
	return CDialog::PreTranslateMessage(pMsg);  
}  
void CGB28181Set::OnEnKillfocusEditEditchannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetListItemText();
}
