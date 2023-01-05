#include <iostream>
#include <Windows.h>
#include "iowkit.h"

int main()
{
	IOWKIT_HANDLE handle = NULL;

	//open iowkit
	handle = IowKitOpenDevice();

	//If no device found exit
	if (handle == NULL)
	{
		printf_s("Failed to open device. EXIT\n");
		IowKitCloseDevice(handle);
		return 1;
	}

	//This example works only with IOW56
	if (IowKitGetProductId(handle) != IOWKIT_PID_IOW56)
	{
		printf_s("No IO-Warrior56 found. This example will only work with an IO-Warrior56. EXIT\n");
		IowKitCloseDevice(handle);
		return 2;
	}

	//Get revision HEX from String
	ULONG l = strtol("2000", NULL, 16);

	//IO-Warrior56 version must be >= 2.0.0.0 for one channel PWM and >=2.0.0.2 for two channel PWM
	if (IowKitGetRevision(handle) < l)
	{
		printf_s("Revision of IO-Warrior56 to low. Revision 2.0.0.0 or higher needed. EXIT\n");
		IowKitCloseDevice(handle);
		return 3;
	}

	IOWKIT56_SPECIAL_REPORT report;
	memset(&report, 0x00, IOWKIT56_SPECIAL_REPORT_SIZE);

	//input values, blink slow
	uint16_t periode = 512;	//16bit value (0..65535)
	uint16_t pulse = 255;	//16bit value (0..65535)

	BYTE period_msb = 0x00;
	BYTE period_lsb = 0x00;
	BYTE pulse_msb = 0x00;
	BYTE pulse_lsb = 0x00;

	//Get MSB and LSB from input
	period_msb = (periode & 0xFF00) >> 8;
	period_lsb = (periode & 0x00FF);

	pulse_msb = (pulse & 0xFF00) >> 8;
	pulse_lsb = (pulse & 0x00FF);


	//Create report
	report.ReportID = 0x20;			//Special mode PWM output
	report.Bytes[0] = 0x01;			//Enable only Channel 1

	//Channel 1
	report.Bytes[1] = period_lsb;	//period LSB
	report.Bytes[2] = period_msb;	//period MSB
	report.Bytes[3] = pulse_lsb;	//pulse LSB
	report.Bytes[4] = pulse_msb;	//pulse MSB
	report.Bytes[5] = 0;			//Clock 1kHz

	//Channel 2
	report.Bytes[6] = 0;	//period LSB
	report.Bytes[7] = 0;	//period MSB
	report.Bytes[8] = 0;	//pulse LSB
	report.Bytes[9] = 0;	//pulse MSB
	report.Bytes[10] = 0;	//Clock 1kHz

	//Send report to IO-Warrior56
	IowKitWrite(handle, IOW_PIPE_SPECIAL_MODE, (char*)&report, IOWKIT56_SPECIAL_REPORT_SIZE);
	//No IowKitRead() nessesary/possible!


	IowKitCloseDevice(handle);
	return 0;
}
