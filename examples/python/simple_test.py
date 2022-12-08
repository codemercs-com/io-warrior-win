import ctypes, sys
from includes.iowkit import *

# Open iowkit.dll
ioHandle = iowkit.IowKitOpenDevice()

if ioHandle != 0:

    # Get number of IO-Warrior
    numdevs = iowkit.IowKitGetNumDevs()
    print("number of devices: ", numdevs)
    print ("----------\n")

    # Get all IO-Warrior on PC
    for i in range(numdevs):
        subHandle = iowkit.IowKitGetDeviceHandle(i+1)
        pid = iowkit.IowKitGetProductId(subHandle)

        if pid == IOWKIT_PRODUCT_ID_IOW24: print ("Device Type: IO-Warrior24")
        if pid == IOWKIT_PRODUCT_ID_IOW40: print ("Device Type: IO-Warrior40")
        if pid == IOWKIT_PRODUCT_ID_IOW56: print ("Device Type: IO-Warrior56")
        if pid == IOWKIT_PRODUCT_ID_IOW28: print ("Device Type: IO-Warrior28")

        revision = iowkit.IowKitGetRevision(subHandle)
        print ("Revision: ", format(revision, 'x'))

        serial = ctypes.create_unicode_buffer("00000000")
        IowKit_SerNumb = iowkit.IowKitGetSerialNumber(subHandle, serial)
        print ("Serial: ", str(serial.value))

        print ("----------")

else:
    print('No Device')

# Don't forget to close !
iowkit.IowKitCloseDevice(ioHandle)
print ("Close iowkit, Exit")