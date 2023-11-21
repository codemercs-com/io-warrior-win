// LCD_Sample.h : Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CLCD_SampleApp:
// Siehe LCD_Sample.cpp für die Implementierung dieser Klasse
//

class CLCD_SampleApp : public CWinApp
{
public:
	CLCD_SampleApp();

// Überschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CLCD_SampleApp theApp;