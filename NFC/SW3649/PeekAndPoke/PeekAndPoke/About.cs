using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PeekAndPoke
{
    public partial class About : Form
    {
        private bool form96 = false;
        private bool form120 = false;

        /// <summary>
        ///Now we have to distinguish between the three different kind of windows form size (96 = smaller, 120 = medium, 144 = large)
        /// </summary>
        protected int WinForm()
        {
            float dpiX;
            Graphics graphics = this.CreateGraphics();
            dpiX = graphics.DpiX;
            return (int)dpiX;
        }

        /// <summary>
        ///This function sets the current value for windows form
        /// </summary>
        protected void DetectForm()
        {
            int value = WinForm();
            switch (value)
            {
                case 96: form96 = true; break;
                case 120: form120 = true; break;
            }
        }

        public About()
        {
            DetectForm();
            if (form120)
            {
                InitializeComponent120();
            }
            else
            {
                InitializeComponent96();
            }

            this.label1.Text = System.Reflection.Assembly.GetEntryAssembly().GetName().Version.ToString();
            this.label2.Text = "";
        }

        public About(String FWVersion)
        {
            DetectForm();
            if (form120)
            {
                InitializeComponent120();
            }
            else
            {
                InitializeComponent96();
            }

            this.label1.Text = System.Reflection.Assembly.GetEntryAssembly().GetName().Version.ToString();
            this.label2.Text = FWVersion;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
