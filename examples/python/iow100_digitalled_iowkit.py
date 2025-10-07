import ctypes, sys
from includes.iowkit import *

# Open iowkit.dll
ioHandle = iowkit.IowKitOpenDevice()

if ioHandle != 0:

    pid = iowkit.IowKitGetProductId(ioHandle)

    if pid == IOWKIT_PRODUCT_ID_IOW100:
        revision = iowkit.IowKitGetRevision(ioHandle)
        print ("Revision: ", format(revision, 'x'))

        serial = ctypes.create_unicode_buffer("00000000")
        IowKit_SerNumb = iowkit.IowKitGetSerialNumber(ioHandle, serial)
        print ("Serial: ", str(serial.value))

        status = iowkit.IowKitSetTimeout(ioHandle, ctypes.c_ulong(1000))

        #Set the default settings for WS2812 
        report = IOWKIT100_SPECIAL_REPORT(
            0x28, #report_ID
            0x01, #enable
            0x3C, #timing
            0x13, #timing
            0x3C, #timing
            0x26, #timing
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00
        )
       

        status = iowkit.IowKitWrite(ioHandle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT100_SPECIAL_REPORT_SIZE)


        #Set 1st three digital LEDs to RGB
        report = IOWKIT100_SPECIAL_REPORT(
            0x29, #report_ID
            0x80, #block
            0x03, 0x00,#LED count
            0xFF, 0x00, 0x00, #led data for 1st LED RGB
            0x00, 0xFF, 0x00, #led data for 2nd LED RGB
            0x00, 0x00, 0xFF, #led data for 3rd LED RGB
            0x00, 0x00, 0x00, #led data for 4th LED RGB
            0x00, 0x00, 0x00, #...
            0x00, 0x00, 0x00,
            0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00  
            )

        status = iowkit.IowKitWrite(ioHandle, IOW_PIPE_SPECIAL_MODE, ctypes.byref(report), IOWKIT100_SPECIAL_REPORT_SIZE)

    else:
        print("No IO-Warrior100 found")

else:
    print('No Device')

# Don't forget to close !
iowkit.IowKitCloseDevice(ioHandle)
print ("Close iowkit, Exit")