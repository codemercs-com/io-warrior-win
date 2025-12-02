from iow100_lcd import IOW100_LCD

device = IOW100_LCD(vendor_id=0x7C0, product_id=0x1506, interface_number=1)

try:
    device.connect()
    device.enable(0x01) # Enable LCD-Mode

    """ init HD44780 """
    device.write([0x20 | 0x10 | 0x08 | 0x04]) # ???
    device.write([0x08 | 0x04 | 0x02 | 0x01]) # Display on, Cursor on and blinking cursor
    device.write([IOW100_LCD.LCD_CLEAR]) # Clear display
    device.write([IOW100_LCD.LCD_HOME]) # Return home position

    """ Write something on LCD """
    device.write_string("Hallo Welt")

    """ Go to the first position """
    device.write([0x80]) # Set DDRAM pos to 0x00 

finally:
    device.disconnect()