using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SimpleIO
{
    public partial class Form1 : Form
    {
        private IntPtr ioHandle;
        private byte buffer = 0x00;
        private uint pID;

        public Form1()
        {
            InitializeComponent();
            
        }

        private void connect_Click(object sender, EventArgs e)
        {
            ioHandle = IOWarrior.Functions.IowKitOpenDevice();
            StringBuilder ioSn = new StringBuilder();
            String new_ioSn;
            
            //String ioSn = new StringBuilder();


            if (ioHandle != IntPtr.Zero)
            {
                IOWarrior.Functions.IowKitGetSerialNumber(ioHandle, ioSn);
                new_ioSn = ioSn.ToString();
                serial.Text = ioSn.ToString();

                pID = IOWarrior.Functions.IowKitGetProductId(ioHandle);


                switch (pID)
                {
                    case IOWarrior.Defines.IOWKIT_PRODUCT_ID_IOW24:
                        device.Text = "IO-Warrior 24";
                        port0.Visible = true;
                        port1.Visible = true;
                        port2.Visible = false;
                        port3.Visible = false;
                        port4.Visible = false;
                        port5.Visible = false;
                        port6.Visible = false;

                        port0.Checked = true;
                        
                        break;
                    case IOWarrior.Defines.IOWKIT_PRODUCT_ID_IOW40:
                        device.Text = "IO-Warrior 40";
                        port0.Visible = true;
                        port1.Visible = true;
                        port2.Visible = true;
                        port3.Visible = true;
                        port4.Visible = false;
                        port5.Visible = false;
                        port6.Visible = false;

                        port0.Checked = true;

                        break;
                    case IOWarrior.Defines.IOWKIT_PRODUCT_ID_IOW56:
                        device.Text = "IO-Warrior 56";
                        port0.Visible = true;
                        port1.Visible = true;
                        port2.Visible = true;
                        port3.Visible = true;
                        port4.Visible = true;
                        port5.Visible = true;
                        port6.Visible = true;

                        port0.Checked = true;

                        break;
                }

            }
            else
            {
                MessageBox.Show("Connect FAIL");

                IOWarrior.Functions.IowKitCloseDevice(ioHandle);
            }
        }

        private void exit_Click(object sender, EventArgs e)
        {
            IOWarrior.Functions.IowKitCloseDevice(ioHandle);
            this.Close();
        }

        private byte AddCheckbox()
        {
           // buffer = (byte)(buffer | value);

            byte value = 0;

            if (checkBox1.Checked)
                value |= 0x01;
            else
                value &= 0xFE;


            if (checkBox2.Checked)
                value |= 0x02;
            else
                value &= 0xFD;


            if (checkBox3.Checked)
                value |= 0x04;
            else
                value &= 0xFB;


            if (checkBox4.Checked)
                value |= 0x08;
            else
                value &= 0xF7;


            if (checkBox5.Checked)
                value |= 0x10;
            else
                value &= 0xEF;


            if (checkBox6.Checked)
                value |= 0x20;
            else
                value &= 0xDF;


            if (checkBox7.Checked)
                value |= 0x40;
            else
                value &= 0xBF;


            if (checkBox8.Checked)
                value |= 0x80;
            else
                value &= 0x7F;


            buffer = value;
 
            return buffer;
        }


        private void WriteSimple(byte value)
        {
            byte[] report = new byte[9];

            report[0] = 0;

            switch(pID)
            {
                case IOWarrior.Defines.IOWKIT_PID_IOW24:
                    report[1] = value;
                    IOWarrior.Functions.IowKitWrite(ioHandle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, 8);

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW40:
                    report[4] = value;
                    IOWarrior.Functions.IowKitWrite(ioHandle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, 8);

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW56:
                    report[7] = value;
                    IOWarrior.Functions.IowKitWrite(ioHandle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, 8);

                    break;
            }          
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox7_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {
            byte hex = AddCheckbox();
            hex_view.Text = hex.ToString("X");
            WriteSimple(AddCheckbox());
        }

        private void reset_Click_1(object sender, EventArgs e)
        {
            WriteSimple(255);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            IOWarrior.Functions.IowKitCloseDevice(ioHandle);
        }

        private void random_Click(object sender, EventArgs e)
        {
            Random rand = new Random();
            int a;

            a = rand.Next(0, 255);      //Get random between 0 and 255
        }

    }
}