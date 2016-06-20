// DeviceUpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "DeviceUpdateDlg.h"
#include "Pub_Data.h"
#include "CAttributeDlg.h"

// CDeviceUpdateDlg �Ի���

IMPLEMENT_DYNAMIC(CDeviceUpdateDlg, CDialog)


CDeviceUpdateDlg::CDeviceUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceUpdateDlg::IDD, pParent)
{
	m_lUpgHandle = NULL;
}

CDeviceUpdateDlg::~CDeviceUpdateDlg()
{
	DestroyWindow();
}

void CDeviceUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_eShowFilePath);
	DDX_Control(pDX, IDC_PROGRESS1, m_UpdateProgress);
}


BEGIN_MESSAGE_MAP(CDeviceUpdateDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CDeviceUpdateDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CDeviceUpdateDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_CLOSE, &CDeviceUpdateDlg::OnBnClickedButtonDeviceClose)
	ON_BN_CLICKED(IDC_BUTTON_OUT_AGAIN, &CDeviceUpdateDlg::OnBnClickedButtonOutAgain)
	ON_BN_CLICKED(IDC_BUTTON_MOREN, &CDeviceUpdateDlg::OnBnClickedButtonMoren)
	ON_BN_CLICKED(IDC_BUTTON_DESTROYCHECK, &CDeviceUpdateDlg::OnBnClickedButtonDestroycheck)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_CHECK, &CDeviceUpdateDlg::OnBnClickedButtonLightCheck)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDeviceUpdateDlg ��Ϣ�������
BOOL CDeviceUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_UpdateProgress.SetRange(0,100);
	m_UpdateProgress.SetStep(1);
	m_UpdateProgress.SetPos(0);
	m_UpdateProgress.ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
	
	return TRUE;
}
void CDeviceUpdateDlg::OnBnClickedButtonOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE, _T("bin"),NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T(" Files (*.bin)|*.bin|(*.upg)|*.upg|All Files (*.*)|*.*||"),this);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();  //��ȡ�ļ�������·��
		m_eShowFilePath.SetWindowText(m_strPath);
	}
	else
	{
		return;
	}
}
void CDeviceUpdateDlg::UpdateEnable(bool bFlag)
{
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_DESTROYCHECK)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_DEVICE_CLOSE)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_LIGHT_CHECK)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_MOREN)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUTTON_OUT_AGAIN)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_FILEPATH)->EnableWindow(bFlag);
}

DWORD CDeviceUpdateDlg::ControlThreadFun(LPVOID lpThreadParameter)
{
	CDeviceUpdateDlg *pDlg=(CDeviceUpdateDlg*)lpThreadParameter;
	while(1)
	{
		if(g_PubData.g_iControlDevRet == DETECT_DEAL_PIX_START)
		{
			pDlg->UpdateEnable(FALSE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_SHOW);
		}
		else if(g_PubData.g_iControlDevRet == DETECT_DEAL_PIX_END)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox( _T("Success"));
			return 0;
		}
		else if(g_PubData.g_iControlDevRet == DETECT_DEAL_PIX_FAIL)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox( _T("failed"));
			return 0;
		}
		else if(g_PubData.g_iControlDevRet == DETECT_DEAL_PIX_TIMEOUT)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox( _T("Timeout"));
			return 0;
		}
		else if(g_PubData.g_iControlDevRet == REGULATE_IRIS_START)
		{
			pDlg->UpdateEnable(FALSE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_SHOW);
		}
		else if(g_PubData.g_iControlDevRet == REGULATE_IRIS_END)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox( _T("Success"));
			return 0;
		}
		else if(g_PubData.g_iControlDevRet == REGULATE_IRIS_FAIL)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox( _T("Failed"));
			return 0;
		}
		else if(g_PubData.g_iControlDevRet == REGULATE_IRIS_TIMEOUT)
		{
			pDlg->UpdateEnable(TRUE);
			pDlg->GetDlgItem(IDC_STATIC_CONTROLDEV)->ShowWindow(SW_HIDE);
			g_PubData.g_iControlDevRet = -1;
			AfxMessageBox(_T("Timeout"));
			return 0;
		}
		Sleep(1000);
		if(g_PubData.g_iControlDevRet < 0)
		{
			return 0;
		}
	}
	
	return 0;
}

DWORD CDeviceUpdateDlg::ThreadFun(LPVOID lpThreadParameter)
{
	CDeviceUpdateDlg *pDlg=(CDeviceUpdateDlg*)lpThreadParameter;
	while(upDev.percent!=100)
	{
		//%20 ֮ǰΪ�������� �������֮ǰ�豸���� ������ʧ�ܣ� ֮�������ɹ�
		if(upDev.percent < 20 && g_PubData.g_bUpgDeviceClose)
		{
			pDlg->m_UpdateProgress.SetPos(0);
			pDlg->UpdateEnable(TRUE);
			pDlg->m_UpdateProgress.ShowWindow(SW_HIDE);
			g_PubData.g_bUpgDeviceClose =FALSE;
			AfxMessageBox(_T("Upgrade error!"));	
		}
		
		Sleep(1000);
		if(!IsWindow(pDlg->m_UpdateProgress.m_hWnd))
		{
			return 0;
		}
		pDlg->m_UpdateProgress.SetPos(upDev.percent);	
	}	
	if (upDev.percent==100)
	{
		pDlg->m_UpdateProgress.SetPos(0);
		pDlg->UpdateEnable(TRUE);
		pDlg->m_UpdateProgress.ShowWindow(SW_HIDE);
		g_PubData.g_bUpgDeviceClose = FALSE;
		upDev.percent = 0;
		AfxMessageBox(_T("Upgrade success!"));	
	}

	if(upDev.percent == -100) //����ʧ��
	{
		pDlg->m_UpdateProgress.SetPos(0);
		pDlg->UpdateEnable(TRUE);
		pDlg->m_UpdateProgress.ShowWindow(SW_HIDE);
		g_PubData.g_bUpgDeviceClose = FALSE;
		upDev.percent = 0;
		AfxMessageBox(_T("Upgrade error!"));
	}


	return 0;
}

void CDeviceUpdateDlg::OnBnClickedButtonUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilePath(_T(""));
	m_eShowFilePath.GetWindowText(strFilePath);
	if(strFilePath == _T(""))
	{
		
		AfxMessageBox(_T("Please select the upgrade file!"));	
		return;
	}
	if(g_PubData.g_DeviceClose[g_PubData.g_iAttributeIng])
	{
		AfxMessageBox(_T("Device disconnected!"));	
		return;
	}
	int iRet = -1;
	//iRet = jcu_net_upg(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng], m_strPath.GetBuffer(0));
	
	JNetUpgOpen(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng], m_strPath.GetBuffer(0), m_lUpgHandle);
	if( m_lUpgHandle < 0 )
	{
		AfxMessageBox(_T("Upgrade error!"));	
		return;
	}
	m_strPath.ReleaseBuffer();

	UpdateEnable(FALSE);
	m_UpdateProgress.ShowWindow(SW_SHOW);
	//�����������߳�
	HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFun,this,0,0);
	CloseHandle(hThread);
}


void CDeviceUpdateDlg::OnBnClickedButtonDeviceClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*SHUTDOWN_DEVICE  = 0x01,
	RESTART_DEVICE   = 0x02,
	RESTORE_DEFAULT  = 0x03,
	DETECT_DEAL_PIX  = 0x04,
	DETECT_IRIS 	= 0x05,
*/
	JControlDevice controlDevice;
	controlDevice.command = SHUTDOWN_DEVICE;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_CONTROL_DEV, (char *)&controlDevice, sizeof(controlDevice), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Shutdown failure!"));	
		return;
	}
}

void CDeviceUpdateDlg::OnBnClickedButtonOutAgain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	JControlDevice controlDevice;
	controlDevice.command = RESTART_DEVICE;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_CONTROL_DEV, (char *)&controlDevice, sizeof(controlDevice), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Restar failure!"));
		return;
	}
}

void CDeviceUpdateDlg::OnBnClickedButtonMoren()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	JControlDevice controlDevice;
	controlDevice.command = RESTORE_DEFAULT;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_CONTROL_DEV, (char *)&controlDevice, sizeof(controlDevice), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Restore the default failure!"));
		return;
	}
}

void CDeviceUpdateDlg::OnBnClickedButtonDestroycheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	JControlDevice controlDevice;
	controlDevice.command = DETECT_DEAL_PIX;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_CONTROL_DEV, (char *)&controlDevice, sizeof(controlDevice), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Bad pixel detection failed!"));
		return;
	}
	HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ControlThreadFun,this,0,0);
	CloseHandle(hThread);
}

void CDeviceUpdateDlg::OnBnClickedButtonLightCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	JControlDevice controlDevice;
	controlDevice.command = DETECT_IRIS;
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_CONTROL_DEV, (char *)&controlDevice, sizeof(controlDevice), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(_T("Iris detection failed!"));
		return;
	}
	HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ControlThreadFun,this,0,0);
	CloseHandle(hThread);
}


void CDeviceUpdateDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

HBRUSH CDeviceUpdateDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_CONTROLDEV )
	{
		pDC->SetTextColor(RGB(255,0,0));  //������ɫ
		//pDC->SetBkColor(RGB(0, 0, 255));   //���屳��ɫ  
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);  

	}

	return hbr;
}
