
using System.Reflection.Metadata;
using System.Runtime.CompilerServices;
using System.Text;

IntPtr iow = IntPtr.Zero;
uint pid = 0;                               //ProductID
StringBuilder sn = new StringBuilder();     //Serialnumber
uint version = 0;
ushort error = IOWarrior.CIow28IoClass.DEF.ERROR_NONE;

iow = IOWarrior.Functions.IowKitOpenDevice();            //Open iowkit and get the 1st. IO-Warrior found
pid = IOWarrior.Functions.IowKitGetProductId(iow);       //Get ProductID to get a specific IO-Warrior
IOWarrior.Functions.IowKitSetTimeout(iow, 1000);         //Timeout for Read, if not IowKitRead() will wait infinite
IOWarrior.Functions.IowKitSetWriteTimeout(iow, 1000);    //Timeout for Write


if (pid != IOWarrior.Defines.IOWKIT_PID_IOW28)
{
    Console.WriteLine("Device: No IO-Warrior28 found. Exit");
}
else
{
    Console.WriteLine("Device: IO-Warrior28");

    IOWarrior.Functions.IowKitGetSerialNumber(iow, sn);      //Get serial number
    Console.WriteLine("Serialnumber: " + sn);

    version = IOWarrior.Functions.IowKitGetRevision(iow);    //Get version of firmware
    Console.WriteLine("Firmware version: " + version.ToString("X"));


    IOWarrior.CIow28IoClass ports = new IOWarrior.CIow28IoClass();
    ports.SetHandle(iow);
    ports.InitPorts(0xFF, 0xFF, 0xFF, 0xFF);

    //Set the IO-Ports with some values
    ports.SetPort(IOWarrior.CIow28IoClass.DEF.PORT_0, 0xab);
    ports.SetPort(IOWarrior.CIow28IoClass.DEF.PORT_1, 0xcd);
    ports.SetPort(IOWarrior.CIow28IoClass.DEF.PORT_2, 0xff);
    ports.SetPort(IOWarrior.CIow28IoClass.DEF.PORT_3, 0xff);

    error = ports.WritePorts(); //Write the IO-Ports

    //Let's blink the LED on the IOW28Eval
    Console.WriteLine("Let's blink the LED on the IOW28Eval");
    for (int i = 0; i < 10; i++)
    {
        ports.ClearPortPins(IOWarrior.CIow28IoClass.DEF.PORT_2, 0x01);
        error = ports.WritePorts();

        if (error != IOWarrior.CIow28IoClass.DEF.ERROR_NONE)
            break;

        Thread.Sleep(250);

        ports.SetPortPins(IOWarrior.CIow28IoClass.DEF.PORT_2, 0x01);
        error = ports.WritePorts();

        if (error != IOWarrior.CIow28IoClass.DEF.ERROR_NONE)
            break;

        Thread.Sleep(250);
    }
}

IOWarrior.Functions.IowKitCloseDevice(iow); //Never forget to close the iowkit