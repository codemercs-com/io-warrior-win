// LCD_SampleDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "LCD_Sample.h"
#include "LCD_SampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLCD_SampleDlg-Dialogfeld

CLCD_SampleDlg::CLCD_SampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLCD_SampleDlg::IDD, pParent)
	, m_output(0)
	, m_write(_T(""))
	, m_lcdonoff(TRUE)
	, m_cursoronoff(TRUE)
	, m_position(0)
	, m_iPosition(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLCD_SampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_READLIST, m_readlist);
	DDX_Radio(pDX, IDC_RADIO1, m_output);
	DDX_Text(pDX, IDC_WRITESTRING, m_write);
	DDX_Check(pDX, IDC_LCDONOFF, m_lcdonoff);
	DDX_Check(pDX, IDC_LCDCURSOR, m_cursoronoff);
	DDX_Control(pDX, IDC_REPORTLIST, m_reportlist);
	DDX_Text(pDX, IDC_COUNTER, m_iPosition);
}

BEGIN_MESSAGE_MAP(CLCD_SampleDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INITIATE, &CLCD_SampleDlg::OnBnClickedInitiate)
	ON_BN_CLICKED(IDC_LCDCLEAR, &CLCD_SampleDlg::OnBnClickedLcdclear)
	ON_BN_CLICKED(IDC_LCDHOME, &CLCD_SampleDlg::OnBnClickedLcdhome)
	ON_BN_CLICKED(IDC_WRITEDATA, &CLCD_SampleDlg::OnBnClickedWritedata)
	ON_BN_CLICKED(IDC_LCDONOFF, &CLCD_SampleDlg::OnBnClickedLcdonoff)
	ON_BN_CLICKED(IDC_LCDCURSOR, &CLCD_SampleDlg::OnBnClickedLcdcursor)
	ON_BN_CLICKED(IDC_CLEARREPORT, &CLCD_SampleDlg::OnBnClickedClearreport)
	ON_BN_CLICKED(IDC_READDATA, &CLCD_SampleDlg::OnBnClickedReaddata)
	ON_BN_CLICKED(IDC_CLEARLIST, &CLCD_SampleDlg::OnBnClickedClearlist)
	ON_BN_CLICKED(IDC_CHARFW, &CLCD_SampleDlg::OnBnClickedCharfw)
	ON_BN_CLICKED(IDC_CHARBW, &CLCD_SampleDlg::OnBnClickedCharbw)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLCD_SampleDlg-Meldungshandler

BOOL CLCD_SampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	//Create table for "read"
	m_readlist.InsertColumn(0, "Package", LVCFMT_LEFT, 100);
	m_readlist.InsertColumn(1, "b1", LVCFMT_LEFT, 35);
	m_readlist.InsertColumn(2, "b2", LVCFMT_LEFT, 35);
	m_readlist.InsertColumn(3, "b3", LVCFMT_LEFT, 35);
	m_readlist.InsertColumn(4, "b4", LVCFMT_LEFT, 35);
	m_readlist.InsertColumn(5, "b5", LVCFMT_LEFT, 35);
	m_readlist.InsertColumn(6, "b6", LVCFMT_LEFT, 35);
	m_readlist.SetTextColor(RGB(0, 0, 255));
	m_readlist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	ioHandle_1 = IowKitOpenDevice();
	IowKitSetWriteTimeout(ioHandle_1, 2000);

	if(ioHandle_1 != NULL)
	{
		// Get Serialnumber
		WCHAR sn[10];
		CString Serial;
		m_position = 128; //1st position on LCD HD44780
		m_iPosition = 1;

		IowKitGetSerialNumber(ioHandle_1, sn);

		if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW40 || IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW24)
		{
			IOWKIT_SPECIAL_REPORT report;
			memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
			report.ReportID = 0x04; //ReportID for LCD-Mode
			report.Bytes[0] = 0x01; // enable LCD Special Function
			IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);

			Serial.Format("IOWarrior 24/40 found -> SN: %S", sn);
			InsertReport(Serial);
		}

		if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW56)
		{
			IOWKIT56_SPECIAL_REPORT report;
			memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
			report.ReportID = 0x04; // ReportID for LCD-Mode
			report.Bytes[0] = 0x01; // enable LCD Special Function
		
			IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);

			Serial.Format("IOWarrior 56 found -> SN: %S", sn);
			InsertReport(Serial);

			// Deactivate the buttons without read-function
			GetDlgItem(IDC_READDATA)->EnableWindow(FALSE);
			GetDlgItem(IDC_CLEARLIST)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);

			InsertReport("ERROR: Read function disabled");
		}
		UpdateData(FALSE);
	}
	else
	{
		IowKitCloseDevice(ioHandle_1);
		MessageBox("Please connect an IOWarrior and start the program again.", "No IOWarrior found", NULL);
		OnOK();
	}
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CLCD_SampleDlg::OnPaint()
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

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CLCD_SampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLCD_SampleDlg::InsertReport(CString reporter)
{
	//Function for insert a report in the report-field
	CTime lt = CTime::GetCurrentTime();
	CString text;

	text.Format("%.2d.%.2d %.2d:%.2d    %s",lt.GetDay(), 
											lt.GetMonth(), 
											lt.GetHour(), 
											lt.GetMinute(),
											reporter);

	m_reportlist.InsertString(0, text); //Set a string to fisrt line of list
	UpdateData(FALSE);
}


void CLCD_SampleDlg::OnBnClickedInitiate()
{
	// Init sequence of the LCD (HD44780)
	// Details in datasheet of your LCD

	// Sequence for IOW24/40
	if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW40 || IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW24)
	{
		IOWKIT_SPECIAL_REPORT report;
		memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x05; //ReportID for LCD-Mode "write"
		report.Bytes[0] = 0x04; // R/S mode=0 / Send bytes
		report.Bytes[1] = 0x38; // function "8-Bit mode"
		report.Bytes[2] = 0x0F; // function "display on"
		report.Bytes[3] = 0x01; // function "clear display"
		report.Bytes[4] = 0x06; // function "entry mode set"
		
		IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);
		InsertReport("HD44780 LCD initialized");
	}
	// Sequence for IOW56
	if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW56)
	{
		IOWKIT56_SPECIAL_REPORT report;
		memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x05; //ReportID for LCD-Mode "write"
		report.Bytes[0] = 0x20; // R/S mode=0 / Send bytes
		report.Bytes[1] = 0x0F; // function "display on"
		report.Bytes[2] = 0x01; // function "clear display"
		
		IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
		InsertReport("HD44780 LCD initialized");
	}
}
void CLCD_SampleDlg::OnBnClickedLcdclear()
{
	// Clear the LCD from all characters
	IOWKIT56_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //ReportID for LCD-Mode "write"
	report.Bytes[0] = 0x01; // R/S mode=0 / Send bytes
	report.Bytes[1] = 0x01; // function "clear display"
	
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);

	m_iPosition = 1;
	InsertReport("LCD cleared");

	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedLcdhome()
{
	UpdateData(TRUE);

	// Cursor goes to first LCD-Position
	IOWKIT56_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; // Open LCD "write"
	report.Bytes[0] = 0x01; // open command mode
	report.Bytes[1] = 0x02; // Set cursor to "home position" 

	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);

	m_iPosition = 1;
	InsertReport("Set LCD to 'home position'");

	UpdateData(FALSE);
}


void CLCD_SampleDlg::WriteLine(UCHAR line, CString send)
{
	// Function for write the data to the LCD
	IOWKIT56_SPECIAL_REPORT report;
	int size = 0; //Init size of loop
	int car; 
			
	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //Open LCD-mode 'write'
	report.Bytes[0] = 0x01; //Write from position 0 (1st) and overwrite the old
	report.Bytes[1] = line; //write to line 1 or 2

	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
	
	size = send.GetLength(); //Get length for know how many bytes to send
	
	// loop for write the chars on LCD
	for(int x = 0; x < size; x++)
	{
		memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x05; //Open LCD-mode "write"
		report.Bytes[0] = 0x81; //Register = 0 / datacount = 1 byte send
				
		car = (int) send.GetAt(x); //Get char 'x' as integer
		report.Bytes[1] = car ; //send integer of 'x' to LCD

		IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
	}
}


void CLCD_SampleDlg::OnBnClickedWritedata()
{
	// Call the WriteLine-function for send data
	UpdateData(TRUE);
	WriteLine(m_position, m_write);

	InsertReport("LCD data written");
	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedLcdonoff()
{
	// Set the LCD On or Off
	UpdateData(TRUE);

	IOWKIT56_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //LCD Write-mode
	report.Bytes[0] = 0x01; //Write 1 byte
	
	if(m_lcdonoff != NULL)
	{
		report.Bytes[1] = 0x0F; //Command for Cursor-Enable
		GetDlgItem(IDC_LCDCURSOR)->EnableWindow(TRUE);
		InsertReport("Set LCD-Cursor 'On'");
	}
	else 
	{
		report.Bytes[1] = 0x0B; //Command for Cursor-Disable
		GetDlgItem(IDC_LCDCURSOR) -> EnableWindow(FALSE);
		InsertReport("Set LCD-Cursor 'Off'");
	}

	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
	
	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedLcdcursor()
{
	// Set the Cursor-blinking On/Off
	UpdateData(true);

	IOWKIT56_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //LCD Write-mode
	report.Bytes[0] = 0x01; //datacount = 1 byte

	if(m_cursoronoff != NULL) 
	{
		report.Bytes[1] = 0x0F; //Command for LCD-Enable
		GetDlgItem(IDC_LCDONOFF)->EnableWindow(true);
		InsertReport("Set LCD 'On'");
	}
	else 
	{
		report.Bytes[1] = 0x0E; //Command for LCD-Disable
		GetDlgItem(IDC_LCDONOFF) -> EnableWindow(FALSE);
		InsertReport("Set LCD 'Off'");
	}

	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedClearreport()
{
	// Clear the report-list from all inserts
	m_reportlist.ResetContent();
	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedReaddata()
{
	// Read data from the LCD-Register and insert it into the list	
	IOWKIT_SPECIAL_REPORT report;
	CString readdata;
	CString newData;

	UpdateData(TRUE);

	m_readlist.DeleteAllItems(); //Clear all items from list for next reading

	// Go to first display-position
	memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; // Open LCD "write"
	report.Bytes[0] = 0x01; // open commandmode
	report.Bytes[1] = 0x02; // Set cursor to "home position" 
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);

	// Order to send data from 1st line
	memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE); 
	report.ReportID = 0x06; // function "read"
	report.Bytes[0] = 0xA0; // Read RS=1 and all Bytes
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);	

	// Order to send data from 2nd line
	memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE); 
	report.ReportID = 0x06; // function "read"
	report.Bytes[0] = 0xA0; // Read RS=1 and all Bytes
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);	

	//-----------------------IOWarrior 24 or 40----------------------------------------------------------------
	if(IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW24 || IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW40)
	{
		report.ReportID = 0x06; // function read
		report.Bytes[0] = 0x63; //# of bytes to read

	    // loop for getting data from LCD-Register
		for(int f = 0; f < 14; f++)
		{
			IowKitReadNonBlocking(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);

	    	// Convert character into CString
			readdata.Format("%d", f); // .InsertItem char[2] don't accept int-values.
			m_readlist.InsertItem(f, readdata, NULL); //Got to next free pos. in the list for writing

			for(int d = 1; d < 7; d++)
			{
				switch(m_output)
				{
				case 0: //HEX
					newData.Format("%0x", (char*) report.Bytes[d]);	
					break;
				case 1: //DEC
					newData.Format("%.2d", (char*) report.Bytes[d]);	
					break;
				case 2://CHAR
					newData.Format("%c", (char*) report.Bytes[d]);	
					break;
				}
				m_readlist.SetItemText(f, d, newData); //Write values into list
			}
		}
	}

	InsertReport("Data read from LCD-Register");

	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedClearlist()
{
	//Manual list-reset (readinglist)
	UpdateData(TRUE);
	m_readlist.DeleteAllItems();
	InsertReport("Manual clear 'Read-list'");
	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedCharfw()
{
	UpdateData(TRUE);

	//Move the cursor 1 step forward
	IOWKIT56_SPECIAL_REPORT report;
	
	if(m_position == 144)
	{
		m_position = 192; //144 = end of line 1 -> go to line 2
		m_iPosition = 17;
	}

	if(m_position == 208)
	{
		m_position = 128; //208 = end of line 2 -> go to line 1
		m_iPosition = 1;
	}

	m_position++;
	m_iPosition++;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //LCD Write-Mode
	report.Bytes[0] = 0x01; // Write 1 Byte
	report.Bytes[1] = m_position; //Write new position
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);

	UpdateData(FALSE);
}

void CLCD_SampleDlg::OnBnClickedCharbw()
{
	UpdateData(TRUE);

	//Move the cursor 1 step backward
	IOWKIT56_SPECIAL_REPORT report;
	
	if(m_position == 191)
	{ 
		m_position = 143; //191 = 1st character of line 2 -> go to last line 2
		m_iPosition = 16;
	}
	
	if(m_position == 127)
	{ 
		m_position = 209; //127 = 1st character of line 1 -> go to last line 1
		m_iPosition = 32;
	}
	
	m_position--; //decrement position
	m_iPosition--;

	memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x05; //LCD Write-mode
	report.Bytes[0] = 0x01; //data count = 1 Byte
	report.Bytes[1] = m_position; //New position
	IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);

	UpdateData(false);
}

void CLCD_SampleDlg::OnClose()
{
	if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW40 || IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW24)
	{
		IOWKIT_SPECIAL_REPORT report;
		memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x04;
		report.Bytes[0] = 0x00; 
		IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT_SPECIAL_REPORT_SIZE);
	}
    else
	if (IowKitGetProductId(ioHandle_1) == IOWKIT_PID_IOW56)
	{
		IOWKIT56_SPECIAL_REPORT report;
		memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x04; // ReportID for LCD-Mode
		report.Bytes[0] = 0x00; // enable LCD Special Function
	
		IowKitWrite(ioHandle_1, IOW_PIPE_SPECIAL_MODE, (char *) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
	}

    IowKitCloseDevice(ioHandle_1);

	CDialog::OnClose();
}
