# iowkit definitions and declarations -----------------------------------------
# using CodeMerc doc: IO-Warrior Dynamic Library V1.6 for Windows

import ctypes, os

try:
	iowkit = ctypes.WinDLL(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'iowkit'))
except:
	try:
		iowkit = ctypes.WinDLL(os.path.join(os.curdir, 'iowkit'))
	except:
		iowkit = ctypes.WinDLL('iowkit')

# IOWKIT_HANDLE IOWKIT_API IowKitOpenDevice(void);
iowkit.IowKitOpenDevice.argtypes        = None
iowkit.IowKitOpenDevice.restype         = ctypes.c_voidp

# void IOWKIT_API IowKitCloseDevice(IOWKIT_HANDLE devHandle); # devhandle ignored
# void IOWKIT_API IowKitCloseDevice(void);    # allowed also; compare with open
iowkit.IowKitCloseDevice.argtypes       = [ctypes.c_voidp]
iowkit.IowKitCloseDevice.restype        = None

# IOWKIT_HANDLE IOWKIT_API IowKitGetDeviceHandle(ULONG numDevice);
iowkit.IowKitGetDeviceHandle.argtypes   = [ctypes.c_ulong]  # numDev = 1 ... 16
iowkit.IowKitGetDeviceHandle.restype    = ctypes.c_voidp

# ULONG IOWKIT_API IowKitGetNumDevs(void);
iowkit.IowKitGetNumDevs.argtypes        = None
iowkit.IowKitGetNumDevs.restype         = ctypes.c_ulong

# PCHAR IOWKIT_API IowKitVersion(void);
# res like: IO-Warrior Kit V1.5
iowkit.IowKitVersion.argtypes           = None
iowkit.IowKitVersion.restype            = ctypes.c_char_p

# ULONG IOWKIT_API IowKitProductId(IOWKIT_HANDLE iowHandle);
# res like: 0x1501
iowkit.IowKitGetProductId.argtypes      = [ctypes.c_voidp]
iowkit.IowKitGetProductId.restype       = ctypes.c_ulong

# ULONG IOWKIT_API IowKitGetRevision(IOWKIT_HANDLE iowHandle);
# res like: 0x1030
iowkit.IowKitGetRevision.argtypes       = [ctypes.c_voidp]
iowkit.IowKitGetRevision.restype        = ctypes.c_ulong

# BOOL IOWKIT_API IowKitSetTimeout(IOWKIT_HANDLE devHandle, ULONG timeout);
iowkit.IowKitSetTimeout.argtypes        = [ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitSetTimeout.restype         = ctypes.c_bool

# BOOL IOWKIT_API IowKitSetWriteTimeout(IOWKIT_HANDLE devHandle, ULONG timeout);
iowkit.IowKitSetWriteTimeout.argtypes   = [ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitSetWriteTimeout.restype    = ctypes.c_bool

# ULONG IOWKIT_API IowKitWrite(IOWKIT_HANDLE devHandle, ULONG numPipe, PCHAR buffer, ULONG length);
iowkit.IowKitWrite.argtypes             = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitWrite.restype              = ctypes.c_ulong

# ULONG IOWKIT_API IowKitRead(IOWKIT_HANDLE devHandle, ULONG numPipe, PCHAR buffer, ULONG length);
iowkit.IowKitRead.argtypes              = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
iowkit.IowKitRead.restype               = ctypes.c_ulong

# ULONG IOWKIT_API IowKitReadNonBlocking(IOWKIT_HANDLE devHandle, ULONG numPipe, PCHAR buffer, ULONG length);
#NOT WORKING with python. Don't know why :(
#iowkit.IowKitReadNonBlocking.argtypes   = [ctypes.c_voidp, ctypes.c_ulong, ctypes.c_voidp, ctypes.c_ulong]
#iowkit.IowKitReadNonBlocking.restype    = ctypes.c_ulong

# BOOL IOWKIT_API IowKitReadImmediate(IOWKIT_HANDLE devHandle, PDWORD value);
# Return current value directly read from the IO-Warrior I/O pins.
iowkit.IowKitReadImmediate.argtypes     = [ctypes.c_voidp, ctypes.POINTER(ctypes.c_ulong)]
iowkit.IowKitReadImmediate.restype      = ctypes.c_bool

# BOOL IOWKIT_API IowKitGetSerialNumber(IOWKIT_HANDLE iowHandle, PWCHAR serialNumber);
# from iowkit.h:
# typedef unsigned short *       PWCHAR;
# from library docu:
# "The serial number is represented as an Unicode string. The buffer pointed to
# by serialNumber must be big enough to hold 9 Unicode characters (18 bytes),
# because the string is terminated in the usual C way with a 0 character."
#
# Originally suggested code fails:
# iowkit.IowKitGetSerialNumber.argtypes  = [ctypes.c_voidp, ctypes.c_wchar_p]
# It results in Python crashing on conversion of c_wchar_p, probably because
# the implicit conversion of Python3 expects 4 bytes per unicode char, while
# the iowlibrary uses only 2.
# Workaround is a string buffer of length 18 and the conversion is per
# buffer.raw.decode("utf-8")
iowkit.IowKitGetSerialNumber.argtypes   = [ctypes.c_voidp, ctypes.c_voidp] # ok
iowkit.IowKitGetSerialNumber.restype    = ctypes.c_bool


# Max number of IOW devices in system = 16
IOWKIT_MAX_DEVICES                      = ctypes.c_ulong(16)

# Max number of pipes per IOW device = 2
IOWKIT_MAX_PIPES                        = ctypes.c_ulong(4)

# pipe names
IOW_PIPE_IO_PINS                        = ctypes.c_ulong(0)
IOW_PIPE_SPECIAL_MODE                   = ctypes.c_ulong(1) # use for I2C for Iow24/40/56
IOW_PIPE_I2C_MODE                       = ctypes.c_ulong(2) #use for I2C for Iow28/Iow100
IOW_PIPE_ADC_MODE                   	= ctypes.c_ulong(3) # use for ADC for Iow28/Iow100

# IO-Warrior vendor & product IDs
IOWKIT_VENDOR_ID                        = 0x07c0
# IO-Warrior 40 (discontinued 2019)
IOWKIT_PRODUCT_ID_IOW40                 = 0x1500
# IO-Warrior 24 (discontinued 2019)
IOWKIT_PRODUCT_ID_IOW24                 = 0x1501
IOWKIT_PRODUCT_ID_IOW24_SENSI           = 0x158A
# IO-Warrior PowerVampire (discontinued 2019)
IOWKIT_PRODUCT_ID_IOWPV1                = 0x1511
IOWKIT_PRODUCT_ID_IOWPV2                = 0x1512
# IO-Warrior 56
IOWKIT_PRODUCT_ID_IOW56                 = 0x1503
IOWKIT_PRODUCT_ID_IOW56_ALPHA           = 0x158B
# IO-Warrior 28
IOWKIT_PRODUCT_ID_IOW28                 = 0x1504
# IO-Warrior 28L
IOWKIT_PRODUCT_ID_IOW28L                = 0x1505
# IO-Warrior 100
IOWKIT_PRODUCT_ID_IOW100                 = 0x1506

# IOW Legacy devices open modes
IOW_OPEN_SIMPLE                         = ctypes.c_ulong(1)
IOW_OPEN_COMPLEX                        = ctypes.c_ulong(2)

# Report structur and size
# First byte represent the reportID, others data

# IO interface fir IOW40
IOWKIT40_IO_REPORT                      = ctypes.c_ubyte * 5
IOWKIT40_IO_REPORT_SIZE 				= 5

# IO interface fir IOW24
IOWKIT24_IO_REPORT                      = ctypes.c_ubyte * 3
IOWKIT24_IO_REPORT_SIZE 				= 3

# Special mode interace for IOW24 and IOW40
IOWKIT_SPECIAL_REPORT                   = ctypes.c_ubyte * 8
IOWKIT_SPECIAL_REPORT_SIZE              = 8

# IO interface for IOW56
IOWKIT56_IO_REPORT                      = ctypes.c_ubyte * 8
IOWKIT56_IO_REPORT_SIZE 				= 8

# Special mode interace for IOW56
IOWKIT56_SPECIAL_REPORT                 = ctypes.c_ubyte * 64
IOWKIT56_SPECIAL_REPORT_SIZE 			= 64

# IO interface for IOW28
IOWKIT28_IO_REPORT                      = ctypes.c_ubyte * 8
IOWKIT28_IO_REPORT_SIZE 				= 8

# Special mode, i2c and adc interace for IOW28
IOWKIT28_SPECIAL_REPORT                 = ctypes.c_ubyte * 64 #use for special mode, I2C, and ADC
IOWKIT28_SPECIAL_REPORT_SIZE 			= 64

# IO interface for IOW100
IOWKIT100_IO_REPORT                     = ctypes.c_ubyte * 13
IOWKIT100_IO_REPORT_SIZE 				= 13

# Special mode, i2c and adc interace for IOW100
IOWKIT100_SPECIAL_REPORT                = ctypes.c_ubyte * 64 #use for special mode, I2C, and ADC
IOWKIT100_SPECIAL_REPORT_SIZE 			= 64
#
# end iowkit definitions and declarations -------------------------------------