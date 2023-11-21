package simpleiopackage;
import com.codemercs.iow.*;
import java.util.Random;

public class SimpleIOKlasse {

	public static void main(String[] args) {
		
		long handle = IowKit.openDevice();		//Get first device Handle, which found
		int[] buffer = new int[8];				//Set IO-Port variable (8 is max of iow56)
		long pid = IowKit.getProductId(handle);	//get ProductID
		
		//Get random number for write 
		Random generator = new Random();
		int r = generator.nextInt(255);
		
		/*ProductIds:
		 * 0x1500 -> IO-Warrior40
		 * 0x1501 -> IO-Warrior24 and Dongle
		 * 0x1502 -> IO-Warrior24 PV
		 * 0x1503 -> IO-Warrior56 and Dongle
		 */
		
		if(pid == 0x1500) //IO-Warrior40
		{
			buffer[0] = 0x00;	//ReportID
			buffer[4] = r;		//Starterkit port with LED, Last IO-Port
		}
		
		if(pid == 0x1501)
		{
			buffer[0] = 0x00;	//ReportID
			buffer[2] = r;		//Last IO-Port
		
		}
		if(pid == 0x1503)
		{
			buffer[0] = 0x00;	//ReportID
			buffer[7] = r;		//Last IO-Port
		}
		
		IowKit.write(handle,  0,  buffer);	//Write data to IO-Warrior
		
		IowKit.closeDevice(handle);	//Dont forget to close handle and API

	}

}
