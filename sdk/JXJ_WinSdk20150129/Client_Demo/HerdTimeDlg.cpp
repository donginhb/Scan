// HerdTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HerdTimeDlg.h"


// CHerdTimeDlg �Ի���

IMPLEMENT_DYNAMIC(CHerdTimeDlg, CDialog)

CHerdTimeDlg::CHerdTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHerdTimeDlg::IDD, pParent)
{

}

CHerdTimeDlg::~CHerdTimeDlg()
{
}

void CHerdTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_week);
	DDX_Control(pDX, IDC_CHECK_FULLDAYREC, m_fullDayEnable);
	DDX_Control(pDX, IDC_CHECK_ENABLE1, m_enable1);
	DDX_Control(pDX, IDC_CHECK_ENABLE2, m_enable2);
	DDX_Control(pDX, IDC_CHECK_ENABLE3, m_enable3);
	DDX_Control(pDX, IDC_CHECK_ENABLE4, m_enable4);
	DDX_Control(pDX, IDC_START1, m_startTime1);
	DDX_Control(pDX, IDC_START2, m_startTime2);
	DDX_Control(pDX, IDC_START3, m_startTime3);
	DDX_Control(pDX, IDC_START4, m_startTime4);
	DDX_Control(pDX, IDC_END1, m_endTime1);
	DDX_Control(pDX, IDC_END2, m_endTime2);
	DDX_Control(pDX, IDC_END3, m_endTime3);
	DDX_Control(pDX, IDC_END4, m_endTime4);
}


BEGIN_MESSAGE_MAP(CHerdTimeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CHerdTimeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHerdTimeDlg ��Ϣ�������
BOOL CHerdTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

void CHerdTimeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
