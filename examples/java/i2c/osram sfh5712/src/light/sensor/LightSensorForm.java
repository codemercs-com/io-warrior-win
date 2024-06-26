/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package light.sensor;
import com.codemercs.iow.*;
import java.util.Timer;
import javax.swing.JOptionPane;
/**
 *
 * @author christoph
 */
public class LightSensorForm extends javax.swing.JFrame {
    
    
    /** Constant for the ProductId of an IOWarrior40 */
    public static final long PID_IOW40 = 0x1500L;
    /** Constant for the ProductId of an IOWarrior24 */
    public static final long PID_IOW24 = 0x1501L;
    /** Constant for the ProductId of an IOWarrior56 */
    public static final long PID_IOW56 = 0x1503L;
    /** Constant for the IO-Pipe */
    public static final long IOW_PIPE_IO_PINS = 0;
    /** Constant for the Specialmode-Pipe */
    public static final long IOW_PIPE_SPECIAL_MODE = 1;
    
    
    public long handle;
    public Timer timer;
    
    
    public LightSensorForm() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        button_connect = new javax.swing.JButton();
        label_device = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        label_serial = new javax.swing.JLabel();
        label_light = new javax.swing.JLabel();
        button_timer = new javax.swing.JButton();
        button_stop = new javax.swing.JButton();
        filler1 = new javax.swing.Box.Filler(new java.awt.Dimension(0, 0), new java.awt.Dimension(0, 0), new java.awt.Dimension(0, 32767));

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        jLabel1.setText("Device:");

        button_connect.setText("Connect");
        button_connect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                button_connectActionPerformed(evt);
            }
        });

        label_device.setText("No Device");
        label_device.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.RAISED));

        jLabel3.setText("Serial No.:");

        label_serial.setText("00000000");
        label_serial.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.RAISED));

        label_light.setBackground(new java.awt.Color(255, 255, 255));
        label_light.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
        label_light.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        label_light.setText("0 Lux");
        label_light.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        button_timer.setText("Start");
        button_timer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                button_timerActionPerformed(evt);
            }
        });

        button_stop.setText("Stop");
        button_stop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                button_stopActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(0, 0, Short.MAX_VALUE)
                .addComponent(button_connect)
                .addGap(18, 18, 18)
                .addComponent(button_timer)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(button_stop)
                .addGap(49, 49, 49))
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(label_light, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(label_device, javax.swing.GroupLayout.PREFERRED_SIZE, 105, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(label_serial, javax.swing.GroupLayout.DEFAULT_SIZE, 84, Short.MAX_VALUE)))
                .addContainerGap())
            .addComponent(filler1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(button_connect)
                    .addComponent(button_timer)
                    .addComponent(button_stop))
                .addGap(26, 26, 26)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(label_device)
                    .addComponent(jLabel3)
                    .addComponent(label_serial))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(filler1, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(label_light)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void button_connectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_button_connectActionPerformed
        
        handle = IowKit.openDevice();
        long pid;
        String sn;
        int[] writeBuffer = new int[8]; //Report structure, 0-> ReportID, 1-7 -> Data
        int[] readBuffer = new int[8];
        
        if(handle != 0)
        {
            pid = IowKit.getProductId(handle);      //Get ProductID
            if(pid == PID_IOW40) label_device.setText("IO-Warrior40");
            if(pid == PID_IOW24) label_device.setText("IO-Warrior24");
            if(pid == PID_IOW56) label_device.setText("IO-Warrior56");
            
            sn = IowKit.getSerialNumber(handle);    //Get SerialNo
            label_serial.setText(sn);
            
            writeBuffer[0] = 0x01;  //Special-Mode I2C
            writeBuffer[1] = 0x01;  //Enable
            writeBuffer[2] = 0x00;  //Flags
            writeBuffer[3] = 0x00;  //Timeout
            IowKit.write(handle, IOW_PIPE_SPECIAL_MODE, writeBuffer);   //Write
        }
    }//GEN-LAST:event_button_connectActionPerformed

    private void button_timerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_button_timerActionPerformed
            
        int[] writeBuffer = new int[8];
        int[] readBuffer = new int[8];
                   
        //Enable Light Senror
        writeBuffer[0] = 0x02;  //Write I2C
        writeBuffer[1] = 0xC3;  //Start + Stop, 3 data bytes
        writeBuffer[2] = 0x52;  //device address
        writeBuffer[3] = 0x80;  //Controlregister of sensor
        writeBuffer[4] = 0x03;  //mode-> active
        IowKit.write(handle, IOW_PIPE_SPECIAL_MODE, writeBuffer);
        readBuffer = IowKit.read(handle, IOW_PIPE_SPECIAL_MODE, 8); //Swallow ACK Report
        
        if(readBuffer[1] != 0x80) //Write successfully
        {
            //Set Timer
            timer = new Timer();  
            LoopTimer lTimer = new LoopTimer(this);
            lTimer.deviceHandle = handle;   //Send IO-Warrior handle to LoopTimer-Class
            lTimer.timer = timer;   //Send timer handle to LoopTimer-Class
            timer.schedule(lTimer, 0, 1000);    //Set Timer
        }
        else
            JOptionPane.showMessageDialog(null, "Write not successfully", "Error: Write", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_button_timerActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        IowKit.closeDevice(handle);
    }//GEN-LAST:event_formWindowClosing

    private void button_stopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_button_stopActionPerformed
        timer.cancel();
        
        int[] writeBuffer = new int[8];
        int[] readBuffer = new int[8];
                   
        //Disable Light Senror
        writeBuffer[0] = 0x02;  //Write I2C
        writeBuffer[1] = 0xC3;  //Start + Stop, 3 data bytes
        writeBuffer[2] = 0x52;  //device address
        writeBuffer[3] = 0x80;  //Controlregister of sensor
        writeBuffer[4] = 0x00;  //mode-> active
        IowKit.write(handle, IOW_PIPE_SPECIAL_MODE, writeBuffer);
        readBuffer = IowKit.read(handle, IOW_PIPE_SPECIAL_MODE, 8); //Swallow ACK Report
    }//GEN-LAST:event_button_stopActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(LightSensorForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(LightSensorForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(LightSensorForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(LightSensorForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new LightSensorForm().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton button_connect;
    private javax.swing.JButton button_stop;
    private javax.swing.JButton button_timer;
    private javax.swing.Box.Filler filler1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel label_device;
    public javax.swing.JLabel label_light;
    private javax.swing.JLabel label_serial;
    // End of variables declaration//GEN-END:variables
}
