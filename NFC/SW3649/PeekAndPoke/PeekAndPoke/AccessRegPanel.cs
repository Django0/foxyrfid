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
    public partial class AccessRegPanel : Form
    {
        private NtagI2CDevice myDevice;
        private byte I2CAddress;
        private byte address;
        private byte[] registers;
        private Label logging;

        public AccessRegPanel()
        {
            InitializeComponent();

            myInitializeComponent();

            this.readAccess_Btn.PerformClick();
        }

        public AccessRegPanel(NtagI2CDevice device, byte I2CAddress, byte address, byte[] registers, Label loggingLbl)
        {
            InitializeComponent();

            this.myDevice = device;
            this.I2CAddress = I2CAddress;
            this.address = address;
            this.registers = registers;
            this.logging = loggingLbl;
            myInitializeComponent();
            this.Shown += new EventHandler(this.readAccessRegAndShow);
        }

        private void myInitializeComponent()
        {
            this.I2C_PROT_Combo.SelectedIndex = 0;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////// Buttons ///////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void readAccessRegAndShow(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                byte[] readRegisters;
                String log;
                I2CError error;
                
                // Read the AUTH0 register
                error = this.myDevice.readBlock(this.I2CAddress, this.address, out readRegisters, out log);
                this.logging.Text = log;
                if (error == I2CError.Success)
                {
                    // Update the byte array
                    for (int i = 0; i < this.registers.Length; i++)
                        this.registers[i] = readRegisters[i];

                    // Update the GUI
                    // AUTH0
                    this.AUTH0_TextBox.Text = readRegisters[(int)AccessReg.AUTH0].ToString("X2");   // AUTH0 value

                    // Read the remaining registers
                    error = this.myDevice.readBlock(this.I2CAddress, 0x39, out readRegisters, out log);
                    this.logging.Text = log;
                    if (error == I2CError.Success)
                    {
                        // Update the byte array
                        for (int i = 0; i < this.registers.Length; i++)
                            this.registers[i] = readRegisters[i];

                        // Update the GUI
                        // ACCESS
                        this.NFC_PROT_CheckBox.Checked = (readRegisters[(int)AccessReg.ACCESS] & 0x80) == 0x80; // NFC_PROT
                        this.NFC_DIS_SEC1_CheckBox.Checked = (readRegisters[(int)AccessReg.ACCESS] & 0x20) == 0x20; // NFC_DIS_SEC1
                        this.AUTHLIM_TextBox.Text = (readRegisters[(int)AccessReg.ACCESS] & 0x07).ToString("X1"); //AUTHLIM
                        // PWD
                        this.PWD_TextBox.Text = (readRegisters[(int)AccessReg.PWD].ToString("X8")); //PWD
                        // PACK
                        this.PACK_TextBox.Text = (readRegisters[(int)AccessReg.PACK] & 0x0F).ToString("X4"); //PACK
                        // PT_I2C
                        this._2K_PROT_CheckBox.Checked = (readRegisters[(int)AccessReg.PT_I2C] & 0x08) == 0x08; // 2K_PROT
                        this.SRAM_PROT_CheckBox.Checked = (readRegisters[(int)AccessReg.PT_I2C] & 0x04) == 0x04; // SRAM_PROT
                        this.I2C_PROT_Combo.SelectedIndex = (readRegisters[(int)AccessReg.PT_I2C] & 0x03) >> 0;  // I2C_PROT
                    }
                }
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        private void writeFormValuesToAccessReg(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                //byte[] writeRegisters = new byte[NtagI2CDevice.bytesInBlock];
                byte[] writeRegisters;
                String log;
                I2CError errorRead, errorWrite;

                // Get the information from the GUI
                // AUTH0

                errorRead = this.myDevice.readBlock(this.I2CAddress, 0x38, out writeRegisters, out log);
                if(errorRead == I2CError.Success)
                {
                    writeRegisters[(int)AccessReg.AUTH0] = Utils.HexToByte(this.AUTH0_TextBox.Text);
                    errorWrite = this.myDevice.writeBlock(this.I2CAddress, 0x38, writeRegisters, out log);
                    this.logging.Text = log; 
                    if (errorWrite != I2CError.Success)
                    {
                        //  Error Writing the Dynamic Lock block
                    }
                }
                else
                {
                    //  Error reading Dynamic Lock block
                }


                errorRead = this.myDevice.readBlock(this.I2CAddress, 0x39, out writeRegisters, out log);
                if (errorRead == I2CError.Success)
                {
                    // ACCESS
                    writeRegisters[(int)AccessReg.ACCESS] = 0x00;
                    writeRegisters[(int)AccessReg.ACCESS] += (byte)(this.NFC_PROT_CheckBox.Checked ? 0x80 : 0);
                    writeRegisters[(int)AccessReg.ACCESS] += (byte)(this.NFC_DIS_SEC1_CheckBox.Checked ? 0x20 : 0);

                    int number;
                    if (int.TryParse(AUTHLIM_TextBox.Text, out number))
                    {
                        if (number <= 7)
                        {
                            //in range
                            for (int k = 0; k < 2; k++)
                                writeRegisters[(int)AccessReg.ACCESS + k] += Utils.HexToByte(this.AUTHLIM_TextBox.Text);
                        }
                        else
                        {
                            // not in range
                            MessageBox.Show("Invalid number");
                        }
                    }
                    else
                    {
                        //invalid number
                        MessageBox.Show("Invalid number");
                    }
                        
                    // PWD
                    for (int j = 0; j < 4; j++)
                        writeRegisters[(int)AccessReg.PWD + j] = Utils.HexToByte(this.PWD_TextBox.Text);

                    // PACK
                    for (int h = 0; h < 2; h++)
                        writeRegisters[(int)AccessReg.PACK + h] = Utils.HexToByte(this.PACK_TextBox.Text);

                    // PT_I2C
                    writeRegisters[(int)AccessReg.PT_I2C] = 0x00;
                    writeRegisters[(int)AccessReg.PT_I2C] += (byte)(this.I2C_PROT_Combo.SelectedIndex << 0);
                    writeRegisters[(int)AccessReg.PT_I2C] += (byte)(this.SRAM_PROT_CheckBox.Checked ? 0x04 : 0);
                    writeRegisters[(int)AccessReg.PT_I2C] += (byte)(this._2K_PROT_CheckBox.Checked ? 0x08 : 0);
                        
                    // Write the register
                    errorWrite = this.myDevice.writeBlock(this.I2CAddress, 0x39, writeRegisters, out log);
                    this.logging.Text = log;
                    if (errorWrite != I2CError.Success)
                    {
                        //  Error Writing Access Register block
                    }
                }
                else
                {
                    //  Error reading Access Register block
                }    
                
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////// Info buttons ////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void AUTH0_Info_PicBox_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Page address of Sector 0 from which onwards the password\n" +
                            "authentication is required to access the user memory from NFC\n" +
                            "perspective, dependent on NFC_PROT bit.\n \n" +

                            "If AUTH0 is set to a page address greater than EBh, the\n" +
                            "password protection is effectively disabled. Password protected\n" +
                            "area starts from page AUTH0 and ends at page EBh.\n \n" +

                            "Password protection is excluded for Dynamic Lock Bits, session\n" +
                            "registers and mirrored SRAM pages.\n \n" +

                            "Note: From I²C interface you have access to all configuration\n" +
                            "pages until REG_LOCK_I2C bit is set to 1b.\n \n");
        }

        private void ACCESS_Info_PicBox_Click(object sender, EventArgs e)
        {
            MessageBox.Show("NFC_PROT: OFF-> write access to protected area is protected by the password.\n" +
                                       "ON-> read and write access to protected area is protected by the password.\n \n" +

                            "NFC_DIS_SEC1: OFF-> Sector 1 is accessible in 2K version.\n" +
                                           "ON-> Sector 1 is inaccessible and returns NAK0.\n \n" +

                            "AUTHLIM:Limitation of negative password authentication attempts. After\n" +
                                    "reaching the limit, protected area is not accessible any longer.\n" +
                                    "000b: limiting of negative password authentication attempts disabled.\n" +
                                    "001b-111b: maximum number of negative password authentication attempts is 2^AUTHLIM.\n");
        }

        private void PT_I2C_Info_PicBox_Click(object sender, EventArgs e)
        {
            MessageBox.Show("2K_PROT: OFF-> password authentication for Sector 1 disabled. \n"+
                                      "ON-> password authentication needed to access Sector 1.\n \n" +

                            "SRAM_PROT: OFF-> password authentication for pass-through mode disabled.\n" +
                                        "ON-> password authentication needed to access SRAM in pass-through mode.\n \n" +

                            "I2C_PROT 00b-> entire user memory accessible from I²C.\n" +
                                      "01b-> read and write access to unprotected user area, read only access to protected area.\n" +
                                      "1Xb-> read and write access to unprotected area, no access to protected area.\n \n"
                );
        }

        private void PACK_Info_PicBox_Click(object sender, EventArgs e)
        {
            MessageBox.Show("16-bit password acknowledge used during the password authentication process.\n \n " +
                            "The textbox will be disabled by default, please click on 'Enable' to permit changes.\n");
        }

        private void PWD_Info_PicBox_Click(object sender, EventArgs e)
        {
            MessageBox.Show("32-bit password used for memory access protection.\n \n " +
                            "The textbox will be disabled by default, please click on 'Enable' to permit changes.\n");
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }


        

    }
}