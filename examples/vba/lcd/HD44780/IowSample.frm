VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IO-Warrior LCD sample"
   ClientHeight    =   3000
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4410
   LinkTopic       =   "Form1"
   ScaleHeight     =   3000
   ScaleWidth      =   4410
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.CommandButton CursorRightBtn 
      Caption         =   "Cursor Right"
      Height          =   495
      Left            =   1560
      TabIndex        =   12
      ToolTipText     =   "Move cursor to the right"
      Top             =   2340
      Width           =   615
   End
   Begin VB.CommandButton CursorLeftBtn 
      Caption         =   "Cursor Left"
      Height          =   495
      Left            =   840
      TabIndex        =   11
      ToolTipText     =   "Move cursor to the left"
      Top             =   2340
      Width           =   615
   End
   Begin VB.CommandButton ToggleCursorButton 
      Caption         =   "Cursor"
      Height          =   495
      Left            =   120
      TabIndex        =   10
      ToolTipText     =   "Toggle cursor on or off"
      Top             =   2340
      Width           =   615
   End
   Begin VB.CommandButton SetDRAMAddrButton 
      Caption         =   "DDRAM Addr"
      Height          =   495
      Left            =   3360
      TabIndex        =   9
      ToolTipText     =   "Set DDRAM (cursor) address"
      Top             =   1560
      Width           =   855
   End
   Begin VB.TextBox TextVal2 
      Height          =   375
      Left            =   3720
      TabIndex        =   7
      Text            =   "0"
      Top             =   480
      Width           =   495
   End
   Begin VB.CommandButton LCDWriteButton 
      Caption         =   "Write"
      Height          =   495
      Left            =   2400
      TabIndex        =   6
      Top             =   1560
      Width           =   735
   End
   Begin VB.CommandButton LCDHomeButton 
      Caption         =   "Home"
      Height          =   495
      Left            =   1560
      TabIndex        =   5
      ToolTipText     =   "Move cursor to home position"
      Top             =   1560
      Width           =   615
   End
   Begin VB.CommandButton LcdClearButton 
      Caption         =   "CLR"
      Height          =   495
      Left            =   840
      TabIndex        =   2
      ToolTipText     =   "Clear LCD screen"
      Top             =   1560
      Width           =   615
   End
   Begin VB.CommandButton LCDInitButton 
      Caption         =   "Init"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      ToolTipText     =   "Init LCD display"
      Top             =   1560
      Width           =   615
   End
   Begin VB.TextBox TextVal1 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   3495
   End
   Begin VB.Image Image1 
      Height          =   675
      Left            =   2730
      Picture         =   "IOWSAM~1.frx":0000
      Top             =   2160
      Width           =   1485
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "DDRAM Address"
      Height          =   195
      Left            =   3000
      TabIndex        =   8
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "String to write"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label ReadLabel 
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1200
      Width           =   2655
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' IO-Warrior handle
Dim iowHandle As Long
Dim cursorOn As Boolean

Private Sub CursorLeftBtn_Click()
    Dim Res As Boolean

    ' Move cursor to the left
    Res = IowKitCursorLeftLCD(iowHandle)
End Sub

Private Sub CursorRightBtn_Click()
    Dim Res As Long

    ' Move cursor to the right
    Res = IowKitCursorRightLCD(iowHandle)
End Sub

' Called when program starts and form is loaded
Private Sub Form_Load()
    Dim Res As Boolean

    ' Initialize everything
    ' Open device
    iowHandle = IowKitOpenDevice()
    ' Fail if can't open
    If iowHandle = 0 Then
        ' Exit from program
        MsgBox "Can not open device!", 0, "Error"
        End
    End If

    ' Enable IIC
    Res = IowKitEnableLCD(iowHandle, 1)
    ' Check for error
    If Not Res Then
        ' Something is wrong, exit
        MsgBox "LCD not present", 0, "Error"
        End
    End If
    ' Initialize LCD screen
    Res = IowKitInitLCD(iowHandle, 1)
    ' Turn on display, cursor and blinking
    Res = IowKitDispControlLCD(iowHandle, True, True, True)
    ' Set cursor movement to right and no shifting
    Res = IowKitEntryModeSet(iowHandle, True, False)
    cursorOn = True
End Sub

' Called when program exits
Private Sub Form_Unload(Cancel As Integer)
    ' Disable LCD
    Dim Res As Boolean

    Res = IowKitEnableLCD(iowHandle, 0)
    ' Close IO-Warrior device
    IowKitCloseDevice (iowHandle)
End Sub

Private Sub LCDHomeButton_Click()
    Dim Res As Boolean

    ' Move cursor to home
    Res = IowKitCursorHomeLCD(iowHandle)
End Sub

' Readbutton click handler
Private Sub LCDInitButton_Click()
    Dim Res As Boolean

    ' Initialize LCD
    Res = IowKitInitLCD(iowHandle, 1)
End Sub

' Write button click handler
Private Sub LCDClearButton_Click()
    ' Result
    Dim Res As Boolean

    ' Clear screen
    Res = IowKitClearLCD(iowHandle)
    ReadLabel.Caption = "Screen clear"
    ReadLabel.Refresh
End Sub

Private Sub LCDWriteButton_Click()
    Dim Res As Boolean

    Res = IowKitWriteStringLCD(iowHandle, TextVal1.Text)
End Sub

' Set DDRAM address button handler
Private Sub SetDRAMAddrButton_Click()
    Dim Res As Boolean
    Dim Addr As Byte

    ' Get and convert address
    Addr = Val("&H" & TextVal2.Text)
    ' Set DDRAM address
    Res = IowKitSetDDRAMAddr(iowHandle, Addr)
End Sub

Private Sub ToggleCursorButton_Click()
    Dim Res As Boolean
  
    ' Toggle cursor on/off
    If cursorOn Then
        Res = IowKitCursorOffLCD(iowHandle)
    Else
        Res = IowKitCursorOnLCD(iowHandle)
    End If
    cursorOn = Not cursorOn
End Sub
