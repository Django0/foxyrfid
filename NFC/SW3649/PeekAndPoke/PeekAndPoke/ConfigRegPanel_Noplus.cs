using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NTAG_I2C.Contracts;

namespace PeekAndPoke
{
    public partial class ConfigRegPanel_Noplus : Form
    {
        private NtagI2CDevice myDevice;
        private byte I2CAddress;
        private byte address;
        private byte[] registers;
        private Label logging;

        public ConfigRegPanel_Noplus()
        {
            InitializeComponent();

            myInitializeComponent();

            this.readConfig_Btn.PerformClick();
        }

        public ConfigRegPanel_Noplus(NtagI2CDevice device, byte I2CAddress, byte address, byte[] registers, Label loggingLbl)
        {
            InitializeComponent();

            this.myDevice = device;
            this.I2CAddress = I2CAddress;
            this.address = address;
            this.registers = registers;
            this.logging = loggingLbl;
            myInitializeComponent();
            this.Shown += new EventHandler(this.readConfigRegAndShow);
        }

        private void myInitializeComponent()
        {            
            this.FD_OFF_Combo.SelectedIndex = 0;            
            this.FD_ON_Combo.SelectedIndex = 0;
          
            this.NC_REG_Box.Text += this.address.ToString("X2") + ":0";
            this.LAST_NDEF_BLOCK_Box.Text += this.address.ToString("X2") + ":1";
            this.WDT_Box.Text += this.address.ToString("X2") + ":[4:3]";
            this.I2C_CLOCK_STR_Box.Text += this.address.ToString("X2") + ":5";
            this.SRAM_MIRROR_Box.Text += this.address.ToString("X2") + ":2";
            this.REG_LOCK_Box.Text += this.address.ToString("X2") + ":6";
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////// Buttons ///////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void readConfigRegAndShow(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte[] readRegisters;
                String log;
                I2CError error;

                // Read the WDT_LS register
                error = this.myDevice.readBlock(this.I2CAddress, this.address, out readRegisters, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    for (int i = 0; i < this.registers.Length; i++)
                        this.registers[i] = readRegisters[i];

                    // Update the GUI
                    // NC_REG
                    this.I2C_RST_CheckBox.Checked = (readRegisters[(int)ConfigReg.NC_REG] & 0x80) == 0x80; // I2C_RST_ON_OFF
                    this.PTHRU_CheckBox.Checked = (readRegisters[(int)ConfigReg.NC_REG] & 0x40) == 0x40; // PTHRU_ON_OFF
                    this.FD_OFF_Combo.SelectedIndex = (readRegisters[(int)ConfigReg.NC_REG] & 0x30) >> 4;  // FD_OFF
                    this.FD_ON_Combo.SelectedIndex = (readRegisters[(int)ConfigReg.NC_REG] & 0x0C) >> 2;  // FD_ON
                    this.SRAM_MIRROR_CheckBox.Checked = (readRegisters[(int)ConfigReg.NC_REG] & 0x02) == 0x02; // SRAM_MIRROR_ON_OFF
                    this.Transfer_DIR_Checkbox.Checked = (readRegisters[(int)ConfigReg.NC_REG] & 0x01) == 0x01; // PTHRU_DIR
                    // I2C_CLOCK_STR
                    this.I2C_CLOCK_EN_Chcekbox.Checked = (readRegisters[(int)ConfigReg.I2C_CLOCK_STR] & 0x01) == 0x01;
                    // LAST_NDEF_BLOCK
                    this.Last_Ndef_Msg_textBox.Text = readRegisters[(int)ConfigReg.LAST_NDEF_BLOCK].ToString("X2");
                    // SRAM_MIRROR_BLOCK
                    this.SRAM_Block_TextBox.Text = readRegisters[(int)ConfigReg.SRAM_MIRROR_BLOCK].ToString("X2");
                    // WDT
                    this.WDT_LS_TextBox.Text = readRegisters[(int)ConfigReg.WDT_LS].ToString("X2");   // WDT_LS
                    this.WDT_MS_TextBox.Text = readRegisters[(int)ConfigReg.WDT_MS].ToString("X2");   // WDT_MS
                    // REG_LOCK
                    this.i2cLocked_CheckBox.Checked = (readRegisters[(int)ConfigReg.REG_LOCK] & 0x02) == 0x02; // I2C_LOCKED
                    this.rfLocked_CheckBox.Checked = (readRegisters[(int)ConfigReg.REG_LOCK] & 0x01) == 0x01; // RF_LOCKED
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        private void writeFormValuesToConfigReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte[] writeRegisters = new byte[NtagI2CDevice.bytesInBlock];
                String log;
                I2CError error;

                // Get the information from the GUI
                // NC_REG
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.I2C_RST_CheckBox.Checked ? 0x80 : 0); // I2C_RST_ON_OFF
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.PTHRU_CheckBox.Checked ? 0x40 : 0); // PTHRU_ON_OFF
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.FD_OFF_Combo.SelectedIndex << 4); // FD_OFF
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.FD_ON_Combo.SelectedIndex << 2); // FD_ON
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.SRAM_MIRROR_CheckBox.Checked ? 0x02 : 0); // SRAM_MIRROR_ON_OFF
                writeRegisters[(int)ConfigReg.NC_REG] += (byte)(this.Transfer_DIR_Checkbox.Checked ? 0x01 : 0); // PTHRU_DIR
                // I2C_CLOCK_STR
                writeRegisters[(int)ConfigReg.I2C_CLOCK_STR] += (byte)(this.I2C_RST_CheckBox.Checked ? 0x01 : 0);
                // LAST_NDEF_BLOCK
                writeRegisters[(int)ConfigReg.LAST_NDEF_BLOCK] = Utils.HexToByte(this.Last_Ndef_Msg_textBox.Text);
                // SRAM_MIRROR_BLOCK
                writeRegisters[(int)ConfigReg.SRAM_MIRROR_BLOCK] = Utils.HexToByte(this.SRAM_Block_TextBox.Text);
                // WDT
                writeRegisters[(int)ConfigReg.WDT_LS] = Utils.HexToByte(this.WDT_LS_TextBox.Text);    // WDT_LS
                writeRegisters[(int)ConfigReg.WDT_MS] = Utils.HexToByte(this.WDT_MS_TextBox.Text);    // WDT_MS
                // REG_LOCK
                writeRegisters[(int)ConfigReg.REG_LOCK] += (byte)(this.i2cLocked_CheckBox.Checked ? 0x02 : 0); // I2C_LOCKED
                writeRegisters[(int)ConfigReg.REG_LOCK] += (byte)(this.rfLocked_CheckBox.Checked ? 0x01 : 0); // RF_LOCKED

                // Check if the user has set to 1 any of the REG_LOCK bits
                DialogResult result = DialogResult.OK;
                if (writeRegisters[(int)ConfigReg.REG_LOCK] != 0x00)
                    result = MessageBox.Show("Changing the I²C Lock bit is not reversible. Press 'Cancel' to terminate lock, or 'OK' to continue",
                        "Confirm", MessageBoxButtons.OKCancel);

                if (result == DialogResult.OK)
                {
                        // Write the register
                        error = this.myDevice.writeBlock(this.I2CAddress, this.address, writeRegisters, out log);

                        this.logging.Text = log;

                        if (error == I2CError.Success)
                        {
                            // Update the byte array
                            for (int i = 0; i < this.registers.Length; i++)
                                this.registers[i] = writeRegisters[i];
                        }
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////// GUI changes /////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void show_I2C_CLOCK_STR_Value(object sender, EventArgs e)
        {
            this.I2C_CLOCK_EN_Chcekbox.Text = "I2C_CLOCK_STR: ";
            this.I2C_CLOCK_EN_Chcekbox.Text += this.I2C_CLOCK_EN_Chcekbox.Checked ? "Enabled" : "Disabled";
        }
        
        private void show_WDT_MS_Value(object sender, EventArgs e)
        {
            // Obtain the watchdog time-out value
            double timeOutValue = ((((int)Utils.HexToByte(this.WDT_MS_TextBox.Text)) << 8) + Utils.HexToByte(this.WDT_LS_TextBox.Text));
            timeOutValue /= 106;
            this.watchDog_Label.Text = "Watchdog time-out: " + timeOutValue.ToString("0.000", System.Globalization.CultureInfo.CreateSpecificCulture("en-US")) + " ms";
        }

        private void show_WDT_LS_Value(object sender, EventArgs e)
        {
            // Obtain the watchdog time-out value
            double timeOutValue = ((((int)Utils.HexToByte(this.WDT_MS_TextBox.Text)) << 8) + Utils.HexToByte(this.WDT_LS_TextBox.Text));
            timeOutValue /= 106;
            this.watchDog_Label.Text = "Watchdog time-out: " + timeOutValue.ToString("0.000", System.Globalization.CultureInfo.CreateSpecificCulture("en-US")) + " ms";
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////// Info buttons ////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void show_NC_REG_Info(object sender, EventArgs e)
        {
            MessageBox.Show("I2C_RST_ON_OFF: Enables soft reset through I²C repeated start\r\n\r\n" +

                "PTHRU_ON_OFF: Enables data transfer use of SRAM\r\n\r\n" +

                "FD_OFF: defines the event upon which the signal output on the FD pin is brought up\r\n" +
                "00b: if the field is switched off\r\n" +
                "01b: if the field is switched off or the tag is set to the HALT state\r\n" +
                "10b: if the field is switched off or the last page of the NDEF message has been read (defined in LAST_NDEF_BLOCK)\r\n" +
                "11b: (if FD_ON = 11b) if the field is switched off or if last data is read by I²C\r\n" +
                "(in Pass-through mode RF --> I²C) or last data is written by I²C (in Pass-through mode I²C --> RF)\r\n" +
                "11b: (if FD_ON= 00b or 01b or 10b), if the field is switched off\r\n\r\n" +

                "FD_ON: defines the event upon which the signal output on the FD pin is brought down\r\n" +
                "00b: by field presence\r\n" +
                "01b: by first valid Start-of-Frame (SoF)\r\n" +
                "10b: by selection of the tag\r\n" +
                "11b: (in Pass-though mode RF--> I²C) if the data is ready to be read from the I²C interface\r\n" +
                "11b: (in Pass-though mode I²C--> RF) if the data is read by the RF interface\r\n\r\n" +

                "SRAM_MIRROR_ON_OFF: Enables SRAM mirror mode\r\n\r\n" +

                "PTHRU_DIR: Defines the data flow for the Pass-through mode\r\n" +
                "0b: From I²C to RF interface\r\n" +
                "1b: From RF to I²C interface\r\n" +
                "In case the pass through mode is not enabled:\r\n" +
                "0b: No WRITE access from the RF side",

                "NC_REG byte");
        }

        private void show_I2C_Clock_STR_Info(object sender, EventArgs e)
        {
            MessageBox.Show("I2C_CLOCK_STR: Enables (1b) or disables (0b) the I²C clock stretching", "I2C_CLOCK_STR byte (0xFE:5)");
        }

        private void show_LAST_NDEF_Block_Info(object sender, EventArgs e)
        {
            MessageBox.Show("Address of last BLOCK NDEF message\r\n" +
                "1h is page 4h (first page of User Memory)\r\n" +
                "2h is page 8h\r\n" +
                "3h is page Ch\r\n" +
                "....\r\n" +
                "74h is page 1D0h (last page possible of the User Memory)",

                "LAST_NDEF_BLOCK byte");
        }

        private void show_SRAM_Block_Info(object sender, EventArgs e)
        {
            MessageBox.Show("SRAM mirror lower page address in 4 page granularity\r\n" +
                "1h is page 4h (first page of User Memory)\r\n" +
                "2h is page 8h\r\n" +
                "3h is page Ch\r\n" +
                "....\r\n" +
                "74h is page 1D0h (last page possible of the User Memory)",

                "SRAM_MIRROR_ADDR byte");
        }

        private void show_WDT_Info(object sender, EventArgs e)
        {
            MessageBox.Show("Since it is possible that the host can keep the I²C bus 'locked' for a longer period, it is " +
                "possible to program a watchdog timer to unlock the I²C host from the tag, so that the RF " +
                "reader can access the tag. The host itself will not be notified of this event directly, but the " +
                "NS_REG register is updated accordingly (the register bit I2C_LOCKED will be cleared.\r\n\r\n" +

                "The default value is set to 20 ms (848h), but the watch dog timer can be freely set from " +
                "0001h (9.43 us) up to FFFFh (617.995 ms). The timer starts ticking when the " +
                "communication between the NTAG I²C and the I²C interface starts. In case the " +
                "communication with the I²C is still going on after the watchdog timer expires, the " +
                "communication will continue until the communication has completed. Then the status " +
                "register I2C_LOCKED will be immediately cleared.",

                "Watchdog Timer bytes");
        }

        private void show_NS_REG_Info(object sender, EventArgs e)
        {
            MessageBox.Show("I2C_LOCKED: Disables configuration byte access from I²C\r\n\r\n" +

                "RF_LOCKED: Disables Configuration bytes access from RF",

                "NS_REG byte");
        }


    }
}
