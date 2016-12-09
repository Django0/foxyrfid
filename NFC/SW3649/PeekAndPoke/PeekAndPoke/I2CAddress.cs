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
    public partial class I2CAddress : Form
    {
        String oldAddress;
        public String newAddress { get; set; }

        public I2CAddress(String oldAddress)
        {
            InitializeComponent();
            this.oldAddress = oldAddress;
            this.currentAddressTextBox.Text = Convert.ToString(this.oldAddress);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(string.IsNullOrWhiteSpace(this.newAddressTextBox.Text))
            {
                MessageBox.Show("Introduce a valid value");
                this.Close();
            }
            else
            {
                this.newAddress = this.newAddressTextBox.Text;
                this.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        
    }
}
