#pragma once
//Defines für IOW28 ADC mode
#define IOW28_ADC_MODE			0x1C
#define IOW28_ADC_ENDABLE		0x1D
#define IOW28_ADC_DATA			0x1E

//defines for setup ADC mode
#define IOW28_ADC_ENABLE		0x01
#define IOW28_ADC_DISABLE		0x00
#define IOW28_ADC_NONE			0x00	//get temperatur from IO-Warrior28
#define IOW28_ADC_1CH			0x01
#define IOW28_ADC_2CH			0x02
#define IOW28_ADC_4CH			0x04

//defines for ADC data mode
#define IOW28_ADC_CALIBRATION	0x00
#define IOW28_ADC_VALUES		0x01

#define IOW28_ADC_MODE_SINGLE	0x00
#define IOW28_ADC_MODE_CONT		0x01

//Calibration values
typedef struct IOW28_ADC_CALIB_STRUCT
{
	unsigned short VrefCal;
	unsigned short TempCal1;
	unsigned short TempCal2;
	unsigned short Vref;
	unsigned short Temp;
}IOW28_ADC_CALIB_STRUCT;

//Data values
typedef struct IOW28_ADC_DATA_STRUCT
{
	unsigned short seq;
	unsigned short Ch1;
	unsigned short Ch2;
	unsigned short Ch3;
	unsigned short Ch4;
}IOW28_ADC_DATA_STRUCT;