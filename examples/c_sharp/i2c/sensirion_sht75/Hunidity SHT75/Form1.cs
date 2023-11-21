using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace Hunidity_SHT75
{
    public partial class Form1 : Form
    {
        //Register / Commands for read data
        public const byte CONST_HUM = 0x05;
        public const byte CONST_TEMP = 0x03;
            
        public IntPtr m_ioHandle;   //Member of IO-Warrior
        public double m_Temperature;
        public double m_Humidity;

        public Form1()
        {
            InitializeComponent();
        }

        private void start_Click(object sender, EventArgs e)
        {
            byte[] report = new byte[9];            //report data
            uint ret = 0;
            StringBuilder sn = new StringBuilder(); //For serialnumber
            uint pid;       //Product ID

            m_ioHandle = IntPtr.Zero;                               //Clear Handle
            m_ioHandle = IOWarrior.Functions.IowKitOpenDevice();    //Open IO-Warrior

            if (m_ioHandle != IntPtr.Zero)
            {
                //Get device info
                pid = IOWarrior.Functions.IowKitGetProductId(m_ioHandle);
                IOWarrior.Functions.IowKitGetSerialNumber(m_ioHandle, sn);

                switch (pid)                                        
                {
                    case IOWarrior.Defines.IOWKIT_PID_IOW40:
                        devinfo.Text = "IO-Warrior40 - SN: " + sn;
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW24:
                        devinfo.Text = "IO-Warrior24 - SN: " + sn;
                        break;
                    case IOWarrior.Defines.IOWKIT_PID_IOW56:
                        devinfo.Text = "IO-Warrior56 - SN: " + sn;
                        break;
                }

                //Init I2C Mode 
                report[0] = 0x01;   //I2C Mode
                report[1] = 0x01;   //Enable
                report[2] = 0x40;   //Enable sensibus
                ret = IOWarrior.Functions.IowKitWrite(m_ioHandle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT_SPECIAL_REPORT_SIZE);

                //Init SHT75 measurement
                report[0] = 0x02;
                report[1] = 0xC1;
                report[2] = 0x1E;
                ret = IOWarrior.Functions.IowKitWrite(m_ioHandle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT_SPECIAL_REPORT_SIZE);
                ret = IOWarrior.Functions.IowKitRead(m_ioHandle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT_SPECIAL_REPORT_SIZE);    //Swallow ACK

                //Start timer
                timer1.Enabled = true;
                timer1.Start();

                start.Enabled = false;
                stop.Enabled = true;
            }
            else
                MessageBox.Show("No Device found.");
        }

        private void stop_Click(object sender, EventArgs e)
        {
            //Stop timer
            timer1.Enabled = false;
            timer1.Stop();

            start.Enabled = true;
            stop.Enabled = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //Don't forget to close !
            IOWarrior.Functions.IowKitCloseDevice(m_ioHandle);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {      
            //Calc temperature and humidity
            CalcTRH(ReadSHT75(CONST_TEMP), ReadSHT75(CONST_HUM));

            //Output
            temperature.Text = m_Temperature.ToString("00.00") + " °C";
            humidity.Text = m_Humidity.ToString("00.00") + " %RH";
        }

        //Read drom I2C-Device
        public double ReadSHT75(byte cmd)
        {
            byte[] report = new byte[9];  //report data
            uint ret;

            report[0] = 0x03;
            report[1] = 0x03;
            report[2] = cmd;
            ret = IOWarrior.Functions.IowKitWrite(m_ioHandle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT_SPECIAL_REPORT_SIZE);
            ret = IOWarrior.Functions.IowKitRead(m_ioHandle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT_SPECIAL_REPORT_SIZE);

            return (double)((report[2] << 8) | report[3]);
        }

        //Calc temperature and humidity 
        public void CalcTRH(double temp, double humi)
        {
            const double C1 = -4.0;         // for 12 Bit
            const double C2 = +0.0405;      // for 12 Bit
            const double C3 = -0.0000028;   // for 12 Bit
            const double T1 = +0.01;        // for 14 Bit @ 5V
            const double T2 = +0.00008;     // for 14 Bit @ 5V

            double rh = humi;				// rh:      Humidity [Ticks] 12 Bit 
            double t = temp;			    // t:       Temperature [Ticks] 14 Bit
            double rh_lin;					// rh_lin:  Humidity linear
            double rh_true;					// rh_true: Temperature compensated humidity
            double t_C;						// t_C   :  Temperature [°C]

            t_C = t * 0.01 - 40;						        //calc. temperature from ticks to [°C]
            rh_lin = C3 * rh * rh + C2 * rh + C1;		    	//calc. humidity from ticks to [%RH]
            rh_true = (t_C - 25) * (T1 + T2 * rh) + rh_lin;	    //calc. temperature compensated humidity [%RH]

            if (rh_true > 100) rh_true = 100;		//cut if the value is outside of
            if (rh_true < 0.1) rh_true = 0.1;		//the physical possible range

            m_Humidity = rh_true;   //return humidity[%RH]
            m_Temperature = t_C;      //return temperature [°C]
        }
    }
}
