// LCD_Sample.h : Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CLCD_SampleApp:
// Siehe LCD_Sample.cpp f�r die Implementierung dieser Klasse
//

class CLCD_SampleApp : public CWinApp
{
public:
	CLCD_SampleApp();

// �berschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CLCD_SampleApp theApp;