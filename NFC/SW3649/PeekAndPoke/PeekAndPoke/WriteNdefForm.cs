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
    public partial class WriteNdefForm : Form
    {
        public String NDEFtext;
        public bool isDefault = false;
        public bool isNDEFbuttonpressed = false;
        private NtagI2CDevice myDevice;
        private TagType type;
        private DataGridView hexaTable,asciiTable;
        private DGVUtils dgvUtils;
        private ToolStripStatusLabel operationStatus_Lbl;
        private ToolStripTextBox addressInput_TxtB;
        private Label logging;
        private NDEFUtils utils;

        public WriteNdefForm()
        {
            InitializeComponent();
            utils = new NDEFUtils(this.myDevice);
        }

        public WriteNdefForm(NtagI2CDevice device,
                            TagType type,
                            DataGridView mainWindowHexaTable, 
                            DataGridView mainWindowAsciiTable, 
                            ToolStripStatusLabel mainWindowOperationStatus, 
                            ToolStripTextBox mainWindowAddressInput,
                            Label logging)
        {
            InitializeComponent();
            this.myDevice = device;
            this.hexaTable = mainWindowHexaTable;
            this.asciiTable = mainWindowAsciiTable;
            this.operationStatus_Lbl = mainWindowOperationStatus;
            this.addressInput_TxtB = mainWindowAddressInput;
            this.logging = logging;
            this.type = type;
            dgvUtils = new DGVUtils(hexaTable, asciiTable, null);
        }

        private void writeTextNdef(object sender, EventArgs e)
        {
            if (this.myDevice.isPresent)
            {
                
                this.NDEFtext = this.textNdef_textBox.Text;
                byte[] NDEFmessage = Encoding.UTF8.GetBytes(this.NDEFtext.ToCharArray());
                this.isNDEFbuttonpressed = true;
                //this.CreateNdefText(Encoding.UTF8.GetBytes(this.NDEFtext.ToCharArray()), out NDEFmessage);
                byte i2cAddress = Utils.HexToByte(this.addressInput_TxtB.Text);

                I2CData result = this.myDevice.writeNdef(i2cAddress, NDEFmessage);
                this.logging.Text = result.log;
                if (result.error == I2CError.Success)
                {
                    this.updateTablesWithNdef(result.data);
                }
                this.operationStatus_Lbl.Text = this.GetTextError(result.error);
                dgvUtils.markTlvs(type);
                
            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

      

        private void updateTablesWithNdef(byte[] NDEFmessage)
        {
            // Obtain the number of blocks
            int numBlocks = (int)Math.Ceiling(((double)NDEFmessage.Length) / NtagI2CDevice.bytesInBlock);

            // Go through all the blocks
            for (int i = 0; i < numBlocks; i++)
            {
                // Obtain the bytes for this block
                byte[] block = new byte[NtagI2CDevice.bytesInBlock];
                Array.Copy(NDEFmessage, i * NtagI2CDevice.bytesInBlock, block, 0, Math.Min(NtagI2CDevice.bytesInBlock, NDEFmessage.Length - i * NtagI2CDevice.bytesInBlock));

                // Show those bytes on the data grid views
                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                {
                    this.hexaTable.Rows[i + 1].Cells[j].Value = block[j].ToString("X2");
                    this.asciiTable.Rows[i + 1].Cells[j].Value = (char)block[j];
                }
            }
        }

        String GetTextError(I2CError error)
        {
            String sError;
            switch (error)
            {
                case I2CError.Success:
                    sError = "I²C Success";
                    break;
                case I2CError.Unknown:
                    sError = "Unknown error condition";
                    break;
                case I2CError.Nak:
                    sError = "No acknowledge (NAK)";
                    break;
                case I2CError.BusError:
                    sError = "I²C bus error";
                    break;
                case I2CError.NakAfterSla:
                    sError = "NAK received after SLA+W or SLA+R";
                    break;
                case I2CError.ArbitrationLost:
                    sError = "Arbitration lost";
                    break;
                case I2CError.TimeOut:
                    sError = "Transaction timed out";
                    break;
                case I2CError.InvalidRequest:
                    sError = "Invalid HID_I2C Request";
                    break;
                case I2CError.InvalidParameters:
                    sError = "Invalid parameters";
                    break;
                case I2CError.PartialCompleted:
                    sError = "Partial transfer completed";
                    break;
                case I2CError.NoHw:
                    sError = "No hardware connected";
                    break;
                default:
                    sError = "Undefined result";
                    break;
            }

            return sError;
        }

        // When the Write button in the default NDEF groupbox is pressed, the form is closed
        private void writeDefaultNdef(object sender, EventArgs e)
        {
            if (utils == null)
                utils = new NDEFUtils(this.myDevice); 

            byte i2cAddress = Utils.HexToByte(this.addressInput_TxtB.Text);
            byte[] NDEFmessage;
            this.isNDEFbuttonpressed = true;
            this.NDEFtext = this.textNdef_textBox.Text;


            if (this.myDevice.isPresent)
            {
                utils.CreateDefaultNdef(out NDEFmessage);

                // Write the message into the tag and update the data grid views                
                I2CData result = this.myDevice.writeMessage(i2cAddress, NDEFmessage);

                this.logging.Text = result.log;
                if (result.error == I2CError.Success)
                {
                    this.updateTablesWithNdef(NDEFmessage);
                }

                // Update error status bar
                this.operationStatus_Lbl.Text = this.GetTextError(result.error);
                dgvUtils.markTlvs(type);

            }
            else
            {
                Utils.showDevLostAndClose(this);
            }
        }

       

       private void WriteNdefForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (this.isNDEFbuttonpressed == true)
            {
                e.Cancel = true;
                this.isNDEFbuttonpressed = false;
            }
            else
            {
                e.Cancel = false;
            }
        }
    }
}
