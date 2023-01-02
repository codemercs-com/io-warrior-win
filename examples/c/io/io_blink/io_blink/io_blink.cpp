#include <iostream>
#include <Windows.h>
#include "iowkit.h"


//Write IO-Pins to port 0 based on IO-Warrior type
bool write_io(IOWKIT_HANDLE handle, uint8_t value)
{
    bool ret = false;

    switch (IowKitGetProductId(handle))
    {
    case IOWKIT_PID_IOW40: //Discontinued
        IOWKIT40_IO_REPORT rep40;
        memset(&rep40, 0xFF, IOWKIT40_IO_REPORT_SIZE);
        rep40.ReportID = 0x00;
        rep40.Bytes[0] = value;

        if (IowKitWrite(handle, IOW_PIPE_IO_PINS, (char*)&rep40, IOWKIT40_IO_REPORT_SIZE) == IOWKIT40_IO_REPORT_SIZE)
            ret = true;
        break;
    case IOWKIT_PID_IOW24: //Discontinued
        IOWKIT24_IO_REPORT rep24;
        memset(&rep24, 0xFF, IOWKIT24_IO_REPORT_SIZE);
        rep24.ReportID = 0x00;
        rep24.Bytes[0] = value;

        if (IowKitWrite(handle, IOW_PIPE_IO_PINS, (char*)&rep24, IOWKIT24_IO_REPORT_SIZE) == IOWKIT24_IO_REPORT_SIZE)
            ret = true;
        break;
    case IOWKIT_PID_IOW56:
        IOWKIT56_IO_REPORT rep56;
        memset(&rep56, 0xFF, IOWKIT40_IO_REPORT_SIZE);
        rep56.ReportID = 0x00;
        rep56.Bytes[0] = value;

        if (IowKitWrite(handle, IOW_PIPE_IO_PINS, (char*)&rep56, IOWKIT56_IO_REPORT_SIZE) == IOWKIT56_IO_REPORT_SIZE)
            ret = true;
        break;
    case IOWKIT_PID_IOW28:
        IOWKIT28_IO_REPORT rep28;
        memset(&rep28, 0xFF, IOWKIT28_IO_REPORT_SIZE);
        rep28.ReportID = 0x00;
        rep28.Bytes[0] = value;

        if (IowKitWrite(handle, IOW_PIPE_IO_PINS, (char*)&rep28, IOWKIT28_IO_REPORT_SIZE) == IOWKIT28_IO_REPORT_SIZE)
            ret = true;
        break;
    case IOWKIT_PID_IOW100:
        IOWKIT100_IO_REPORT rep100;
        memset(&rep100, 0xFF, IOWKIT100_IO_REPORT_SIZE);
        rep100.ReportID = 0x00;
        rep100.Bytes[0] = value;

        if (IowKitWrite(handle, IOW_PIPE_IO_PINS, (char*)&rep100, IOWKIT100_IO_REPORT_SIZE) == IOWKIT100_IO_REPORT_SIZE)
            ret = true;
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

int main(int argc, char* argv[])
{
    IOWKIT_HANDLE handle = NULL;
    IOWKIT_HANDLE iows[IOWKIT_MAX_DEVICES];
    UINT numIows = 0;
    WCHAR sn[9];
    bool rc = 0;
    ULONG pid = 0;

    //Open iowkit
    handle = IowKitOpenDevice();

    if (handle == NULL)
    {
        printf_s("Failed to open device. EXIT\n");
		IowKitCloseDevice(handle);
        return 0;
    }

    // Get number of IOWs in system
    numIows = IowKitGetNumDevs();
    printf("%d IOWs in system\n", numIows);

    for (UINT i = 0; i < numIows; i++)
    {
        // Get device handle and init object
        iows[i] = IowKitGetDeviceHandle(i + 1);
        // Get serial number
        IowKitGetSerialNumber(iows[i], sn);
        pid = IowKitGetProductId(iows[i]);
        printf("%d PID %x, S/N \"%ws\"\n", i + 1, pid, sn);
    }

    printf("Blinking LEDs for first found IO-Warrior...\n");

    ULONG bits;
    for (UINT i = 0; i < 50; i++)
    {
        bits = rand();
        rc = write_io(iows[0], bits);

        if (rc == false)
            printf("Cannot write, err %d\n", GetLastError());

        // Sleep for 25ms
        Sleep(50);
    }
    printf("Blinking complete\n");

    // Close device ('iows' will also closed)
    IowKitCloseDevice(handle);

    return 0;
}
