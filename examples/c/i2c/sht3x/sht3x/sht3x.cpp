#include <iostream>
#include <Windows.h>
#include "iowkit.h"
#include "sht3x.h"

double get_humidity(WORD value)
{
    return 100.0 * (value / (pow(2.0, 16) - 1));
}

double get_temperature(WORD value, BYTE mode)
{
    switch (mode)
    {
    case FAHRENHEIT: return -49.0 + 347.0 * (value / (pow(2.0, 16) - 1));
    case CELSUIS: return -45.0 + 175.0 * (value / (pow(2.0, 16) - 1));
    default: return -1;
    }
}

bool set_periodic_read(HANDLE handle, BYTE adr, WORD value)
{
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

	rep.ReportID = 0x02;	//Write I2C
	rep.Bytes[0] = 0xC3;	//start bit + stop bit + 3 byte data
	rep.Bytes[1] = adr;		//I2C device address (8bit)
	rep.Bytes[2] = (value & 0xFF00) >> 8;	//data
	rep.Bytes[3] = value & 0x00FF;			//data

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			return true;
		else
			return false;
	}

	return false;
}

bool get_periodic_read(HANDLE handle, BYTE adr)
{
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

	rep.ReportID = 0x02;
	rep.Bytes[0] = 0xC3;
	rep.Bytes[1] = adr;
	rep.Bytes[2] = 0xE0;
	rep.Bytes[3] = 0x00;

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			return true;
		else
			return false;
	}

	return false;
}

bool set_heater(HANDLE handle, BYTE adr, WORD value)
{
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

	rep.ReportID = 0x02;
	rep.Bytes[0] = 0xC3;
	rep.Bytes[1] = adr;
	rep.Bytes[2] = (value & 0xFF00) >> 8;
	rep.Bytes[3] = value & 0x00FF;

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			return true;
		else
			return false;
	}

	return false;
}

WORD get_status(HANDLE handle, BYTE adr)
{
	WORD ret = 0;
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

	rep.ReportID = 0x02;
	rep.Bytes[0] = 0xC3;
	rep.Bytes[1] = adr;
	rep.Bytes[2] = SHT30_STATUS >> 8;
	rep.Bytes[3] = SHT30_STATUS & 0x00FF;

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
		{
			//Read Data
			memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
			rep.ReportID = 0x03;	//Read I2C
			rep.Bytes[0] = 0x03;	//3 byte 
			rep.Bytes[1] = adr | 0x01;	//I2C device address (8bit) with read bit

			if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			{
				if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
				{
					ret = (rep.Bytes[1] << 8) | rep.Bytes[2];
				}
			}
		}
	}

	return ret;
}

bool clear_status(HANDLE handle, BYTE adr)
{
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

	rep.ReportID = 0x02;
	rep.Bytes[0] = 0xC3;
	rep.Bytes[1] = adr;
	rep.Bytes[2] = SHT30_CLEAR_STATUS >> 8;
	rep.Bytes[3] = SHT30_CLEAR_STATUS & 0x00FF;

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			return true;
		else
			return false;
	}

	return false;
}

bool get_measurement(HANDLE handle, BYTE adr, double& tmp, double& rh, BYTE mode)
{
	IOWKIT28_SPECIAL_REPORT rep;
	memset(&rep, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
	rep.ReportID = 0x03;	//Read I2C
	rep.Bytes[0] = 0x06;	//6 byte data
	rep.Bytes[1] = adr | 0x01;	//I2C device address (8bit) with read bit

	if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&rep, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
		{
			if (rep.Bytes[0] != 0x80) //Only ACK !
			{
				tmp = get_temperature((rep.Bytes[1] << 8) | rep.Bytes[2], mode);
				rh = get_humidity((rep.Bytes[4] << 8) | rep.Bytes[5]);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	
	return false;
}


int main(int argc, char* argv[])
{ 
    IOWKIT_HANDLE handle = NULL;
	IOWKIT28_SPECIAL_REPORT report;
	BYTE i2c_adr = SHT30_ADR_1 << 1;	//IO-Warrior28 use 8bit I2C addresses
    
    //open iowkit
    handle = IowKitOpenDevice();

	//If no device found exit
    if (handle == NULL)
    {
        printf_s("Failed to open device. EXIT\n");
        IowKitCloseDevice(handle);
        return 1;
    }

	//This example works only with IOW28
	if (IowKitGetProductId(handle) != IOWKIT_PID_IOW28)
	{
		printf_s("No IO-Warrior28 found. This example will only work with an IO-Warrior28. EXIT\n");
		IowKitCloseDevice(handle);
		return 2;
	}


	//enable i2c mode
	memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);	//Clear report struct
	report.ReportID = 0x01;	//Use I2C mode
	report.Bytes[0] = 0x01; //Enable I2C mode
	report.Bytes[1] = 0x00; //100kbit/s
	report.Bytes[2] = 0x00;	//timeout (not implemented yet)
	IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);

	double temperatur = 0.0f;
	double rh = 0.0f;

	if (set_periodic_read(handle, i2c_adr, SHT30_4MPS_HI) == false)
		printf_s("Error on set_periodic_read()\n");

	if (get_periodic_read(handle, i2c_adr) == false)
		printf_s("Error on get_periodic_read()\n");

	if (get_measurement(handle, i2c_adr, temperatur, rh, CELSUIS) == false)
		printf_s("Error on get_measurement()\n");

	printf_s("Temperature: %0.2f Celsius\n", temperatur);
	printf_s("Humidity: %0.2f %%\n", rh);


	//disable i2c mode
	memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);	//Clear report struct
	report.ReportID = 0x01;	//Use I2C mode
	report.Bytes[0] = 0x00; //Enable I2C mode
	report.Bytes[1] = 0x00; //100kbit/s
	report.Bytes[2] = 0x00;	//timeout (not implemented yet)
	IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);

	//Close iowkit
    IowKitCloseDevice(handle);

    return 0;
}
