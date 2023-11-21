Public Class Form1
    'Defines / Constants
    Public Const ENABLE_TIMER As Byte = &H1
    Public Const DISABLE_TIMER As Byte = &H0
    Public Const TIMER_A As Byte = &H29
    Public Const TIMER_B As Byte = &H2A

    Public Const TIME_RESOLUTION As Double = 0.000004

    'Var
    Dim m_handle As Integer
    Dim m_data(8) As Byte
    Dim m_timer As Boolean = False

    Private Sub InitMode(enable As Byte)
        Dim data(8) As Byte
        data(0) = &H28 'Special Mode for Camputer Timer
        data(1) = enable 'Enable Timer A, for Timer B = 2 and Both = 3

        IowKitWrite(m_handle, IOW_PIPE_SPECIAL_MODE, data(0), 8)
    End Sub

    Private Sub EnableTimerA()
        InitMode(ENABLE_TIMER)
    End Sub

    Private Sub DisableTimerA()
        InitMode(DISABLE_TIMER)
    End Sub

    Function CalculateEdge(data0 As Byte, data1 As Byte, data2 As Byte) As Integer
        'Resolution: 1 step = 4 µS

        Dim ret As Integer = 0
        ret = data0 + (256 * data1) + (65536 * data2)
        CalculateEdge = ret

    End Function

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
                EnableTimerA() 'Enable CaptureTimerMode
            Else
                lbl_status.Text = "Connection SUCCEED, wrong device (Only IOW24)"
                lbl_status.ForeColor = Color.Red
            End If
        End If

    End Sub

    Private Sub Form1_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        If (m_handle <> 0) Then
            DisableTimerA() 'Disable CaptureTimerMode
            IowKitCloseDevice(m_handle) 'Close Devices
        End If
    End Sub

    Private Sub btn_exit_Click(sender As Object, e As EventArgs) Handles btn_exit.Click
        If (m_handle <> 0) Then
            DisableTimerA() 'Disable CaptureTimerMode
            IowKitCloseDevice(m_handle) 'Close Devices
        End If
        Close()
    End Sub

    Private Sub ClearList()
        list_timer.Items.Clear()
    End Sub

    Private Sub InsertLine(title As String, tick As Integer)
        Dim arr As String() = New String(3) {}
        Dim itm As ListViewItem 'add items to ListView 
        arr(0) = title
        arr(1) = tick.ToString()
        arr(2) = (tick * TIME_RESOLUTION).ToString() + " Seconds"
        itm = New ListViewItem(arr)
        list_timer.Items.Add(itm)
    End Sub

    Private Sub btn_run_Click(sender As Object, e As EventArgs) Handles btn_run.Click
        If m_timer = False Then
            Timer1.Start()
            m_timer = True
            btn_run.Text = "Stop"
        Else
            Timer1.Stop()
            m_timer = False
            btn_run.Text = "Run"
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim rise As Integer
        Dim fall As Integer
        Dim difference As Integer
        Dim ret As Integer

        If m_handle <> 0 Then
            ret = IowKitReadNonBlocking(m_handle, IOW_PIPE_SPECIAL_MODE, m_data(0), 8) 'Read Data

            If ret <> 0 Then

                If m_data(0) = TIMER_A Then 'Only TimerA

                    If m_data(1) = &H2 Then 'New Falling Edge detected?

                        ClearList() 'Reset ListView

                        rise = CalculateEdge(m_data(2), m_data(3), m_data(4)) 'Calc rise edge tick
                        fall = CalculateEdge(m_data(5), m_data(6), m_data(7)) 'Calc fall edgle tick
                        difference = fall - rise 'difference between edges

                        'Output
                        InsertLine("Rise Edge", rise)
                        InsertLine("Fall Edge", fall)
                        InsertLine("Difference", difference)

                    End If


                End If

            End If

            
        End If


    End Sub
End Class
