<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Das Formular überschreibt den Löschvorgang, um die Komponentenliste zu bereinigen.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Wird vom Windows Form-Designer benötigt.
    Private components As System.ComponentModel.IContainer

    'Hinweis: Die folgende Prozedur ist für den Windows Form-Designer erforderlich.
    'Das Bearbeiten ist mit dem Windows Form-Designer möglich.  
    'Das Bearbeiten mit dem Code-Editor ist nicht möglich.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.btn_connect = New System.Windows.Forms.Button()
        Me.btn_run = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.list_timer = New System.Windows.Forms.ListView()
        Me.title = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.tick = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.time = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.btn_exit = New System.Windows.Forms.Button()
        Me.lbl_status = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'btn_connect
        '
        Me.btn_connect.Location = New System.Drawing.Point(12, 12)
        Me.btn_connect.Name = "btn_connect"
        Me.btn_connect.Size = New System.Drawing.Size(75, 23)
        Me.btn_connect.TabIndex = 0
        Me.btn_connect.Text = "Connect"
        Me.btn_connect.UseVisualStyleBackColor = True
        '
        'btn_run
        '
        Me.btn_run.Location = New System.Drawing.Point(12, 41)
        Me.btn_run.Name = "btn_run"
        Me.btn_run.Size = New System.Drawing.Size(75, 23)
        Me.btn_run.TabIndex = 1
        Me.btn_run.Text = "Run"
        Me.btn_run.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        Me.Timer1.Interval = 8
        '
        'list_timer
        '
        Me.list_timer.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.title, Me.tick, Me.time})
        Me.list_timer.Location = New System.Drawing.Point(12, 70)
        Me.list_timer.Name = "list_timer"
        Me.list_timer.Size = New System.Drawing.Size(388, 130)
        Me.list_timer.TabIndex = 2
        Me.list_timer.UseCompatibleStateImageBehavior = False
        Me.list_timer.View = System.Windows.Forms.View.Details
        '
        'title
        '
        Me.title.Text = "Edge"
        '
        'tick
        '
        Me.tick.Text = "Ticks"
        Me.tick.Width = 120
        '
        'time
        '
        Me.time.Text = "Time"
        Me.time.Width = 120
        '
        'btn_exit
        '
        Me.btn_exit.Location = New System.Drawing.Point(325, 206)
        Me.btn_exit.Name = "btn_exit"
        Me.btn_exit.Size = New System.Drawing.Size(75, 23)
        Me.btn_exit.TabIndex = 3
        Me.btn_exit.Text = "Exit"
        Me.btn_exit.UseVisualStyleBackColor = True
        '
        'lbl_status
        '
        Me.lbl_status.AutoSize = True
        Me.lbl_status.Location = New System.Drawing.Point(119, 17)
        Me.lbl_status.Name = "lbl_status"
        Me.lbl_status.Size = New System.Drawing.Size(39, 13)
        Me.lbl_status.TabIndex = 4
        Me.lbl_status.Text = "Label1"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(412, 232)
        Me.Controls.Add(Me.lbl_status)
        Me.Controls.Add(Me.btn_exit)
        Me.Controls.Add(Me.list_timer)
        Me.Controls.Add(Me.btn_run)
        Me.Controls.Add(Me.btn_connect)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Form1"
        Me.Text = "Capturetimer Sample"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents btn_connect As System.Windows.Forms.Button
    Friend WithEvents btn_run As System.Windows.Forms.Button
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents list_timer As System.Windows.Forms.ListView
    Friend WithEvents title As System.Windows.Forms.ColumnHeader
    Friend WithEvents tick As System.Windows.Forms.ColumnHeader
    Friend WithEvents time As System.Windows.Forms.ColumnHeader
    Friend WithEvents btn_exit As System.Windows.Forms.Button
    Friend WithEvents lbl_status As System.Windows.Forms.Label

End Class
