Attribute VB_Name = "lcd"

' IO-Warrior library API functions
' LCD functions
' Note: these functions are intended to be used with HD44780-based LCDs,
' and have been tested only with them.

' Enable LCD interface
' Parameters:
' iowHandle - IO-Warrior handle
' enable - 1 to enable, 0 to disable

Dim Pid As Long
Public Function IowKitEnableLCD(iowHandle As Long, enable As Byte) As Boolean
    ' LCD enable packet
    Dim lcdPacket(64) As Byte
    Dim nWritten As Long

    Pid = IowKitGetProductId(iowHandle)
    
    ' Set up IIC enable packet
    ' Report ID 4 is LCD enable/disable
    lcdPacket(0) = 4
    ' Enable/disable LCD
    ' If enable is on, LCD is powered on and backlight is turned on
    lcdPacket(1) = enable

    ' Write Report
    If Pid = IOWKIT_PID_IOW56 Then
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 64)
    Else
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 8)
    End If
    ' Return number of bytes written  to IO-Warrior
    IowKitEnableLCD = nWritten <> 0
End Function

' Write command to LCD
' Parameters:
' iowHandle - IO-Warrior handle
' Cmd - Command to be sent to LCD
Public Function IowKitWriteCmdLCD(iowHandle As Long, Cmd As Byte) As Boolean
    ' LCD Report/packet
    Dim lcdPacket(64) As Byte
    ' Number of bytes written
    Dim nWritten As Long

    ' Set up LCD packet
    ' Report ID 5 - Write to LCD
    lcdPacket(0) = 5
    ' Instruction register, 1 bytes to write
    lcdPacket(1) = 1
    ' Save command in packet
    lcdPacket(2) = Cmd
    ' Go ahead and write to IO-Warrior
    If Pid = IOWKIT_PID_IOW56 Then
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 64)
    Else
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 8)
    End If
    ' Return number of bytes written to IO-Warrior
    IowKitWriteCmdLCD = nWritten <> 0
End Function

' Initialize LCD
' Parameters:
' iowHandle - IO-Warrior handle
' numLines - Number of lines
Public Function IowKitInitLCD(iowHandle As Long, numLines As Long) As Boolean
    ' LCD Report/packet
    Dim lcdPacket(64) As Byte
    ' Number of bytes written
    Dim nWritten As Long

    ' Set up LCD packet
    ' Report ID 5 - Write to LCD
    lcdPacket(0) = 5
    ' Instruction register, 3 bytes to write
    lcdPacket(1) = 3
    ' Init LCD
    lcdPacket(2) = &H28
    ' More than 1 line? Set that flag
    If numLines >= 1 Then
        lcdPacket(2) = lcdPacket(2) Or &H10
    End If
    ' Clear LCD screen
    lcdPacket(3) = 1
    ' Set cursor to line and blinking and move it to home position
    lcdPacket(4) = &HF
    ' Write to LCD
    If Pid = IOWKIT_PID_IOW56 Then
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 64)
    Else
        nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 8)
    End If
    ' After this write, LCD is initialized, DDRAM/cursor address is set to zero,
    ' and you can write to LCD screen
    IowKitInitLCD = nWritten <> 0
End Function

' Clear LCD screen
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitClearLCD(iowHandle As Long) As Boolean
    ' Send clear screen command to LCD
    IowKitClearLCD = IowKitWriteCmdLCD(iowHandle, 1)
End Function

' Entry mode set - set cursor move direction, shift display
' Parameters:
' iowHandle - IO-Warrior handle
' moveForward - cursor moves forward or backward
' shiftDisp - display shifts on write
Public Function IowKitEntryModeSet(iowHandle As Long, _
    moveForward As Boolean, shiftDisp As Boolean) As Boolean

    Dim Cmd As Byte

    ' Entry mode set command
    Cmd = &H4
    ' Set move direction - forward
    If moveForward Then
        Cmd = Cmd Or 2
    End If
    ' Set display shift mode
    If shiftDisp Then
        Cmd = Cmd Or 1
    End If
    ' Set "entry mode set" command to LCD
    IowKitEntryModeSet = IowKitWriteCmdLCD(iowHandle, Cmd)
End Function

' Move cursor to 1st row, 1st col of LCD screen
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorHomeLCD(iowHandle As Long) As Boolean
    ' Send cursor home command to LCD
    IowKitCursorHomeLCD = IowKitWriteCmdLCD(iowHandle, 3)
End Function

' Display control
' Parameters:
' iowHandle - IO-Warrior handle
' dispOn - turn display on or off
' cursorOn - turn cursor on or off
' cursorBlink - turn blinking of cursor on or off
Public Function IowKitDispControlLCD(iowHandle As Long, _
    dispOn As Boolean, cursorOn As Boolean, cursorBlink As Boolean) As Boolean
    ' Command
    Dim Cmd As Byte

    ' Init command
    Cmd = &H8
    ' Check and set dispon, cursonon and cursorblink bits
    If dispOn Then
        Cmd = Cmd Or 4
    End If
    If cursorOn Then
        Cmd = Cmd Or 2
    End If
    If cursorBlink Then
        Cmd = Cmd Or 1
    End If
    ' Send display control command to LCD
    IowKitDispControlLCD = IowKitWriteCmdLCD(iowHandle, Cmd)
End Function

' Shift mode control
' Parameters:
' iowHandle - IO-Warrior handle
' shiftDisp - Shift display
' shiftDir - Shift direction - left or right
Public Function IowKitShiftControlLCD(iowHandle As Long, _
    shiftDisp As Boolean, shiftDir As Boolean) As Boolean
    ' Command
    Dim Cmd As Byte

    ' Cursor/display shift command
    Cmd = &H10
    ' Check and set bits
    If shiftDisp Then
        Cmd = Cmd Or 8
    End If
    If shiftDir Then
        Cmd = Cmd Or 4
    End If
    ' Send "Shift control" command to LCD
    IowKitShiftControlLCD = IowKitWriteCmdLCD(iowHandle, Cmd)
End Function

' Write string to LCD
' Parameters:
' iowHandle - IO-Warrior handle
' strLcd - String to write
' NOTE: This function can write only one line of screen
' you have to manage multiline writes by yourself
Public Function IowKitWriteStringLCD(iowHandle As Long, strLcd As String) As Boolean
    ' Local variables
    Dim lcdPacket(64) As Byte
    Dim nWritten As Long
    Dim nChars As Long
    Dim nCurr As Long
    Dim nNow As Long
    Dim I As Long

    ' Set up packet for writing
    ' Report ID 5 - Write to LCD
    lcdPacket(0) = 5
    nCurr = 0
    ' Get string length
    nChars = Len(strLcd)
    Do While nCurr < nChars
        ' Check if we write last time
        If (nCurr + 6) > nChars Then
            nNow = nChars - nCurr
        Else
            nNow = 6
        End If
        ' Flags Or number of characters to write
        lcdPacket(1) = &H80 Or nNow
        For I = 1 To nNow
            ' Save characters to packet
            lcdPacket(1 + I) = Asc(Mid(strLcd, nCurr + I, 1))
        Next I
        ' Write to LCD
        If Pid = IOWKIT_PID_IOW56 Then
            nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 64)
        Else
            nWritten = IowKitWrite(iowHandle, IOW_PIPE_SPECIAL_MODE, lcdPacket(0), 8)
        End If
        nCurr = nCurr + 6
    Loop
    ' Return number of bytes written to IO-Warrior
    IowKitWriteStringLCD = nWritten <> 0
End Function

' Set DDRAM address
' Parameters:
' iowHandle - IO-Warrior handle
' Address - DDRAM address
Public Function IowKitSetDDRAMAddr(iowHandle As Long, Address As Byte) As Boolean
    ' Local variables
    ' Command
    Dim Cmd As Byte

    ' Command - Set DDRAM address or Address
    Cmd = &H80 Or Address
    ' Send "Set DDRAM Address" command to LCD
    IowKitSetDDRAMAddr = IowKitWriteCmdLCD(iowHandle, Cmd)
End Function

' This functions moves cursor to new position
' Parameters:
' iowHandle - IO-Warrior handle
' Row - Row
' Col - Col
' Due to weird addressing modes, some 1-line models act like 2-line models,
' so you have first half of screen on first line, and second half is on
' second line (ie at 40H address)
' See your LCD module specs for more details on addressing
Public Function IowKitSetCursorLCD(iowHandle As Long, _
    Row As Byte, Col As Byte) As Boolean
    ' Local variables
    Dim Address As Byte

    ' Calculate DDRAM memory address
    If Row = 1 Then
        Address = &H0
    End If
    If Row = 2 Then
        Address = &H40
    End If
    If Row = 3 Then
        Address = &H14
    End If
    If Row = 4 Then
        Address = &H54
    End If

    Address = Address + Col - 1
    ' Set DDRAM address and move cursor to new position
    IowKitSetCursorLCD = IowKitSetDDRAMAddr(iowHandle, Address)
End Function

'
' LCD display control functions
'

' Turn LCD display on
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorDispOnLCD(iowHandle As Long) As Boolean
  ' Send "Display on" command
  IowKitCursorDispOnLCD = IowKitWriteCmdLCD(iowHandle, &HC)
End Function

' Turn LCD display off
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitDispOffLCD(iowHandle As Long) As Boolean
    ' Send "display off" command
    IowKitDispOffLCD = IowKitWriteCmdLCD(iowHandle, &H8)
End Function

'
' LCD cursor control functions
'

' Turn LCD cursor on
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorOnLCD(iowHandle As Long) As Boolean
    ' Send "turn cursor on" command
    IowKitCursorOnLCD = IowKitWriteCmdLCD(iowHandle, &HD)
End Function

' Turn LCD cursor off
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorOffLCD(iowHandle As Long) As Long
    ' Send "turn cursor off" command
    IowKitCursorOffLCD = IowKitWriteCmdLCD(iowHandle, &HC)
End Function

'
' LCD Cursor movement functions
'

' Move LCD cursor to the left
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorLeftLCD(iowHandle As Long) As Boolean
    ' Send "move cursor the left" command
    IowKitCursorLeftLCD = IowKitWriteCmdLCD(iowHandle, &H10)
End Function

' Move LCD cursor to the right
' Parameters:
' iowHandle - IO-Warrior handle
Public Function IowKitCursorRightLCD(iowHandle As Long) As Boolean
    ' Send "move cursor to the right" command
    IowKitCursorRightLCD = IowKitWriteCmdLCD(iowHandle, &H14)
End Function
