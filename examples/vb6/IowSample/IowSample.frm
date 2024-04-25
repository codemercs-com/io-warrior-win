VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IO-Warrior sample application"
   ClientHeight    =   1605
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5070
   LinkTopic       =   "Form1"
   ScaleHeight     =   1605
   ScaleWidth      =   5070
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.TextBox TextVal7 
      Height          =   375
      Left            =   3000
      TabIndex        =   11
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.TextBox TextVal6 
      Height          =   375
      Left            =   2520
      TabIndex        =   10
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.TextBox TextVal5 
      Height          =   375
      Left            =   2040
      TabIndex        =   9
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.TextBox TextVal4 
      Height          =   375
      Left            =   1560
      TabIndex        =   8
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton ClearAllButton 
      Caption         =   "Clear All"
      Height          =   495
      Left            =   3960
      TabIndex        =   7
      Top             =   960
      Width           =   975
   End
   Begin VB.TextBox TextVal3 
      Height          =   375
      Left            =   1080
      TabIndex        =   2
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.TextBox TextVal2 
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton ReadButton 
      Caption         =   "Read Value"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   975
   End
   Begin VB.CommandButton RandomButton 
      Caption         =   "Random Bits"
      Height          =   495
      Left            =   2680
      TabIndex        =   5
      Top             =   960
      Width           =   975
   End
   Begin VB.TextBox TextVal1 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Text            =   "0"
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton WriteButton 
      Caption         =   "Write Value"
      Height          =   495
      Left            =   1400
      TabIndex        =   4
      Top             =   960
      Width           =   975
   End
   Begin VB.Image Image1 
      Height          =   675
      Left            =   3480
      Picture         =   "IOWSAM~1.frx":0000
      Top             =   120
      Width           =   1485
   End
   Begin VB.Label ReadLabel 
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   600
      Width           =   2655
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' This is Basic IO-Warrior usage sample
' This sample shows how to program IO-Warrior for input and output
' and how to use multiple devices

' IO-Warrior handles
Dim iowHandles(IOWKIT_MAX_DEVICES) As Long
' Number of IOWs
Dim numIows As Long
' Data buffer
' Basic data buffer is 8 bytes long: 1 byte for report id, max 7 bytes for data
Dim data(8) As Byte

Private Sub WriteLEDs(Value As Byte)
    ' Number of bytes written
    Dim nWritten As Long
    ' Loop variable
    Dim I As Long
    ' ProductID of IOWarrior
    Dim Pid As Long

    ' Set up Report ID
    data(0) = 0
    For I = 0 To numIows - 1
        ' Set up bytes
        data(1) = &HFF
        data(2) = &HFF
        data(3) = &HFF
        data(4) = &HFF
        data(5) = &HFF
        data(6) = &HFF
        data(7) = &HFF

        Pid = IowKitGetProductId(iowHandles(I))
        If Pid = IOWKIT_PID_IOW24 Then
          ' First byte is controlling standard LED
          data(1) = Value
          ' Write to IOW 24
          nWritten = IowKitWrite(iowHandles(I), IOW_PIPE_IO_PINS, data(0), 3)
        Else
        If Pid = IOWKIT_PID_IOW40 Then
          ' Fourth byte is controlling standard LEDs
          data(4) = Value
          ' Write to IOW 40
          nWritten = IowKitWrite(iowHandles(I), IOW_PIPE_IO_PINS, data(0), 5)
        Else
        If Pid = IOWKIT_PID_IOW56 Then
          ' Seventh byte is controlling standard LEDs
          data(7) = Value
          ' Write to IOW 56
          nWritten = IowKitWrite(iowHandles(I), IOW_PIPE_IO_PINS, data(0), 8)
        End If
        End If
        End If
    Next I
End Sub

Private Sub ClearAllButton_Click()
    ' Clear all LEDs (negative logic)
    Call WriteLEDs(&HFF)
End Sub

' Blink all IOWs
Private Sub RandomButton_Click()
    ' Write random bits to LEDs
    Randomize
    Call WriteLEDs(Int(256 * Rnd) And &HFF)
End Sub

Private Sub Form_Load()
    Dim I As Long
    Dim S(18) As Byte

    ' Initialize everything
    ' Open device
    iowHandles(0) = IowKitOpenDevice()
    ' Fail if can't open
    If iowHandles(0) = 0 Then
        ' Barf and exit from program
        MsgBox "Can not open device!", 0, "Error"
        End
    End If
    ' Get number of IO-Warrior devices in system
    numIows = IowKitGetNumDevs()
    ' Get all IO-Warrior handles
    For I = 2 To numIows
        iowHandles(I - 1) = IowKitGetDeviceHandle(I)
    Next I
    Call ClearAllButton_Click
    I = IowKitGetSerialNumber(iowHandles(0), S(0))
    ReadLabel.Caption = S
    ReadLabel.Caption = "Serial number: " + ReadLabel.Caption
    ReadLabel.Refresh
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Call ClearAllButton_Click

    ' Close all IO-Warrior devices
    IowKitCloseDevice (iowHandles(0))
End Sub

' Read something from IO-Warrior
Private Sub ReadButton_Click()
    Dim Res As Long
    Dim N As Long
    Dim Pid As Long

    ' Perform a read
    Pid = IowKitGetProductId(iowHandles(0))
    If Pid = IOWKIT_PID_IOW24 Then
      N = 3
    Else
    If Pid = IOWKIT_PID_IOW40 Then
      N = 5
    Else
    If Pid = IOWKIT_PID_IOW56 Then
      N = 8
    End If
    End If
    End If

    ReadLabel.Caption = "Reading from IOW"
    ReadLabel.Refresh
    ' Read from IO-Warrior
    Res = IowKitRead(iowHandles(0), 0, data(0), N)
    ' Check results
    If Res <> N Then
        ReadLabel.Caption = "Read from IOW wrong?"
    Else
        ' Convert and set data
        TextVal3.Text = ""
        TextVal4.Text = ""
        TextVal5.Text = ""
        TextVal6.Text = ""
        TextVal7.Text = ""

        TextVal1.Text = Hex$(data(1))
        TextVal2.Text = Hex$(data(2))
        If N = 5 Or N = 8 Then
          TextVal3.Text = Hex$(data(3))
          TextVal4.Text = Hex$(data(4))
        End If
        If N = 8 Then
          TextVal5.Text = Hex$(data(5))
          TextVal6.Text = Hex$(data(6))
          TextVal7.Text = Hex$(data(7))
        End If
        ReadLabel.Caption = "Read from IOW complete"
    End If
End Sub

' Write value
Private Sub WriteButton_Click()
    Dim Res As Long
    Dim Value As Byte
    Dim N As Long
    Dim Pid As Long

    Pid = IowKitGetProductId(iowHandles(0))
    If Pid = IOWKIT_PID_IOW24 Then
      N = 3
    Else
    If Pid = IOWKIT_PID_IOW40 Then
      N = 5
    Else
    If Pid = IOWKIT_PID_IOW56 Then
      N = 8
    End If
    End If
    End If

    ' Report ID 0
    data(0) = 0
    ' Get values from text
    ' Note: we don't check values here
    ' so you'd better enter correct values
    Value = Val("&H" & TextVal1.Text)
    data(1) = Value
    Value = Val("&H" & TextVal2.Text)
    data(2) = Value
    If N = 5 Or N = 8 Then
      Value = Val("&H" & TextVal3.Text)
      data(3) = Value
      Value = Val("&H" & TextVal4.Text)
      data(4) = Value
    End If
    If N = 8 Then
      Value = Val("&H" & TextVal5.Text)
      data(5) = Value
      Value = Val("&H" & TextVal6.Text)
      data(6) = Value
      Value = Val("&H" & TextVal7.Text)
      data(7) = Value
    End If

    ' Write to IOW
    Res = IowKitWrite(iowHandles(0), 0, data(0), N)
    ' Handle error
    If Res <> N Then
        ' You can get error code from GetLastError()
        MsgBox "Write to IOW failed!", 0, "Error"
    End If
End Sub
