namespace led_matrix
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
            this.init = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.device = new System.Windows.Forms.Label();
            this.serial = new System.Windows.Forms.Label();
            this.random = new System.Windows.Forms.Button();
            this.clear = new System.Windows.Forms.Button();
            this.input_text = new System.Windows.Forms.TextBox();
            this.img_send = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // connect
            // 
            this.connect.Location = new System.Drawing.Point(12, 12);
            this.connect.Name = "connect";
            this.connect.Size = new System.Drawing.Size(141, 23);
            this.connect.TabIndex = 0;
            this.connect.Text = "Connect";
            this.connect.UseVisualStyleBackColor = true;
            this.connect.Click += new System.EventHandler(this.connect_Click);
            // 
            // init
            // 
            this.init.Location = new System.Drawing.Point(159, 12);
            this.init.Name = "init";
            this.init.Size = new System.Drawing.Size(141, 23);
            this.init.TabIndex = 0;
            this.init.Text = "Init LED-Matrix";
            this.init.UseVisualStyleBackColor = true;
            this.init.Click += new System.EventHandler(this.init_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Device:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Serial:";
            // 
            // device
            // 
            this.device.AutoSize = true;
            this.device.Location = new System.Drawing.Point(68, 51);
            this.device.Name = "device";
            this.device.Size = new System.Drawing.Size(67, 13);
            this.device.TabIndex = 1;
            this.device.Text = "No Device...";
            // 
            // serial
            // 
            this.serial.AutoSize = true;
            this.serial.Location = new System.Drawing.Point(68, 64);
            this.serial.Name = "serial";
            this.serial.Size = new System.Drawing.Size(67, 13);
            this.serial.TabIndex = 1;
            this.serial.Text = "No Device...";
            // 
            // random
            // 
            this.random.Location = new System.Drawing.Point(234, 90);
            this.random.Name = "random";
            this.random.Size = new System.Drawing.Size(75, 23);
            this.random.TabIndex = 2;
            this.random.Text = "Random";
            this.random.UseVisualStyleBackColor = true;
            this.random.Click += new System.EventHandler(this.random_Click);
            // 
            // clear
            // 
            this.clear.Location = new System.Drawing.Point(153, 90);
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(75, 23);
            this.clear.TabIndex = 3;
            this.clear.Text = "Clear";
            this.clear.UseVisualStyleBackColor = true;
            this.clear.Click += new System.EventHandler(this.clear_Click);
            // 
            // input_text
            // 
            this.input_text.Location = new System.Drawing.Point(43, 120);
            this.input_text.Name = "input_text";
            this.input_text.Size = new System.Drawing.Size(100, 20);
            this.input_text.TabIndex = 1;
            // 
            // img_send
            // 
            this.img_send.Location = new System.Drawing.Point(153, 119);
            this.img_send.Name = "img_send";
            this.img_send.Size = new System.Drawing.Size(75, 23);
            this.img_send.TabIndex = 0;
            this.img_send.Text = "Send";
            this.img_send.UseVisualStyleBackColor = true;
            this.img_send.Click += new System.EventHandler(this.img_send_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 124);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Text:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(321, 180);
            this.Controls.Add(this.input_text);
            this.Controls.Add(this.clear);
            this.Controls.Add(this.random);
            this.Controls.Add(this.img_send);
            this.Controls.Add(this.serial);
            this.Controls.Add(this.device);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.init);
            this.Controls.Add(this.connect);
            this.Name = "Form1";
            this.Text = "LED-Matrix Sample";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button connect;
        private System.Windows.Forms.Button init;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label device;
        private System.Windows.Forms.Label serial;
        private System.Windows.Forms.Button random;
        private System.Windows.Forms.Button clear;
        private System.Windows.Forms.TextBox input_text;
        private System.Windows.Forms.Button img_send;
        private System.Windows.Forms.Label label3;
    }
}

