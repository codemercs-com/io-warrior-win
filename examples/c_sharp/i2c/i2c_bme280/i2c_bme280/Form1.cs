using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace i2c_bme280
{
    //typedefs for data calculation from datasheet bmp280/bme280
    using BME280_S32_t = Int32;
    using BME280_U32_t = UInt32;
    using BME280_S64_t = UInt64;

    public partial class Form1 : Form
    {
        /***** Konstanten und Funtionen des iowkit *****/

        // IO-Warrior vendor & product IDs
        public const uint IOWKIT_VENDOR_ID = 0x07c0;
        public const uint IOWKIT_VID = IOWKIT_VENDOR_ID;

        // IO-Warrior 40
        public const uint IOWKIT_PRODUCT_ID_IOW40 = 0x1500;
        public const uint IOWKIT_PID_IOW40 = IOWKIT_PRODUCT_ID_IOW40;

        // IO-Warrior 24
        public const uint IOWKIT_PRODUCT_ID_IOW24 = 0x1501;
        public const uint IOWKIT_PID_IOW24 = IOWKIT_PRODUCT_ID_IOW24;

        // IO-Warrior PowerVampire
        public const uint IOWKIT_PRODUCT_ID_IOWPV1 = 0x1511;
        public const uint IOWKIT_PID_IOWPV1 = IOWKIT_PRODUCT_ID_IOWPV1;

        public const uint IOWKIT_PRODUCT_ID_IOWPV2 = 0x1512;
        public const uint IOWKIT_PID_IOWPV2 = IOWKIT_PRODUCT_ID_IOWPV2;

        // IO-Warrior Sensirion
        public const uint IOWKIT_PRODUCT_ID_IOW_SENSI1 = 0x158a;
        public const uint IOWKIT_PID_IOW_SENSI1 = IOWKIT_PRODUCT_ID_IOW_SENSI1;

        // IO-Warrior 56
        public const uint IOWKIT_PRODUCT_ID_IOW56 = 0x1503;
        public const uint IOWKIT_PID_IOW56 = IOWKIT_PRODUCT_ID_IOW56;

        // IO-Warrior 28
        public const uint IOWKIT_PRODUCT_ID_IOW28 = 0x1504;
        public const uint IOWKIT_PID_IOW28 = IOWKIT_PRODUCT_ID_IOW28;

        // IO-Warrior 28L
        public const uint IOWKIT_PRODUCT_ID_IOW28L = 0x1505;
        public const uint IOWKIT_PID_IOW28L = IOWKIT_PRODUCT_ID_IOW28L;

        // IO-Warrior 100
        public const uint IOWKIT_PRODUCT_ID_IOW100 = 0x1506;
        public const uint IOWKIT_PID_IOW100 = IOWKIT_PRODUCT_ID_IOW100;

        // Max number of pipes per IOW device
        public const uint IOWKIT_MAX_PIPEX = 4;

        // pipe names
        public const uint IOW_PIPE_IO_PINS = 0;
        public const uint IOW_PIPE_SPECIAL_MODE = 1;
        public const uint IOW_PIPE_I2C_MODE = 2;     //only IOW28 (not IOW28L)
        public const uint IOW_PIPE_ADC_MODE = 3;     //only IOW28 (not IOW28L)

        // Max number of IOW devices in system
        public const uint IOWKIT_MAX_DEVICES = 16;

        // IOW Legacy devices open modes
        public const uint IOW_OPEN_SIMPLE = 1;
        public const uint IOW_OPEN_COMPLEX = 2;

        // first IO-Warrior revision with serial numbers
        public const uint IOW_NON_LEGACY_REVISION = 0x1010;

        //Report size (incl. ReportID)
        public const uint IOWKIT40_IO_REPORT_SIZE = 5;
        public const uint IOWKIT24_IO_REPORT_SIZE = 3;
        public const uint IOWKIT56_IO_REPORT_SIZE = 8;
        public const uint IOWKIT28_IO_REPORT_SIZE = 5;
        public const uint IOWKIT100_IO_REPORT_SIZE = 13;

        public const uint IOWKIT40_SPECIAL_REPORT_SIZE = 8;
        public const uint IOWKIT24_SPECIAL_REPORT_SIZE = 8;
        public const uint IOWKIT56_SPECIAL_REPORT_SIZE = 64;
        public const uint IOWKIT28_SPECIAL_REPORT_SIZE = 64;
        public const uint IOWKIT100_SPECIAL_REPORT_SIZE = 64;

        [DllImport("iowkit.dll")] public static extern IntPtr IowKitOpenDevice();
        [DllImport("iowkit.dll")] public static extern void IowKitCloseDevice(IntPtr IowHandle);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitGetProductId(IntPtr IowHandle);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitGetNumDevs();
        [DllImport("iowkit.dll")] public static extern IntPtr IowKitGetDeviceHandle(UInt32 numDevice);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitGetRevision(IntPtr IowHandle);
        [DllImport("iowkit.dll", CharSet = CharSet.Unicode)] public static extern bool IowKitGetSerialNumber(IntPtr IowHandle, StringBuilder SnTarget);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitRead(IntPtr IowHandle, UInt32 numPipe, byte[] buffer, UInt32 Length);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitReadNonBlocking(IntPtr IowHandle, UInt32 numPipe, byte[] buffer, UInt32 Length);
        [DllImport("iowkit.dll")] public static extern bool IowKitReadImmediate(IntPtr IowHandle, byte[] IoPinStatus);
        [DllImport("iowkit.dll")] public static extern bool IowKitSetTimeout(IntPtr IowHandle, UInt32 Timeout);
        [DllImport("iowkit.dll")] public static extern bool IowKitSetWriteTimeout(IntPtr IowHandle, UInt32 Timeout);
        [DllImport("iowkit.dll")] public static extern bool IowKitCancelIo(IntPtr IowHandle, UInt32 numPipe);
        [DllImport("iowkit.dll")] public static extern UInt32 IowKitWrite(IntPtr IowHandle, UInt32 numPipe, byte[] buffer, UInt32 length);
        [DllImport("iowkit.dll")] public static extern IntPtr IowKitGetThreadHandle(IntPtr IowHandle);
        [DllImport("iowkit.dll")] public static extern string IowKitVersion();
        [DllImport("iowkit.dll")] public static extern bool IowKitSetLegacyOpenMode(UInt32 legacyOpenMode);
        [DllImport("iowkit.dll")] public static extern uint GetLastError();

        /***** END *****/


        /***** Stuff for BMP280/BME280 *****/
        //Compensation from datasheet 
        struct CompensationData
        {
            public UInt16 dig_T1;   //0x88 + 0x89
            public Int16 dig_T2;    //0x8A + 0x8B
            public Int16 dig_T3;    //0x8C + 0x8D
            public UInt16 dig_P1;    //0x8E + 0x8F
            public Int16 dig_P2;    //0x90 + 0x91
            public Int16 dig_P3;    //0x92 + 0x93
            public Int16 dig_P4;    //0x94 + 0x95
            public Int16 dig_P5;    //0x96 + 0x97
            public Int16 dig_P6;    //0x98 + 0x99
            public Int16 dig_P7;    //0x9A + 0x9B
            public Int16 dig_P8;    //0x9C + 0x9D
            public Int16 dig_P9;    //0x9E + 0x9F
            public byte dig_H1;     //0xA1
            public Int16 dig_H2;    //0xE1 + 0xE2
            public byte dig_H3;     //0xE3
            public Int16 dig_H4;    //0xE4 + 0xE5(3:0)
            public Int16 dig_H5;    //0xE5(7:4) + 0xE6
            public byte dig_H6;     //0xE7
        }

        struct SensorData
        {
            public Int32 pressure;      //msb, lsb, xlsb
            public Int32 temperatur;    //msb, lsb, xlsb
            public Int32 humidity;      //msb lsb

        }

        //Register für BME280
        public const byte REG__CALIB00 = 0x88;
        //public const byte REG__CALIB01 = 0x89;
        //.......
        //public const byte REG__CALIB25 = 0xA1;
        public const byte REG__ID = 0xD0;
        public const byte REG__RESET = 0xD0;
        public const byte REG__CALIB26 = 0xE1;
        //public const byte REG__CALIB27 = 0xE2;
        //.......
        //public const byte REG__CALIB41 = 0xF0;
        public const byte REG__CTRL_HUM = 0xF2;
        public const byte REG__STATUS = 0xF3;
        public const byte REG__CTR_MEAS = 0xF4;
        public const byte REG__CONFIG = 0xF5;

        public const byte REG__PRESS_MSB = 0xF7;
        public const byte REG__PRESS_LSB = 0xF8;
        public const byte REG__PRESS_XSB = 0xF9;

        public const byte REG__TEMP_MSB = 0xFA;
        public const byte REG__TEMP_LSB = 0xFB;
        public const byte REG__TEMP_XSB = 0xFC;

        public const byte REG__HUM_MSB = 0xFD;
        public const byte REG__HUM_LSB = 0xFE;

        /***** END *****/

        /***** Globals *****/

        byte m_I2c = 0xEC; //8Bit I2C-Address for BMP280/BME280
        IntPtr m_Handle;
        
        CompensationData m_Compensation;
        SensorData m_Sensor;
        BME280_S32_t m_tFine;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            byte[] report = new byte[IOWKIT28_SPECIAL_REPORT_SIZE];

            m_Handle = IowKitOpenDevice();

            if (m_Handle != IntPtr.Zero)
            {
                IowKitSetTimeout(m_Handle, 1000);   //Cancel write/read operations after 1000ms

                //Enable I2C

                //Init/Enable I2C Mode 
                Array.Clear(report, 0, report.Length); //Clear array
                report[0] = 0x01;   //I2C Mode
                report[1] = 0x01;   //Enable
                report[2] = 0x00;   //Enable sensibus

                if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) != IOWKIT28_SPECIAL_REPORT_SIZE)
                    MessageBox.Show("Can not Init the IO-Warrior");

                
                //BMP280 initialisieren
                Array.Clear(report, 0, report.Length); //Clear array
                report[0] = 0x02;   //Write to I2C-device
                report[1] = 0xC3;   //Start + Stop + 2 byte
                report[2] = m_I2c;  //I2C-address
                report[3] = REG__CTR_MEAS;   //Register -> CTRL_MEAS

                //osrs_t = b001
                //osrs_p = b001
                //mode = b11
                //============
                //value = b00100111 -> 0x27
                report[4] = 0x27;   //datasheet page 29 to enable Measurement

                if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                    {
                        //Rückantwort auswerten, Fehlerbits, etc.
                    }
                    else
                        MessageBox.Show("Error Read");
                }
                else
                    MessageBox.Show("Error Write");
                

                button_read.Enabled = true;

            }
            else
                MessageBox.Show("NO IO-Warrior found");
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            IowKitCloseDevice(m_Handle);
        }

        public void ReadCalibration()
        {
            byte[] report = new byte[IOWKIT28_SPECIAL_REPORT_SIZE];

            //Erster Teil der Calibrierung
            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x02;
            report[1] = 0xC2;
            report[2] = m_I2c;
            report[3] = REG__CALIB00;

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    //Answere from I2C device (ACK, errors, etc)
                    //report[0] -> ReportID
                    //report[1] -> flags
                    //report[2] -> code
                }
                else
                    MessageBox.Show("Error Read Calibration");
            }
            else
                MessageBox.Show("Error Write Calibration");


            //Die Daten auslesen
            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x03;   //Write to I2C-device
            report[1] = 26;
            report[2] = (byte)(m_I2c | 0x01);  //I2C-address fürs Lesen einstellen
            report[3] = 0x00;

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    m_Compensation.dig_T1 = (UInt16)((report[3] << 8) | report[2]);
                    m_Compensation.dig_T2 = (Int16)((report[5] << 8) | report[4]);
                    m_Compensation.dig_T3 = (Int16)((report[7] << 8) | report[6]);
                    m_Compensation.dig_P1 = (UInt16)((report[9] << 8) | report[8]);
                    m_Compensation.dig_P2 = (Int16)((report[11] << 8) | report[10]);
                    m_Compensation.dig_P3 = (Int16)((report[13] << 8) | report[12]);
                    m_Compensation.dig_P4 = (Int16)((report[15] << 8) | report[14]);
                    m_Compensation.dig_P5 = (Int16)((report[17] << 8) | report[16]);
                    m_Compensation.dig_P6 = (Int16)((report[19] << 8) | report[18]);
                    m_Compensation.dig_P7 = (Int16)((report[21] << 8) | report[20]);
                    m_Compensation.dig_P8 = (Int16)((report[23] << 8) | report[22]);
                    m_Compensation.dig_P9 = (Int16)((report[25] << 8) | report[24]);
                    m_Compensation.dig_H1 = (byte)(report[26]);
                }
                else
                    MessageBox.Show("Error Read");
            }
            else
                MessageBox.Show("Error Write");

            //Zeiter Teil der Calibrierung

            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x02;
            report[1] = 0xC2;
            report[2] = m_I2c;
            report[3] = REG__CALIB26;

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    //Rückantwort auswerten, Fehlerbits, etc.
                }
                else
                    MessageBox.Show("Error Read Calibration");
            }
            else
                MessageBox.Show("Error Write Calibration");


            //Die Daten auslesen
            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x03;   //Write to I2C-device
            report[1] = 8;
            report[2] = (byte)(m_I2c | 0x01);  //I2C-address fürs Lesen einstellen
            report[3] = 0x00;

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    m_Compensation.dig_H2 = (Int16)((report[3] << 8) | report[2]);
                    m_Compensation.dig_H3 = (byte)(report[4]);
                    m_Compensation.dig_H4 = (Int16)((report[5] << 4) | (report[6] & 0x0F));
                    m_Compensation.dig_H5 = (Int16)((report[7] << 4) | ((report[6] & 0xF0) >> 4));
                    m_Compensation.dig_H6 = (byte)(report[8]);
                }
                else
                    MessageBox.Show("Error Read");
            }
            else
                MessageBox.Show("Error Write");
        }

        public void ReadData()
        {
            byte[] report = new byte[IOWKIT28_SPECIAL_REPORT_SIZE];

            //Set register pointer for read data
            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x02;   //Write to I2C-device
            report[1] = 0xC2;   //Start + Stop + 2 byte
            report[2] = m_I2c;  //I2C-address
            report[3] = REG__PRESS_MSB;   //Set Start register to read from

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    //Answere from I2C device (ACK, errors, etc)
                    //report[0] -> ReportID
                    //report[1] -> flags
                    //report[2] -> code
                }
                else
                    MessageBox.Show("Error Read");
            }
            else
                MessageBox.Show("Error Write");


            //Read Data from register postion set before
            Array.Clear(report, 0, report.Length); //Clear array
            report[0] = 0x03;   //Read from I2C-device
            report[1] = 9;
            report[2] = (byte)(m_I2c | 0x01);  //I2C-address for read
            report[3] = 0x00;

            if (IowKitWrite(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IowKitRead(m_Handle, IOW_PIPE_I2C_MODE, report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    if ((report[1] & 0x80) == 0x80)
                    {
                        //Error, set if slave does not ACK command byte
                        MessageBox.Show("ERROR: NO SCK command received");
                    }

                    m_Sensor.pressure = (report[2] << 12) | (report[3] << 4) | ((report[4] & 0xF0) >> 4);
                    m_Sensor.temperatur = (report[5] << 12) | (report[6] << 4) | ((report[7] & 0xF0) >> 4);
                    m_Sensor.humidity = (report[8] << 8) | (report[9]);
                }
                else
                    MessageBox.Show("Error Read");
            }
            else
                MessageBox.Show("Error Write");
        }

        private void button_read_Click(object sender, EventArgs e)
        {
            ReadCalibration();
            timer1.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            ReadData();

            BME280_S32_t t = BME280_compensate_T_int32(m_Sensor.temperatur);
            BME280_U32_t p = BME280_compensate_P_int64(m_Sensor.pressure);

            double temp = (double)t / 100.0f;
            label_temp.Text = temp.ToString("f2") + " °C";

            double press = ((double)p / 256.0f) / 100.0f;
            label_press.Text = press.ToString("f2") + "hPa";
        }


        // Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
        // t_fine carries fine temperature as global value
        public BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T)
        {
            BME280_S32_t var1, var2, T;

            var1 = ((((adc_T >> 3) - ((BME280_S32_t)m_Compensation.dig_T1 << 1))) * ((BME280_S32_t)m_Compensation.dig_T2)) >> 11;
            var2 = (((((adc_T >> 4) - ((BME280_S32_t)m_Compensation.dig_T1)) * ((adc_T >> 4) - ((BME280_S32_t)m_Compensation.dig_T1))) >> 12) * ((BME280_S32_t)m_Compensation.dig_T3)) >> 14;

            m_tFine = var1 + var2;
            T = (m_tFine * 5 + 128) >> 8;

            return T;
        }

        // Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
        // Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
        public BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P)
        {
            BME280_S64_t var1, var2, p;

            var1 = ((BME280_S64_t)m_tFine) - 128000;
            var2 = var1 * var1 * (BME280_S64_t)m_Compensation.dig_P6;
            var2 = var2 + ((var1 * (BME280_S64_t)m_Compensation.dig_P5) << 17);
            var2 = var2 + (((BME280_S64_t)m_Compensation.dig_P4) << 35);
            var1 = ((var1 * var1 * (BME280_S64_t)m_Compensation.dig_P3) >> 8) + ((var1 * (BME280_S64_t)m_Compensation.dig_P2) << 12);
            var1 = (((((BME280_S64_t)1) << 47) + var1)) * ((BME280_S64_t)m_Compensation.dig_P1) >> 33;
            if (var1 == 0)
            {
                return 0; // avoid exception caused by division by zero
            }
            p = 1048576 - ((BME280_S64_t)adc_P);
            p = (((p << 31) - var2) * 3125) / var1;
            var1 = (((BME280_S64_t)m_Compensation.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
            var2 = (((BME280_S64_t)m_Compensation.dig_P8) * p) >> 19;
            p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)m_Compensation.dig_P7) << 4);
            return (BME280_U32_t)p;
        }

        // Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
        // Output value of “47445” represents 47445/1024 = 46.333 %RH
        BME280_U32_t BME280_compensate_H_int32(BME280_S32_t adc_H)
        {
            BME280_S32_t v_x1_u32r;
            v_x1_u32r = (m_tFine - ((BME280_S32_t)76800));

            v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)m_Compensation.dig_H4) << 20) - (((BME280_S32_t)m_Compensation.dig_H5) * v_x1_u32r)) + ((BME280_S32_t)16384)) >> 15) * (((((((v_x1_u32r *
            ((BME280_S32_t)m_Compensation.dig_H6)) >> 10) * (((v_x1_u32r * ((BME280_S32_t)m_Compensation.dig_H3)) >> 11) +
            ((BME280_S32_t)32768))) >> 10) + ((BME280_S32_t)2097152)) * ((BME280_S32_t)m_Compensation.dig_H2) +
            8192) >> 14));
            v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
            ((BME280_S32_t)m_Compensation.dig_H1)) >> 4));
            v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
            v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
            return (BME280_U32_t)(v_x1_u32r >> 12);
        }
    }
}
