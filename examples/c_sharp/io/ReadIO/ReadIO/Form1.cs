using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ReadIO
{
    public partial class Form1 : Form
    {
        Boolean m_Timer = false;
        IntPtr m_Handle = IntPtr.Zero;
        uint m_Pid = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btn_connect_Click(object sender, EventArgs e)
        {
            StringBuilder sn = new StringBuilder();

            m_Handle = IOWarrior.Functions.IowKitOpenDevice(); //Open IO-Warrior

            if (m_Handle == IntPtr.Zero)
            {
                MessageBox.Show("No IO-Warrior found");
            }
            else
            {
                btn_start.Enabled = true;
                m_Pid = IOWarrior.Functions.IowKitGetProductId(m_Handle);     //Get PID from IO-Warrior
                IOWarrior.Functions.IowKitSetTimeout(m_Handle, 1000);       //Set Timeout to exit Read-Actions after defined time (IowKitRead only)
                IOWarrior.Functions.IowKitGetSerialNumber(m_Handle, sn);    //Get serial number

                switch (m_Pid)
                {
                    case IOWarrior.Defines.IOWKIT_PID_IOW40:
                        lbl_device.Text = "IO-Warrior40 (Serial: " + sn + ")";
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW24:
                        lbl_device.Text = "IO-Warrior24 (Serial: " + sn + ")";
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW56:
                        lbl_device.Text = "IO-Warrior56 (Serial: " + sn + ")";
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW28:
                        lbl_device.Text = "IO-Warrior28 (Serial: " + sn + ")";
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW100:
                        lbl_device.Text = "IO-Warrior100 (Serial: " + sn + ")";
                        break;
                }
            }
        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            if (m_Timer == false)
            {
                btn_start.Text = "Stop";
                timer1.Start();
                m_Timer = true;
            }
            else
            {
                btn_start.Text = "Start";
                timer1.Stop();
                m_Timer = false;
            }
        }

        private void btn_clear_Click(object sender, EventArgs e)
        {
            grid_result.Rows.Clear();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //Don'T forget to close IO-Warrior !
            if (m_Handle != IntPtr.Zero)
                IOWarrior.Functions.IowKitCloseDevice(m_Handle);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (m_Handle != IntPtr.Zero)
            {
                //Read IO-Ports with IowKitReadNonBlocking()
                //Reads only new data on IO-Pins
                ReadWithIoPipe();

                //Read IO-Ports with IowKitRead() and Special-Mode 0xFF
                //Reads every time
                //ReadWithSpecialPipe();
            }
        }

        private void InsertIntoGrid(byte[] report)
        {
            switch (m_Pid)
            {
                case IOWarrior.Defines.IOWKIT_PID_IOW40:
                    grid_result.Rows.Insert(0, report[1].ToString("X"), report[2].ToString("X"), report[3].ToString("X"),
                                            report[4].ToString("X"), "-", "-", "-");
                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW24:
                    grid_result.Rows.Insert(0, report[1].ToString("X"), report[2].ToString("X"), "-", "-", "-", "-", "-");

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW56:
                    grid_result.Rows.Insert(0, report[1].ToString("X"), report[2].ToString("X"), report[3].ToString("X"),
                                            report[4].ToString("X"), report[5].ToString("X"), report[6].ToString("X"),
                                            report[7].ToString("X"));
                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW28:
                    grid_result.Rows.Insert(0, report[1].ToString("X"), report[2].ToString("X"), report[3].ToString("X"), report[4].ToString("X"));
                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW100:
                    grid_result.Rows.Insert(0, report[1].ToString("X"), report[2].ToString("X"), report[3].ToString("X"),
                                            report[4].ToString("X"), report[5].ToString("X"), report[6].ToString("X"),
                                            report[7].ToString("X"), report[8].ToString("X"), report[9].ToString("X"),
                                            report[10].ToString("X"), report[11].ToString("X"), report[12].ToString("X"));
                    break;
            }

            if (grid_result.Rows.Count == 20)
                grid_result.Rows.RemoveAt(grid_result.Rows.Count - 1);
        }


        private void ReadWithIoPipe()
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT56_SPECIAL_REPORT_SIZE]; //Set array-size from IO-Warrior56, because this sample supports them
            uint ret = 0;

            switch (m_Pid)
            {
                case IOWarrior.Defines.IOWKIT_PID_IOW40:
                    ret = IOWarrior.Functions.IowKitReadNonBlocking(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT40_IO_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT40_IO_REPORT_SIZE) //Only execute if new data received
                        InsertIntoGrid(report);

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW24:
                    ret = IOWarrior.Functions.IowKitReadNonBlocking(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT24_IO_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT24_IO_REPORT_SIZE) //Only execute if new data received
                        InsertIntoGrid(report);

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW56:
                    ret = IOWarrior.Functions.IowKitReadNonBlocking(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT56_IO_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT56_IO_REPORT_SIZE) //Only execute if new data received
                        InsertIntoGrid(report);
                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW28:
                    ret = IOWarrior.Functions.IowKitReadNonBlocking(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT28_IO_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT28_IO_REPORT_SIZE) //Only execute if new data received
                        InsertIntoGrid(report);
                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW100:
                    ret = IOWarrior.Functions.IowKitReadNonBlocking(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT100_IO_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT100_IO_REPORT_SIZE) //Only execute if new data received
                        InsertIntoGrid(report);
                    break;
            }

        }


        //Read IO-Ports without check for new data. Use the report size for iow56 to fit all devices
        private void ReadWithSpecialPipe()
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT56_SPECIAL_REPORT_SIZE]; //Set array-size from IO-Warrior56, because this sample supports them
            uint ret = 0;

            report[0] = 0xFF; //Specialmode for getting pin Status

            switch (m_Pid)
            {
                case IOWarrior.Defines.IOWKIT_PID_IOW40:
                case IOWarrior.Defines.IOWKIT_PID_IOW24:

                    ret = IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT40_SPECIAL_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT40_SPECIAL_REPORT_SIZE)
                    {
                        IOWarrior.Functions.IowKitRead(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT40_SPECIAL_REPORT_SIZE);
                        InsertIntoGrid(report);
                    }

                    break;

                case IOWarrior.Defines.IOWKIT_PID_IOW56:

                    ret = IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT56_SPECIAL_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT56_SPECIAL_REPORT_SIZE)
                    {
                        IOWarrior.Functions.IowKitRead(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT56_SPECIAL_REPORT_SIZE);
                        InsertIntoGrid(report);
                    }

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW28:

                    ret = IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE)
                    {
                        IOWarrior.Functions.IowKitRead(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE);
                        InsertIntoGrid(report);
                    }

                    break;
                case IOWarrior.Defines.IOWKIT_PID_IOW100:

                    ret = IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE);

                    if (ret == IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE)
                    {
                        IOWarrior.Functions.IowKitRead(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE);
                        InsertIntoGrid(report);
                    }

                    break;
            }
        }
    }
}
