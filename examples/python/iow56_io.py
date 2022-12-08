import time, os, sys
import ctypes

#defines
IOWKIT56_IO_REPORT = ctypes.c_ubyte * 8
IOWKIT56_IO_REPORT_SIZE = 8

IOWKIT56_SPECIAL_REPORT = ctypes.c_ubyte * 64
IOWKIT56_SPECIAL_REPORT_SIZE = 64

SERIAL_NUMBER_BUFFER = ctypes.c_ubyte * 9

#Interfaces
IOW_PIPE_IO_PINS = 0
IOW_PIPE_SPECAIL_MODE = 1

#ProductIDs for IO-Warrior devices
IOWKIT_PRODUCT_ID_IOW40 = 0x1500
IOWKIT_PRODUCT_ID_IOW24 = 0x1501
IOWKIT_PRODUCT_ID_IOW56 = 0x1503


print("Python version: ", sys.version)

#load/find iowkit
try:
	iowkit = ctypes.WinDLL(os.path.join(os.curdir, 'iowkit'))
except:
	try:
		iowkit = ctypes.WinDLL(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'iowkit'))	
	except:
		iowkit = ctypes.WinDLL('iowkit')

#IowKitOpen
iowkit.IowKitOpenDevice.restype = ctypes.c_voidp

#IowKitCloseDevice
iowkit.IowKitCloseDevice.argtypes = [ctypes.c_voidp]

#IowKitWrite()
iowkit.IowKitWrite.argtypes = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitWrite.restype = ctypes.c_ulong

#IowKitRead()
iowkit.IowKitRead.argtypes = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitRead.restype = ctypes.c_ulong

#IowKitReadNonBlocking()
iowkit.IowKitReadNonBlocking.argtypes = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitReadNonBlocking.restype = ctypes.c_ulong

#IowKitReadImediate()
iowkit.IowKitReadImmediate.argtypes = [ctypes.c_voidp, ctypes.POINTER(ctypes.c_ulong)]
iowkit.IowKitReadImmediate.restype = ctypes.c_bool

#IowKitGetNumDevs
iowkit.IowKitGetNumDevs.restype = ctypes.c_ulong

#IowKitGetDeviceHandle
iowkit.IowKitGetDeviceHandle.argtypes = [ctypes.c_ulong]
iowkit.IowKitGetDeviceHandle.restype = ctypes.c_voidp

#IowKitgetProductID
iowkit.IowKitGetProductId.argtypes = [ctypes.c_voidp]
iowkit.IowKitGetProductId.restype = ctypes.c_ulong

#IowKitGetRevision
iowkit.IowKitGetRevision.argtypes = [ctypes.c_voidp]
iowkit.IowKitGetRevision.restype = ctypes.c_ulong

#IowKitGetSerianlNumber
iowkit.IowKitGetSerialNumber.argtypes = [ctypes.c_voidp, ctypes.c_voidp]
iowkit.IowKitGetSerialNumber.restype = ctypes.c_bool

#IowKitSetTimeout
iowkit.IowKitSetTimeout.argtypes = [ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitSetTimeout.restype = ctypes.c_bool

#IowKitSetWriteTimeout
iowkit.IowKitSetWriteTimeout.argtypes = [ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitSetWriteTimeout.restype = ctypes.c_bool

#IowKitVersion
iowkit.IowKitVersion.restype = ctypes.c_char_p


#open iowkit and get first IO-Warrior device
ioHandle = iowkit.IowKitOpenDevice()

#IO-Warrior found and get first handle from IowKitOpenDevice
if ioHandle != 0:
	print("Handle: {0:02x}".format(ioHandle))
	
	#Get number of IO-Warrior
	IowKit_NumbDevs = iowkit.IowKitGetNumDevs()
	print ("NumbDevs: " , str(IowKit_NumbDevs))

	#Get product ID of first IO-Warrior found on USB
	pid = iowkit.IowKitGetProductId(ioHandle)
	print("Product ID: {0:02x}".format(pid))
	
	#Revision
	revision = iowkit.IowKitGetRevision(ioHandle)
	print("Revision: {0:02x}".format(revision))
	
	#Serial
	SerNumb = ctypes.create_unicode_buffer("xxxxxxxx")
	IowKit_SerNumb = iowkit.IowKitGetSerialNumber(ioHandle, SerNumb)
	print ("SerNumb: " , str(SerNumb.value))

	# set read timeout to 1000 msecs
	status = iowkit.IowKitSetTimeout(ioHandle, ctypes.c_ulong(1000))
	
	#Create report. 1x report ID, 7x data bytes
	report = IOWKIT56_IO_REPORT(0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF)

	status = iowkit.IowKitWrite(ioHandle, IOW_PIPE_IO_PINS, ctypes.byref(report), IOWKIT56_IO_REPORT_SIZE)
	
else:
	print ("No IO-Warrior found")

# DON'T FORGETT TO CLOSE AT THE END OF THE SCRIPT!!!!!
iowkit.IowKitCloseDevice(ioHandle)