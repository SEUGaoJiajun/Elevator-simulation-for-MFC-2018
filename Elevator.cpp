// Elevator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Elevator.h"
#include "MainDlg.h"
#include "SplashWnd.h"
#include "Redo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ���������Ӧ��

BEGIN_MESSAGE_MAP(CElevatorApp, CWinApp)
	
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


//�����๹������������

CElevatorApp::CElevatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
CElevatorApp::~CElevatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

//���еĵ��������

CElevatorApp theApp;


//�������ʼ��

BOOL CElevatorApp::InitInstance()
{
	AfxEnableControlContainer();
    //��׼��ʼ��

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//Ϊ��ʾ����������׼��
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	

	//ʹ��XP��񴰿�
	
		typedef BOOL  (WINAPI *pClassXP)(HWND,BOOL);
		HINSTANCE hInst=NULL;
		hInst=::LoadLibrary("ClassXP.dll");
		if (hInst)
		{
			pClassXP pFunc= (pClassXP)GetProcAddress (hInst,"ClassXP");
			pFunc(NULL,TRUE);		
		}

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/*CString CElevatorApp::OSVer()
{
 	OSVERSIONINFOEX os;
	::ZeroMemory(&os,sizeof(os));
	os.dwOSVersionInfoSize=sizeof(os);
	::GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&os));

	if(os.dwPlatformId==VER_PLATFORM_WIN32_NT && os.dwMajorVersion >=5)
	{
		if(os.dwMinorVersion==0)
			return "Win2000";
		else
			return "WinXP";
	}
	else if(os.dwPlatformId ==VER_PLATFORM_WIN32_WINDOWS)
		return "Win9x";
	else
		return "unknown os";
}

//Ϊ���Ƶ���Ϣ�����صĺ���
/*int CElevatorApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{

	if (MB_USERDEFINE == nType)
	{

		RECT rect;
		::GetClientRect(theApp.GetMainWnd()->m_hWnd,&rect);
		int x = (rect.right - 340 + 1) / 2;
		int y = (rect.bottom - 80 + 1) / 2;

		CRedo dlg;
		
		dlg.Create(IDD_ABOUTBOX, NULL);
		dlg.SetWindowText(lpszPrompt);
		
		dlg.MoveWindow(x,y,400,200, true);
		dlg.ShowWindow(SW_SHOW);
		dlg.UpdateWindow();

		Sleep(3000);

		dlg.DestroyWindow();

		return TRUE;

	}

	return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}*/
