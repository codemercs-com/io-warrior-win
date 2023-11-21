// LED-MatrixDlg.h : header file
//

#pragma once
#include "iowkit.h"
#include "atltypes.h"


// CLEDMatrixDlg dialog
class CLEDMatrixDlg : public CDialog
{
// Construction
public:
	CLEDMatrixDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LEDMATRIX_DIALOG };

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
	IOWKIT_HANDLE iowHandle;
	CString m_value;
	int m_scroll;
	UCHAR bits[512];
	UCHAR bytes[64];
	ULONG Pid;
	int nWalk;
	int m_tScroll;
	int m_nLength;
	CSize m_nSize;
public:
    void TextToBitmap(CString value, CString font,int pos_x, int pos_y, int font_size);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeScrolling();


	afx_msg void OnClose();
};
