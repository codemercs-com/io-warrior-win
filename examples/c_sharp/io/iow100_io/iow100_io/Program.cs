using System.Security.Cryptography;
using System;
using System.Text;

namespace iow100_io
{
    class Program
    {
        static void Main(string[] args)
        {
            IntPtr handle = IntPtr.Zero;                                //Handle to IO-Warrior device
            uint pid;                                                   //ProductID
            StringBuilder sn = new StringBuilder();                     //Serialnumber
            uint version;                                               //Firmware version

            handle = IOWarrior.Functions.IowKitOpenDevice();
            pid = IOWarrior.Functions.IowKitGetProductId(handle);       //Get ProductID to get a specific IO-Warrior
            IOWarrior.Functions.IowKitSetTimeout(handle, 1000);         //Timeout for Read, if not IowKitRead() will wait infinite
            IOWarrior.Functions.IowKitSetWriteTimeout(handle, 1000);    //Timeout for Write

            if (pid != IOWarrior.Defines.IOWKIT_PID_IOW100)
            {
                Console.WriteLine("Device: No IO-Warrior100 found. Exit");
            }
            else
            {
                Console.WriteLine("Device: IO-Warrior100");

                IOWarrior.Functions.IowKitGetSerialNumber(handle, sn);      //Get serial number
                Console.WriteLine("Serialnumber: " + sn);

                version = IOWarrior.Functions.IowKitGetRevision(handle);    //Get version of firmware
                Console.WriteLine("Firmware version: " + version.ToString("X"));

                Console.WriteLine("\nPress any key to start");
                Console.ReadKey();

                //Write a random number (byte) to IO-Warrior100
                Random rnd = new Random();
                uint ret = WriteReport(handle, (byte)rnd.Next(255));

                if (ret != IOWarrior.Defines.IOWKIT100_IO_REPORT_SIZE)
                    Console.WriteLine("\nWrite to IO-Warrior100 failed");

                ReadReport(handle); //Read Bytes
            }

            IOWarrior.Functions.IowKitCloseDevice(handle);              //Close IO-Warrior and release DLL

            Console.WriteLine("\nPress any key to escape...");
            Console.ReadKey();
        }

        //Write a byte value to IO-Port 0
        static uint WriteReport(IntPtr handle, byte value)
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT100_IO_REPORT_SIZE];
            Array.Clear(report, 0, report.Length);  //Init array with "0"

            report[0] = 0x00;       //Report-ID
            report[1] = value;       //Data for IO-Port 1 -> DEMO Port
            report[2] = 0xFF;       //Data for IO-Port 2
            report[3] = 0xFF;       //Data for IO-Port 3
            report[4] = 0xFF;       //Data for IO-Port 4
            report[5] = 0xFF;       //Data for IO-Port 5
            report[6] = 0xFF;       //Data for IO-Port 6
            report[7] = 0xFF;       //Data for IO-Port 7
            report[8] = 0xFF;       //Data for IO-Port 8
            report[9] = 0xFF;       //Data for IO-Port 9
            report[10] = 0xFF;      //Data for IO-Port 10
            report[11] = 0xFF;      //Data for IO-Port 11
            report[12] = 0xFF;      //Data for IO-Port 12

            return IOWarrior.Functions.IowKitWrite(handle, IOWarrior.Defines.IOW_PIPE_IO_PINS, report, IOWarrior.Defines.IOWKIT100_IO_REPORT_SIZE);
        }

        static void ReadReport(IntPtr handle)
        {
            byte[] report = new byte[IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE];
            Array.Clear(report, 0, report.Length);  //Init array with "0"

            report[0] = 0xFF;   //Report-ID for special mode "Getting pin status"

            if (IOWarrior.Functions.IowKitWrite(handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE) == IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE)
            {
                if (IOWarrior.Functions.IowKitRead(handle, IOWarrior.Defines.IOW_PIPE_SPECIAL_MODE, report, IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE) == IOWarrior.Defines.IOWKIT100_SPECIAL_REPORT_SIZE)
                {
                    Console.WriteLine("\nRead IO pins from IO-Warrior100\n");

                    //Write report ID. To distinguish the modes if you use multiple 
                    Console.WriteLine("ReportID : " + string.Format("{0:X2}", report[0]));

                    //Write Data
                    for (int i = 1; i < 12; i++)
                        Console.WriteLine("Byte " + i + ": " + string.Format("{0:X2}", report[i]));
                }
                else
                {
                    //Read fails or timeout
                    Console.WriteLine("Error during read or timeout");
                }
            }
            else
            {
                //Write fails or timeout
                Console.WriteLine("Error during write or timeout");
            }
        }
    }
}
