// MAXIM6675.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMAXIM6675App:
// See MAXIM6675.cpp for the implementation of this class
//

class CMAXIM6675App : public CWinApp
{
public:
	CMAXIM6675App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMAXIM6675App theApp;