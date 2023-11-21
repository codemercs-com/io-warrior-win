// KeyMatrixDlg.h : Headerdatei
//

#pragma once
#include "iowkit.h"
#include "iowkitcustom.h"
#include "afxwin.h"


// CKeyMatrixDlg-Dialogfeld
class CKeyMatrixDlg : public CDialog
{
// Konstruktion
public:
	CKeyMatrixDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_KEYMATRIX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedClear();

	IOWKIT_HANDLE ioHandle;
	CListBox cList;
	CStatic cKey[64];
	UCHAR bytes[4];

	void DrawBitmap(CStatic &key, UINT bitmap);
	void DecodeButton(UCHAR b0);
};
