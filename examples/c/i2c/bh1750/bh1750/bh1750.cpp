#include <iostream>
#include <Windows.h>

#include "iowkit.h"


//BH1750 I2C address (8bit)
#define I2C_ADDRESS 0x46

int main()
{
	IOWKIT_HANDLE handle = NULL;
	IOWKIT28_SPECIAL_REPORT report;
	int lux = 0;


	
	handle = IowKitOpenDevice();

	if (handle != NULL)
	{
		//enable i2c mode
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);	//Clear report struct
		report.ReportID = 0x01;	//Use I2C mode
		report.Bytes[0] = 0x01; //Enable I2C mode
		report.Bytes[1] = 0x00; //100kbit/s
		report.Bytes[2] = 0x00;	//timeout (not implemented yet)
		IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);


		//Write instruction to BH1750
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);	//Clear report struct
		report.ReportID = 0x02; //Write I2C
		report.Bytes[0] = 0xC2; //Start + Stop and 2 bytes of adr and data
		report.Bytes[1] = I2C_ADDRESS;	//I2C write address as 8bit
		report.Bytes[2] = 0x10; //Continously H-Resolution

		if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
		{
			if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			{
				//OK
			}
			else
			{
				std::cout << "Error on IowKitRead()" << std::endl;
			}
		}
		else
		{
			std::cout << "Error on IowKitWrite()" << std::endl;
		}

		Sleep(180); //Wait until BH1750 has set the configuration

		//measure Lux X times
		for (int i = 0; i < 20; i++)
		{
			//Read measurement data
			memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
			report.ReportID = 0x03;	//Read I2C
			report.Bytes[0] = 0x02;	//2 byte data
			report.Bytes[1] = I2C_ADDRESS | 0x01;	//I2C device address (8bit) with read bit

			if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			{
				if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
				{
					if (report.Bytes[0] != 0x80) //Only ACK !
					{
						lux = ((report.Bytes[1] << 8) | report.Bytes[2]) / 1.2;
						std::cout << lux << " Lux" << std::endl;
					}
					else
					{
						std::cout << "Error on IowKitRead()" << std::endl;
					}
				}
				else
				{
					std::cout << "Error on IowKitWrite()" << std::endl;
				}
			}


			Sleep(150); //Wait between read measurements
		}

		//disable i2c mode
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);	//Clear report struct
		report.ReportID = 0x01;	//Use I2C mode
		report.Bytes[0] = 0x00; //Enable I2C mode
		report.Bytes[1] = 0x00; //100kbit/s
		report.Bytes[2] = 0x00;	//timeout (not implemented yet)
		IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);
	}

	IowKitCloseDevice(handle);
}

