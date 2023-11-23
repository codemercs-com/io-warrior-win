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

		#Create report to read via special mode "Pin Status". This will return a report each time with the actual status
		report = IOWKIT_SPECIAL_REPORT(
									0xFF, # reportID
									0x00, 
									0x00, 
									0x00, 
									0x00,
									0x00,
									0x00,
									0x00 
									)
		#Read the pin status via special mode.
		if iowkit.IowKitWrite(ioHandle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT_SPECIAL_REPORT_SIZE) == IOWKIT_SPECIAL_REPORT_SIZE:
			if iowkit.IowKitRead(ioHandle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT_SPECIAL_REPORT_SIZE) == IOWKIT_SPECIAL_REPORT_SIZE:
				# report[0] -> ReportID
				print("Product ID: {0:02x} {1:02x} {2:02x} {3:02x} {4:02x}".format(report[0], report[1], report[2], report[3], report[4]))
			else:
				print("Error during read")
		else:
			print("Error during write")
	else:
		print ("No IO-Warrior40 found")
	
else:
	print ("No IO-Warrior found")

# DON'T FORGETT TO CLOSE AT THE END OF THE SCRIPT!!!!!
iowkit.IowKitCloseDevice(ioHandle)