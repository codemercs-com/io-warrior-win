#pragma once
#include "CDigitalLEDClass.h"
#include "iowkit.h"
#include <iostream>
#include <math.h>
#include <string>	//memset



CDigitalLEDClass::CDigitalLEDClass()
{
	m_Handle = NULL;
	m_Enabled = false;
	m_PixelCount = 0;
	m_ColorType = LEDTYPE_GRB;

	//Default values for WS2812B
	m_Cycle_Zero = 59;
	m_Cycle_One = 59;
	m_Zero = 19;
	m_One = 39;
	Clear();
	CreateLogTable();
}

CDigitalLEDClass::CDigitalLEDClass(short count)
{
	m_Handle = NULL;
	m_Enabled = false;
	m_PixelCount = count;
	m_ColorType = LEDTYPE_GRB;
	m_Cycle_Zero = 59;
	m_Cycle_One = 59;
	m_Zero = 19;
	m_One = 39;
	Clear();
	CreateLogTable();
}

CDigitalLEDClass::~CDigitalLEDClass()
{

}

short CDigitalLEDClass::GetLogValue(short steps, short pos)
{
	int a = steps;  //Anzahl an Schritte (4, 8, 16, 32, 64, 256) bzw. die anzahl der LEDs
	int b = 255;	//Auflösung des PWM's (256, 1024, 65536)
	int y = 0;		//y = Errechneter Wert an einer stelle x
	int x = pos;
	//y = 0 wenn x = 0

	return (int)pow(2, log2(b) * (x + 1) / a) - 1;
}

void CDigitalLEDClass::CreateLogTable()
{
	for (int i = 0; i < 100; i++)
		m_LogTable[i] = (unsigned char)GetLogValue(100, i) & 0xFF;
}

void CDigitalLEDClass::SetIowHandle(IOWKIT_HANDLE handle)
{
	m_Handle = handle;
}

void CDigitalLEDClass::SetTransfer(unsigned char cycle_zero, unsigned char zero, unsigned char cycle_one, unsigned char one)
{
	m_Cycle_Zero = cycle_zero;
	m_Cycle_One = cycle_one;
	m_Zero = zero;
	m_One = one;
}

int CDigitalLEDClass::EnableSpecialMode(bool mode)
{
	unsigned char b;

	if (mode == true) b = 0x01;
	else b = 0x00;

	IOWKIT28_SPECIAL_REPORT report;
	memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
	report.ReportID = 0x28;
	report.Bytes[0] = b;
	report.Bytes[1] = m_Cycle_Zero;
	report.Bytes[2] = m_Zero;
	report.Bytes[3] = m_Cycle_One;
	report.Bytes[4] = m_One;

	if (m_Handle != NULL)
	{
		IowKitWrite(m_Handle, IOW_PIPE_SPECIAL_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);
		m_Enabled = mode;
	}
	else
	{
		std::cout << "No HANDLE from IowKitOpenDevice() set" << std::endl;
		return LED_RETURN_ERROR_HANDLE;
	}

	return LED_RETURN_SUCCESS;
}

int CDigitalLEDClass::Enable()
{
	return EnableSpecialMode(true);
}

int CDigitalLEDClass::Disable()
{
	return EnableSpecialMode(false);
}

void CDigitalLEDClass::Init()
{
	for (int i = 0; i < PIXEL_MAX; i++)
	{
		m_Pixel[i].Reset();
		m_Shaddow[i].Reset();
	}
}

void CDigitalLEDClass::Clear()
{
	for (int i = 0; i < PIXEL_MAX; i++)
		m_Pixel[i].SetColor(0, 0, 0);
}

void CDigitalLEDClass::CopyPixel()
{
	memcpy(&m_Shaddow, &m_Pixel, sizeof(m_Pixel));
}

int CDigitalLEDClass::SetPixelCount(int num)
{
	if ((num <= PIXEL_MAX) && (num >= 0))
		m_PixelCount = num;
	else
	{
		std::cout << "Pixel COUNT out of range (1..500)" << std::endl;
		return LED_RETURN_ERROR_OUTOFRANGE;
	}

	return LED_RETURN_SUCCESS;
}

int CDigitalLEDClass::GetPixelCount()
{
	return m_PixelCount;
}

void CDigitalLEDClass::SetPixelType(unsigned char num)
{
	m_ColorType = num;
}

void CDigitalLEDClass::SetPixelMode(unsigned char num)
{
	m_PixelMode = num;
}

int CDigitalLEDClass::SetPixel(int num, unsigned char r, unsigned char g, unsigned char b)
{
	if ((num < PIXEL_MAX) && (num >= 0))
	{
		//Remap the colors
		switch (m_ColorType)
		{
		case LEDTYPE_RGB:
				m_Pixel[num].SetColor((r & 0xFF), (g & 0xFF), (b & 0xFF));
			break;
		case LEDTYPE_GRB:
		default:
				m_Pixel[num].SetColor((g & 0xFF), (r & 0xFF), (b & 0xFF));
			break;
		}

		return LED_RETURN_SUCCESS;
	}
	else
	{
		std::cout << "Pixel NUM out of range (0..499)" << std::endl;
		return LED_RETURN_ERROR_OUTOFRANGE;
	}
}

int CDigitalLEDClass::SetPixelLog(int num, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char red = r, green = g, blue = b;
	if ((num < PIXEL_MAX) && (num >= 0))
	{

		if (r >= 100) red = 99;
		if (g >= 100) green = 99;
		if (b >= 100) blue = 99;

		switch (m_ColorType)
		{
		case LEDTYPE_RGB:
			m_Pixel[num].SetColor(m_LogTable[red], m_LogTable[green], m_LogTable[blue]);
			break;
		case LEDTYPE_GRB:
		default:
			m_Pixel[num].SetColor(m_LogTable[green], m_LogTable[red], m_LogTable[blue]);
			break;
		}

		return LED_RETURN_SUCCESS;
	}
	else
	{
		std::cout << "Pixel NUM out of range (0..499)" << std::endl;
		return LED_RETURN_ERROR_OUTOFRANGE;
	}
}

CLed CDigitalLEDClass::GetPixel(int num)
{
	return m_Pixel[num];
}

void CDigitalLEDClass::Fade(CLed color1, CLed color2)
{
	unsigned char steps = 255 / m_PixelCount;    //Schritte für die Helligkeit ohne LOG-Tabelle, (255 = max Helligkeit)
	int tmp = 0;

	CLed t[2];
	t[0] = color1;
	t[1] = color2;

	CLed c1[PIXEL_MAX];
	CLed c2[PIXEL_MAX];
	CLed tempPixel[PIXEL_MAX];

	for (int i = 0; i < PIXEL_MAX; i++)
	{
		c1[i].Reset();
		c2[i].Reset();
		tempPixel[i].Reset();
	}
		

	//Farbverlauf Links -> Rechts
	for (int i = 0; i < m_PixelCount; i++)
	{
		//Rot
		//t[0].r -= steps;
		t[0].m_Red -= steps;
		if (t[0].m_Red < 0) 
			c1[i].m_Red = 0;
		else 
			c1[i].m_Red = t[0].m_Red;

		//Grün
		t[0].m_Green -= steps;

		if (t[0].m_Green < 0)
			c1[i].m_Green = 0;
		else 
			c1[i].m_Green = t[0].m_Green;

		//Blau
		t[0].m_Blue -= steps;

		if (t[0].m_Blue < 0)
			c1[i].m_Blue = 0;
		else 
			c1[i].m_Blue = t[0].m_Blue;
	}

	//Farbverlauf Rechts -> Links
	for (int i = 0; i < m_PixelCount; i++)
	{
		//Rot
		t[1].m_Red -= steps;
		if (t[1].m_Red <= 0) 
			c2[(m_PixelCount - 1) - i].m_Red = 0; 
		else 
			c2[(m_PixelCount - 1) - i].m_Red = t[1].m_Red;

		//Grün
		t[1].m_Green -= steps;
		if (t[1].m_Green <= 0) 
			c2[(m_PixelCount - 1) - i].m_Green = 0; 
		else 
			c2[(m_PixelCount - 1) - i].m_Green = t[1].m_Green;

		//Blau
		t[1].m_Blue -= steps;
		if (t[1].m_Blue <= 0) 
			c2[(m_PixelCount - 1) - i].m_Blue = 0; 
		else 
			c2[(m_PixelCount - 1) - i].m_Blue = t[1].m_Blue;
	}

	//Farbverläufe addieren und in Pixel schreiben
	for (int i = 0; i < m_PixelCount; i++)
	{
		tmp = c1[i].m_Red + c2[i].m_Red;

		if (tmp > 255) 
			tempPixel[i].m_Red = 255;
		else if (tmp < 0)  
			tempPixel[i].m_Red = 0;
		else 
			tempPixel[i].m_Red = tmp;
	}

	for (int i = 0; i < m_PixelCount; i++)
	{
		tmp = c1[i].m_Green + c2[i].m_Green;
		if (tmp > 255) 
			tempPixel[i].m_Green = 255;
		else if (tmp < 0)  
			tempPixel[i].m_Green = 0;
		else 
			tempPixel[i].m_Green = tmp;
	}

	for (int i = 0; i < m_PixelCount; i++)
	{
		tmp = c1[i].m_Blue + c2[i].m_Blue;
		if (tmp > 255) 
			tempPixel[i].m_Blue = 255;
		else if (tmp < 0)  
			tempPixel[i].m_Blue = 0;
		else 
			tempPixel[i].m_Blue = tmp;
	}
	
	for (int i = 0; i < m_PixelCount; i++)
		SetPixel(i, (unsigned char)tempPixel[i].m_Red, (unsigned char)tempPixel[i].m_Green, (unsigned char)tempPixel[i].m_Blue);


	//Write();
}

int CDigitalLEDClass::Write()
{
	IOWKIT28_SPECIAL_REPORT report;
	int error = LED_RETURN_NONE;

	if (m_Handle != NULL)
	{
		if (m_Enabled)
		{
			int repCount = (int)ceil((double)m_PixelCount / (double)PIXEL_BLOCK);
			int ledCount = m_PixelCount;
			int ledSend = 0;
			int offset = 0;
			int pixel = 0;

			for (int i = 0; i < repCount; i++)
			{
				if (ledCount >= PIXEL_BLOCK)
				{
					ledSend = PIXEL_BLOCK;
					ledCount -= PIXEL_BLOCK;
				}
				else
				{
					ledSend = ledCount;
				}

				memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
				report.ReportID = 0x29;
				report.Bytes[0] = i;// 0x00 | i;
				report.Bytes[1] = 0x00; // m_PixelCount & 0x00FF;
				report.Bytes[2] = 0x00; // (m_PixelCount & 0xFF00) >> 8;

				offset = 0;

				for (int j = 0; j < ledSend; j++)
				{
					offset += 3;
					report.Bytes[offset + 0] = m_Pixel[pixel].Red();
					report.Bytes[offset + 1] = m_Pixel[pixel].Green();
					report.Bytes[offset + 2] = m_Pixel[pixel].Blue();

					pixel++;
				}

				if (IowKitWrite(m_Handle, IOW_PIPE_SPECIAL_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) != IOWKIT28_SPECIAL_REPORT_SIZE)
				{
					std::cout << "Something wrong on write. Kill loop!" << std::endl;
					error |= LED_RETURN_ERROR_WRITE;
					break;
				}
			}

			//Write from Shadow 
			report.ReportID = 0x29;
			report.Bytes[0] = 0x80 | BLOCK_COUNT;
			report.Bytes[1] = m_PixelCount & 0x00FF;
			report.Bytes[2] = (m_PixelCount & 0xFF00) >> 8;
			if (IowKitWrite(m_Handle, IOW_PIPE_SPECIAL_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) != IOWKIT28_SPECIAL_REPORT_SIZE)
			{
				std::cout << "Something wrong on write." << std::endl;
				error |= LED_RETURN_ERROR_WRITE;
			}
		}
		else
		{
			std::cout << "Special mode 'Inteligent LED function' not enabled" << std::endl;
			error |= LED_RETURN_ERROR_ENABLE;
		}
	}
	else
	{
		std::cout << "No HANDLE from IowKitOpenDevice() set" << std::endl;
		error |= LED_RETURN_ERROR_HANDLE;
	}

	return error;
}

void CDigitalLEDClass::ShiftPixelsLeft()
{
	CLed pixel;
	pixel = m_Pixel[0];

	for (int i = 0; i < (m_PixelCount-1); i++)
		m_Pixel[i] = m_Pixel[i + 1];
	
	m_Pixel[m_PixelCount - 1] = pixel;
}

void CDigitalLEDClass::ShiftPixelsRight()
{
	CLed pixel;
	pixel = m_Pixel[m_PixelCount - 1];

	for (int i = (m_PixelCount - 1); i >= 0; i--)
		m_Pixel[i + 1] = m_Pixel[i];

	m_Pixel[0] = pixel;
}

void CDigitalLEDClass::HalfSinus()
{
	int calc = 0;

	for (int i = 0; i < m_PixelCount/*360*/; i++)
	{
		calc = (int)trunc((sin((double)i * ((2.0 * 3.14159) / m_PixelCount/*360*/)) + 0.0) * 100.0); //+1.0 to get only positiv values
		
		if (calc > 0)
			m_Pixel[i].m_Red = m_LogTable[calc];
		else
			m_Pixel[i].m_Red = 0;
	}
}
