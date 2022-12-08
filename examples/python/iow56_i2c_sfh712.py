# Sample code for read/write I2C device 'Osram SFH5712 Lux sensor'

import ctypes, sys
from includes.iowkit import *

def EnableI2C(handle, state):
	report = IOWKIT56_SPECIAL_REPORT(
									0x01,  # reportID
									state, #Enable 1, Disable 0
									0x00,  # Flags
									0x00   # Timeout
									)
									
	iowkit.IowKitWrite(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT56_SPECIAL_REPORT_SIZE)
	return

def WriteReport(handle, report):

	read_report = IOWKIT56_SPECIAL_REPORT()

	if iowkit.IowKitWrite(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT56_SPECIAL_REPORT_SIZE) == IOWKIT56_SPECIAL_REPORT_SIZE:
		if iowkit.IowKitRead(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(read_report), IOWKIT56_SPECIAL_REPORT_SIZE) != IOWKIT56_SPECIAL_REPORT_SIZE:
			print("Error during read")
	else:
		print("Error during write")
	
	return read_report

def ReadReport(handle, cmd):

	ret = 0 # return value
	
	# Create two reports
	write_report = IOWKIT56_SPECIAL_REPORT()
	read_report = IOWKIT56_SPECIAL_REPORT()

	# Set read register to read from
	write_report[0] = 0x02 # Write to I2C device
	write_report[1] = 0xC2 # Flags: Start + Stop, 2 bytes of data
	write_report[2] = 0x52 # I2C address (8bit)
	write_report[3] = cmd  # I2C device register to read from

	if iowkit.IowKitWrite(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(write_report), IOWKIT56_SPECIAL_REPORT_SIZE) == IOWKIT56_SPECIAL_REPORT_SIZE:
		if iowkit.IowKitRead(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(write_report), IOWKIT56_SPECIAL_REPORT_SIZE) != IOWKIT56_SPECIAL_REPORT_SIZE:
			print("Error during read")
	else:
		print("Error during write")

	# Read from I2C device
	read_report[0] = 0x03 # Read I2C device
	read_report[1] = 0x01 # Read bytes
	read_report[2] = 0x52 | 0x01 # I2C address + read bit (8bit)

	if iowkit.IowKitWrite(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(read_report), IOWKIT56_SPECIAL_REPORT_SIZE) == IOWKIT56_SPECIAL_REPORT_SIZE:
		if iowkit.IowKitRead(handle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(read_report), IOWKIT56_SPECIAL_REPORT_SIZE) == IOWKIT56_SPECIAL_REPORT_SIZE:
			ret = read_report[2]
		else:
			print("Error during read")
	else:
		print("Error during write")

	return ret

#open iowkit and get first IO-Warrior device
ioHandle = iowkit.IowKitOpenDevice()

#IO-Warrior found and get first handle from IowKitOpenDevice
if ioHandle != 0:


	# set read timeout to 1000 msecs to cancel read operations after time X
	status = iowkit.IowKitSetTimeout(ioHandle, ctypes.c_ulong(1000))

	# init I2C mode
	EnableI2C(ioHandle, 1)

	# init report
	report = IOWKIT56_SPECIAL_REPORT()

	# Enable Osram SFH5712
	report[0] = 0x02; # Write I2C device
	report[1] = 0xC3; # Flags: Start + Stop, 3 bytes of data
	report[2] = 0x52; # I2C address (8bit)
	report[3] = 0x80; # I2C register to write on
	report[4] = 0x03; # data
	WriteReport(ioHandle, report) # igrnore return

	# Read data from I2C device
	lsb = ReadReport(ioHandle, 0x8C)
	msb = ReadReport(ioHandle, 0x8D)

	# Print out result
	print("Lux: {0}".format((msb << 8) | lsb))

	# Disable Osram SFH5712
	report[0] = 0x02; # Write I2C device
	report[1] = 0xC3; # Flags: Start + Stop, 3 bytes of data
	report[2] = 0x52; # I2C address (8bit)
	report[3] = 0x80; # I2C register to write on
	report[4] = 0x00; # data
	WriteReport(ioHandle, report) # igrnore return

	#if we are done with all, disable I2C mode
	EnableI2C(ioHandle, 0)

else:
	print ("No IO-Warrior found")

# DON'T FORGETT TO CLOSE AT THE END OF THE SCRIPT!!!!!
iowkit.IowKitCloseDevice(ioHandle)