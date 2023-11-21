// LED-MatrixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LED-Matrix.h"
#include "LED-MatrixDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLEDMatrixDlg dialog

CLEDMatrixDlg::CLEDMatrixDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CLEDMatrixDlg::IDD, pParent)
    , m_value(_T(""))
    , m_scroll(0)
    , Pid(0)
    , nWalk(0)
    , m_tScroll(0)
    , m_nLength(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLEDMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_VALUE, m_value);
    DDX_CBIndex(pDX, IDC_SCROLLING, m_scroll);
}

BEGIN_MESSAGE_MAP(CLEDMatrixDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_CBN_SELCHANGE(IDC_SCROLLING, &CLEDMatrixDlg::OnCbnSelchangeScrolling)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLEDMatrixDlg message handlers

BOOL CLEDMatrixDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    iowHandle = IowKitOpenDevice();
    
    if(iowHandle != NULL)
    {
        Pid = IowKitGetProductId(iowHandle);

        if(Pid == IOWKIT_PID_IOW24 || Pid == IOWKIT_PID_IOW40)
        {
            IOWKIT_SPECIAL_REPORT report;

            memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
            report.ReportID = 0x14; //Special-Mode "LED-Matrix"
            report.Bytes[0] = 0x01; //Enable Special-mode

            IowKitWrite(iowHandle,IOW_PIPE_SPECIAL_MODE,(PCHAR) &report, IOWKIT_SPECIAL_REPORT_SIZE);
        }
        else
        if(Pid == IOWKIT_PID_IOW56)
        {
            IOWKIT56_SPECIAL_REPORT report;

            memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
            report.ReportID = 0x14; //Special-Mode "LED-Matrix"
            report.Bytes[0] = 0x01; //Enable Special-mode

            IowKitWrite(iowHandle,IOW_PIPE_SPECIAL_MODE,(PCHAR) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
        }
        SetTimer(IDC_LOOPTIME, 100, NULL);

        m_scroll = 0;
        m_value.SetString("Hello World!");
        nWalk = 0;
        m_nLength = 128; //Sets the length of text for LED-Matrix
    }
    else
    {
        IowKitCloseDevice(iowHandle);
        MessageBoxA("Please connect an IOWarrior and restart the program.", "No IOWarrior found", NULL);
        OnOK();
    }

    UpdateData(false);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLEDMatrixDlg::OnPaint()
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
HCURSOR CLEDMatrixDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CLEDMatrixDlg::TextToBitmap(CString value, CString font, int pos_x, int pos_y, int font_size)
{
    CBitmap cBitmap;
    CDC cDC;
    CDC* pDC = this->GetDC();
    int loop = 0;
    int wBit = 0;
    CFont cFont;

    //Create a font for use (best for 8x8-Segment is "Small Fonts")
    cFont.CreateFontA(font_size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
        CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font);

    //Create a bitmap and set the options
    cDC.CreateCompatibleDC(pDC);
    cDC.SetBkColor(RGB(0,0,0));
    cDC.SetTextColor(RGB(255,255,255));
    cBitmap.CreateCompatibleBitmap(pDC, m_nLength, 8);

    //Select the bitmap and write into it
    cDC.SelectObject(&cBitmap);
    cDC.SelectObject(&cFont);
    cDC.TextOutA(pos_x, pos_y, value, value.GetLength()); 
            
    pDC->StretchBlt(20, 100, 64, 16,& cDC, 0, 0, 32, 8, SRCCOPY);
    pDC->StretchBlt(100, 100, 64, 16, &cDC, 33, 0, 32, 8, SRCCOPY);

    //Get Pixel from cDC into array bits[]
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            loop++; 
            bits[loop-1] = (UCHAR) GetPixel(cDC,j,i);
        }
    }

    //Clear cDC-Object for further use
    cDC.DeleteDC(); 
    cBitmap.DeleteObject();

    for(int x = 0; x < 64; x++)
    {
        //Create a Byte from 8 bit with "shifting"
        for(int y = 0; y < 8; y++)
        {
            wBit++;
            bytes[x] = bytes[x]>>1;
            if( bits[wBit-1] != NULL )
                bytes[x] |= 128;
        } 
    }

}


void CLEDMatrixDlg::OnTimer(UINT_PTR nIDEvent)
{
    //Set the movement of the text
    //Values of TextToBitmap:
    //value of Edit-control, font-type, x-pos, y-pos, font-height

    switch(m_tScroll)
    {
    case 0: //No movement
        nWalk = 0;
        TextToBitmap(m_value,"Small Fonts",0,-2,10);		
        break;
    case 1: //Forward
        nWalk--;
        if(nWalk == -m_nLength)
            nWalk = 64+2;       	//Use a const width
        TextToBitmap(m_value, "Small Fonts", nWalk, -2, 10);		
        break; 
    case 2: //Reverse
        nWalk++;
        if(nWalk == m_nLength)
            nWalk = -m_nLength;		//Use a const width
        TextToBitmap(m_value, "Small Fonts", nWalk, -2, 10);		
        break;
    case 3: //Down
        nWalk++;
        if(nWalk == 12)
            nWalk = -8;
        TextToBitmap(m_value, "Small Fonts", 0, nWalk-2, 10);		
        break;
    case 4: //Up
        nWalk--;
        if(nWalk == -12)
            nWalk = 8;
        TextToBitmap(m_value, "Small Fonts", 0, nWalk-2, 10);		
        break;
    }

    UpdateData(TRUE);

    if(iowHandle != NULL)
    {
        //For Using an IOW56
        if(Pid == IOWKIT_PID_IOW56)
        {
            IOWKIT56_SPECIAL_REPORT report;
            int nBlock = 0;

            memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
            report.ReportID = 0x15;

            for(int z1 = 0; z1 <= 1; z1++)
            {
                //Select rh right block for the bytes
                if(z1 == 0)
                    nBlock = 0;
                else
                    nBlock = 32;

                report.Bytes[0] = z1;
        
                for(int z2 = 0; z2 < 32; z2++)
                    report.Bytes[z2+1] = bytes[z2+nBlock]; //Write generated bytes to report.Bytes[]
                
                IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (PCHAR) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
            }
        }
        else
        //For using an IOW24 or IOW40
        if(Pid == IOWKIT_PID_IOW24 || Pid == IOWKIT_PID_IOW40)
        {
            IOWKIT_SPECIAL_REPORT report;
            static int nCount[9] = {0, 8, 16, 24, 32, 40, 48, 56}; //For select the right bytes

            memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
            report.ReportID = 0x15;
                
            for(int z1 = 0; z1 < 8; z1++) //Select the row for bytes
            {
                report.Bytes[0] = z1;

                for(int z3 = 0; z3 < 4; z3++)
                    report.Bytes[z3+1] = bytes[z3+nCount[z1]];

                IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (PCHAR) &report, IOWKIT_SPECIAL_REPORT_SIZE);
            }
        }
    }

    CDialog::OnTimer(nIDEvent);
}

void CLEDMatrixDlg::OnCbnSelchangeScrolling()
{
    //This is used for eleminate autoselect by timer-event
    //for the ComboBox by running the programm

    UpdateData(TRUE);

    m_scroll = m_tScroll;

    UpdateData(FALSE);
}

void CLEDMatrixDlg::OnClose()
{
    Pid = IowKitGetProductId(iowHandle);

    if(Pid == IOWKIT_PID_IOW24 || Pid == IOWKIT_PID_IOW40)
    {
        IOWKIT_SPECIAL_REPORT report;

        memset(&report, 0, IOWKIT_SPECIAL_REPORT_SIZE);
        report.ReportID = 0x14;
        report.Bytes[0] = 0x00;

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (PCHAR) &report, IOWKIT_SPECIAL_REPORT_SIZE);
    }
    else
    if(Pid == IOWKIT_PID_IOW56)
    {
        IOWKIT56_SPECIAL_REPORT report;

        memset(&report, 0, IOWKIT56_SPECIAL_REPORT_SIZE);
        report.ReportID = 0x14;
        report.Bytes[0] = 0x00;

        IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, (PCHAR) &report, IOWKIT56_SPECIAL_REPORT_SIZE);
    }
    KillTimer(IDC_LOOPTIME);

    IowKitCloseDevice(iowHandle);

    CDialog::OnClose();
}
