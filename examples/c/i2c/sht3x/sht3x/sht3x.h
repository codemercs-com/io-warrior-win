#pragma once
//#define SHT30_ 0x00

//Defines for SHT30 Chip
#define SHT30_ADR_1 0x44 //7 Bit
#define SHT30_ADR_2 0x45 //7 Bit

//Define for Temperature calculation
#define FAHRENHEIT FALSE
#define CELSUIS TRUE

//With Clockstretching
#define SHT30_COCK_HI 0x2C06
#define SHT30_COCK_MED 0x2C0D
#define SHT30_COCK_LOW 0x2C10

//Without Clockstretching
#define SHT30_HI 0x2400
#define SHT30_MED 0x240B
#define SHT30_LOW 0x2416

//Periodic Read
#define SHT30_05MPS_HI 0x2032
#define SHT30_05MPS_MED 0x2024
#define SHT30_05MPS_LOW 0x202F

#define SHT30_1MPS_HI 0x2130
#define SHT30_1MPS_MED 0x2126
#define SHT30_1MPS_LOW 0x212D

#define SHT30_2MPS_HI 0x2236
#define SHT30_2MPS_MED 0x2220
#define SHT30_2MPS_LOW 0x222B

#define SHT30_4MPS_HI 0x2334
#define SHT30_4MPS_MED 0x2322
#define SHT30_4MPS_LOW 0x2329

#define SHT30_10MPS_HI 0x2737
#define SHT30_10MPS_MED 0x2721
#define SHT30_10MPS_LOW 0x272A

//Readout Results for Periodic Mode
#define SHT30_FETCH_DATA 0xE000

//ART Command
#define SHT30_ART 0x30A2

//Soft Reset
#define SHT30_RESET 0x30A2

//General Call
#define SHT30_GENERAL_CALL 0x0006

//Heater
#define SHT30_HEATER_ON 0x306D
#define SHT30_HEATER_OFF 0x3066

//Status Register
#define SHT30_STATUS 0xF32D

//Clear Status Register
#define SHT30_CLEAR_STATUS 0x3041

//Bits of Status Register
#define SHT30_FIELD_STATUS_ALERT 0x4000
#define SHT30_FIELD_STATUS_HEATER 0x1000
#define SHT30_FIELD_STATUS_RH 0x0400
#define SHT30_FIELD_STATUS_TEMP 0x0200
#define SHT30_FIELD_STATUS_RESET 0x0008
#define SHT30_FIELD_STATUS_COMMAND 0x0002
#define SHT30_FIELD_STATUS_CRC 0x0001

typedef struct SHT3X_STRUCT
{
	double temperatur;
	double humidity;

}SHT3X_STRUCT;