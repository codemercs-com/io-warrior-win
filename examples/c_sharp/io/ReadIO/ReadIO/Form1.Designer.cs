namespace ReadIO
{
    partial class Form1
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btn_connect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.grid_result = new System.Windows.Forms.DataGridView();
            this.btn_clear = new System.Windows.Forms.Button();
            this.btn_start = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.lbl_device = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.b1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b8 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b9 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b10 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b11 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.b12 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.grid_result)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_connect
            // 
            this.btn_connect.Location = new System.Drawing.Point(12, 12);
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.Size = new System.Drawing.Size(75, 23);
            this.btn_connect.TabIndex = 0;
            this.btn_connect.Text = "Connect";
            this.btn_connect.UseVisualStyleBackColor = true;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Result";
            // 
            // grid_result
            // 
            this.grid_result.AllowUserToAddRows = false;
            this.grid_result.AllowUserToDeleteRows = false;
            this.grid_result.AllowUserToOrderColumns = true;
            this.grid_result.AllowUserToResizeColumns = false;
            this.grid_result.AllowUserToResizeRows = false;
            this.grid_result.BackgroundColor = System.Drawing.Color.White;
            this.grid_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grid_result.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.b1,
            this.b2,
            this.b3,
            this.b4,
            this.b5,
            this.b6,
            this.b7,
            this.b8,
            this.b9,
            this.b10,
            this.b11,
            this.b12});
            this.grid_result.EnableHeadersVisualStyles = false;
            this.grid_result.Location = new System.Drawing.Point(12, 75);
            this.grid_result.Name = "grid_result";
            this.grid_result.RowHeadersVisible = false;
            this.grid_result.Size = new System.Drawing.Size(756, 475);
            this.grid_result.TabIndex = 3;
            // 
            // btn_clear
            // 
            this.btn_clear.Location = new System.Drawing.Point(693, 556);
            this.btn_clear.Name = "btn_clear";
            this.btn_clear.Size = new System.Drawing.Size(75, 23);
            this.btn_clear.TabIndex = 4;
            this.btn_clear.Text = "Clear";
            this.btn_clear.UseVisualStyleBackColor = true;
            this.btn_clear.Click += new System.EventHandler(this.btn_clear_Click);
            // 
            // btn_start
            // 
            this.btn_start.Enabled = false;
            this.btn_start.Location = new System.Drawing.Point(612, 556);
            this.btn_start.Name = "btn_start";
            this.btn_start.Size = new System.Drawing.Size(75, 23);
            this.btn_start.TabIndex = 5;
            this.btn_start.Text = "Start";
            this.btn_start.UseVisualStyleBackColor = true;
            this.btn_start.Click += new System.EventHandler(this.btn_start_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 8;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(113, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Conneted Device:";
            // 
            // lbl_device
            // 
            this.lbl_device.AutoSize = true;
            this.lbl_device.Location = new System.Drawing.Point(212, 17);
            this.lbl_device.Name = "lbl_device";
            this.lbl_device.Size = new System.Drawing.Size(19, 13);
            this.lbl_device.TabIndex = 7;
            this.lbl_device.Text = "no";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 561);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(139, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "New Results add to first row";
            // 
            // b1
            // 
            this.b1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b1.HeaderText = "Port 1";
            this.b1.Name = "b1";
            this.b1.Width = 60;
            // 
            // b2
            // 
            this.b2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b2.HeaderText = "Port 2";
            this.b2.Name = "b2";
            this.b2.Width = 60;
            // 
            // b3
            // 
            this.b3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b3.HeaderText = "Port 3";
            this.b3.Name = "b3";
            this.b3.Width = 60;
            // 
            // b4
            // 
            this.b4.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b4.HeaderText = "Port 4";
            this.b4.Name = "b4";
            this.b4.Width = 60;
            // 
            // b5
            // 
            this.b5.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b5.HeaderText = "Port 5";
            this.b5.Name = "b5";
            this.b5.Width = 60;
            // 
            // b6
            // 
            this.b6.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b6.HeaderText = "Port 6";
            this.b6.Name = "b6";
            this.b6.Width = 60;
            // 
            // b7
            // 
            this.b7.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b7.HeaderText = "Port 7";
            this.b7.Name = "b7";
            this.b7.Width = 60;
            // 
            // b8
            // 
            this.b8.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b8.HeaderText = "Port 8";
            this.b8.Name = "b8";
            this.b8.Width = 60;
            // 
            // b9
            // 
            this.b9.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b9.HeaderText = "Port 9";
            this.b9.Name = "b9";
            this.b9.Width = 60;
            // 
            // b10
            // 
            this.b10.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b10.HeaderText = "Port 10";
            this.b10.Name = "b10";
            this.b10.Width = 66;
            // 
            // b11
            // 
            this.b11.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b11.HeaderText = "Port 11";
            this.b11.Name = "b11";
            this.b11.Width = 66;
            // 
            // b12
            // 
            this.b12.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.b12.HeaderText = "Port 12";
            this.b12.Name = "b12";
            this.b12.Width = 66;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(781, 591);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbl_device);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_start);
            this.Controls.Add(this.btn_clear);
            this.Controls.Add(this.grid_result);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_connect);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "IO-Warrior IO-Port Read";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.grid_result)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView grid_result;
        private System.Windows.Forms.Button btn_clear;
        private System.Windows.Forms.Button btn_start;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbl_device;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridViewTextBoxColumn b1;
        private System.Windows.Forms.DataGridViewTextBoxColumn b2;
        private System.Windows.Forms.DataGridViewTextBoxColumn b3;
        private System.Windows.Forms.DataGridViewTextBoxColumn b4;
        private System.Windows.Forms.DataGridViewTextBoxColumn b5;
        private System.Windows.Forms.DataGridViewTextBoxColumn b6;
        private System.Windows.Forms.DataGridViewTextBoxColumn b7;
        private System.Windows.Forms.DataGridViewTextBoxColumn b8;
        private System.Windows.Forms.DataGridViewTextBoxColumn b9;
        private System.Windows.Forms.DataGridViewTextBoxColumn b10;
        private System.Windows.Forms.DataGridViewTextBoxColumn b11;
        private System.Windows.Forms.DataGridViewTextBoxColumn b12;
    }
}

