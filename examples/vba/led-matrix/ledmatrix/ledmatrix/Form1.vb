Public Class Form1

    Dim m_handle As Integer 'Global IO-Warrior Handle (get the first IO-Warrior on USB)

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        cmb_row.SelectedIndex = 0

    End Sub

    Private Sub Form1_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        If (m_handle <> 0) Then
            EnableMatrix(&H0) 'Disable LED-Matrix
            IowKitCloseDevice(m_handle) 'Close Devices
        End If

    End Sub

    Private Sub EnableMatrix(enable As Byte)
        Dim data(8) As Byte

        'Enable LED-Matrix Mode
        data(0) = &H14 'Special Mode LED-Matrix
        data(1) = enable  'Enable = 1, Disable = 0
        IowKitWrite(m_handle, IOW_PIPE_SPECIAL_MODE, data(0), 8) '8 bytes for Special Mode IOW24 / 40
    End Sub

    Private Sub btn_connect_Click(sender As Object, e As EventArgs) Handles btn_connect.Click
        Dim pid As ULong

        m_handle = IowKitOpenDevice()

        If (m_handle = 0) Then
            lbl_status.Text = "Connection FAILED"
            lbl_status.ForeColor = Color.Red
            Close() 'Exit Application
        Else
            pid = IowKitGetProductId(m_handle)

            If pid = IOWKIT_PID_IOW24 Then
                lbl_status.Text = "Connection SUCCEED"
                lbl_status.ForeColor = Color.Green

                EnableMatrix(&H1) 'Enable LED-Matrix

            Else
                lbl_status.Text = "Connection SUCCEED, wrong device (Only IOW24 for this sample)"
                lbl_status.ForeColor = Color.Red
            End If
        End If
    End Sub


    Private Sub btn_send_Click(sender As Object, e As EventArgs) Handles btn_send.Click
        Dim data(8) As Byte

        data(0) = &H15
        data(1) = Val("&H" & cmb_row.Text) - 1 'row
        data(2) = Val("&H" & txt_byte1.Text) 'byte 1 ; 8 Bit, 1 LED per bit
        data(3) = Val("&H" & txt_byte2.Text) 'byte 2 ; 8 Bit, 1 LED per bit
        data(4) = Val("&H" & txt_byte3.Text) 'byte 3 ; 8 Bit, 1 LED per bit
        data(5) = Val("&H" & txt_byte4.Text) 'byte 4 ; 8 Bit, 1 LED per bit

        IowKitWrite(m_handle, IOW_PIPE_SPECIAL_MODE, data(0), 8)
    End Sub

    Private Sub txt_byte1_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txt_byte1.KeyPress
        e.Handled = Not (System.Uri.IsHexDigit(e.KeyChar) Or e.KeyChar = ChrW(8))
    End Sub

    Private Sub txt_byte2_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txt_byte2.KeyPress
        e.Handled = Not (System.Uri.IsHexDigit(e.KeyChar) Or e.KeyChar = ChrW(8))
    End Sub

    Private Sub txt_byte3_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txt_byte3.KeyPress
        e.Handled = Not (System.Uri.IsHexDigit(e.KeyChar) Or e.KeyChar = ChrW(8))
    End Sub

    Private Sub txt_byte4_KeyPress(sender As Object, e As KeyPressEventArgs) Handles txt_byte4.KeyPress
        e.Handled = Not (System.Uri.IsHexDigit(e.KeyChar) Or e.KeyChar = ChrW(8))
    End Sub
End Class
