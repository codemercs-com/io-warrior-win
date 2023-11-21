#pragma once
#include "iowkit.h"

#define PIXEL_MAX	500		//maximum auf LED count supported by IOW28
#define BLOCK_COUNT	24		//1 BLOCK = 20 LEDs
#define PIXEL_BLOCK 20		//RGB-LED count per Block


//index for TypeClass to load enable values
#define LEDTYPE_GRB 0		//Color order: Greed, Red, Blue   ->   default, most types
#define LEDTYPE_RGB 1		//Color order: Red, Green, Blue


#define LED_RETURN_NONE				0x0000
#define LED_RETURN_SUCCESS			0x0001
#define LED_RETURN_ERROR_HANDLE		0x0002
#define LED_RETURN_ERROR_ENABLE		0x0004
#define LED_RETURN_ERROR_WRITE		0x0008
#define LED_RETURN_ERROR_OUTOFRANGE	0x0010

class CLed
{
public:
	~CLed() {};
	CLed() { m_Red = 0; m_Green = 0; m_Blue = 0; }
	CLed(short r, short g, short b) { m_Red = r; m_Green = g; m_Blue = b; }
	void Reset() { m_Red = 0; m_Green = 0; m_Blue = 0; }
	void SetColor(short r, short g, short b) { m_Red = r; m_Green = g; m_Blue = b; }
	unsigned char Red() { return (unsigned char)m_Red; }
	unsigned char Green() { return (unsigned char)m_Green; }
	unsigned char Blue() { return (unsigned char)m_Blue; }
	
	short m_Red;
	short m_Green;
	short m_Blue;
};

class CDigitalLEDClass
{
private:
	
	short GetLogValue(short steps, short pos);
	void CreateLogTable();								//Create a static table of light output based on 0 - 100%

	IOWKIT_HANDLE m_Handle;
	bool m_Enabled;
	short m_PixelCount;
	unsigned char m_ColorType;
	unsigned char m_PixelMode;

	unsigned char m_Cycle_Zero;
	unsigned char m_Cycle_One;
	unsigned char m_Zero;
	unsigned char m_One;

	CLed m_Pixel[PIXEL_MAX];							//LED vales of RGB as 'Pixel'	
	CLed m_Shaddow[PIXEL_MAX];							//Copy of Pixels
	unsigned char m_LogTable[100];

	void Init();
	void CopyPixel();
	int EnableSpecialMode(bool mode);

public:
	CDigitalLEDClass();
	CDigitalLEDClass(short count);
	~CDigitalLEDClass();
	
	//IO-Warrior basic functions
	void SetIowHandle(IOWKIT_HANDLE handle);			//IOWKIT_HANDLE from iowkit
	void SetTransfer(unsigned char cycle_zero, unsigned char zero, unsigned char cycle_one, unsigned char one);	//Set transfer rate for specific LED Type (Neopixels, WS2812B, etc.)
	
	
	int Enable();										//Enable 'intel. LED function' of IO-Warrior28
	int Disable();										//Disable 'intel. LED function' of IO-Warrior28
	
	//LED specific functions
	int SetPixelCount(int num);						//Set count of pixel of LED-Strip
	int GetPixelCount();								//Get pixel count

	void SetPixelType(unsigned char num);						//Set type of Color order (RGB, GRB, BRG, etc)
	void SetPixelMode(unsigned char num);


	int SetPixel(int num, unsigned char r, unsigned char g, unsigned char b);		//Set color of specific pixel
	int SetPixelLog(int num, unsigned char r, unsigned char g, unsigned char b);	//Set color RGB based on 0..100 for log output in %
	CLed GetPixel(int num);								//Get color of specific pixel


	void SetPixelRange(int count);						//Turn Pixel fom 0 to count an

	
	void Clear();										//Clear all pixel (set to zero)
	int Write();										//Write data to IO-Warrior28 / LED-Stripe
	
	void Fade(CLed color1, CLed color2);				//Effect

	void ShiftPixelsLeft();
	void ShiftPixelsRight();

	void HalfSinus();
};