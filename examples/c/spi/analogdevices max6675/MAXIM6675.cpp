// MAXIM6675.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MAXIM6675.h"
#include "MAXIM6675Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMAXIM6675App

BEGIN_MESSAGE_MAP(CMAXIM6675App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMAXIM6675App construction

CMAXIM6675App::CMAXIM6675App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMAXIM6675App object

CMAXIM6675App theApp;


// CMAXIM6675App initialization

BOOL CMAXIM6675App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMAXIM6675Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
