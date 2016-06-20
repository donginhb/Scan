
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#include "..\inc\mb_api.h"
#include "..\inc\JNetSDK.h"
#include "..\inc\stdint.h"
#include "..\inc\Jtype.h"
#include "..\inc\AVPlayer.h"

#include "MessageBoxDlg.h"


#pragma comment(lib, "..\\lib\\JNetSDK")
#pragma comment(lib, "..\\lib\\AVPlayer")





#define DRAW_MAX_COUNT		2048*10
#define DRAW_MAX_TROUGH_COUNT		16

#define GET_MAX_DEV_NUM	    81   //���Ļ�ȡ�豸����
#define OUTPUT_INTERVAL     3  
#define GET_MAX_IP      50

//��ѯ�豸
typedef struct queryDevConfig
{
	char				dst_id[MB_SERIAL_LEN];
	j_Device_T			stDev;
}DevConfig;




//�豸�������µĽ���
extern JUpgradeProgress  upDev;



typedef enum
{	
	Encoder_Unknow	= -1,
	Encoder_DM365	= 0,
	Encoder_DM368	= 1,
	Encoder_DM8127	= 2,
	Encoder_DM8168	= 3,
	Encoder_HI		= 0x100-1,
	Encoder_3507	= 0x100,
	Encoder_3510,
	Encoder_3511,
	Encoder_3512,
	Encoder_3515,
	Encoder_3516,
	Encoder_3517,
	Encoder_3518,
	Encoder_3520,
	Encoder_3521,
	Encoder_3531,
	Encoder_3532,
	Encoder_3531_3532,
}eEncoderType;






#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


