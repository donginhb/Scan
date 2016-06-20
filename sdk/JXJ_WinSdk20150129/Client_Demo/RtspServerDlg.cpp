// RtspServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "RtspServerDlg.h"
#include "Pub_Data.h"


// CRtspServerDlg �Ի���

IMPLEMENT_DYNAMIC(CRtspServerDlg, CDialog)

CRtspServerDlg::CRtspServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRtspServerDlg::IDD, pParent)
{

}

CRtspServerDlg::~CRtspServerDlg()
{
}

void CRtspServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_enable);
	DDX_Control(pDX, IDC_EDIT1, m_rtspServerPort);
}


BEGIN_MESSAGE_MAP(CRtspServerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CRtspServerDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CRtspServerDlg::OnBnClickedButtonFlash)
	ON_EN_CHANGE(IDC_EDIT1, &CRtspServerDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRtspServerDlg ��Ϣ�������

BOOL CRtspServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;
}

void CRtspServerDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rtspParam.enable = m_enable.GetCheck();

	CString str;
	m_rtspServerPort.GetWindowText(str);
	m_rtspParam.svr_port = _ttoi(str);


	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RTSP_SVR_CFG, (char *)&m_rtspParam, sizeof(m_rtspParam), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}
}



void CRtspServerDlg::OnBnClickedButtonFlash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RTSP_SVR_CFG, (char *)&m_rtspParam, sizeof(m_rtspParam),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return;
	}
	ReFreshWindow();
}


int CRtspServerDlg::ReFreshWindow()
{
	
	m_enable.SetCheck(m_rtspParam.enable);

	CString str;
	str.Format(_T("%d"), m_rtspParam.svr_port);
	m_rtspServerPort.SetWindowText(str);
	
	return 0;
}

void CRtspServerDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
