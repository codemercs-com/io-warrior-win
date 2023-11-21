// LCD_SampleDlg.h : Headerdatei
//

#pragma once
#include "afxcmn.h"
#include "iowkit.h"
#include "afxwin.h"



// CLCD_SampleDlg-Dialogfeld
class CLCD_SampleDlg : public CDialog
{
// Konstruktion
public:
	CLCD_SampleDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_LCD_SAMPLE_DIALOG };

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
	IOWKIT_HANDLE ioHandle_1;
	CListCtrl m_readlist;
	CString m_write;
	CListBox m_reportlist;
	int m_output;
	int m_position;
	int m_iPosition;
	BOOL m_lcdonoff;
	BOOL m_cursoronoff;
public:
	void InsertReport(CString reporter);
	void WriteLine(UCHAR line, CString send);
	afx_msg void OnBnClickedInitiate();
	afx_msg void OnBnClickedLcdclear();
	afx_msg void OnBnClickedLcdhome();
	afx_msg void OnBnClickedWritedata();
	afx_msg void OnBnClickedLcdonoff();
	afx_msg void OnBnClickedLcdcursor();
	afx_msg void OnBnClickedClearreport();
	afx_msg void OnBnClickedReaddata();
	afx_msg void OnBnClickedClearlist();
	afx_msg void OnBnClickedCharfw();
	afx_msg void OnBnClickedCharbw();
	afx_msg void OnClose();
};