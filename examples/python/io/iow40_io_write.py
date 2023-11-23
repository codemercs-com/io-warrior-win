import ctypes, sys
sys.path.append("../includes") # Adds include directory above
from iowkit import *


#open iowkit and get first IO-Warrior device
ioHandle = iowkit.IowKitOpenDevice()

#IO-Warrior found and get first handle from IowKitOpenDevice
if ioHandle != 0:
	# set read timeout to 1000 msecs
	status = iowkit.IowKitSetTimeout(ioHandle, ctypes.c_ulong(1000))

	pid = iowkit.IowKitGetProductId(ioHandle)

	if pid == IOWKIT_PRODUCT_ID_IOW40:
	
		#Create report. 1x report ID, 4x data bytes
		report = IOWKIT_SPECIAL_REPORT(
									0x00, # reportID
									0xFF, # Port 0
									0xFF, # Port 1
									0xFF, # Port 2
									0xAA  # Port 3 -> LEDs on IOW40 Starterkit 
									)

		status = iowkit.IowKitWrite(ioHandle, IOW_PIPE_IO_PINS, ctypes.byref(report), IOWKIT40_IO_REPORT_SIZE)
	else:
		print ("No IO-Warrior40 found")
else:
	print ("No IO-Warrior found")

# DON'T FORGETT TO CLOSE AT THE END OF THE SCRIPT!!!!!
iowkit.IowKitCloseDevice(ioHandle)