using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace led_matrix
{
    public partial class Form1 : Form
    {
        public IntPtr handle;
        public int[] blocks = new int[4];
        public int[] rows = new int[8];


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public void SetLedMatrix(int row, int col0, int col1, int col2, int col3)
        {
            //report Structure for IO-Warrior
            byte[] report = new byte[8];

            //Write LED-Matrix at row X with data Y
            report[0] = 0x15;
            report[1] = (byte)row;
            report[2] = (byte)col0;
            report[3] = (byte)col1;
            report[4] = (byte)col2;
            report[5] = (byte)col3;
                
            Functions.IowKitWrite(handle, Defines.IOW_PIPE_SPECIAL_MODE, report, 8);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Functions.IowKitCloseDevice(Handle);
        }

        private void connect_Click(object sender, EventArgs e)
        {
            //Open Device and get first device Handle which found
            handle = Functions.IowKitOpenDevice();

            //Device found?
            if (handle != IntPtr.Zero)
            {
                StringBuilder sn = new StringBuilder();

                //Get ProductID
                uint pid = Functions.IowKitGetProductId(handle);

                //Get serial number
                Functions.IowKitGetSerialNumber(handle, sn);

                //RC5 only works with IO-Warrior24
                if (pid != Defines.IOWKIT_PID_IOW24)
                {
                    MessageBox.Show("No IO-Warrior24 Connected", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    serial.Text = sn.ToString();
                    device.Text = "IO-Warrior24";
                }
            }
            else
            {
                MessageBox.Show("No Device Found", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void init_Click(object sender, EventArgs e)
        {
            //report Structure for IO-Warrior
            byte[] report = new byte[8];

            if (handle != IntPtr.Zero)
            {
                //Enable LED-Matrix Mode
                report[0] = 0x14;
                report[1] = 0x01;
                Functions.IowKitWrite(handle, Defines.IOW_PIPE_SPECIAL_MODE, report, 8);
            }

        }

        private void random_Click(object sender, EventArgs e)
        {
            Random rnd = new Random();

            for (int i = 0; i < 8; i++) //Set Row
            {
                SetLedMatrix(i, rnd.Next(0, 255), rnd.Next(0, 255), rnd.Next(0, 255), rnd.Next(0, 255));
            }
        }

        private void clear_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 8; i++) //Set Row
            {
                SetLedMatrix(i, 0, 0, 0, 0);
            }
        }

        private void img_send_Click(object sender, EventArgs e)
        {
            String text = input_text.Text;
            int length = 0;
            byte[,] data = new byte[8,4];
            
            //Create an image 32x8 Pixel
            Bitmap bitmap = new Bitmap(32, 8);
            Graphics gfx = Graphics.FromImage(bitmap);
            Font drawFont = new Font("System", 6);

            //Fill the image
            Rectangle rect = new Rectangle(0, 0, 32, 8); 
            SolidBrush B_black = new SolidBrush(Color.Black);
            gfx.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixel; //Draw sharp text without shaddow or anti aliasing
            
            gfx.Clear(Color.White);
            gfx.DrawString(text, drawFont, B_black, new PointF(0, 0));
            gfx.Save();
            gfx.Dispose();

            //Get the pixel and create data bytes
            for (int row = 0; row < 8; row++)
            {
                length = 0;
                
                for (int pos = 0; pos < 4; pos++)
                {
                    for (int bit = 0; bit < 8; bit++)
                    {
                        if (bitmap.GetPixel(length, row) == Color.FromArgb(255,0,0,0))
                        {
                            data[row, pos] += (byte)Math.Pow(2, bit);
                        }

                        length++;
                    }
                }
            }

            //Output
            for (int i = 0; i < 8; i++)
            {
                SetLedMatrix(i, data[i, 0], data[i, 1], data[i, 2], data[i, 3]);
            }
        }
    }
}
