# Read from IO-Warrior
There are two different ways to read the IO-Pins.

#### By using IowKitRead()
By default the IowKitRead() function will wait until new data are available on the IO-Pins. This may look like the pgramm is stuck.To cancel a read operation you have to use IowKitSetTimeout(...). 

#### By using IowKitRead() via special mode 0xFF
This read operation will return the actual PIN status immediatly. For this you have to use the special mode "Getting current pin status (0xFF)".
