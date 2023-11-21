/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package light.sensor;
import com.codemercs.iow.*;
import java.util.Timer;
import java.util.TimerTask;
import static light.sensor.LightSensorForm.IOW_PIPE_SPECIAL_MODE;

/**
 *
 * @author christoph
 */
class LoopTimer extends TimerTask {
    
    public long deviceHandle;
    public int lux;
    public Timer timer;
    
    private LightSensorForm MainForm;
    
    LoopTimer( LightSensorForm form)
    {
        this.MainForm = form;
    }

    public void run()
    {
        int[] writeBuffer = new int[8];
        int[] readBuffer = new int[8];
        
        //Set Read Register
        writeBuffer[0] = 0x02;  //Write I2C
        writeBuffer[1] = 0xC2;  //Start + Stop, 2 data bytes
        writeBuffer[2] = 0x52;  //device address
        writeBuffer[3] = 0x8C;  //LSB of sensor
        IowKit.write(deviceHandle, IOW_PIPE_SPECIAL_MODE, writeBuffer);
        readBuffer = IowKit.read(deviceHandle, IOW_PIPE_SPECIAL_MODE, 8); //Swallow ACK Report
   
        if(readBuffer[1] != 0x80)   //Write successfully?
        {
            //Read
            writeBuffer[0] = 0x03;  //Write I2C
            writeBuffer[1] = 0x02;  //read 1 data bytes
            writeBuffer[2] = 0x52 | 0x01;  //device address and read-bit
            IowKit.write(deviceHandle, IOW_PIPE_SPECIAL_MODE, writeBuffer);
            readBuffer = IowKit.read(deviceHandle, IOW_PIPE_SPECIAL_MODE, 8); //Swallow ACK Report        

            //lux =  (msb << 8) + lsb;
            lux = (readBuffer[3] << 8) + readBuffer[2];

            MainForm.label_light.setText(String.valueOf(lux));
            //System.out.println(lux + " Lux");    
        }
        else
            timer.cancel();
    }
}
