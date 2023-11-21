// MAXIM6675Dlg.h : header file
//

#pragma once
#include "iowkit.h"
#include "afxwin.h"
#include "afxcmn.h"


// CMAXIM6675Dlg dialog
class CMAXIM6675Dlg : public CDialog
{
// Construction
public:
	CMAXIM6675Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MAXIM6675_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_font;
public:
	CFont font;
public:
	IOWKIT_HANDLE iowHandle;
public:
	CString m_temperature;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	IOWKIT_SPECIAL_REPORT m_report;
	CProgressCtrl m_progress;
	int m_tempmax;
	int m_tempmin;
public:
	IOWKIT56_SPECIAL_REPORT m_rep56;
	IOWKIT_SPECIAL_REPORT m_rep24;
    UINT m_Pid;
	afx_msg void OnClose();
};
