// KeyMatrix.h : Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CKeyMatrixApp:
// Siehe KeyMatrix.cpp für die Implementierung dieser Klasse
//

class CKeyMatrixApp : public CWinApp
{
public:
	CKeyMatrixApp();

// Überschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CKeyMatrixApp theApp;