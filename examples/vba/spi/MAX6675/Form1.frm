VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "MAXIM 6675 SPI Temperature"
   ClientHeight    =   1470
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5955
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1470
   ScaleWidth      =   5955
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   5280
      Top             =   960
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "?,?? °C"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   48
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   5895
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim IOWarrior As Long
Dim Pid As Long

Private Sub Form_Load()
  Dim I As Long
  Dim Report(64) As Byte

  ' open the IO-Warriors
  IOWarrior = IowKitOpenDevice
  Pid = IowKitGetProductId(IOWarrior)
  If Pid <> IOWKIT_PID_IOW24 And Pid <> IOWKIT_PID_IOW56 Then
    ' Exit from program
    MsgBox "No IOWarrior 24 or 56 found!", 0, "Error"
    End
  End If

  ' if found activate SPI
  If Pid = IOWKIT_PID_IOW24 Then
    Report(0) = &H8
    Report(1) = &H1  ' enable SPI
    Report(2) = &H7  ' mode /CPOL, CPHA, 62.5 KBit
    I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 8)
  Else
    Report(0) = &H8
    Report(1) = &H1  ' Enable SPI
    Report(2) = &H1  ' mode MSB first, /CPOL, CPHA
    Report(3) = &H0  ' 93.75 KBit
    I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 64)
  End If
  ' start timer for reading temperature
  Timer1.Enabled = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Dim I As Long
  Dim Report(8) As Byte

  ' stop timer
  Timer1.Enabled = False
  ' deactivate SPI
  If IOWarrior <> 0 Then
    Report(0) = &H8
    Report(1) = &H0
    Report(2) = &H0
    If Pid = IOWKIT_PID_IOW24 Then
      I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 8)
    Else
      I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 64)
    End If
  End If
  ' close IO-Warriors
  IowKitCloseDevice (IOWarrior)
End Sub

Private Sub Timer1_Timer()
  Dim I As Long
  Dim Report(64) As Byte
  
  ' write 2 bytes of dummy data to SPI to trigger read
  Report(0) = &H9
  Report(1) = &H2
  Report(2) = &H0
  If Pid = IOWKIT_PID_IOW24 Then
    I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 8)
    ' read temperature data
    I = IowKitRead(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 8)
  Else
    I = IowKitWrite(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 64)
    ' read temperature data
    I = IowKitRead(IOWarrior, IOW_PIPE_SPECIAL_MODE, Report(0), 64)
  End If
  ' build 16 bit value and shift it 3 bits to the right
  I = (Report(2) * 256 + Report(3)) / 8
  ' values is in 1/4 degree Celsius
  Label1.Caption = Format(I / 4, "0.00 °C")
End Sub
