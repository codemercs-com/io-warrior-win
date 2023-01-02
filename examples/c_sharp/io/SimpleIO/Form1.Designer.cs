namespace SimpleIO
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
            this.connect = new System.Windows.Forms.Button();
            this.exit = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.serial = new System.Windows.Forms.Label();
            this.device = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.reset = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.hex_view = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.port0 = new System.Windows.Forms.CheckBox();
            this.port1 = new System.Windows.Forms.CheckBox();
            this.port2 = new System.Windows.Forms.CheckBox();
            this.port3 = new System.Windows.Forms.CheckBox();
            this.port4 = new System.Windows.Forms.CheckBox();
            this.port5 = new System.Windows.Forms.CheckBox();
            this.port6 = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.version = new System.Windows.Forms.Label();
            this.random = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // connect
            // 
            this.connect.Location = new System.Drawing.Point(12, 12);
            this.connect.Name = "connect";
            this.connect.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.connect.Size = new System.Drawing.Size(75, 23);
            this.connect.TabIndex = 0;
            this.connect.Text = "Connect";
            this.connect.UseVisualStyleBackColor = true;
            this.connect.Click += new System.EventHandler(this.connect_Click);
            // 
            // exit
            // 
            this.exit.Location = new System.Drawing.Point(385, 18);
            this.exit.Name = "exit";
            this.exit.Size = new System.Drawing.Size(75, 23);
            this.exit.TabIndex = 1;
            this.exit.Text = "Exit";
            this.exit.UseVisualStyleBackColor = true;
            this.exit.Click += new System.EventHandler(this.exit_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Serial:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Device:";
            // 
            // serial
            // 
            this.serial.AutoSize = true;
            this.serial.ForeColor = System.Drawing.Color.Black;
            this.serial.Location = new System.Drawing.Point(59, 48);
            this.serial.Name = "serial";
            this.serial.Size = new System.Drawing.Size(22, 13);
            this.serial.TabIndex = 2;
            this.serial.Text = "- - -";
            // 
            // device
            // 
            this.device.AutoSize = true;
            this.device.ForeColor = System.Drawing.Color.Black;
            this.device.Location = new System.Drawing.Point(59, 26);
            this.device.Name = "device";
            this.device.Size = new System.Drawing.Size(22, 13);
            this.device.TabIndex = 2;
            this.device.Text = "- - -";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(116, 46);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(15, 14);
            this.checkBox1.TabIndex = 3;
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(101, 46);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(15, 14);
            this.checkBox2.TabIndex = 3;
            this.checkBox2.UseVisualStyleBackColor = true;
            this.checkBox2.CheckedChanged += new System.EventHandler(this.checkBox2_CheckedChanged);
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Location = new System.Drawing.Point(86, 46);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(15, 14);
            this.checkBox3.TabIndex = 3;
            this.checkBox3.UseVisualStyleBackColor = true;
            this.checkBox3.CheckedChanged += new System.EventHandler(this.checkBox3_CheckedChanged);
            // 
            // checkBox4
            // 
            this.checkBox4.AutoSize = true;
            this.checkBox4.Location = new System.Drawing.Point(71, 46);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(15, 14);
            this.checkBox4.TabIndex = 3;
            this.checkBox4.UseVisualStyleBackColor = true;
            this.checkBox4.CheckedChanged += new System.EventHandler(this.checkBox4_CheckedChanged);
            // 
            // checkBox5
            // 
            this.checkBox5.AutoSize = true;
            this.checkBox5.Location = new System.Drawing.Point(56, 46);
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.Size = new System.Drawing.Size(15, 14);
            this.checkBox5.TabIndex = 3;
            this.checkBox5.UseVisualStyleBackColor = true;
            this.checkBox5.CheckedChanged += new System.EventHandler(this.checkBox5_CheckedChanged);
            // 
            // checkBox6
            // 
            this.checkBox6.AutoSize = true;
            this.checkBox6.Location = new System.Drawing.Point(41, 46);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(15, 14);
            this.checkBox6.TabIndex = 3;
            this.checkBox6.UseVisualStyleBackColor = true;
            this.checkBox6.CheckedChanged += new System.EventHandler(this.checkBox6_CheckedChanged);
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Location = new System.Drawing.Point(26, 46);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(15, 14);
            this.checkBox7.TabIndex = 3;
            this.checkBox7.UseVisualStyleBackColor = true;
            this.checkBox7.CheckedChanged += new System.EventHandler(this.checkBox7_CheckedChanged);
            // 
            // checkBox8
            // 
            this.checkBox8.AutoSize = true;
            this.checkBox8.Location = new System.Drawing.Point(11, 46);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(15, 14);
            this.checkBox8.TabIndex = 3;
            this.checkBox8.UseVisualStyleBackColor = true;
            this.checkBox8.CheckedChanged += new System.EventHandler(this.checkBox8_CheckedChanged);
            // 
            // reset
            // 
            this.reset.Location = new System.Drawing.Point(140, 82);
            this.reset.Name = "reset";
            this.reset.Size = new System.Drawing.Size(75, 23);
            this.reset.TabIndex = 4;
            this.reset.Text = "Reset";
            this.reset.UseVisualStyleBackColor = true;
            this.reset.Click += new System.EventHandler(this.reset_Click_1);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.random);
            this.groupBox1.Controls.Add(this.hex_view);
            this.groupBox1.Controls.Add(this.reset);
            this.groupBox1.Controls.Add(this.checkBox1);
            this.groupBox1.Controls.Add(this.checkBox2);
            this.groupBox1.Controls.Add(this.checkBox8);
            this.groupBox1.Controls.Add(this.checkBox3);
            this.groupBox1.Controls.Add(this.checkBox7);
            this.groupBox1.Controls.Add(this.checkBox4);
            this.groupBox1.Controls.Add(this.checkBox6);
            this.groupBox1.Controls.Add(this.checkBox5);
            this.groupBox1.Location = new System.Drawing.Point(239, 118);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(221, 113);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Bits on selected port";
            // 
            // hex_view
            // 
            this.hex_view.AutoSize = true;
            this.hex_view.Location = new System.Drawing.Point(146, 46);
            this.hex_view.Name = "hex_view";
            this.hex_view.Size = new System.Drawing.Size(30, 13);
            this.hex_view.TabIndex = 5;
            this.hex_view.Text = "0x00";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.port6);
            this.groupBox2.Controls.Add(this.port5);
            this.groupBox2.Controls.Add(this.port4);
            this.groupBox2.Controls.Add(this.port3);
            this.groupBox2.Controls.Add(this.port2);
            this.groupBox2.Controls.Add(this.port1);
            this.groupBox2.Controls.Add(this.port0);
            this.groupBox2.Location = new System.Drawing.Point(12, 118);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(221, 113);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Port Select";
            // 
            // port0
            // 
            this.port0.AutoSize = true;
            this.port0.Location = new System.Drawing.Point(11, 19);
            this.port0.Name = "port0";
            this.port0.Size = new System.Drawing.Size(54, 17);
            this.port0.TabIndex = 6;
            this.port0.Text = "Port 0";
            this.port0.UseVisualStyleBackColor = true;
            this.port0.Visible = false;
            // 
            // port1
            // 
            this.port1.AutoSize = true;
            this.port1.Location = new System.Drawing.Point(11, 42);
            this.port1.Name = "port1";
            this.port1.Size = new System.Drawing.Size(54, 17);
            this.port1.TabIndex = 6;
            this.port1.Text = "Port 1";
            this.port1.UseVisualStyleBackColor = true;
            this.port1.Visible = false;
            // 
            // port2
            // 
            this.port2.AutoSize = true;
            this.port2.Location = new System.Drawing.Point(11, 65);
            this.port2.Name = "port2";
            this.port2.Size = new System.Drawing.Size(54, 17);
            this.port2.TabIndex = 6;
            this.port2.Text = "Port 2";
            this.port2.UseVisualStyleBackColor = true;
            this.port2.Visible = false;
            // 
            // port3
            // 
            this.port3.AutoSize = true;
            this.port3.Location = new System.Drawing.Point(11, 88);
            this.port3.Name = "port3";
            this.port3.Size = new System.Drawing.Size(54, 17);
            this.port3.TabIndex = 6;
            this.port3.Text = "Port 3";
            this.port3.UseVisualStyleBackColor = true;
            this.port3.Visible = false;
            // 
            // port4
            // 
            this.port4.AutoSize = true;
            this.port4.Location = new System.Drawing.Point(77, 19);
            this.port4.Name = "port4";
            this.port4.Size = new System.Drawing.Size(54, 17);
            this.port4.TabIndex = 6;
            this.port4.Text = "Port 4";
            this.port4.UseVisualStyleBackColor = true;
            this.port4.Visible = false;
            // 
            // port5
            // 
            this.port5.AutoSize = true;
            this.port5.Location = new System.Drawing.Point(77, 42);
            this.port5.Name = "port5";
            this.port5.Size = new System.Drawing.Size(54, 17);
            this.port5.TabIndex = 6;
            this.port5.Text = "Port 5";
            this.port5.UseVisualStyleBackColor = true;
            this.port5.Visible = false;
            // 
            // port6
            // 
            this.port6.AutoSize = true;
            this.port6.Location = new System.Drawing.Point(77, 65);
            this.port6.Name = "port6";
            this.port6.Size = new System.Drawing.Size(54, 17);
            this.port6.TabIndex = 6;
            this.port6.Text = "Port 6";
            this.port6.UseVisualStyleBackColor = true;
            this.port6.Visible = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.version);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.serial);
            this.groupBox3.Controls.Add(this.device);
            this.groupBox3.Location = new System.Drawing.Point(107, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(263, 100);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Device information";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(5, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Version:";
            // 
            // version
            // 
            this.version.AutoSize = true;
            this.version.Location = new System.Drawing.Point(59, 70);
            this.version.Name = "version";
            this.version.Size = new System.Drawing.Size(22, 13);
            this.version.TabIndex = 4;
            this.version.Text = "- - -";
            // 
            // random
            // 
            this.random.Location = new System.Drawing.Point(56, 82);
            this.random.Name = "random";
            this.random.Size = new System.Drawing.Size(75, 23);
            this.random.TabIndex = 6;
            this.random.Text = "Random";
            this.random.UseVisualStyleBackColor = true;
            this.random.Click += new System.EventHandler(this.random_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(465, 235);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.exit);
            this.Controls.Add(this.connect);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button connect;
        private System.Windows.Forms.Button exit;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label serial;
        private System.Windows.Forms.Label device;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox5;
        private System.Windows.Forms.CheckBox checkBox6;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.Button reset;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label hex_view;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox port6;
        private System.Windows.Forms.CheckBox port5;
        private System.Windows.Forms.CheckBox port4;
        private System.Windows.Forms.CheckBox port3;
        private System.Windows.Forms.CheckBox port2;
        private System.Windows.Forms.CheckBox port1;
        private System.Windows.Forms.CheckBox port0;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label version;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button random;
    }
}

