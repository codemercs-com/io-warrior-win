// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__65AB8F5E_B895_4216_8C5B_6B3B3F9C73FA__INCLUDED_)
#define AFX_STDAFX_H__65AB8F5E_B895_4216_8C5B_6B3B3F9C73FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// switch off deprecated warnings
#define _CRT_SECURE_NO_DEPRECATE 1

#include <windows.h>

#include <stdlib.h>
#include <stdio.h>

#include <SetupAPI.h>
#include <cfgmgr32.h>
#include <dbt.h>
#include "hidsdi.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__65AB8F5E_B895_4216_8C5B_6B3B3F9C73FA__INCLUDED_)
