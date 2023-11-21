/*
* This sample requires a IO-Warrior28 with revision 1.0.1.4 or higher.
*/

#pragma once
#include <iostream>
#include <Windows.h>
#include "iowkit.h"
#include "CDigitalLEDClass.h"

int main()
{
	char chr = 0;
	IOWKIT_HANDLE handle;

	handle = IowKitOpenDevice();

	if (handle != NULL)
	{
		if (IowKitGetNumDevs() == 1)
		{
			if (IowKitGetProductId(handle) == IOWKIT_PID_IOW28)
			{
				if (IowKitGetRevision(handle) >= 0x1014)
				{
					CDigitalLEDClass led;

					led.SetIowHandle(handle);					//Set handle for class
					led.SetTransfer(0x3B, 0x0E, 0x3B, 0x1F);	//Set LED-Stripe setup
					led.Enable();								//Enable special mode "digital LED"
					led.SetPixelCount(12);						//Set count of LEDs on stripe (aka "pixel")

					//Set some pixel
					led.SetPixel(0, 255, 0, 0);					//Set 1st pixel RED
					led.SetPixel(6, 255, 0, 255);				//Set 7th pixel PINK
					led.Write();								//Write pixel

					std::cout << "Press any key to go on..." << std::endl;
					chr = std::cin.get();

					led.SetPixel(2, 0, 0, 255);					//Set 3rd pixel BLUE
					led.Write();								//Write pixel, other pixel will be ignored


					std::cout << "Press any key to go on..." << std::endl;
					chr = std::cin.get();

					//Fade from one color to another based on pixel count
					led.Fade(CLed(255, 0, 0), CLed(0, 0, 255));
					led.Write();

					std::cout << "Press any key to go on..." << std::endl;
					chr = std::cin.get();

					//Clear
					led.Clear();								//Clear all pixel (off or "black")
					led.Write();
					led.Disable();
				}
				else
				{
					std::cout << "ERROR: The IO-Warrior28 must have revision 1.0.1.4 or higher" << std::endl;
				}
			}
			else
			{
				std::cout << "ERROR: Please connect only IO-Warrior28 devices for this demo" << std::endl;
			}
		}
		else
		{
			std::cout << "ERROR: Please connect only one IO-Warrior28 for this demo" << std::endl;
		}
	}
	else
	{
		std::cout << "No IO-Warrior found on USB" << std::endl;
	}

	//Never forget to close at the end!
	IowKitCloseDevice(handle);

	return 0;
}
