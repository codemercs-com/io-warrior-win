#include <iostream>
#include <Windows.h>
#include "iowkit.h"
#include "iow28_adc.h"

//Init ADC mode with parameter
void set_parameter(IOWKIT_HANDLE handle, BYTE enable, BYTE chan, BYTE mod)
{
	IOWKIT28_SPECIAL_REPORT report;
	memset(&report, 0, IOWKIT28_ADC_REPORT_SIZE);

	report.ReportID = IOW28_ADC_MODE;
	report.Bytes[0] = enable;		//Enable / Disable ADC mode
	report.Bytes[1] = chan;			//Channel count 
	report.Bytes[2] = 0x00;			//Must be 0
	report.Bytes[3] = 0x00;			//Must be 0
	report.Bytes[4] = mod;			//Single short or continues mode

	IowKitWrite(handle, IOW_PIPE_ADC_MODE, (char*)&report, IOWKIT28_ADC_REPORT_SIZE);
}

IOW28_ADC_CALIB_STRUCT get_calibration_data(IOWKIT_HANDLE handle)
{
	IOW28_ADC_CALIB_STRUCT data = { 0 };
	IOWKIT28_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT28_ADC_REPORT_SIZE);
	report.ReportID = IOW28_ADC_DATA;
	report.Bytes[0] = IOW28_ADC_CALIBRATION;

	if (IowKitWrite(handle, IOW_PIPE_ADC_MODE, (char*)&report, IOWKIT28_ADC_REPORT_SIZE) == IOWKIT28_ADC_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_ADC_MODE, (char*)&report, IOWKIT28_ADC_REPORT_SIZE) == IOWKIT28_ADC_REPORT_SIZE)
		{
			data.VrefCal = (report.Bytes[2] << 8) | report.Bytes[1];
			data.TempCal1 = (report.Bytes[4] << 8) | report.Bytes[3];
			data.TempCal2 = (report.Bytes[6] << 8) | report.Bytes[5];
			data.Vref = (report.Bytes[8] << 8) | report.Bytes[7];
			data.Temp = (report.Bytes[10] << 8) | report.Bytes[9];
		}
		else
			printf_s("IowKitRead() ERROR\n");
	}
	else
		printf_s("IowKitWrite() ERROR\n");

	return data;
}

IOW28_ADC_DATA_STRUCT get_ADC_singleshot(IOWKIT_HANDLE handle)
{
	IOW28_ADC_DATA_STRUCT data = { 0 };
	IOWKIT28_SPECIAL_REPORT report;

	memset(&report, 0, IOWKIT28_ADC_REPORT_SIZE);
	report.ReportID = IOW28_ADC_DATA;
	report.Bytes[0] = IOW28_ADC_VALUES;

	if (IowKitWrite(handle, IOW_PIPE_ADC_MODE, (char*)&report, IOWKIT28_ADC_REPORT_SIZE) == IOWKIT28_ADC_REPORT_SIZE)
	{
		if (IowKitRead(handle, IOW_PIPE_ADC_MODE, (char*)&report, IOWKIT28_ADC_REPORT_SIZE) == IOWKIT28_ADC_REPORT_SIZE)
		{
			data.seq = report.Bytes[0];
			data.Ch1 = (report.Bytes[2] << 8) | report.Bytes[1];
			data.Ch2 = (report.Bytes[4] << 8) | report.Bytes[3];
			data.Ch3 = (report.Bytes[6] << 8) | report.Bytes[5];
			data.Ch4 = (report.Bytes[8] << 8) | report.Bytes[7];
		}
		else
			printf_s("IowKitRead() ERROR\n");
	}
	else
		printf_s("IowKitWrite() ERROR\n");

	return data;
}

/*Get ADC value as mili voltage*/
double GetVoltage(unsigned short VrefCal, unsigned short Vref, unsigned short ADCdata)
{
	return 3.3/*V*/ * VrefCal * ADCdata / Vref / 4095;
}

/*Get temperature from sensor */
double GetTemperatur(unsigned short TempCal1, unsigned short TempCal2, unsigned short VrefCal, unsigned short Vref, unsigned short Temp)
{
	return 80.0/*°C*/ / (TempCal2 - TempCal1) * (Temp * VrefCal / Vref - TempCal1) + 30.0;
}


int main()
{
	IOWKIT_HANDLE handle;
	IOW28_ADC_CALIB_STRUCT adcCalib;	//defined in iow28_adc.h
	IOW28_ADC_DATA_STRUCT adcData;		//defined in iow28_adc.h


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

	//Disable ADC mode to change the channels if ADC is activated.
	set_parameter(handle, IOW28_ADC_DISABLE, IOW28_ADC_NONE, IOW28_ADC_MODE_SINGLE);

	//Enable adc mode with 4 channel
	set_parameter(handle, IOW28_ADC_ENABLE, IOW28_ADC_4CH, IOW28_ADC_MODE_SINGLE);	//Enable one ADC channel

	//Get calibration data for ADC from IO-Warrior28
	adcCalib = get_calibration_data(handle);

	//Get ADC data
	adcData = get_ADC_singleshot(handle);

	printf_s("Channel 1: %0.3f V\n", GetVoltage(adcCalib.VrefCal, adcCalib.Vref, adcData.Ch1));
	printf_s("Channel 2: %0.3f V\n", GetVoltage(adcCalib.VrefCal, adcCalib.Vref, adcData.Ch2));
	printf_s("Channel 3: %0.3f V\n", GetVoltage(adcCalib.VrefCal, adcCalib.Vref, adcData.Ch3));
	printf_s("Channel 4: %0.3f V\n", GetVoltage(adcCalib.VrefCal, adcCalib.Vref, adcData.Ch4));

	//Disable ADC mode
	set_parameter(handle, IOW28_ADC_DISABLE, IOW28_ADC_NONE, IOW28_ADC_MODE_SINGLE);

	IowKitCloseDevice(handle);
	return 0;
}