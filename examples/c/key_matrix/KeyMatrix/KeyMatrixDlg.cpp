// KeyMatrixDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "KeyMatrix.h"
#include "KeyMatrixDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyMatrixDlg-Dialogfeld




CKeyMatrixDlg::CKeyMatrixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyMatrixDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, cList);

	DDX_Control(pDX, IDC_FIELD1, cKey[0]);
	DDX_Control(pDX, IDC_FIELD2, cKey[1]);
	DDX_Control(pDX, IDC_FIELD3, cKey[2]);
	DDX_Control(pDX, IDC_FIELD4, cKey[3]);
	DDX_Control(pDX, IDC_FIELD5, cKey[4]);
	DDX_Control(pDX, IDC_FIELD6, cKey[5]);
	DDX_Control(pDX, IDC_FIELD7, cKey[6]);
	DDX_Control(pDX, IDC_FIELD8, cKey[7]);
		
	DDX_Control(pDX, IDC_FIELD9, cKey[8]);
	DDX_Control(pDX, IDC_FIELD10, cKey[9]);
	DDX_Control(pDX, IDC_FIELD11, cKey[10]);
	DDX_Control(pDX, IDC_FIELD12, cKey[11]);
	DDX_Control(pDX, IDC_FIELD13, cKey[12]);
	DDX_Control(pDX, IDC_FIELD14, cKey[13]);
	DDX_Control(pDX, IDC_FIELD15, cKey[14]);
	DDX_Control(pDX, IDC_FIELD16, cKey[15]);
		
	DDX_Control(pDX, IDC_FIELD17, cKey[16]);
	DDX_Control(pDX, IDC_FIELD18, cKey[17]);
	DDX_Control(pDX, IDC_FIELD19, cKey[18]);
	DDX_Control(pDX, IDC_FIELD20, cKey[19]);
	DDX_Control(pDX, IDC_FIELD21, cKey[20]);
	DDX_Control(pDX, IDC_FIELD22, cKey[21]);
	DDX_Control(pDX, IDC_FIELD23, cKey[22]);
	DDX_Control(pDX, IDC_FIELD24, cKey[23]);
		
	DDX_Control(pDX, IDC_FIELD25, cKey[24]);
	DDX_Control(pDX, IDC_FIELD26, cKey[25]);
	DDX_Control(pDX, IDC_FIELD27, cKey[26]);
	DDX_Control(pDX, IDC_FIELD28, cKey[27]);
	DDX_Control(pDX, IDC_FIELD29, cKey[28]);
	DDX_Control(pDX, IDC_FIELD30, cKey[29]);
	DDX_Control(pDX, IDC_FIELD31, cKey[30]);
	DDX_Control(pDX, IDC_FIELD32, cKey[31]);
	
	DDX_Control(pDX, IDC_FIELD33, cKey[32]);
	DDX_Control(pDX, IDC_FIELD34, cKey[33]);
	DDX_Control(pDX, IDC_FIELD35, cKey[34]);
	DDX_Control(pDX, IDC_FIELD36, cKey[35]);
	DDX_Control(pDX, IDC_FIELD37, cKey[36]);
	DDX_Control(pDX, IDC_FIELD38, cKey[37]);
	DDX_Control(pDX, IDC_FIELD39, cKey[38]);
	DDX_Control(pDX, IDC_FIELD40, cKey[39]);
		
	DDX_Control(pDX, IDC_FIELD41, cKey[40]);
	DDX_Control(pDX, IDC_FIELD42, cKey[41]);
	DDX_Control(pDX, IDC_FIELD43, cKey[42]);
	DDX_Control(pDX, IDC_FIELD44, cKey[43]);
	DDX_Control(pDX, IDC_FIELD45, cKey[44]);
	DDX_Control(pDX, IDC_FIELD46, cKey[45]);
	DDX_Control(pDX, IDC_FIELD47, cKey[46]);
	DDX_Control(pDX, IDC_FIELD48, cKey[47]);

	DDX_Control(pDX, IDC_FIELD49, cKey[48]);
	DDX_Control(pDX, IDC_FIELD50, cKey[49]);
	DDX_Control(pDX, IDC_FIELD51, cKey[50]);
	DDX_Control(pDX, IDC_FIELD52, cKey[51]);
	DDX_Control(pDX, IDC_FIELD53, cKey[52]);
	DDX_Control(pDX, IDC_FIELD54, cKey[53]);
	DDX_Control(pDX, IDC_FIELD55, cKey[54]);
	DDX_Control(pDX, IDC_FIELD56, cKey[55]);
		
	DDX_Control(pDX, IDC_FIELD57, cKey[56]);
	DDX_Control(pDX, IDC_FIELD58, cKey[57]);
	DDX_Control(pDX, IDC_FIELD59, cKey[58]);
	DDX_Control(pDX, IDC_FIELD60, cKey[59]);
	DDX_Control(pDX, IDC_FIELD61, cKey[60]);
	DDX_Control(pDX, IDC_FIELD62, cKey[61]);
	DDX_Control(pDX, IDC_FIELD63, cKey[62]);
	DDX_Control(pDX, IDC_FIELD64, cKey[63]);


}

BEGIN_MESSAGE_MAP(CKeyMatrixDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONNECT, &CKeyMatrixDlg::OnBnClickedConnect)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, &CKeyMatrixDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CKeyMatrixDlg-Meldungshandler

BOOL CKeyMatrixDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	ioHandle = NULL;

	return TRUE;  
}

void CKeyMatrixDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CKeyMatrixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKeyMatrixDlg::OnBnClickedConnect()
{
	ULONG pid;
	WCHAR sn[9];
	CString text;
	CString product;
	ioHandle = IowKitOpenDevice();

	if(ioHandle != NULL){

		IOWKIT_SPECIAL_REPORT report;
		memset(&report, 0x00, IOWKIT_SPECIAL_REPORT_SIZE);

		report.ReportID = 0x18;  //Use KeyMatrix-Mode
		report.Bytes[0] = 0x01;  //Enable

		IowKitWrite(ioHandle, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);

		pid = IowKitGetProductId(ioHandle);   //Get product-ID
		IowKitGetSerialNumber(ioHandle, sn);  //Get serialnumber


		//Create string
		switch(pid){
			case IOWKIT_PRODUCT_ID_IOW56:
				product.SetString(_T("IO-Warrior56"));
				SetTimer(IDC_TIMELOOP, 25, NULL);  //Start timer for reading
			break;
			case IOWKIT_PRODUCT_ID_IOW40:
			case IOWKIT_CUSTOM_PRODUCT_ID_3:
				product.SetString(_T("IO-Warrior40"));
				SetTimer(IDC_TIMELOOP, 25, NULL);  //Start timer for reading
			break;
			default:
				product.SetString(_T("IO-Warrior24"));
				MessageBox(_T("This IO-Warrior not support KeyMatrix mode."), _T("Not Supported"), NULL);
			break;

		}

		text.Format(_T("Type:%s  | Serial:%ws"), product, sn);
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowTextW(text);
	}
}

void CKeyMatrixDlg::OnClose()
{
	if(ioHandle != NULL){
		
		IOWKIT_SPECIAL_REPORT report;
		memset(&report, 0x00, IOWKIT_SPECIAL_REPORT_SIZE);

		report.ReportID = 0x18;  //Use KeyMatrix-Mode
		report.Bytes[0] = 0x00;  //Disable

		IowKitWrite(ioHandle, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);
		IowKitCloseDevice(ioHandle);
	}

	CDialog::OnClose();
}

void CKeyMatrixDlg::OnTimer(UINT_PTR nIDEvent)
{
	IOWKIT_SPECIAL_REPORT report;
	memset(&report, 0x00, IOWKIT_SPECIAL_REPORT_SIZE);

	report.ReportID = 0x19;  //Read KeyMatrix

	if(IowKitReadNonBlocking(ioHandle, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE))
	{
		CString string;

		string.Format(_T("%.2X : %.2X %.2X %.2X %.2X"), report.ReportID, report.Bytes[0], report.Bytes[1], report.Bytes[2], report.Bytes[3]);
		cList.InsertString(0,string);

		UpdateData(FALSE);

		//Buffer read-report for setting bitmaps
		bytes[0] = report.Bytes[0];
		bytes[1] = report.Bytes[1];
		bytes[2] = report.Bytes[2];
		bytes[3] = report.Bytes[3];

		//Set bitmaps for pressed keys
		DecodeButton(report.ReportID); 
	}

	CDialog::OnTimer(nIDEvent);
}

void CKeyMatrixDlg::DecodeButton(UCHAR b0)
{
	if(b0 == 0x19){
		short k=0;

		for(short i=0; i<4; i++){

			if(bytes[i] & 0x01)	DrawBitmap(cKey[0+k], IDB_BITMAP2);  //Key pressed, bitmap will be changed
			else DrawBitmap(cKey[0+k], IDB_BITMAP1);				 //Key released, bitmap will be changed

			if(bytes[i] & 0x02)	DrawBitmap(cKey[1+k], IDB_BITMAP2);
			else DrawBitmap(cKey[1+k], IDB_BITMAP1);

			if(bytes[i] & 0x04) DrawBitmap(cKey[2+k], IDB_BITMAP2);
			else DrawBitmap(cKey[2+k], IDB_BITMAP1);

			if(bytes[i] & 0x08) DrawBitmap(cKey[3+k], IDB_BITMAP2);
			else DrawBitmap(cKey[3+k], IDB_BITMAP1);

			if(bytes[i] & 0x10) DrawBitmap(cKey[4+k], IDB_BITMAP2);
			else DrawBitmap(cKey[4+k], IDB_BITMAP1);

			if(bytes[i] & 0x20) DrawBitmap(cKey[5+k], IDB_BITMAP2);
			else DrawBitmap(cKey[5+k], IDB_BITMAP1);

			if(bytes[i] & 0x40) DrawBitmap(cKey[6+k], IDB_BITMAP2);
			else DrawBitmap(cKey[6+k], IDB_BITMAP1);

			if(bytes[i] & 0x80) DrawBitmap(cKey[7+k], IDB_BITMAP2);
			else DrawBitmap(cKey[7+k], IDB_BITMAP1);

			k = k+8;
		}
	}


	if(b0 == 0x1A){
		short j=0;

		for(short i=0; i<4; i++){

			if(bytes[i] & 0x01)	DrawBitmap(cKey[32+j], IDB_BITMAP2);
			else DrawBitmap(cKey[32+j], IDB_BITMAP1);

			if(bytes[i] & 0x02)	DrawBitmap(cKey[33+j], IDB_BITMAP2);
			else DrawBitmap(cKey[33+j], IDB_BITMAP1);

			if(bytes[i] & 0x04) DrawBitmap(cKey[34+j], IDB_BITMAP2);
			else DrawBitmap(cKey[34+j], IDB_BITMAP1);

			if(bytes[i] & 0x08) DrawBitmap(cKey[35+j], IDB_BITMAP2);
			else DrawBitmap(cKey[35+j], IDB_BITMAP1);

			if(bytes[i] & 0x10) DrawBitmap(cKey[36+j], IDB_BITMAP2);
			else DrawBitmap(cKey[36+j], IDB_BITMAP1);

			if(bytes[i] & 0x20) DrawBitmap(cKey[37+j], IDB_BITMAP2);
			else DrawBitmap(cKey[37+j], IDB_BITMAP1);

			if(bytes[i] & 0x40) DrawBitmap(cKey[38+j], IDB_BITMAP2);
			else DrawBitmap(cKey[38+j], IDB_BITMAP1);

			if(bytes[i] & 0x80) DrawBitmap(cKey[39+j], IDB_BITMAP2);
			else DrawBitmap(cKey[39+j], IDB_BITMAP1);

			j = j+8;
		}
	}
}

void CKeyMatrixDlg::OnBnClickedClear()
{
	while(cList.GetCount() != 0)
		cList.DeleteString(0);
}

void CKeyMatrixDlg::DrawBitmap(CStatic &key, UINT bitmap)
{
	CBitmap b;

	b.DeleteObject();
	b.LoadBitmapW(bitmap);
	key.SetBitmap(b);
}
