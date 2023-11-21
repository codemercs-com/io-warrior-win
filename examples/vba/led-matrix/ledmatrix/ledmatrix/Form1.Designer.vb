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
        Me.btn_connect = New System.Windows.Forms.Button()
        Me.btn_send = New System.Windows.Forms.Button()
        Me.lbl_status = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.cmb_row = New System.Windows.Forms.ComboBox()
        Me.txt_byte1 = New System.Windows.Forms.TextBox()
        Me.txt_byte2 = New System.Windows.Forms.TextBox()
        Me.txt_byte3 = New System.Windows.Forms.TextBox()
        Me.txt_byte4 = New System.Windows.Forms.TextBox()
        Me.Label6 = New System.Windows.Forms.Label()
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
        'btn_send
        '
        Me.btn_send.Location = New System.Drawing.Point(216, 131)
        Me.btn_send.Name = "btn_send"
        Me.btn_send.Size = New System.Drawing.Size(75, 23)
        Me.btn_send.TabIndex = 1
        Me.btn_send.Text = "Send"
        Me.btn_send.UseVisualStyleBackColor = True
        '
        'lbl_status
        '
        Me.lbl_status.AutoSize = True
        Me.lbl_status.Location = New System.Drawing.Point(93, 17)
        Me.lbl_status.Name = "lbl_status"
        Me.lbl_status.Size = New System.Drawing.Size(39, 13)
        Me.lbl_status.TabIndex = 2
        Me.lbl_status.Text = "Label1"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(24, 64)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(29, 13)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "Row"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(92, 64)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(37, 13)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "Byte 1"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(141, 64)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(37, 13)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "Byte 2"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(195, 64)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(37, 13)
        Me.Label4.TabIndex = 3
        Me.Label4.Text = "Byte 3"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(247, 64)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(37, 13)
        Me.Label5.TabIndex = 3
        Me.Label5.Text = "Byte 4"
        '
        'cmb_row
        '
        Me.cmb_row.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmb_row.FormattingEnabled = True
        Me.cmb_row.Items.AddRange(New Object() {"1", "2", "3", "4", "5", "6", "7", "8"})
        Me.cmb_row.Location = New System.Drawing.Point(11, 82)
        Me.cmb_row.Name = "cmb_row"
        Me.cmb_row.Size = New System.Drawing.Size(53, 21)
        Me.cmb_row.TabIndex = 4
        '
        'txt_byte1
        '
        Me.txt_byte1.Location = New System.Drawing.Point(83, 82)
        Me.txt_byte1.MaxLength = 2
        Me.txt_byte1.Name = "txt_byte1"
        Me.txt_byte1.Size = New System.Drawing.Size(48, 20)
        Me.txt_byte1.TabIndex = 5
        Me.txt_byte1.Text = "00"
        '
        'txt_byte2
        '
        Me.txt_byte2.Location = New System.Drawing.Point(135, 82)
        Me.txt_byte2.MaxLength = 2
        Me.txt_byte2.Name = "txt_byte2"
        Me.txt_byte2.Size = New System.Drawing.Size(48, 20)
        Me.txt_byte2.TabIndex = 5
        Me.txt_byte2.Text = "00"
        '
        'txt_byte3
        '
        Me.txt_byte3.Location = New System.Drawing.Point(189, 82)
        Me.txt_byte3.MaxLength = 2
        Me.txt_byte3.Name = "txt_byte3"
        Me.txt_byte3.Size = New System.Drawing.Size(48, 20)
        Me.txt_byte3.TabIndex = 5
        Me.txt_byte3.Text = "00"
        '
        'txt_byte4
        '
        Me.txt_byte4.Location = New System.Drawing.Point(243, 82)
        Me.txt_byte4.MaxLength = 2
        Me.txt_byte4.Name = "txt_byte4"
        Me.txt_byte4.Size = New System.Drawing.Size(48, 20)
        Me.txt_byte4.TabIndex = 5
        Me.txt_byte4.Text = "00"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(113, 105)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(137, 13)
        Me.Label6.TabIndex = 6
        Me.Label6.Text = "Input value: Hex (0..9, A..F)"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(303, 165)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.txt_byte4)
        Me.Controls.Add(Me.txt_byte3)
        Me.Controls.Add(Me.txt_byte2)
        Me.Controls.Add(Me.txt_byte1)
        Me.Controls.Add(Me.cmb_row)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.lbl_status)
        Me.Controls.Add(Me.btn_send)
        Me.Controls.Add(Me.btn_connect)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Form1"
        Me.Text = "LED-Matrix (for IO-Warrior24)"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents btn_connect As System.Windows.Forms.Button
    Friend WithEvents btn_send As System.Windows.Forms.Button
    Friend WithEvents lbl_status As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents cmb_row As System.Windows.Forms.ComboBox
    Friend WithEvents txt_byte1 As System.Windows.Forms.TextBox
    Friend WithEvents txt_byte2 As System.Windows.Forms.TextBox
    Friend WithEvents txt_byte3 As System.Windows.Forms.TextBox
    Friend WithEvents txt_byte4 As System.Windows.Forms.TextBox
    Friend WithEvents Label6 As System.Windows.Forms.Label

End Class
