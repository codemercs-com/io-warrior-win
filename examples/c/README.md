# Examples for C
For each function there will be an example create with Visual Studio but not for all single devices. The functions will be different for the IO-Warrior devices. For example the 'RC5' function will only be supported be the IO-Warrior24 (descontinued). The 'digital LED' function only by IOW28 and IOW100.  
Some of the projects may be older and have to import into the new Visual Studio.  

A list about the supported funtions can be found on the [main readme](https://github.com/codemercs-com/io-warrior-win) page.  

In the 'basic' and 'io' directory will be an example for each IO-Warrior device to show how it works and what the difference is between the devices itself.  


## Differences between the IO-Warrior communication
The main difference between the IO-Warrior is the report size for the communication and the used pipes.
Report size mean how many bytes will be write / read per transcation.  


For example:  
The IO-Warrior24 has 2 byte of data (plus 1 byte report ID) for the IO-Ports,  
The IO-Warrior56 has 7 byte of data (+1).  
You have to set the correct report size. If you have not the transaction will fail.
