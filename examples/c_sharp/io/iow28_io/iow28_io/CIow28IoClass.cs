using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

//Use the same 'namespace' like the IO-Warrior API functions
namespace IOWarrior
{
    internal class CIow28IoClass
    {
        //Defines for statics
        #region Defines
        public static class DEF
        {
            // ReportIDs
            public const byte RID_IO = 0x00;      //ReportID for Write/Read IO-Ports
            public const byte RID_IOPORT = 0xFF;    //ReportID for special mode to get actual port status

            //Ports
            public const byte PORT_0 = 0x01;   //Port 0.0 ... 0.7
            public const byte PORT_1 = 0x02;   //Port 1.0 ... 1.7
            public const byte PORT_2 = 0x03;   //Port 2.0 ... 2.1
            public const byte PORT_3 = 0x04;   //Port 3.7

            //MASK for valid IO-Pins
            public const byte MASK_0 = 0xFF;
            public const byte MASK_1 = 0xFF;
            public const byte MASK_2 = 0x03;
            public const byte MASK_3 = 0x80;

            //Port pins
            public const byte PIN_0 = 0x01;
            public const byte PIN_1 = 0x02;
            public const byte PIN_2 = 0x04;
            public const byte PIN_3 = 0x08;
            public const byte PIN_4 = 0x10;
            public const byte PIN_5 = 0x20;
            public const byte PIN_6 = 0x40;
            public const byte PIN_7 = 0x80;

            //Some flags
            public const byte FLAG_NONE = 0x00;
            public const byte FLAG_ERROR = 0x01;

            //Return errors
            public const ushort ERROR_NONE = 0x0000;
            public const ushort ERROR_HANDLE = 0x0001;
            public const ushort ERROR_WRITE = 0x0002;
            public const ushort ERROR_READ = 0x0004;
            public const ushort ERROR_DEVICE = 0x0008;
            public const ushort ERROR_PORT = 0x0010;
            public const ushort ERROR_RANGE = 0x0020;
            public const ushort ERROR_UNKNOWN = 0x8000;
        }
        #endregion

        //Struct for easier use of the ports
        #region PortStruct
        public struct PORT_STRUCT
        {
            private byte m_Port_0 = 0x00;
            private byte m_Port_1 = 0x00;
            private byte m_Port_2 = 0x00;
            private byte m_Port_3 = 0x00;

            public PORT_STRUCT(byte p0, byte p1, byte p2, byte p3)
            {
                m_Port_0 = p0;
                m_Port_0 = p1;
                m_Port_0 = p2;
                m_Port_0 = p3;
            }

            public byte Port_0
            {
                get { return m_Port_0; }
                set { m_Port_0 = value; }
            }

            public byte Port_1
            {
                get { return m_Port_1; }
                set { m_Port_1 = value; }
            }

            public byte Port_2
            {
                get { return m_Port_2; }
                set { m_Port_2 = value; }
            }

            public byte Port_3
            {
                get { return m_Port_3; }
                set { m_Port_3 = value; }
            }
        }
        #endregion

        //Global var
        private IntPtr m_Handle = IntPtr.Zero;
        private PORT_STRUCT m_Ports = new PORT_STRUCT(0xFF,0xFF,0xFF,0xFF);

        public void SetHandle(IntPtr handle)
        {
            if(handle != IntPtr.Zero)
                m_Handle = handle;
        }

        private ushort Write()
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT28_IO_REPORT_SIZE];
            Array.Clear(report, 0, report.Length);  //Init array with "0"

            if (m_Handle == IntPtr.Zero)
                return DEF.ERROR_HANDLE;

            report[0] = DEF.RID_IO;      //Report-ID
            report[1] = m_Ports.Port_0;       //Data for IO-Port 0
            report[2] = m_Ports.Port_1;       //Data for IO-Port 1
            report[3] = m_Ports.Port_2;       //Data for IO-Port 2
            report[4] = m_Ports.Port_3;       //Data for IO-Port 3

            if (IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT28_IO_REPORT_SIZE) != IOWarrior.Defines.IOWKIT28_IO_REPORT_SIZE)
                return DEF.ERROR_WRITE;
            else
                return DEF.ERROR_NONE;
        }

        private ushort Read()
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE];
            Array.Clear(report, 0, report.Length);  //Init array with "0"

            if (m_Handle == IntPtr.Zero)
                return DEF.ERROR_HANDLE;

            report[0] = DEF.RID_IOPORT;   //Report-ID for special mode "Getting pin status"

            if (IOWarrior.Functions.IowKitWrite(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE) == IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                if (IOWarrior.Functions.IowKitRead(m_Handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE) == IOWarrior.Defines.IOWKIT28_SPECIAL_REPORT_SIZE)
                {
                    m_Ports.Port_0 = report[1];
                    m_Ports.Port_1 = report[2];
                    m_Ports.Port_2 = report[3];
                    m_Ports.Port_3 = report[4];
                    return DEF.ERROR_NONE;
                }
                else
                    return DEF.ERROR_READ;
            }
            else
                return DEF.ERROR_WRITE;
        }

        public void InitPorts(byte p0, byte p1, byte p2, byte p3)
        {
            m_Ports.Port_0 = p0;
            m_Ports.Port_1 = p1;
            m_Ports.Port_2 = p2;
            m_Ports.Port_3 = p3;
        }

        //Set the whole PORT without store or check old values
        public void SetPort(byte port, byte value)
        {
            switch (port)
            {
                case DEF.PORT_0: m_Ports.Port_0 = (byte)(value & DEF.MASK_0); break;
                case DEF.PORT_1: m_Ports.Port_1 = (byte)(value & DEF.MASK_1); break;
                case DEF.PORT_2: m_Ports.Port_2 = (byte)(value & DEF.MASK_2); break;
                case DEF.PORT_3: m_Ports.Port_3 = (byte)(value & DEF.MASK_3); break;
                default: break;
            }
        }

        //Write the IO-Ports
        public ushort WritePorts()
        {
            return Write();
        }

        //Return the PORT value from specific port
        public byte GetPort(byte port)
        {
            switch (port)
            {
                case DEF.PORT_0: return m_Ports.Port_0;
                case DEF.PORT_1: return m_Ports.Port_1;
                case DEF.PORT_2: return m_Ports.Port_2;
                case DEF.PORT_3: return m_Ports.Port_3;
                default: return 0xFF;
            }
        }

        //Read all PORTS
        public ushort ReadPorts()
        {
            return Read();
        }

        //Set PORT by adding (OR) the value
        public void SetPortPins(byte port, byte value)
        {
            byte oldPort = 0x00;

            switch (port)
            {
                case DEF.PORT_0: oldPort = m_Ports.Port_0; break;
                case DEF.PORT_1: oldPort = m_Ports.Port_1; break;
                case DEF.PORT_2: oldPort = m_Ports.Port_2; break;
                case DEF.PORT_3: oldPort = m_Ports.Port_3; break;
                default: break;
            }

            oldPort |= (byte)value;

            switch (port)
            {
                case DEF.PORT_0: m_Ports.Port_0 = oldPort; break;
                case DEF.PORT_1: m_Ports.Port_1 = oldPort; break;
                case DEF.PORT_2: m_Ports.Port_2 = oldPort; break;
                case DEF.PORT_3: m_Ports.Port_3 = oldPort; break;
                default: break;
            }
        }

        //Clear PORT by remove (AND) the value
        public void ClearPortPins(byte port, byte value)
        {
            byte oldPort = 0x00;

            switch (port)
            {
                case DEF.PORT_0: oldPort = m_Ports.Port_0; break;
                case DEF.PORT_1: oldPort = m_Ports.Port_1; break;
                case DEF.PORT_2: oldPort = m_Ports.Port_2; break;
                case DEF.PORT_3: oldPort = m_Ports.Port_3; break;
                default: break;
            }

            oldPort &= (byte)~value;

            switch (port)
            {
                case DEF.PORT_0: m_Ports.Port_0 = oldPort; break;
                case DEF.PORT_1: m_Ports.Port_1 = oldPort; break;
                case DEF.PORT_2: m_Ports.Port_2 = oldPort; break;
                case DEF.PORT_3: m_Ports.Port_3 = oldPort; break;
                default: break;
            }
        }
    }
}
