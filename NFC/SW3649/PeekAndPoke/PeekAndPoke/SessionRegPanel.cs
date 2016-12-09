using System;
using System.Windows.Forms;
using NTAG_I2C.Contracts;

namespace PeekAndPoke
{
    public partial class SessionRegPanel : Form
    {
        private NtagI2CDevice myDevice;
        private byte I2CAddress;
        private byte[] registers;
        private Label logging;

        public SessionRegPanel()
        {
            InitializeComponent();

            this.FD_OFF_Combo.SelectedIndex = 0;
            this.FD_ON_Combo.SelectedIndex = 0;
        }

        public SessionRegPanel(NtagI2CDevice device, byte I2CAddress, byte[] registers, Label logging)
        {
            InitializeComponent();

            this.myDevice = device;
            this.I2CAddress = I2CAddress;
            this.registers = registers;

            this.FD_OFF_Combo.SelectedIndex = 0;
            this.FD_ON_Combo.SelectedIndex = 0;

            this.logging = logging;   
            this.Shown += new System.EventHandler(this.readAllRegistersAndShow); 
            
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////// NC_REG ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // If the button Read NC_REG is pressed, the group box is updated with the content of the register
        private void updateRead_NC_REG(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;
                byte[] registers;

                error = this.myDevice.readSessionRegisters(this.I2CAddress, TagType.NTAG2K, out registers, out log);
                readRegister = registers[(int)SessionReg.NC_REG];
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.NC_REG] = readRegister;

                    // Update the GUI
                    this.I2C_RST_CheckBox.Checked = (readRegister & 0x80) == 0x80; // NFCS_I2C_RST_ON_OFF
                    this.PTHRU_CheckBox.Checked = (readRegister & 0x40) == 0x40; // PTHRU_ON_OFF
                    this.FD_OFF_Combo.SelectedIndex = (readRegister & 0x30) >> 4;  // FD_OFF
                    this.FD_ON_Combo.SelectedIndex = (readRegister & 0x0C) >> 2;  // FD_ON
                    this.SRAM_MIRROR_Checkbox.Checked = (readRegister & 0x02) == 0x02; // SRAM_MIRROR_ON_OFF
                    this.Transfer_DIR_Checkbox.Checked = (readRegister & 0x01) == 0x01; // PTHRU_DIR
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the button Write NC_REG is pressed, the content in the group box is writen to the register
        private void write_NC_REF(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte writeRegister = 0;
                String log;
                I2CError error;

                // Get the information from the GUI
                writeRegister += (byte)(this.I2C_RST_CheckBox.Checked ? 0x80 : 0); // NFCS_I2C_RST_ON_OFF
                writeRegister += (byte)(this.PTHRU_CheckBox.Checked ? 0x40 : 0); // PTHRU_ON_OFF
                writeRegister += (byte)(this.FD_OFF_Combo.SelectedIndex << 4); // FD_OFF
                writeRegister += (byte)(this.FD_ON_Combo.SelectedIndex << 2); // FD_ON
                writeRegister += (byte)(this.SRAM_MIRROR_Checkbox.Checked ? 0x02 : 0); // SRAM_MIRROR_ON_OFF
                writeRegister += (byte)(this.Transfer_DIR_Checkbox.Checked ? 0x01 : 0); // PTHRU_DIR

                byte[] registers;
 
                var res = this.myDevice.readSessionRegisters(this.I2CAddress, TagType.NTAG2K, out registers, out log);
                registers[(int)SessionReg.NC_REG] = writeRegister;
                error = this.myDevice.writeSessionRegisters(this.I2CAddress, registers, out log);
                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.NC_REG] = writeRegister;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // Shows information about the NC_REG register
        private void showNC_REG_Info(object sender, EventArgs e)
        {
            MessageBox.Show("NFCS_I2C_RST_ON_OFF: Enables NFC Silence mode and soft reset through I²C repeated start\r\n\r\n" +

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
                
                "NC_REG byte (0xFE:0)");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////// I2C_CLOCK_STR ////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // If the button Read I2C_STR is pressed, the I2C_CLOCK_STR group box is updated with the content of the register
        private void updateRead_I2C_STR(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;

                // Read the register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.I2C_CLOCK_STR, out readRegister, out log);

                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.I2C_CLOCK_STR] = readRegister;

                    // Update the GUI
                    this.I2C_Clock_EN_ChckB.Checked = (readRegister & 0x01) == 0x01;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the I2C_CLOCK_STR check box is changed, its text is changed
        private void updateI2C_CLOCK_STR_ChckChanged(object sender, EventArgs e)
        {
            this.I2C_Clock_EN_ChckB.Text = "I2C_CLOCK_STR: ";
            this.I2C_Clock_EN_ChckB.Text += this.I2C_Clock_EN_ChckB.Checked ? "Enabled" : "Disabled";
        }

        // Shows information about the I2C_CLOCK_STR register
        private void showI2C_CLOCK_STR_Info(object sender, EventArgs e)
        {
            MessageBox.Show("I2C_CLOCK_STR: Enables (1b) or disables (0b) the I²C clock stretching", "I2C_CLOCK_STR byte (0xFE:5)");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////// LAST_NDEF_BLOCK ///////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // If the button Read NDEF is pressed, the LAST_NDEF_BLOCK group box is updated with the content of the register
        private void updateLAST_Ndef_Block(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;

                // Read the register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.LAST_NDEF_BLOCK, out readRegister, out log);

                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.LAST_NDEF_BLOCK] = readRegister;

                    // Update the GUI
                    this.LstNdefBlock_TextBox.Text = readRegister.ToString("X2");
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the button Write NDEF is pressed, the content in the LAST_NDEF_BLOCK group box is writen to the register
        private void writeLast_Ndef_BlockToReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte writeRegister = 0;
                String log;
                I2CError error;

                // Get the LAST_NDEF_BLOCK information from the GUI
                writeRegister = Utils.HexToByte(this.LstNdefBlock_TextBox.Text);

                // Write the LAST_NDEF_BLOCK register
                error = this.myDevice.writeSessionRegister(this.I2CAddress, (byte)SessionReg.LAST_NDEF_BLOCK, writeRegister, out log);
                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.LAST_NDEF_BLOCK] = writeRegister;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // Shows information about the LAST_NDEF_BLOCK register
        private void showLast_Ndef_Block_Info(object sender, EventArgs e)
        {
            MessageBox.Show("Address of last BLOCK NDEF message\r\n" +
                "1h is page 4h (first page of User Memory)\r\n" +
                "2h is page 8h\r\n" +
                "3h is page Ch\r\n" +
                "....\r\n" +
                "74h is page 1D0h (last page possible of the User Memory)",

                "LAST_NDEF_BLOCK byte (0xFE:1)");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////// SRAM_MIRROR_BLOCK //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // If the button Read SM_REG is pressed, the SRAM_MIRROR_BLOCK group box is updated with the content of the register
        private void updateSRAM_MIRROR(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;

                // Read the register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.SRAM_MIRROR_BLOCK, out readRegister, out log);

                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.SRAM_MIRROR_BLOCK] = readRegister;

                    // Update the GUI
                    this.SRAM_Addr_TextBox.Text = readRegister.ToString("X2");
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the button Write SM_REG is pressed, the content in the SRAM_MIRROR_BLOCK group box is writen to the register
        private void writeSRAM_MIRROR_ToReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte writeRegister = 0;
                String log;
                I2CError error;

                // Get the SRAM_MIRROR_BLOCK information from the GUI
                writeRegister = Utils.HexToByte(this.SRAM_Addr_TextBox.Text);

                // Write the SRAM_MIRROR_BLOCK register
                error = this.myDevice.writeSessionRegister(this.I2CAddress, (byte)SessionReg.SRAM_MIRROR_BLOCK, writeRegister, out log);

                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.SRAM_MIRROR_BLOCK] = writeRegister;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // Shows information about the SRAM_MIRROR_BLOCK register
        private void showSRAM_MIRROR_Info(object sender, EventArgs e)
        {
            MessageBox.Show("SRAM mirror lower page address in 4 page granularity\r\n" +
                "1h is page 4h (first page of User Memory)\r\n" +
                "2h is page 8h\r\n" +
                "3h is page Ch\r\n" +
                "....\r\n" +
                "74h is page 1D0h (last page possible of the User Memory)",

                "SRAM_MIRROR_ADDR byte (0xFE:2)");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////// WDT //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // If the button Read WDT is pressed, the group box is updated with the content of the WDT_LS and WDT_MS registers
        private void updateWDT(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;

                // Read the WDT_LS register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.WDT_LS, out readRegister, out log);
                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.WDT_LS] = readRegister;

                    // Update the GUI
                    this.WDT_LS_TextBox.Text = readRegister.ToString("X2");
                }

                // Read the WDT_MS register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.WDT_MS, out readRegister, out log);
                this.logging.Text = log;

                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.WDT_MS] = readRegister;

                    // Update the GUI
                    this.WDT_MS_TextBox.Text = readRegister.ToString("X2");
                }

                // Obtain the watchdog time-out value
                double timeOutValue = ((this.registers[(int)SessionReg.WDT_MS] << 8) + this.registers[(int)SessionReg.WDT_LS]);
                timeOutValue /= 106;
                this.WatchDog_Label.Text = "Watchdog time-out: " + timeOutValue.ToString("0.000", System.Globalization.CultureInfo.CreateSpecificCulture("en-US")) + " ms";
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the button Write WDT is pressed, the content in the group box is writen to the WDT_LS and WDT_MS registers
        private void writeWDT_ToReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte writeRegister = 0;
                String log;
                I2CError error;

                // Get the WDT_LS information from the GUI
                writeRegister = Utils.HexToByte(this.WDT_LS_TextBox.Text);

                // Write the WDT_LS register
                error = this.myDevice.writeSessionRegister(this.I2CAddress, (byte)SessionReg.WDT_LS, writeRegister, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.WDT_LS] = writeRegister;
                }

                // Get the WDT_MS information from the GUI
                writeRegister = Utils.HexToByte(this.WDT_MS_TextBox.Text);

                // Write the WDT_MS register
                error = this.myDevice.writeSessionRegister(this.I2CAddress, (byte)SessionReg.WDT_MS, writeRegister, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.WDT_MS] = writeRegister;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the WDT_MS text is changed, the label below is changed
        private void updateWatchdog_withWDT_MS(object sender, EventArgs e)
        {
            // Obtain the watchdog time-out value
            double timeOutValue = ((((int)Utils.HexToByte(this.WDT_MS_TextBox.Text)) << 8) + Utils.HexToByte(this.WDT_LS_TextBox.Text));
            timeOutValue /= 106;
            this.WatchDog_Label.Text = "Watchdog time-out: " + timeOutValue.ToString("0.000", System.Globalization.CultureInfo.CreateSpecificCulture("en-US")) + " ms";
        }

        // If the WDT_LS text is changed, the label below is changed
        private void updateWatchdog_withWDT_LS(object sender, EventArgs e)
        {
            // Obtain the watchdog time-out value
            double timeOutValue = ((((int)Utils.HexToByte(this.WDT_MS_TextBox.Text)) << 8) + Utils.HexToByte(this.WDT_LS_TextBox.Text));
            timeOutValue /= 106;
            this.WatchDog_Label.Text = "Watchdog time-out: " + timeOutValue.ToString("0.000", System.Globalization.CultureInfo.CreateSpecificCulture("en-US")) + " ms";
        }

        // Shows information about the WDT_LS and WDT_MS registers
        private void showWDT_Info(object sender, EventArgs e)
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

                "Watchdog Timer bytes (0xFE:[4:3])");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////// NS_REG ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // If the button Read NS_REG is pressed, the group box is updated with the content of the register
        private void updateNS_REG(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte readRegister;
                String log;
                I2CError error;

                // Read the register
                error = this.myDevice.readSessionRegister(this.I2CAddress, (byte)SessionReg.NS_REG, out readRegister, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.NS_REG] = readRegister;

                    // Update the GUI
                    this.NDEF_READ_ChBox.Checked = (readRegister & 0x80) == 0x80; // NDEF_DATA_READ
                    this.I2C_LOCKED_ChB.Checked = (readRegister & 0x40) == 0x40; // I2C_LOCKED
                    this.RF_LOCKED_ChB.Checked = (readRegister & 0x20) == 0x20; // RF_LOCKED
                    this.SRAM_I2C_RDY_ChB.Checked = (readRegister & 0x10) == 0x10; // SRAM_I2C_READY
                    this.SRAM_RF_RDY_ChB.Checked = (readRegister & 0x08) == 0x08; // SRAM_RF_READY
                    this.EEPROM_ERR_ChB.Checked = (readRegister & 0x04) == 0x04; // EEPROM_WR_ERR
                    this.EEPROM_BSY_ChB.Checked = (readRegister & 0x02) == 0x02; // EEPROM_WR_BUSY
                    this.RF_F_Present_ChB.Checked = (readRegister & 0x01) == 0x01; // RF_FIELD_PRESENT
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // If the button Write NS_REG is pressed, the content in the group box is writen to the register
        private void writeNS_REG_ToReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte writeRegister = 0;
                String log;
                I2CError error;

                // Get the information from the GUI
                writeRegister += (byte)(this.NDEF_READ_ChBox.Checked ? 0x80 : 0); // NDEF_DATA_READ
                writeRegister += (byte)(this.I2C_LOCKED_ChB.Checked ? 0x40 : 0); // I2C_LOCKED
                writeRegister += (byte)(this.RF_LOCKED_ChB.Checked ? 0x20 : 0); // RF_LOCKED
                writeRegister += (byte)(this.SRAM_I2C_RDY_ChB.Checked ? 0x10 : 0); // SRAM_I2C_READY
                writeRegister += (byte)(this.SRAM_RF_RDY_ChB.Checked ? 0x08 : 0); // SRAM_RF_READY
                writeRegister += (byte)(this.EEPROM_ERR_ChB.Checked ? 0x04 : 0); // EEPROM_WR_ERR
                writeRegister += (byte)(this.EEPROM_BSY_ChB.Checked ? 0x02 : 0); // EEPROM_WR_BUSY
                writeRegister += (byte)(this.RF_F_Present_ChB.Checked ? 0x01 : 0); // RF_FIELD_PRESENT

                // Write the register
                error = this.myDevice.writeSessionRegister(this.I2CAddress, (byte)SessionReg.NS_REG, writeRegister, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    this.registers[(int)SessionReg.NS_REG] = writeRegister;
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        // Shows information about the NS_REG register
        private void showNS_REG_Info(object sender, EventArgs e)
        {
            MessageBox.Show("NDEF_DATA_READ: All data bytes read from the address specified in LAST_NDEF_BLOCK\r\n\r\n" +

                "I2C_LOCKED: Memory access is locked to I²C interface\r\n\r\n" +

                "RF_LOCKED: Memory access is locked to RF interface\r\n\r\n" +

                "SRAM_RF_READY: data is ready in SRAM for RF read\r\n\r\n" +

                "SRAM_I2C_READY: data is ready in SRAM for I²C read\r\n\r\n" +

                "EEPROM_WR_ERR: HV voltage error during EPP cycle via I²C host\r\n\r\n" +

                "EEPROM_WR_BUSY: \r\n" +
                "1b: EEPROM write cycle active - access to EEPROM disabled\r\n" +
                "0b: EEPROM write cycle is possible\r\n\r\n" +

                "RF_FIELD_PRESENT: RF field is detected",

                "NS_REG byte (0xFE:6)");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////// General ///////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Pressing the Read All button is as pressing all the Read buttons
        private void readAllRegistersAndShow(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                ReadNC_REG_Btn.PerformClick(); // NC_REG
                ReadI2C_STR_Btn.PerformClick(); // I2C_CLOCK_STR
                ReadNdef_Btn.PerformClick(); // LAST_NDEF_BLOCK
                ReadSM_Reg_Btn.PerformClick(); // SRAM_MIRROR_BLOCK
                ReadWDT_Btn.PerformClick(); // WDT
                ReadNS_REG_Btn.PerformClick(); // NS_REG
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

       
    }
}
