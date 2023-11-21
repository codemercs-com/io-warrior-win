// MAXIM6675Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MAXIM6675.h"
#include "MAXIM6675Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMAXIM6675Dlg dialog

CMAXIM6675Dlg::CMAXIM6675Dlg(CWnd* pParent /*=NULL*/)
    : CDialog(CMAXIM6675Dlg::IDD, pParent)
    , m_temperature(_T(""))
    , m_tempmax(0)
    , m_tempmin(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMAXIM6675Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TEMPERATURE, m_font);
    DDX_Text(pDX, IDC_TEMPERATURE, m_temperature);
    DDX_Control(pDX, IDC_PROGRESS, m_progress);
    DDX_Text(pDX, IDC_TEMPMAX, m_tempmax);
    DDX_Text(pDX, IDC_TEMPMIN, m_tempmin);
}

BEGIN_MESSAGE_MAP(CMAXIM6675Dlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMAXIM6675Dlg message handlers

BOOL CMAXIM6675Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    //Open connected device
    iowHandle = IowKitOpenDevice();

    m_Pid = IowKitGetProductId(iowHandle);

    if(m_Pid == IOWKIT_PID_IOW56) 
    {
        memset(&m_rep56, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
        m_rep56.ReportID = 0x08; //SPI-Mode
        m_rep56.Bytes[0] = 0x01; //Enable SPI-Mode
        m_rep56.Bytes[1] = 0x01; // mode MSB first, /CPOL, CPHA
        m_rep56.Bytes[2] = 0xFF; // 93.75 KBit

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep56, IOWKIT56_SPECIAL_REPORT_SIZE);
    }
    else
    if(m_Pid == IOWKIT_PID_IOW24)
    {
        memset(&m_rep24, 0, IOWKIT_SPECIAL_REPORT_SIZE);
        m_rep24.ReportID = 0x08; //SPI-Mode
        m_rep24.Bytes[0] = 0x01; //Enable SPI-Mode
        m_rep24.Bytes[1] = 0x07; // mode /CPOL, CPHA, 62.5 KBit

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep24, IOWKIT_SPECIAL_REPORT_SIZE);
    }
    else
    if(m_Pid == IOWKIT_PID_IOW40 || iowHandle == NULL)
    {
        MessageBox("Please connect an IOWarrior 24 or 56 and run this program again.", "No IOWarrior found", NULL);
        IowKitCloseDevice(iowHandle);
        OnOK();
    }

    //Start timer, interval 1 sec
    SetTimer(IDC_LOCALTIME, 1000, NULL);

    //Default values
    m_tempmax = 100;
    m_tempmin = 0;

    //Setup progressbar
    m_progress.SetBkColor(RGB(255, 255, 255));
    m_progress.SetRange(0, 100);
    m_progress.SetStep(100);

    //Create a font to display the temperature
    CString type = "Arial";
    font.CreateFont(28, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, type);
    m_font.SetFont(&font);

    UpdateData(FALSE);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMAXIM6675Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMAXIM6675Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CMAXIM6675Dlg::OnTimer(UINT_PTR nIDEvent)
{
    double value;

    UpdateData(true);

    if(m_tempmax > 100)
      m_tempmax = 100;
    if(m_tempmin < 0)
      m_tempmin = 0;

    //Found an IOW56 and set the report
    if(m_Pid == IOWKIT_PID_IOW56)
    {
        memset(&m_rep56, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
        m_rep56.ReportID = 0x09; //SPI-Mode
        m_rep56.Bytes[0] = 0x02; //Write / Read 2 bytes
        m_rep56.Bytes[1] = 0x00; //flags

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep56, IOWKIT56_SPECIAL_REPORT_SIZE);
        IowKitRead(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep56, IOWKIT56_SPECIAL_REPORT_SIZE);
        if (m_rep56.ReportID == 0x09)
        {
            value = (double) (((m_rep56.Bytes[1] << 8) | m_rep56.Bytes[2]) >> 3) / 4.0;
            //show temperature
            m_temperature.Format("%.2f °C", value);
        }
    }
    else
    // Found an IOW24 and set the report
    if(m_Pid == IOWKIT_PID_IOW24)
    {
        memset(&m_rep24, 0, IOWKIT_SPECIAL_REPORT_SIZE);
        m_rep24.ReportID = 0x09; //SPI-Mode
        m_rep24.Bytes[0] = 0x02; //Write / Read 2 Bytes

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep24, IOWKIT_SPECIAL_REPORT_SIZE);
        IowKitRead(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep24, IOWKIT_SPECIAL_REPORT_SIZE);
        if (m_rep24.ReportID == 0x09)
        {
            value = (double) (((m_rep24.Bytes[1] << 8) | m_rep24.Bytes[2]) >> 3) / 4.0;
            //show temperature
            m_temperature.Format("%.2f °C", value);
        }
    }

    // Progressbar-setup		
    m_progress.SetPos((int) value);
        
    // Progressbar-color
    if(value < m_tempmin)
        m_progress.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(0, 0, 255));
    else
    if(value > m_tempmax)
        m_progress.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(255, 0, 0));
    else
        m_progress.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(0, 255, 0));

    UpdateData(false);

    CDialog::OnTimer(nIDEvent);
}

void CMAXIM6675Dlg::OnClose()
{
    if(m_Pid == IOWKIT_PID_IOW56) 
    {
        memset(&m_rep56, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
        m_rep56.ReportID = 0x08;
        m_rep56.Bytes[0] = 0x00;

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep56, IOWKIT56_SPECIAL_REPORT_SIZE);
    }
    else
    if(m_Pid == IOWKIT_PID_IOW24)
    {
        memset(&m_rep24, 0, IOWKIT_SPECIAL_REPORT_SIZE);
        m_rep24.ReportID = 0x08;
        m_rep24.Bytes[0] = 0x00;

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (char *) &m_rep24, IOWKIT_SPECIAL_REPORT_SIZE);
    }
    KillTimer(IDC_LOCALTIME);

    IowKitCloseDevice(iowHandle);

    CDialog::OnClose();
}
