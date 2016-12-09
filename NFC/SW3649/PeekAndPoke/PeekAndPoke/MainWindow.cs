using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NTAG_I2C.Contracts;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading;

namespace PeekAndPoke
{
    public partial class MainWindow : Form
    {
        public NtagI2CDevice myDevice;
        private bool ignoreEvents, initTreeView = false;
        private DGVUtils dgvUtils;

        public MainWindow()
        {
            //disableEvents();
            InitializeComponent();
            disableEvents();
            defineTables();
            selectComboIndex();
            fileOptionsConfig();
            enableTimerToCheckDeviceConncted();
            enableEvents();
            initNTagDevice();
            this.Shown += new EventHandler(ReinitTreeAndGrids_Shown);
        }

        private void enableTimerToCheckDeviceConncted()
        {
            checkDevtimer.Enabled = true;
        }

        private void enableEvents()
        {
            this.ignoreEvents = false;
        }

        private void disableEvents()
        {
            this.ignoreEvents = true;
        }

        private void fileOptionsConfig()
        {
            this.openFileDialog1.InitialDirectory = Environment.CurrentDirectory;
            this.saveFileDialog1.InitialDirectory = Environment.CurrentDirectory;
        }

        private void selectComboIndex()
        {
            this.tagTypeComboBox.SelectedIndex = 0;
            this.changeBusSpeed_Combo.SelectedIndex = 3;
        }

        private void defineTables()
        {
            dgvUtils = new DGVUtils(this.hexaTable, this.asciiTable, this.memoryTreeView);

            var panelWidth = this.memTablesContainer.Width / 2 - 2;

            this.memTablesContainer.Panel1MinSize = panelWidth;
            this.memTablesContainer.Panel2MinSize = panelWidth;


            this.hexaTable.ColumnCount = NtagI2CDevice.bytesInBlock;
            this.hexaTable.RowHeadersWidth = 50;
            this.hexaTable.Width = panelWidth;
            var columnWidth = (panelWidth - 65) / this.hexaTable.ColumnCount;

            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
            {
                this.hexaTable.Columns[i].Width = columnWidth;
                this.hexaTable.Columns[i].Name = i.ToString("X");
                this.hexaTable.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            this.hexaTable.RowCount = NtagI2CDevice.blocks;
            for (int i = 0; i < NtagI2CDevice.blocks; i++)
                this.hexaTable.Rows[i].HeaderCell.Value = i.ToString("X2");

            this.asciiTable.ColumnCount = NtagI2CDevice.bytesInBlock;
            this.asciiTable.RowHeadersWidth = 4;

            this.asciiTable.Width = panelWidth;
            columnWidth = (panelWidth - 14) / this.asciiTable.ColumnCount;
            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
            {
                this.asciiTable.Columns[i].Width = columnWidth;
                this.asciiTable.Columns[i].Name = i.ToString("X");
                this.asciiTable.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }

            this.asciiTable.RowCount = NtagI2CDevice.blocks;
        }

        private void initNTagDevice()
        {
            this.myDevice = new NtagI2CDevice();
            if (this.myDevice.isPresent)
                showDeviceFound();
            else
                showDeviceLost();
        }



        private TagType getNtagType()
        {
            TagType type;
            switch (this.tagTypeComboBox.SelectedIndex)
            {
                case 0:
                    type = TagType.NTAG1K;
                    break;
                case 1:
                    type = TagType.NTAG2K;
                    break;
                case 2:
                    type = TagType.NTAG1KPlus;
                    break;
                case 3:
                    type = TagType.NTAG2KPlus;
                    break;
                default:
                    type = TagType.NTAG1K;
                    break;
            }
            return type;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////// Open and Save buttons ////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the Open button is pressed, an .hex file with the memory contents of an NTAG I2C is loaded
        private void openHexFile(object sender, EventArgs e)
        {
            // Open the Open File dialog
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    // Create a string array with the lines from thefile
                    String[] fileLines = System.IO.File.ReadAllLines(this.openFileDialog1.FileName);

                    // Mark the selected cells
                    dgvUtils.unmarkAllCells();
                    int row, col;
                    TagType ttype = getNtagType();
                    I2CAccess accessConditions = getAccessConditions(ttype);
                    dgvUtils.markCells(ttype, out row, out col, accessConditions);
                    this.hexaTable.Refresh();
                    this.asciiTable.Refresh();

                    // Go  line by line to get their information
                    int i = 0;
                    bool done = false;
                    while (i < fileLines.Length && done == false)
                    {
                        // The lines have Intel HEX format. In this case: ":100AA000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDCC", where A
                        // refers to the address, D to the data, and C to the checksum of all the previous bytes
                        // The last line is ":00000001FF"
                        byte[] line;
                        // Check if it is the last line
                        if (fileLines[i] == ":00000001FF")
                            done = true;
                        // Else, check if it has the right format
                        else if (fileLines[i].ToCharArray()[0] == ':')
                        {
                            line = Utils.HexToByteArray(fileLines[i].TrimStart(':'));
                            if (line.Length == 21 && line[0] == 0x10 && line[3] == 0x00)
                            {
                                // Check the checksum
                                int sum = 0;
                                foreach (byte b in line)
                                    sum += b;
                                if ((sum & 0xFF) == 0)
                                {
                                    // Update the data grid views
                                    int address = ((line[2] & 0xF0) >> 4) + ((line[1] & 0x0F) << 4);
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        this.hexaTable.Rows[address].Cells[j].Value = line[j + 4].ToString("X2");
                                        this.asciiTable.Rows[address].Cells[j].Value = (char)line[j + 4];
                                    }
                                }
                                else
                                    throw new Exception();
                            }
                            else
                                throw new System.IndexOutOfRangeException();
                        }
                        else
                            throw new System.IndexOutOfRangeException();

                        i++;
                    }
                }
                catch (System.IndexOutOfRangeException)
                {
                    MessageBox.Show("The file selected doesn´t have the expected format.");
                }
                catch (System.IO.IOException)
                {
                    MessageBox.Show("The file selected could not be opened. Is it being used by another process?");
                }
                catch (Exception)
                {
                    MessageBox.Show("The file selected may be damaged. Some checksums are wrong.");
                }
            }
        }

        // When the Save button is pressed, the information in the data grid views is saved into an .hex file
        private void save(object sender, EventArgs e)
        {
            // Open the Save File dialog
            if (this.saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Create .hex file
                if (System.IO.File.Exists(this.saveFileDialog1.FileName))
                    System.IO.File.Delete(this.saveFileDialog1.FileName);

                // Go  line by line to introduce the information in the file
                for (int i = 0; i < NtagI2CDevice.blocks; i++)
                {
                    // Obtain the array of bytes that will be stored in the line
                    byte[] bLine = new byte[21];
                    bLine[0] = 0x10;
                    bLine[1] = (byte)((i & 0xF0) >> 4);
                    bLine[2] = (byte)((i & 0x0F) << 4);
                    bLine[3] = 0x00;
                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                        bLine[j + 4] = (byte)asciiTable.Rows[i].Cells[j].Value.ToString().ToCharArray()[0];
                    int sum = 0;
                    foreach (byte b in bLine)
                        sum += b;
                    bLine[20] = (byte)(0x100 - (sum & 0xFF));   // Checksum

                    // Create the string
                    String line = ":";
                    for (int j = 0; j < bLine.Length; j++)
                        line += bLine[j].ToString("X2");

                    // Add the line to the file
                    System.IO.File.AppendAllText(this.saveFileDialog1.FileName, line + Environment.NewLine);
                }

                // Add the last line
                System.IO.File.AppendAllText(this.saveFileDialog1.FileName, ":00000001FF");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////// Read and Write buttons ////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the Read Block button is pressed, the whole selected block is read
        private void readBlock_Click(object sender, EventArgs e)
        {
            byte[] readBytes;
            String log;
            I2CError error;
            byte i2cAddress = getI2CAddress();
            var type = getNtagType();
            var memory = new NTagMemory(type);

            if (this.hexaTable.CurrentRow.Index == memory.sessionMemoryBegin)
            {
                readBytes = new byte[NtagI2CDevice.bytesInBlock];
                for (int b = 0; b < NtagI2CDevice.bytesInBlock; b++)
                {
                    readBytes[b] = 0x00;
                };
                byte[] aux;
                error = this.myDevice.readSessionRegisters(i2cAddress, type, out aux, out log);
                Array.Copy(aux, 0, readBytes, 0, aux.Length);
            }
            else
            {
                // Get the content of the current block
                error = this.myDevice.readBlock(i2cAddress, (byte)hexaTable.CurrentRow.Index, out readBytes, out log);
            }

            if (error == I2CError.Success)
            {
                // Update the data grid views
                for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                {
                    this.hexaTable.CurrentRow.Cells[i].Value = readBytes[i].ToString("X2");
                    this.asciiTable.CurrentRow.Cells[i].Value = (char)readBytes[i];
                }

                // Update flag detect status bar
                this.flagStatus_Label.Text = this.myDevice.flag ? "Flag Detect high" : "Flag Detect low";

                // update log label
                this.loggingText.Text = log;
            }

            // Update error status bar
            this.operationsStatus_Label.Text = this.GetTextError(error);
        }

        // When the Write Block button is pressed, the whole selected block is written with the content of the data grid views
        private void writeBlock_Click(object sender, EventArgs e)
        {
            byte[] writeBytes;
            String log;
            I2CError error;
            byte i2cAddress = getI2CAddress();

            // Get the values to write
            writeBytes = new byte[NtagI2CDevice.bytesInBlock];
            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                writeBytes[i] = (byte)this.asciiTable.CurrentRow.Cells[i].Value.ToString().ToCharArray()[0];


            if (this.asciiTable.CurrentRow.Index == 0)
            {
                writeBytes[0] = i2cAddress;
            }

            // Set the content of the current block
            error = this.myDevice.writeBlock(i2cAddress, (byte)hexaTable.CurrentRow.Index, writeBytes, out log);

            if (error == I2CError.Success)
            {
                // Update flag detect status bar
                this.flagStatus_Label.Text = this.myDevice.flag ? "Flag Detect high" : "Flag Detect low";

                // update log label
                this.loggingText.Text = log;
            }

            // Update error status bar
            this.operationsStatus_Label.Text = this.GetTextError(error);
        }

        private void threadReadCall(TagType type, byte i2cAddress, Action<I2CData> showFeedback)
        {
            var allMemory = this.myDevice.api.readAllMemory(type, i2cAddress, showFeedback);
        }

        // When the Read all button is pressed, all the content of the NTAG I2C device is read
        private void readAllMemory_Click(object sender, EventArgs e)
        {
            byte i2cAddress = getI2CAddress();
            TagType type = getNtagType();
            NTagMemory memory = new NTagMemory(type);
            I2CError error = I2CError.Success;
            int rowIdx = 0;
            int cellIdx = 0;
            this.operationsStatus_Label.Text = "Reading all memory...";
            this.statusStrip1.Refresh();

            var showFeedback = new Action<I2CData>((I2CData memBlock) => {

                while (rowIdx < (NtagI2CDevice.blocks - 1) && !this.hexaTable.Rows[rowIdx].Visible)
                    rowIdx++;

                var addressRead = this.hexaTable.Rows[rowIdx].HeaderCell.Value.ToString();
                this.operationsStatus_Label.Text = "Reading block: 0x" + addressRead;
                this.statusStrip1.Refresh();

                error = memBlock.error;
                this.loggingText.Text = memBlock.log;

                if (error == I2CError.Success && rowIdx < NtagI2CDevice.blocks)
                {
                    if (memBlock.data.Length == NtagI2CDevice.bytesInBlock)
                    {
                        for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                        {
                            this.hexaTable.Rows[rowIdx].Cells[j].Value = memBlock.data[j].ToString("X2");
                            this.asciiTable.Rows[rowIdx].Cells[j].Value = (char)memBlock.data[j];
                        }
                        rowIdx++;
                        cellIdx = 0;
                    }
                    else
                    {
                        this.hexaTable.Rows[rowIdx].Cells[cellIdx].Value = memBlock.data[0].ToString("X2");
                        this.asciiTable.Rows[rowIdx].Cells[cellIdx].Value = (char)memBlock.data[0];
                        cellIdx++;

                        if (cellIdx == NtagI2CDevice.bytesInBlock)
                        {
                            rowIdx++;
                            cellIdx = 0;
                        }
                    }
                }
            });

            //var allMemory = this.myDevice.api.readAllMemory(type, i2cAddress, showFeedback);

            var thread = new Thread(
                 () => threadReadCall(type, i2cAddress, showFeedback));
            thread.Start();

            // Loop until worker thread activates.
            while (!thread.IsAlive) ;

            // Put the main thread to sleep for 1 millisecond to
            // allow the worker thread to do some work:
            Thread.Sleep(1);

            thread.Join();

            if (error == I2CError.Success)
            {
                // Update flag detect status bar
                this.flagStatus_Label.Text = this.myDevice.flag ? "Flag Detect high" : "Flag Detect low";
            }

            // Update error status bar
            this.operationsStatus_Label.Text = this.GetTextError(error);

            // Look for TLVs and highlight them
            dgvUtils.unmarkAllCells();
            dgvUtils.markTlvs(type);
        }
        
        private void threadWriteCall(TagType type, byte i2cAddress, byte[][] writeBytes, Action<I2CData> showFeedback)
        {
            List<I2CData> output = this.myDevice.api.writeAllMemory(type, i2cAddress, writeBytes, showFeedback);
        }

        // When the Write all button is pressed, all the content of the data grid view is written into the NTAG I2C device (except block 0)
        private void writeAllMemory_Click(object sender, EventArgs e)
        {
            byte i2cAddress = getI2CAddress();
            var type = getNtagType();
            var memory = new NTagMemory(type);
            int rowIdx = 1;
            // Write the NTAG
            byte[][] writeBytes;
            I2CError error = I2CError.Success;

            var showFeedback = new Action<I2CData>((I2CData memBlock) =>
            {
                Debug.Write(" entered: " + rowIdx.ToString());
                while (rowIdx < (NtagI2CDevice.blocks - 2) && !this.hexaTable.Rows[rowIdx].Visible)
                    rowIdx++;

                var addressWrite = this.hexaTable.Rows[rowIdx].HeaderCell.Value.ToString();
                this.operationsStatus_Label.Text = "Writing block: 0x" + addressWrite;
                this.statusStrip1.Refresh();

                error = memBlock.error;
                this.loggingText.Text = memBlock.log;

                rowIdx++;
            });

            writeBytes = dgvUtils.readAsciiTableContent();
            //List<I2CData> output = this.myDevice.api.writeAllMemory(type, i2cAddress, writeBytes, showFeedback);

            var thread = new Thread(
                 () => threadWriteCall(type, i2cAddress, writeBytes, showFeedback));
            thread.Start();

            // Loop until worker thread activates.
            while (!thread.IsAlive) ;

            // Put the main thread to sleep for 1 millisecond to
            // allow the worker thread to do some work:
            Thread.Sleep(1);

            thread.Join();

            if (error == I2CError.Success)
            {
                this.flagStatus_Label.Text = this.myDevice.flag ? "Flag Detect high" : "Flag Detect low";
            }

            this.operationsStatus_Label.Text = this.GetTextError(error);
        }

        // When the Write NDEF button is pressed, the Write NDEF form is shown
        private void writeNDefButton_Click(object sender, EventArgs e)
        {
            byte i2cAddress = getI2CAddress();
            TagType type = getNtagType();
            // Create the Write NDEF form
            WriteNdefForm wNdefForm = new WriteNdefForm(this.myDevice, type, this.hexaTable, this.asciiTable, this.operationsStatus_Label, this.i2cAddressInput, this.loggingText);
            wNdefForm.ShowDialog();
        }

        private void i2cAddressAdd_Btn_Click(object sender, EventArgs e)
        {
            byte i2cAddress = this.myDevice.i2cAddress;
            var type = getNtagType();
            var memory = new NTagMemory(type);
            var log = "";
            byte newAddress;
            String oldAddress = this.i2cAddressInput.Text;

            // Create the Edit I2C Address form
            I2CAddress addForm = new I2CAddress(oldAddress);
            addForm.ShowDialog();

            // Update the data grid views with the new values of the access registers
            if (addForm.DialogResult == DialogResult.OK && !(string.IsNullOrWhiteSpace(addForm.newAddress)))
            {
                newAddress = Utils.HexToByte(addForm.newAddress);

                byte[] writeBytes = new byte[NtagI2CDevice.bytesInBlock];
                for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                    writeBytes[i] = (byte)this.asciiTable.Rows[0].Cells[i].Value.ToString().ToCharArray()[0];

                writeBytes[0] = newAddress;

                var error = this.myDevice.writeBlock(i2cAddress, (byte)0, writeBytes, out log);

                this.loggingText.Text = log;
                this.operationsStatus_Label.Text = this.GetTextError(error);

                setI2CAddress(newAddress);
            }
        }

        // When the Reset button is pressed, the memory of the NTAG I2C is reset to its factory default value
        private void resetToDefaultValue_Click(object sender, EventArgs e)
        {
            int row, col;
            var type = getNtagType();
            var memory = new NTagMemory(type);
            byte[] writeBytes = new byte[NtagI2CDevice.bytesInBlock];
            byte i2cAddress = getI2CAddress();
            byte[] NDEFmessage;
            NDEFUtils utils = new NDEFUtils(this.myDevice);
            utils.CreateDefaultNdef(out NDEFmessage);
            // Reset the data grid views
            dgvUtils.resetGrids(type);
            dgvUtils.unmarkAllCells();

            I2CAccess accessConditions = getAccessConditions(type);
            dgvUtils.markCells(type, out row, out col, accessConditions);
            this.hexaTable.Refresh();
            this.asciiTable.Refresh();

            this.writeAll_Btn.PerformClick();
            this.myDevice.writeMessage(i2cAddress, NDEFmessage);


            this.readAll_Btn.PerformClick();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////// Device type selection ////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the device type is changed, need to update the data grid views
        private void changeNtagType_Listener(object sender, EventArgs e)
        {
            byte[] readBytes;
            String log;
            I2CError error;
            var type = getNtagType();
            byte i2cAddress = getI2CAddress();

            if (!this.ignoreEvents) // Don't do it during initialization
            {
                this.disableEvents();
                I2CAccess accessConditions = getAccessConditions(type);
                dgvUtils.ReinitTreeAndGrids(type, accessConditions);
                this.initTreeView = true;

                if (this.myDevice.isPresent)
                {
                    tagTypeRecognition(i2cAddress, type);
                }
                this.enableEvents();
                showDeviceFound();
            }
        }

        private bool tagTypeRecognition(byte i2cAddress, TagType tType)
        {
            I2CError errorRes;
            byte[] readBytes;
            byte[] tempBytes = new byte[16];
            String log;
            byte ptI2C;
            bool changed = false, match = true;
            errorRes = this.myDevice.readBlock(i2cAddress, 0x57, out readBytes, out log);
            this.loggingText.Text = log;

            for (int i = 0; i < 16; i++)
                tempBytes[i] = readBytes[i];

            ptI2C = tempBytes[12];

            if ((ptI2C & 0x02) == 0x02)
            {
                tempBytes.SetValue(ptI2C & 0xFC, 12);
                errorRes = this.myDevice.writeBlock(i2cAddress, 0x57, tempBytes, out log);
                this.loggingText.Text = log;
                changed = true;
            }

            errorRes = this.myDevice.readBlock(i2cAddress, 0x7A, out readBytes, out log);
            this.loggingText.Text = log;
            if (errorRes == I2CError.Nak)
            {
                // In this case the tag is a 1K tag, we have to check if it is a Plus
                errorRes = this.myDevice.readBlock(i2cAddress, 0x39, out readBytes, out log);
                this.loggingText.Text = log;
                if (errorRes == I2CError.Nak)
                {
                    //NTAG 1K (Normal)
                    if (tType != TagType.NTAG1K)
                    {
                        MessageBox.Show("The tag type selected does not match. \n Please confirm you are using a " + tagType2String(tType) + ".");
                        match = false;
                    }
                }
                else if (errorRes == I2CError.Success)
                {
                    //NTAG 1K Plus
                    if (tType != TagType.NTAG1KPlus)
                    {
                        MessageBox.Show("The tag type selected does not match. \n Please confirm you are using a " + tagType2String(tType) + ".");
                        match = false;
                    }
                }
                else
                {
                    MessageBox.Show("There was some issue checking the card type (1k) \nPlease Try again.");
                    match = false;
                }
            }
            else if (errorRes == I2CError.Success || errorRes == I2CError.NakAfterSla)
            {
                //  In this case the tag is a 2K tag, we have to check if it is a Plus
                errorRes = this.myDevice.readBlock(i2cAddress, 0x3F, out readBytes, out log);
                this.loggingText.Text = log;
                if (errorRes == I2CError.Nak)
                {
                    //NTAG 2K Plus
                    if (tType != TagType.NTAG2KPlus)
                    {
                        MessageBox.Show("The tag type selected does not match (CP1). \n Please confirm you are using a " + tagType2String(tType) + ".");
                        match = false;
                    }
                }
                else if (errorRes == I2CError.Success)
                {
                    //NTAG 2K Normal
                    if (tType != TagType.NTAG2K)
                    {
                        MessageBox.Show("The tag type selected does not match (CP2). \n Please confirm you are using a " + tagType2String(tType) + ".");
                        match = false;
                    }
                }
                else
                {
                    MessageBox.Show("There was some issue checking the card type (CP3) (2k) \nPlease Try again.");
                    match = false;
                }
            }
            else
            {
                MessageBox.Show("There was some issue checking the card type (all) \nPlease Try again.");
                match = false;
            }


            if (changed)
            {
                tempBytes.SetValue(ptI2C, 12);
                errorRes = this.myDevice.writeBlock(i2cAddress, 0x57, tempBytes, out log);
                this.loggingText.Text = log;
            }

            return match;
        }

        private String tagType2String(TagType typeIn)
        {
            String textTagType;
            switch (typeIn)
            {
                case TagType.NTAG1K:
                    textTagType = "NT3H1101 (NTAG I²C 1K)";
                    break;
                case TagType.NTAG1KPlus:
                    textTagType = "NT3H2111 (NTAG I²C plus 1K)";
                    break;
                case TagType.NTAG2K:
                    textTagType = "NT3H1201 (NTAG I²C 2K)";
                    break;
                default:
                    textTagType = "NT3H2211 (NTAG I²C plus 2K)";
                    break;
            }
            return textTagType;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////// I2C address selection ////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Action when the lock button is pressed
        private void lockButton_Click(object sender, EventArgs e)
        {
            if (this.i2cAddressInput.Enabled)
            {
                lockI2CAddressBtn();
            }
            else
            {
                unlockI2CAddressBtn();
            }
        }

        private void unlockI2CAddressBtn()
        {
            this.i2cAddressInput.Enabled = true;
            this.i2cAddressAdd_Btn.Enabled = true;
            this.addressLock_Btn.BackColor = System.Drawing.SystemColors.Control;
        }

        private void lockI2CAddressBtn()
        {
            this.i2cAddressInput.Enabled = false;
            this.i2cAddressAdd_Btn.Enabled = false;
            this.addressLock_Btn.BackColor = System.Drawing.Color.Gold;
        }

        // When the Scan button is pressed, need to scan for I2C devices
        private void addressScan_Click(object sender, EventArgs e)
        {
            int found = -1;
            var i = 0;
            var lcdAddress = 124;
            var tempSensorAddress = 144;
            var addressToDiscard = new List<int>();
            addressToDiscard.Add(lcdAddress);
            addressToDiscard.Add(tempSensorAddress);

            this.operationsStatus_Label.Text = "Start to scan for I²C Address...";

            var showFeedback = new Action<I2CData>((I2CData res) => {
                this.operationsStatus_Label.Text = "Scan for I²C Address: 0x" + i.ToString("X2");
                this.statusStrip1.Refresh();

                if (found == -1)
                {
                    this.i2cAddressInput.Text = i.ToString("X2");
                    this.address_navBarStrip.Refresh();

                    if (res.error == I2CError.Success)
                    {
                        found = i;
                        MessageBox.Show("I²C device found at address 0x" + i.ToString("X2"));
                    }
                }
                i += 2;
            });

            List<I2CData> scanResult = this.myDevice.api.ScanI2CAddress(addressToDiscard, showFeedback);

            if (found == -1)
            {
                // No device was found
                MessageBox.Show("I²C device not found");
                this.operationsStatus_Label.Text = "";
            }
            else
            {
                // A device was found
                this.operationsStatus_Label.Text = "I²C Success";
                this.i2cAddressInput.Text = found.ToString("X2");
                this.myDevice.i2cAddress = (byte)found;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////// I2C bus speed selection ///////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the bus speed is changed, the I2C port needs to be reinitialized
        private void changeBusSpeed_Listener(object sender, EventArgs e)
        {
            if (!this.ignoreEvents) // Don't do it during initialization
            {
                char[] chars = { ' ', 'k', 'H', 'z' };
                int busspeedKhz = Convert.ToInt32(this.changeBusSpeed_Combo.Text.Trim(chars));
                //this.myDevice.reinitPort(busspeedKhz);
            }
        }

        // Shows the About form when clicking on the information button
        private void showAboutForm_Click(object sender, EventArgs e)
        {
            new About(this.myDevice.FWversion).ShowDialog();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////// Tree view and data grid views ////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When a new node is selected, the selected cell in the data grid views as well as their colors need to be updated accordingly
        private void selectNodeOnTreeView(object sender, TreeViewEventArgs e)
        {
            if (!this.ignoreEvents) // Don't do it during initialization and during grid update
            {
                this.ignoreEvents = true;

                // Mark the new cells and obtain the row and column of the element to be selected
                dgvUtils.unmarkAllCells();
                int newRow, newCol;
                TagType ttype = getNtagType();
                I2CAccess accessConditions = getAccessConditions(ttype);
                dgvUtils.markCells(ttype, out newRow, out newCol, accessConditions);

                // Select the new cell
                this.hexaTable.CurrentCell = this.hexaTable[newCol, newRow];
                this.asciiTable.CurrentCell = this.asciiTable[newCol, newRow];

                this.ignoreEvents = false;
            }
        }

        private I2CAccess getAccessConditions(TagType tagtype)
        {
            byte[] readBytes;
            String log;
            I2CAccess accConditions = new I2CAccess();
            I2CError error;
            if ((tagtype != TagType.NTAG1K) && (tagtype != TagType.NTAG2K))
            {
                error = this.myDevice.readBlock(getI2CAddress(), 0x39, out readBytes, out log);
                if (error == I2CError.Success)
                {
                    switch ((readBytes[12] & 0x03))
                    {
                        case 0x00:
                            accConditions.accessRights = AccessType.readandwrite;
                            break;
                        case 0x01:
                            accConditions.accessRights = AccessType.onlyread;
                            break;
                        default:
                            accConditions.accessRights = AccessType.noaccess;
                            break;
                    }

                    switch ((readBytes[12] & 0x08))
                    {
                        case 0x08:
                            accConditions.sector1prot = true;
                            break;
                        default:
                            accConditions.sector1prot = false;
                            break;
                    }
                }
                error = this.myDevice.readBlock(getI2CAddress(), 0x38, out readBytes, out log);
                if (error == I2CError.Success)
                {
                    // Mapping the NFC address to the I2C address
                    int rfaddressInt = (int)readBytes[(int)AccessReg.AUTH0];
                    if ((rfaddressInt < 4) & (rfaddressInt >= 0))
                        rfaddressInt = 4;
                    if (rfaddressInt > 235)
                        accConditions.accessRights = AccessType.readandwrite;
                    accConditions.protAreaBegin = BitConverter.GetBytes(rfaddressInt / 4)[0];
                    accConditions.byteOffset = (rfaddressInt % 4) * 4;
                }
            }
            return accConditions;
        }

        // When the cell selected in the first data grid view changes, its colors as well as the tree view and the other data grid view are changed automatically
        private void selectCellOnHexaTable(object sender, EventArgs e)
        {
            int newRow, newCol;
            TagType type = getNtagType();

            if (!this.ignoreEvents && this.initTreeView) // Don't do it during initialization and during grid update
            {
                this.disableEvents();
                dgvUtils.setCurrentAsciiCell();
                dgvUtils.SelectNodeInTreeView(type);
                dgvUtils.unmarkAllCells();
                I2CAccess accessConditions = getAccessConditions(type);
                dgvUtils.markCells(type, out newRow, out newCol, accessConditions);
                this.enableEvents();
            }
        }

        // When the cell selected in the second data grid view changes, its colors as well as the tree view and the other data grid view are changed automatically
        private void selectCellOnAsciiTable(object sender, EventArgs e)
        {
            int newRow, newCol;
            TagType type = getNtagType();
            if (!this.ignoreEvents && this.initTreeView) // Don't do it during initialization and during grid update
            {
                this.disableEvents();
                dgvUtils.setCurrentHexaCell();
                dgvUtils.SelectNodeInTreeView(type);
                dgvUtils.unmarkAllCells();
                I2CAccess accessConditions = getAccessConditions(type);
                dgvUtils.markCells(type, out newRow, out newCol, accessConditions);
                this.enableEvents();
            }
        }

        // When the value of a cell is changed, need to check if it is a right value, and if so, need to update the other data grid view
        private void checkAndSetChangeOnHexaTable_List(object sender, DataGridViewCellEventArgs e)
        {
            if (!this.ignoreEvents) // Don't do it during initialization and during grid update
            {
                byte value;
                if (this.hexaTable.CurrentCell.Value == null)
                    value = 0x00;
                else
                    value = Utils.HexToByte(this.hexaTable.CurrentCell.Value.ToString());

                this.asciiTable.CurrentCell.Value = (char)value;
                this.hexaTable.CurrentCell.Value = value.ToString("X2");
            }
        }

        // When the value of a cell is changed with a new ASCII value, need to update the hexadecimal data grid view
        private void checkAndSetChangeOnAsciiTable_List(object sender, DataGridViewCellEventArgs e)
        {
            if (!this.ignoreEvents) // Don't do it during initialization and during grid update
            {
                this.hexaTable.CurrentCell.Value = ((byte)this.asciiTable.CurrentCell.Value.ToString().ToCharArray()[0]).ToString("X2");
            }
        }

        // When a character is introduced in the ASCII data grid view, jump to the next cell
        private void moveToNextCellOnAsciiTable(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            SendKeys.Send("{Tab}");
        }

        // When the back or delete keys are pressed in the ASCII data grid view, the value is set to 0
        private void setCellToZero(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Back || e.KeyCode == Keys.Delete)
                this.asciiTable.CurrentCell.Value = '\0';
        }

        // When the hexadecimal data grid view is scrolled, the ASCII data grid view is also scrolled
        private void scrollAsciiAsHexaTable(object sender, ScrollEventArgs e)
        {
            this.asciiTable.FirstDisplayedScrollingRowIndex = this.hexaTable.FirstDisplayedScrollingRowIndex;
        }

        // When the ASCII data grid view is scrolled, the hexadecimal data grid view is also scrolled
        private void scrollHexaAsAsciiTable(object sender, ScrollEventArgs e)
        {
            this.hexaTable.FirstDisplayedScrollingRowIndex = this.asciiTable.FirstDisplayedScrollingRowIndex;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////// Config, Session and Access Registers /////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the Config Registers button is pressed, the Config Registers form is shown
        private void showConfigRegPanel_BtnClick(object sender, EventArgs e)
        {
            var type = getNtagType();
            var memory = new NTagMemory(type);

            int numRegs = Enum.GetNames(typeof(ConfigReg)).Length;
            byte[] registers = new byte[numRegs];

            byte configAddress = memory.configMemoryBegin;
            byte i2cAddress = getI2CAddress();

            for (int i = 0; i < numRegs; i++)
                registers[i] = (byte)asciiTable.Rows[configAddress].Cells[i].Value.ToString().ToCharArray()[0];

            if (type == TagType.NTAG1K || type == TagType.NTAG2K)
            {
                // Create the Config Registers form
                ConfigRegPanel_Noplus confForm = new ConfigRegPanel_Noplus(this.myDevice, i2cAddress, configAddress, registers, this.loggingText);
                confForm.ShowDialog();

                // Update the data grid views with the new values of the session registers
                if (confForm.DialogResult == DialogResult.OK || confForm.DialogResult == DialogResult.Cancel)
                {
                    for (int i = 0; i < numRegs; i++)
                    {
                        this.hexaTable.Rows[configAddress].Cells[i].Value = registers[i].ToString("X2");
                        this.asciiTable.Rows[configAddress].Cells[i].Value = (char)registers[i];
                    }
                }
            }
            else
            {
                // Create the Config Registers form
                ConfigRegPanel confForm = new ConfigRegPanel(this.myDevice, i2cAddress, configAddress, registers, this.loggingText);
                confForm.ShowDialog();

                // Update the data grid views with the new values of the session registers
                if (confForm.DialogResult == DialogResult.OK || confForm.DialogResult == DialogResult.Cancel)
                {
                    for (int i = 0; i < numRegs; i++)
                    {
                        this.hexaTable.Rows[configAddress].Cells[i].Value = registers[i].ToString("X2");
                        this.asciiTable.Rows[configAddress].Cells[i].Value = (char)registers[i];
                    }
                }
            }
        }

        // When the Access Registers button is pressed, the Access Registers form is shown
        private void showAccessRegPanel_BtnClick(object sender, EventArgs e)
        {
            var type = getNtagType();
            var memory = new NTagMemory(type);

            int numRegs = Enum.GetNames(typeof(AccessReg)).Length;
            byte[] registers = new byte[numRegs];

            byte accessAddress = memory.accessMemoryBegin;
            byte i2cAddress = getI2CAddress();

            for (int i = 0; i < numRegs; i++)
                registers[i] = (byte)asciiTable.Rows[accessAddress].Cells[i].Value.ToString().ToCharArray()[0];

            // Create the Access Registers form
            AccessRegPanel accForm = new AccessRegPanel(this.myDevice, i2cAddress, accessAddress, registers, this.loggingText);
            accForm.ShowDialog();

            // Update the data grid views with the new values of the access registers
            if (accForm.DialogResult == DialogResult.OK || accForm.DialogResult == DialogResult.Cancel)
            {
                for (int i = 0; i < numRegs; i++)
                {
                    this.hexaTable.Rows[accessAddress].Cells[i].Value = registers[i].ToString("X2");
                    this.asciiTable.Rows[accessAddress].Cells[i].Value = (char)registers[i];
                }
            }
        }

        private byte getI2CAddress()
        {
            byte i2cAddress = Utils.HexToByte(this.i2cAddressInput.Text);
            return i2cAddress;
        }

        private void setI2CAddress(byte address)
        {
            this.myDevice.i2cAddress = address;
            this.i2cAddressInput.Text = address.ToString("X2");
            this.hexaTable.Rows[0].Cells[0].Value = address.ToString("X2");
            this.asciiTable.Rows[0].Cells[0].Value = (char)address;
        }

        // When the Session Registers button is pressed, the Session Registers form is shown
        private void showSessionRegPanel_BtnClick(object sender, EventArgs e)
        {
            // Get the session registers in the data grid view
            byte i2cAddress = getI2CAddress();
            int numRegs = Enum.GetNames(typeof(SessionReg)).Length;
            byte[] registers = new byte[numRegs];
            var type = getNtagType();
            var sessionMemBeg = (int)(new NTagMemory(type).sessionMemoryBegin);


            for (int i = 0; i < numRegs; i++)
                registers[i] = (byte)asciiTable.Rows[(int)NTAG1K.SessionMemoryBegin].Cells[i].Value.ToString().ToCharArray()[0];

            if (type == TagType.NTAG1K || type == TagType.NTAG2K)
            {
                // Create the Session Registers form
                SessionRegPanel_Noplus sesForm = new SessionRegPanel_Noplus(this.myDevice, i2cAddress, registers, this.loggingText);
                sesForm.ShowDialog();
            }
            else
            {
                // Create the Session Registers form
                SessionRegPanel sesForm = new SessionRegPanel(this.myDevice, i2cAddress, registers, this.loggingText);
                sesForm.ShowDialog();
            }
            // Update the data grid views with the new values of the session registers
            /*if (sesForm.DialogResult == DialogResult.OK || sesForm.DialogResult == DialogResult.Cancel)
            {
                for (int i = 0; i < numRegs; i++)
                {
                    this.hexaTable.Rows[sessionMemBeg].Cells[i].Value = registers[i].ToString("X2");
                    this.asciiTable.Rows[sessionMemBeg].Cells[i].Value = (char)registers[i];
                }
            }*/

        }

        private void showPanelifRegPressed(int rowPressed)
        {
            var type = getNtagType();
            var memory = new NTagMemory(type);
            int confAddress = (int)memory.configMemoryBegin;
            int sessionAddress = (int)memory.sessionMemoryBegin;

            if (this.myDevice.isPresent)
            {
                if (rowPressed == confAddress)
                {
                    this.configReg_Btn.PerformClick();
                }
                else
                {
                    if (rowPressed == sessionAddress)
                    {
                        this.sessionReg_Btn.PerformClick();
                    }
                }
            }
        }

        // When a  Config Registers or Session Registers cell is pressed in the ASCII datagrid view, the corresponding dialog opens
        private void showPanelifRegPressed_AsciiClick(object sender, DataGridViewCellEventArgs e)
        {
            var rowPressed = this.asciiTable.CurrentRow.Index;
            showPanelifRegPressed(rowPressed);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////// USB logging /////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // When the USB Logging Enabled checkbox changes, the panel below has to appear/disappear
        private void showOrHideLoggingPanel(object sender, EventArgs e)
        {
            if (this.usbLogging_ChckBox.Checked)
                this.loggingPanel.Height = 250;
            else
                this.loggingPanel.Height = 1;
        }

        // When the Clear button is pressed, clear the log label
        private void clearLoggingPanel(object sender, EventArgs e)
        {
            this.loggingText.Text = "";
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////// Device waiting timer /////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Keeps on checking if a device is present
        private void checkDevicePresence_Tick(object sender, EventArgs e)
        {
            this.checkDevtimer.Stop();

            bool prevStatus = this.myDevice.isPresent;
            bool newStatus = this.myDevice.checkIfPresent(); //I2C_Communications . IsReaderDevicePresent
            //checkDeviceConnectionAndOpenOrCloseIfNeeded & init port also if was not present before but it is now connected
            if (prevStatus != newStatus)
            {
                if (newStatus)
                    showDeviceFound();
                else
                    showDeviceLost();
            }

            this.checkDevtimer.Start();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////// General functions //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Updates the GUI when a device is found
        private void showDeviceFound()
        {
            this.writeBlock_Btn.Enabled = true;
            this.readBlock_Btn.Enabled = true;
            this.writeAll_Btn.Enabled = true;
            this.readAll_Btn.Enabled = true;
            this.reset_Btn.Enabled = true;
            this.scan_Btn.Enabled = true;
            this.writeNdef_Btn.Enabled = true;
            if (getNtagType() == TagType.NTAG1KPlus || getNtagType() == TagType.NTAG2KPlus)
            {
                this.accessReg_Btn.Enabled = true;
            }
            else
            {
                this.accessReg_Btn.Enabled = false;
            }
            this.sessionReg_Btn.Enabled = true;
            this.configReg_Btn.Enabled = true;
            this.operationsStatus_Label.Text = ""; // GetTextError(this.myDevice.error);
            this.deviceStatus_Label.Text = "NTAG I²C hardware detected";
            this.flagStatus_Label.Text = this.myDevice.flag ? "Flag Detect high" : "Flag Detect low";
            this.fwVersion_Label.Text = this.myDevice.FWversion;
        }

        // Updates the GUI when a device is lost
        private void showDeviceLost()
        {
            this.writeBlock_Btn.Enabled = false;
            this.readBlock_Btn.Enabled = false;
            this.writeAll_Btn.Enabled = false;
            this.readAll_Btn.Enabled = false;
            this.reset_Btn.Enabled = false;
            this.scan_Btn.Enabled = false;
            this.writeNdef_Btn.Enabled = false;
            this.accessReg_Btn.Enabled = false;
            this.sessionReg_Btn.Enabled = false;
            this.configReg_Btn.Enabled = false;
            this.operationsStatus_Label.Text = "";
            this.deviceStatus_Label.Text = "NTAG I²C hardware not detected";
            this.flagStatus_Label.Text = "";
            this.fwVersion_Label.Text = "";
        }

        private void ReinitTreeAndGrids_Shown(object sender, EventArgs e)
        {
            TagType ttype = getNtagType();
            I2CAccess accessConditions = getAccessConditions(ttype);
            dgvUtils.ReinitTreeAndGrids(ttype, accessConditions);
        }

        // Translates the I2C error into a text error
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

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////// NDEF parsing /////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Creates a text-type NDEF message
        private void CreateNdefText(byte[] text, out byte[] NDEFmessage)
        {
            // Define the NDEF header
            byte[] ndefHeader = new byte[] { 0x03, (byte)(text.Length + 7), 0xD1, 0x01, (byte)(text.Length + 3), 0x54, 0x02, 0x65, 0x6E };

            // Define the whole NDEF message
            NDEFmessage = new byte[ndefHeader.Length + text.Length + 1];
            Array.Copy(ndefHeader, 0, NDEFmessage, 0, ndefHeader.Length);   // header
            Array.Copy(text, 0, NDEFmessage, ndefHeader.Length, text.Length);   // body
            NDEFmessage[ndefHeader.Length + text.Length] = 0xFE;    // terminator
        }

        // Creates the default NDEF message, which contains a smart poster and an AAR
        private void CreateDefaultNdef(out byte[] NDEFmessage)
        {
            // Define the NDEF contents
            byte[] text = Encoding.UTF8.GetBytes("NTAG I2C EXPLORER".ToCharArray());
            byte[] uri = Encoding.UTF8.GetBytes("http://www.nxp.com/demoboard/OM5569".ToCharArray());
            byte[] aar = Encoding.UTF8.GetBytes("android.com:pkgcom.nxp.ntagi2cdemo".ToCharArray());

            // Define the NDEF headers
            byte[] spHeader = new byte[] { 0x03, (byte)(text.Length + uri.Length + aar.Length + 20), 0x91, 0x02, (byte)(text.Length + uri.Length + 12), 0x53, 0x70 };
            byte[] textHeader = new byte[] { 0x91, 0x01, (byte)(text.Length + 3), 0x54, 0x02, 0x65, 0x6E };
            byte[] uriHeader = new byte[] { 0x51, 0x01, (byte)(uri.Length + 1), 0x55, 0x01 };
            byte[] aarHeader = new byte[] { 0x54, 0x0F, 0x13 };

            // Define the whole NDEF message
            NDEFmessage = new byte[spHeader.Length + textHeader.Length + text.Length + uriHeader.Length + uri.Length + aarHeader.Length + aar.Length + 1];
            Array.Copy(spHeader, 0, NDEFmessage, 0, spHeader.Length);   // Smart Poster header
            Array.Copy(textHeader, 0, NDEFmessage, spHeader.Length, textHeader.Length);   // text header
            Array.Copy(text, 0, NDEFmessage, spHeader.Length + textHeader.Length, text.Length);   // text
            Array.Copy(uriHeader, 0, NDEFmessage, spHeader.Length + textHeader.Length + text.Length, uriHeader.Length);   // URI header
            Array.Copy(uri, 0, NDEFmessage, spHeader.Length + textHeader.Length + text.Length + uriHeader.Length, uri.Length);   // URI
            Array.Copy(aarHeader, 0, NDEFmessage, spHeader.Length + textHeader.Length + text.Length + uriHeader.Length + uri.Length, aarHeader.Length);   // AAR header
            Array.Copy(aar, 0, NDEFmessage, spHeader.Length + textHeader.Length + text.Length + uriHeader.Length + uri.Length + aarHeader.Length, aar.Length);   // AAR
            NDEFmessage[spHeader.Length + textHeader.Length + text.Length + uriHeader.Length + uri.Length + aarHeader.Length + aar.Length] = 0xFE;  // terminator
        }

        // Shows the written NDEF message in the data grid views
        private void ShowNdef(byte[] NDEFmessage)
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



    }
}
