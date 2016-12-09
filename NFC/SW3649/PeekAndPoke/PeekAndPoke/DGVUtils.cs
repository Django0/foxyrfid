using NTAG_I2C.Contracts;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PeekAndPoke
{
    public class DGVUtils
    {
        private DataGridView hexaTable;
        private DataGridView asciiTable;
        private TreeView memoryTreeView;

        public DGVUtils(DataGridView hexaTable, DataGridView asciiTable, TreeView memoryTree)
        {
            this.hexaTable = hexaTable;
            this.asciiTable = asciiTable;
            this.memoryTreeView = memoryTree;
        }

        // Parses the content in the data grid views and marks the TLVs in different colors
        public void markTlvs(TagType type)
        {
            //var memory = new NTagMemory(getNtagType());
            var memory = new NTagMemory(type);

            // Mark the Capability Container and lock bytes
            for (int i = (int)ConfigBlock.CapabilityContainer; i < NtagI2CDevice.bytesInBlock; i++)   // Capability Container
            {
                hexaTable.Rows[memory.userMemoryBegin].Cells[i].Style.BackColor = Color.LightBlue;
                asciiTable.Rows[memory.userMemoryBegin].Cells[i].Style.BackColor = Color.LightBlue;
            }
            for (int i = (int)ConfigBlock.LockBytes; i < (int)ConfigBlock.CapabilityContainer; i++)   // Static lock bytes
            {
                hexaTable.Rows[memory.userMemoryBegin].Cells[i].Style.BackColor = Color.Orange;
                asciiTable.Rows[memory.userMemoryBegin].Cells[i].Style.BackColor = Color.Orange;
            }
            for (int i = memory.dynLockBytesPos; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)  // Dynamic lock bytes
            {
                hexaTable.Rows[memory.userMemoryEnd - 1].Cells[i].Style.BackColor = Color.Gold;
                asciiTable.Rows[memory.userMemoryEnd - 1].Cells[i].Style.BackColor = Color.Gold;
            }

            // Mark the TLVs and reserved area
            int j = 0;
            bool finish = false;
            do
            {
                byte curByte = (byte)asciiTable.Rows[j / 16 + 1].Cells[j % 16].Value.ToString().ToCharArray()[0];
                switch (curByte)
                {
                    case 0x01:  // Lock Control TLV
                        markTlv(ref j, Color.Yellow);
                        break;
                    case 0x02:  // Memory Control TLV
                        markReservedArea(hexaTable, asciiTable, j);
                        markTlv(ref j, Color.Plum);
                        break;
                    case 0x03:// NDEF Message TLV
                        markTlv(ref j, Color.Lime);
                        break;
                    case 0xFE:  // Terminator
                        hexaTable.Rows[j / 16 + 1].Cells[j % 16].Style.BackColor = Color.Red;
                        asciiTable.Rows[j / 16 + 1].Cells[j % 16].Style.BackColor = Color.Red;
                        finish = true;
                        break;
                    default:
                        finish = true;
                        break;
                }

            } while (!finish);
        }

        // Marks a whole TLV with the color indicated
        public void markTlv(ref int offset, Color color)
        {
            // Paint the T cell
            hexaTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;
            asciiTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;

            // Get the length and paint the L cell
            offset++;
            int length = Convert.ToInt32(hexaTable.Rows[offset / 16 + 1].Cells[offset % 16].Value.ToString(), 16);

            if (length == 0xFF && color == Color.Lime)
            {
                var row = hexaTable.Rows[offset / 16 + 1];
                var ms = Convert.ToInt32(hexaTable.Rows[offset / 16 + 1].Cells[2].Value.ToString(), 16);
                var ls = Convert.ToInt32(hexaTable.Rows[offset / 16 + 1].Cells[3].Value.ToString(), 16);
                length = ms * 256 + ls + 3;
            }
            hexaTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;
            asciiTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;

            // Paint the cells from the V field
            offset++;
            for (int i = 0; i < length; i++, offset++)
            {
                hexaTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;
                asciiTable.Rows[offset / 16 + 1].Cells[offset % 16].Style.BackColor = color;
            }
        }

        // Marks the reserved area as indicated in the Memory Control TLV
        public void markReservedArea(DataGridView hexaTable, DataGridView asciiTable, int offset)
        {
            // Get the Memory Control TLV value
            byte[] mcValue = new byte[3];
            mcValue[0] = (byte)asciiTable.Rows[(offset + 2) / 16 + 1].Cells[(offset + 2) % 16].Value.ToString().ToCharArray()[0];
            mcValue[1] = (byte)asciiTable.Rows[(offset + 3) / 16 + 1].Cells[(offset + 3) % 16].Value.ToString().ToCharArray()[0];
            mcValue[2] = (byte)asciiTable.Rows[(offset + 4) / 16 + 1].Cells[(offset + 4) % 16].Value.ToString().ToCharArray()[0];

            // Parse the value
            int pageAddr = (byte)((mcValue[0] & 0xF0) >> 4);
            int byteOffset = (byte)(mcValue[0] & 0x0F);
            int size = mcValue[1];
            int bytesPerPage = (byte)(mcValue[2] & 0x0F);
            int byteAddr = pageAddr * (int)Math.Pow(2, bytesPerPage) + byteOffset;

            // Mark the reserved area
            for (int i = 0; i < size; i++, byteAddr++)
            {
                if (byteAddr < hexaTable.RowCount * hexaTable.ColumnCount)
                {
                    hexaTable.Rows[byteAddr / 16 + 1].Cells[byteAddr % 16].Style.BackColor = Color.LightGray;
                    asciiTable.Rows[byteAddr / 16 + 1].Cells[byteAddr % 16].Style.BackColor = Color.LightGray;
                }
            }
        }

        // Paints all the cells in both data grid views white
        public void unmarkAllCells()
        {
            // Unmark all the cells
            for (int i = 0; i < NtagI2CDevice.blocks; i++)
                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                {
                    this.hexaTable.Rows[i].Cells[j].Style.BackColor = Color.White;
                    this.asciiTable.Rows[i].Cells[j].Style.BackColor = Color.White;
                }
        }

        // Paints the corresponding cells with the appropriate colors, and returns the cell to be selected
        public  void markCells(TagType type, out int row, out int col, I2CAccess accessConditions)
        {
            row = 0;
            col = this.hexaTable.CurrentCell.ColumnIndex;

            var memory = new NTagMemory(type);


            if ((type == TagType.NTAG1K) || (type == TagType.NTAG2K))                                       //Routine for 1K and 2K
            {
                // Check what type of node is the selected node
                if (this.memoryTreeView.SelectedNode.Parent == null)
                {
                    // The selected node is a parent node
                    // Check the node
                    switch (this.memoryTreeView.SelectedNode.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Mark the new row
                            this.hexaTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            this.asciiTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            for (int i = (int)ConfigBlock.SerialNumber; i < (int)ConfigBlock.InternalData; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.InternalData; i < (int)ConfigBlock.LockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.LockBytes; i < (int)ConfigBlock.CapabilityContainer; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)ConfigBlock.CapabilityContainer; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 1: // User memory node
                            row = memory.userMemoryBegin + 1;
                            // Mark the whole user memory
                            for (int i = row; i < memory.userMemoryEnd - 1; i++)
                                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                {
                                    this.hexaTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                }
                            if(memory.dynLockBytesPos!=0)
                            {
                                for (int j = 0; j < memory.dynLockBytesPos; j++)
                                {
                                    this.hexaTable.Rows[memory.userMemoryEnd - 1].Cells[j].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[memory.userMemoryEnd - 1].Cells[j].Style.BackColor = Color.LightGreen;
                                }
                            }
                            break;

                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryEnd - 1;
                            // Mark the new row
                            /*
                            for (int i = 0; i < memory.dynLockBytesPos; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            */
                            for (int i = memory.dynLockBytesPos; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                        case 3: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Mark the new row
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            for (int i = 0; i < numConfRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                        case 4: // SRAM node
                            row = memory.SRAMMemoryBegin;
                            // Mark the whole SRAM
                            for (int i = row; i < memory.SRAMMemoryEnd; i++)
                                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                {
                                    this.hexaTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                }
                            break;
                        case 5: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Mark new row
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            for (int i = 0; i < numSesRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                    }
                }
                else
                {
                    // The selected node is a child node
                    // Check the parent node
                    switch (this.memoryTreeView.SelectedNode.Parent.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Check the subnode
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                case 0: // I2C address
                                    col = (int)ConfigBlock.I2Caddress;
                                    this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    break;
                                case 1: // Serial Number
                                    col = (int)ConfigBlock.SerialNumber;
                                    for (int i = col; i < (int)ConfigBlock.InternalData; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 2: // Internal data
                                    col = (int)ConfigBlock.InternalData;
                                    for (int i = col; i < (int)ConfigBlock.LockBytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 3: // Lock bytes
                                    col = (int)ConfigBlock.LockBytes;
                                    for (int i = col; i < (int)ConfigBlock.CapabilityContainer; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 4: // Capability Container
                                    col = (int)ConfigBlock.CapabilityContainer;
                                    for (int i = col; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                            }
                            break;
                        case 1: // User memory node
                            row = this.memoryTreeView.SelectedNode.Index + (memory.userMemoryBegin + 1);
                            // Mark the corresponding row
                            if ((row != memory.userMemoryEnd-1)||(memory.dynLockBytesPos==0))
                            { 
                                for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                }
                            }
                            else
                            {
                                for (int i = 0; i < 8; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                }
                            }
                            break;
                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryEnd - 1;
                            if (memory.dynLockBytesPos != 0)  // 1K device
                            {
                                // Check the subnode
                                switch (this.memoryTreeView.SelectedNode.Index)
                                {
                                    /*case 0: // User memory
                                        col = 0;
                                        for (int i = col; i < memory.dynLockBytesPos; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        }
                                        break;
                                    */
                                    case 0: // Dynamic lock bytes
                                        col = memory.dynLockBytesPos;
                                        for (int i = col; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        }
                                        break;
                                    case 1: // Fixed bytes
                                        col = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes;
                                        for (int i = col; i < NtagI2CDevice.bytesInBlock; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        }
                                        break;
                                }
                            }
                            else  // 2K device
                            {
                                // Check the subnode
                                switch (this.memoryTreeView.SelectedNode.Index)
                                {
                                    case 0: // Dynamic lock bytes
                                        col = memory.dynLockBytesPos;
                                        for (int i = col; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        }
                                        break;
                                    case 1: // Fixed bytes
                                        col = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes;
                                        for (int i = col; i < NtagI2CDevice.bytesInBlock; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        }
                                        break;
                                }
                            }
                            break;
                        case 3: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            if (col < numConfRegs)
                            {
                                // Configuration registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                        case 4: // SRAM node
                            row = memory.SRAMMemoryBegin + this.memoryTreeView.SelectedNode.Index;
                            // Mark the corresponding row
                            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 5: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            if (col < numSesRegs)
                            {
                                // Session registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                    }
                }
            }
            else if (type == TagType.NTAG1KPlus)                                                            //Routine for 1KPlus
            {
                // Check what type of node is the selected node
                if (this.memoryTreeView.SelectedNode.Parent == null)
                {
                    // The selected node is a parent node
                    // Check the node
                    switch (this.memoryTreeView.SelectedNode.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Mark the new row
                            this.hexaTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            this.asciiTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            for (int i = (int)ConfigBlock.SerialNumber; i < (int)ConfigBlock.InternalData; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.InternalData; i < (int)ConfigBlock.LockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.LockBytes; i < (int)ConfigBlock.CapabilityContainer; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)ConfigBlock.CapabilityContainer; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 1: // User memory node
                            
                            row = memory.userMemoryBegin + 1;
                            Color blockMemColor = Color.LightGreen;    
                            // Mark the whole user memory
                            for (int i = row; i < memory.userMemoryEnd - 1; i++)
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (i == accessConditions.protAreaBegin))
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        if(j == accessConditions.byteOffset)
                                        {
                                            blockMemColor = Color.LightSalmon; 
                                        }
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    }
                                }
                                else
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    } 
                                }
                            }
                            for (int j = 0; j < 8; j++) //Paint the part of user memory in DynLockBytes
                            {
                                this.hexaTable.Rows[memory.userMemoryEnd - 1].Cells[j].Style.BackColor = blockMemColor;
                                this.asciiTable.Rows[memory.userMemoryEnd - 1].Cells[j].Style.BackColor = blockMemColor;
                            }
                            break;
                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryEnd - 1;
                            // Mark the new row
                            /*
                            for (int i = 0; i < memory.dynLockBytesPos; i++)
                            {
                                blockMemColor = Color.LightGray;
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                            }
                            */
                            for (int i = memory.dynLockBytesPos; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i < NtagI2CDevice.bytesInBlock-1; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                        case 3: // Memory protection registers node
                            row = memory.memProtBegin;    
                            //Mark AUTH0
                            this.hexaTable.Rows[row].Cells[(int)AccessReg.AUTH0].Style.BackColor = Color.LightGreen;
                            this.asciiTable.Rows[row].Cells[(int)AccessReg.AUTH0].Style.BackColor = Color.LightGreen;
                            row++;
                            for (int i = (int)AccessReg.ACCESS; i < (int)AccessReg.ACCESS + (int)NtagI2CDevice.accessbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU1; i < (int)AccessReg.RFU1 + (int)NtagI2CDevice.rfu1bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PWD; i < (int)AccessReg.PWD + (int)NtagI2CDevice.pwdbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PACK; i < (int)AccessReg.PACK + (int)NtagI2CDevice.packbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU2; i < (int)AccessReg.RFU2 + (int)NtagI2CDevice.rfu2bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PT_I2C; i < (int)AccessReg.PT_I2C + (int)NtagI2CDevice.pti2cbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU3; i < (int)AccessReg.RFU3 + (int)NtagI2CDevice.rfu3bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 4: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Mark the new row
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            for (int i = 0; i < numConfRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                        case 5: // SRAM node
                            row = memory.SRAMMemoryBegin;
                            // Mark the whole SRAM
                            for (int i = row; i < memory.SRAMMemoryEnd; i++)
                                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                {
                                    this.hexaTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                }
                            break;
                        case 6: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Mark new row
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            for (int i = 0; i < numSesRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                    }
                }
                else
                {
                    // The selected node is a child node
                    // Check the parent node
                    switch (this.memoryTreeView.SelectedNode.Parent.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Check the subnode
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                case 0: // I2C address
                                    col = (int)ConfigBlock.I2Caddress;
                                    this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    break;
                                case 1: // Serial Number
                                    col = (int)ConfigBlock.SerialNumber;
                                    for (int i = col; i < (int)ConfigBlock.InternalData; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 2: // Internal data
                                    col = (int)ConfigBlock.InternalData;
                                    for (int i = col; i < (int)ConfigBlock.LockBytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 3: // Lock bytes
                                    col = (int)ConfigBlock.LockBytes;
                                    for (int i = col; i < (int)ConfigBlock.CapabilityContainer; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 4: // Capability Container
                                    col = (int)ConfigBlock.CapabilityContainer;
                                    for (int i = col; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                            }
                            break;
                        case 1: // User memory node
                            row = this.memoryTreeView.SelectedNode.Index + (memory.userMemoryBegin + 1);
                            // Mark the corresponding row
                            Color blockMemColor = Color.LightGreen;
                            if (row != memory.userMemoryEnd - 1)
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row == accessConditions.protAreaBegin))
                                {
                                    for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        if (i == accessConditions.byteOffset)
                                        {
                                            blockMemColor = Color.LightSalmon;
                                        }
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                }
                                else if ((accessConditions.accessRights != AccessType.readandwrite) && (row > accessConditions.protAreaBegin))
                                {
                                    blockMemColor = Color.LightSalmon;
                                    for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                }
                            }
                            else
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row > accessConditions.protAreaBegin))
                                {
                                    blockMemColor = Color.LightSalmon;
                                }
                                for (int i = 0; i < 8; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                }
                            }
                            break;
                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryEnd - 1; 
                            // Check the subnode
                                switch (this.memoryTreeView.SelectedNode.Index)
                                {
                                    /*
                                    case 0: // User memory
                                        col = 0;
                                        for (int i = col; i < memory.dynLockBytesPos; i++)
                                        {
                                            blockMemColor = Color.LightGreen;
                                            if ((accessConditions.accessRights != AccessType.readandwrite) && (row >= accessConditions.protAreaBegin))
                                            {
                                                blockMemColor = Color.LightSalmon;
                                            }
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        }
                                        break;
                                    */
                                    case 0: // Dynamic lock bytes
                                        col = memory.dynLockBytesPos;
                                        for (int i = col; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        }
                                        break;
                                    case 1: // Fixed bytes
                                        col = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes;
                                        for (int i = col; i < NtagI2CDevice.bytesInBlock - 1; i++)
                                        {
                                            this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                            this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        }
                                        break;
                                }
                            break;
                        case 3: // Access register node
                            row = memory.accessMemoryBegin + 1;
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                case 0: // AUTH0
                                    row--;
                                    col = (int)AccessReg.AUTH0;
                                    this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                    break;
                                case 1: // ACCESS
                                    col = (int)AccessReg.ACCESS;
                                    for (int i = col; i < col + NtagI2CDevice.accessbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 2: // PWD
                                    col = (int)AccessReg.PWD;
                                    for (int i = col; i < col + NtagI2CDevice.pwdbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 3: // PACK
                                    col = (int)AccessReg.PACK;
                                    for (int i = col; i < col + NtagI2CDevice.packbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 4: // PT_I2C
                                    col = (int)AccessReg.PT_I2C;
                                    for (int i = col; i < col + NtagI2CDevice.pti2cbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 5: // RFU
                                    col = (int)AccessReg.RFU1;
                                    for (int i = col; i < col + NtagI2CDevice.rfu1bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    col = (int)AccessReg.RFU2;
                                    for (int i = col; i < col + NtagI2CDevice.rfu2bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    col = (int)AccessReg.RFU3;
                                    for (int i = col; i < col + NtagI2CDevice.rfu3bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                            }
                            break;
                        case 4: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            if (col < numConfRegs)
                            {
                                // Configuration registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                        case 5: // SRAM node
                            row = memory.SRAMMemoryBegin + this.memoryTreeView.SelectedNode.Index;
                            // Mark the corresponding row
                            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 6: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            if (col < numSesRegs)
                            {
                                // Session registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                    }
                }
            }
            else if (type == TagType.NTAG2KPlus)                                                            //Routine for 2KPlus
            {
                // Check what type of node is the selected node
                if (this.memoryTreeView.SelectedNode.Parent == null)
                {
                    // The selected node is a parent node
                    // Check the node
                    switch (this.memoryTreeView.SelectedNode.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Mark the new row
                            this.hexaTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            this.asciiTable.Rows[row].Cells[(int)ConfigBlock.I2Caddress].Style.BackColor = Color.Red;
                            for (int i = (int)ConfigBlock.SerialNumber; i < (int)ConfigBlock.InternalData; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.InternalData; i < (int)ConfigBlock.LockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            for (int i = (int)ConfigBlock.LockBytes; i < (int)ConfigBlock.CapabilityContainer; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)ConfigBlock.CapabilityContainer; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 1: // User memory node (Part1)
                            row = memory.userMemoryS1Begin + 1;
                            Color blockMemColor = Color.LightGreen;    
                            // Mark the whole user memory
                            for (int i = row; i < memory.userMemoryS1End - 1; i++)
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (i == accessConditions.protAreaBegin))
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        if(j == accessConditions.byteOffset)
                                        {
                                            blockMemColor = Color.LightSalmon; 
                                        }
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    }
                                }
                                else
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    } 
                                }
                            }
                            for (int j = 0; j < 8; j++) //Paint the part of user memory in DynLockBytes
                            {
                                this.hexaTable.Rows[memory.userMemoryS1End - 1].Cells[j].Style.BackColor = blockMemColor;
                                this.asciiTable.Rows[memory.userMemoryS1End - 1].Cells[j].Style.BackColor = blockMemColor;
                            }
                            break;
                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryS1End - 1;
                            // Mark the new row
                            /*
                            for (int i = 0; i < memory.dynLockBytesPos; i++)
                            {
                                blockMemColor = Color.LightGreen;
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row >= accessConditions.protAreaBegin))
                                {
                                    blockMemColor = Color.LightSalmon;
                                }
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                            }
                            */
                            for (int i = memory.dynLockBytesPos; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i < NtagI2CDevice.bytesInBlock - 1; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                        case 3: // Memory protection registers node
                            row = memory.memProtBegin;
                            //Mark AUTH0
                            this.hexaTable.Rows[row].Cells[(int)AccessReg.AUTH0].Style.BackColor = Color.LightGreen;
                            this.asciiTable.Rows[row].Cells[(int)AccessReg.AUTH0].Style.BackColor = Color.LightGreen;
                            row++;
                            for (int i = (int)AccessReg.ACCESS; i < (int)AccessReg.ACCESS + (int)NtagI2CDevice.accessbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU1; i < (int)AccessReg.RFU1 + (int)NtagI2CDevice.rfu1bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PWD; i < (int)AccessReg.PWD + (int)NtagI2CDevice.pwdbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PACK; i < (int)AccessReg.PACK + (int)NtagI2CDevice.packbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU2; i < (int)AccessReg.RFU2 + (int)NtagI2CDevice.rfu2bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.PT_I2C; i < (int)AccessReg.PT_I2C + (int)NtagI2CDevice.pti2cbytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = (int)AccessReg.RFU3; i < (int)AccessReg.RFU3 + (int)NtagI2CDevice.rfu3bytes; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 4: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Mark the new row
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            for (int i = 0; i < numConfRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;

                        case 5: // User Memory (Part 2)
                            row = memory.userMemoryS2Begin;
                            
                            blockMemColor = Color.LightGreen;    
                            // Mark the whole user memory
                            for (int i = row; i < memory.userMemoryS2End - 1; i++)
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (i == accessConditions.protAreaBegin)&&(accessConditions.sector1prot))
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        if(j == accessConditions.byteOffset)
                                        {
                                            blockMemColor = Color.LightSalmon; 
                                        }
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    }
                                }
                                else if((accessConditions.accessRights != AccessType.readandwrite) && (i > accessConditions.protAreaBegin)&&(accessConditions.sector1prot))
                                {
                                    blockMemColor = Color.LightSalmon;
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    } 
                                }
                                else
                                {
                                    for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                    {
                                        this.hexaTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[i].Cells[j].Style.BackColor = blockMemColor;
                                    } 
                                }
                            }
                            break;

                        case 6: // SRAM node
                            row = memory.SRAMMemoryBegin;
                            // Mark the whole SRAM
                            for (int i = row; i < memory.SRAMMemoryEnd; i++)
                                for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
                                {
                                    this.hexaTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[i].Cells[j].Style.BackColor = Color.LightGreen;
                                }
                            break;
                        case 7: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Mark new row
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            for (int i = 0; i < numSesRegs; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                            }
                            break;
                    }
                }
                else
                {
                    // The selected node is a child node
                    // Check the parent node
                    switch (this.memoryTreeView.SelectedNode.Parent.Index)
                    {
                        case 0: // Configuration node
                            row = memory.userMemoryBegin;
                            // Check the subnode
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                case 0: // I2C address
                                    col = (int)ConfigBlock.I2Caddress;
                                    this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.Red;
                                    break;
                                case 1: // Serial Number
                                    col = (int)ConfigBlock.SerialNumber;
                                    for (int i = col; i < (int)ConfigBlock.InternalData; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 2: // Internal data
                                    col = (int)ConfigBlock.InternalData;
                                    for (int i = col; i < (int)ConfigBlock.LockBytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                                case 3: // Lock bytes
                                    col = (int)ConfigBlock.LockBytes;
                                    for (int i = col; i < (int)ConfigBlock.CapabilityContainer; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 4: // Capability Container
                                    col = (int)ConfigBlock.CapabilityContainer;
                                    for (int i = col; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                            }
                            break;
                        case 1: // User memory node
                            row = this.memoryTreeView.SelectedNode.Index + (memory.userMemoryS1Begin + 1);
                            Color blockMemColor = Color.LightGreen;
                            if (row != memory.userMemoryS1End - 1)
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row == accessConditions.protAreaBegin))
                                {
                                    for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        if (i == accessConditions.byteOffset)
                                        {
                                            blockMemColor = Color.LightSalmon;
                                        }
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                }
                                else
                                {
                                    if ((accessConditions.accessRights != AccessType.readandwrite) && (row > accessConditions.protAreaBegin))
                                    {
                                        blockMemColor = Color.LightSalmon;
                                    }
                                    for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                }
                            }
                            else
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row > accessConditions.protAreaBegin))
                                {
                                    blockMemColor = Color.LightSalmon;
                                }
                                for (int i = 0; i < 8; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                }
                            }
                            break;
                        case 2: // Dynamic lock bytes node
                            row = memory.userMemoryS1End - 1; 
                            // Check the subnode
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                /*
                                case 0: // User memory
                                    col = 0;
                                    for (int i = col; i < memory.dynLockBytesPos; i++)
                                    {
                                        blockMemColor = Color.LightGreen;
                                        if ((accessConditions.accessRights != AccessType.readandwrite) && (row >= accessConditions.protAreaBegin))
                                        {
                                            blockMemColor = Color.LightSalmon;
                                        }
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    }
                                    break;
                                */
                                case 0: // Dynamic lock bytes
                                    col = memory.dynLockBytesPos;
                                    for (int i = col; i < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 1: // Fixed bytes
                                    col = memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes;
                                    for (int i = col; i < NtagI2CDevice.bytesInBlock - 1; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                            }
                            break;
                        case 3: // Access register node
                            row = memory.accessMemoryBegin + 1;
                            switch (this.memoryTreeView.SelectedNode.Index)
                            {
                                case 0: // AUTH0
                                    row--;
                                    col = (int)AccessReg.AUTH0;
                                    this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                    this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                    break;
                                case 1: // ACCESS
                                    col = (int)AccessReg.ACCESS;
                                    for (int i = col; i < col + NtagI2CDevice.accessbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 2: // PWD
                                    col = (int)AccessReg.PWD;
                                    for (int i = col; i < col + NtagI2CDevice.pwdbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 3: // PACK
                                    col = (int)AccessReg.PACK;
                                    for (int i = col; i < col + NtagI2CDevice.packbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 4: // PT_I2C
                                    col = (int)AccessReg.PT_I2C;
                                    for (int i = col; i < col + NtagI2CDevice.pti2cbytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                    }
                                    break;
                                case 5: // RFU
                                    col = (int)AccessReg.RFU1;
                                    for (int i = col; i < col + NtagI2CDevice.rfu1bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    col = (int)AccessReg.RFU2;
                                    for (int i = col; i < col + NtagI2CDevice.rfu2bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    col = (int)AccessReg.RFU3;
                                    for (int i = col; i < col + NtagI2CDevice.rfu3bytes; i++)
                                    {
                                        this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                        this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    }
                                    break;
                            }
                            break;
                        case 4: // Configuration registers node
                            row = memory.configMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numConfRegs = Enum.GetNames(typeof(ConfigReg)).Length;
                            if (col < numConfRegs)
                            {
                                // Configuration registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numConfRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                        case 5: // User Memory (Part2)
                            row = this.memoryTreeView.SelectedNode.Index + (memory.userMemoryS2Begin);
                            blockMemColor = Color.LightGreen;
                            if ((accessConditions.accessRights != AccessType.readandwrite) && (row == accessConditions.protAreaBegin)&&(accessConditions.sector1prot))
                            {
                                for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    if (i == accessConditions.byteOffset)
                                    {
                                        blockMemColor = Color.LightSalmon;
                                    }
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                }
                            }
                            else
                            {
                                if ((accessConditions.accessRights != AccessType.readandwrite) && (row > accessConditions.protAreaBegin) && (accessConditions.sector1prot))
                                {
                                    blockMemColor = Color.LightSalmon;
                                }
                                for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = blockMemColor;
                                }
                            }
                            break;
                        case 6: // SRAM node
                            row = memory.SRAMMemoryBegin + this.memoryTreeView.SelectedNode.Index;
                            // Mark the corresponding row
                            for (int i = 0; i < NtagI2CDevice.bytesInBlock; i++)
                            {
                                this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGreen;
                            }
                            break;
                        case 7: // Session registers node
                            row = memory.sessionMemoryBegin;
                            // Check the subnode
                            col = this.memoryTreeView.SelectedNode.Index;
                            int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                            if (col < numSesRegs)
                            {
                                // Session registers
                                this.hexaTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                                this.asciiTable.Rows[row].Cells[col].Style.BackColor = Color.LightGreen;
                            }
                            else
                            {
                                // Fixed bytes
                                for (int i = numSesRegs; i < NtagI2CDevice.bytesInBlock; i++)
                                {
                                    this.hexaTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                    this.asciiTable.Rows[row].Cells[i].Style.BackColor = Color.LightGray;
                                }
                            }
                            break;
                    }
                }
            }
        }

        // Resets the two data grid views
        public void resetGrids(TagType type)
        {
            int configAddress = 0;
            int sessionAddress = (int)NTAG1K.SessionMemoryBegin;

            var hexaArr = new string[NtagI2CDevice.bytesInBlock];
            var asciiArr = new string[NtagI2CDevice.bytesInBlock];
            for (int j = 0; j < NtagI2CDevice.bytesInBlock; j++)
            {
                hexaArr[j] = "00";
                asciiArr[j] = "\0";
            }

            for (int i = 0; i < NtagI2CDevice.blocks; i++)
            {
                this.hexaTable.Rows[i].SetValues(hexaArr);
                this.asciiTable.Rows[i].SetValues(asciiArr);

            }

            // Block 0
            this.hexaTable.Rows[0].Cells[0].Value = "AA"; // I2C address
            this.asciiTable.Rows[0].Cells[0].Value = (char)0xAA;

            this.hexaTable.Rows[0].Cells[0].ReadOnly = true;
            this.asciiTable.Rows[0].Cells[0].ReadOnly = true;

            this.hexaTable.Rows[0].Cells[12].Value = "E1";
            this.asciiTable.Rows[0].Cells[12].Value = (char)0xE1;
            this.hexaTable.Rows[0].Cells[13].Value = "10";
            this.asciiTable.Rows[0].Cells[13].Value = (char)0x10;

            switch (type)
            {
                case TagType.NTAG1K: // 1kB device
                    this.hexaTable.Rows[0].Cells[14].Value = "6D";
                    this.asciiTable.Rows[0].Cells[14].Value = (char)0x6D;
                    configAddress = (byte)NTAG1K.ConfigMemoryBegin;
                    break;
                case TagType.NTAG2K: // 2kB device
                    this.hexaTable.Rows[0].Cells[14].Value = "EA";
                    this.asciiTable.Rows[0].Cells[14].Value = (char)0xEA;
                    configAddress = (byte)NTAG2K.ConfigMemoryBegin;
                    break;
            }

            // Block 1
            this.hexaTable.Rows[1].Cells[0].Value = "03";
            this.asciiTable.Rows[1].Cells[0].Value = (char)0x03;
            this.hexaTable.Rows[1].Cells[2].Value = "FE";
            this.asciiTable.Rows[1].Cells[2].Value = (char)0xFE;

            // Configuration registers
            this.hexaTable.Rows[configAddress].Cells[0].Value = "01";
            this.asciiTable.Rows[configAddress].Cells[0].Value = (char)0x01;
            this.hexaTable.Rows[configAddress].Cells[2].Value = "F8";
            this.asciiTable.Rows[configAddress].Cells[2].Value = (char)0xF8;
            this.hexaTable.Rows[configAddress].Cells[3].Value = "48";
            this.asciiTable.Rows[configAddress].Cells[3].Value = (char)0x48;
            this.hexaTable.Rows[configAddress].Cells[4].Value = "08";
            this.asciiTable.Rows[configAddress].Cells[4].Value = (char)0x08;
            this.hexaTable.Rows[configAddress].Cells[5].Value = "01";
            this.asciiTable.Rows[configAddress].Cells[5].Value = (char)0x01;

            // Session registers            
            this.hexaTable.Rows[sessionAddress].Cells[0].Value = "01";
            this.asciiTable.Rows[sessionAddress].Cells[0].Value = (char)0x01;
            this.hexaTable.Rows[sessionAddress].Cells[2].Value = "F8";
            this.asciiTable.Rows[sessionAddress].Cells[2].Value = (char)0xF8;
            this.hexaTable.Rows[sessionAddress].Cells[3].Value = "48";
            this.asciiTable.Rows[sessionAddress].Cells[3].Value = (char)0x48;
            this.hexaTable.Rows[sessionAddress].Cells[4].Value = "08";
            this.asciiTable.Rows[sessionAddress].Cells[4].Value = (char)0x08;
            this.hexaTable.Rows[sessionAddress].Cells[5].Value = "01";
            this.asciiTable.Rows[sessionAddress].Cells[5].Value = (char)0x01;
        }

        public byte[][] readAsciiTableContent()
        {
            List<byte[]> tableData = new List<byte[]>();
            // Don't write block 0, it would modify the I2C address
            for (int block = 1; block < NtagI2CDevice.blocks; block++)
            {
                if (this.asciiTable.Rows[block].Visible)
                {
                    var blockContent = new byte[NtagI2CDevice.bytesInBlock];
                    for (int blockAdd = 0; blockAdd < NtagI2CDevice.bytesInBlock; blockAdd++)
                    {
                        blockContent[blockAdd] = (byte)this.asciiTable.Rows[block].Cells[blockAdd].Value.ToString().ToCharArray()[0];
                    }
                    tableData.Add(blockContent);
                }
            }
            return tableData.ToArray();
        }

        public void setCurrentAsciiCell()
        {
            this.asciiTable.CurrentCell = this.asciiTable[this.hexaTable.CurrentCell.ColumnIndex, this.hexaTable.CurrentCell.RowIndex];
        }

        public void setCurrentHexaCell()
        {
            this.hexaTable.CurrentCell = this.hexaTable[this.asciiTable.CurrentCell.ColumnIndex, this.asciiTable.CurrentCell.RowIndex];
        }

        // Reinitializes the tree view and the two data grid views with the data from the selected device type
        public void ReinitTreeAndGrids(TagType type, I2CAccess accessConditions)
        {
            // Generate the tree view
            UpdateTreeView(type);

            // Show only the right rows from the data grid views, and with their initial content
            UpdateGrids(type);

            resetGrids(type);

            // Select the first element of the three objects
            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0];
            this.hexaTable.CurrentCell = this.hexaTable[0, 0];
            this.asciiTable.CurrentCell = this.asciiTable[0, 0];

            // Mark the cells in the data grid views with the appropriate colors
            unmarkAllCells();
            int row, col;
            markCells(type, out row, out col, accessConditions);
        }

        // Generates the whole data grid view with the data of the device type selected
        public void UpdateTreeView(TagType type)
        {
            var memory = new NTagMemory(type);

            // Add all the nodes
            this.memoryTreeView.Nodes.Clear();
            // Add the configuration nodes
            this.memoryTreeView.Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + "0: Configuration");
            this.memoryTreeView.Nodes[0].Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + ((int)ConfigBlock.I2Caddress).ToString("X") + ": I²C address (W)");
            this.memoryTreeView.Nodes[0].Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + ((int)ConfigBlock.SerialNumber).ToString("X") + ": Serial Number (R)");
            this.memoryTreeView.Nodes[0].Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + ((int)ConfigBlock.InternalData).ToString("X") + ": Internal data (R)");
            this.memoryTreeView.Nodes[0].Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + ((int)ConfigBlock.LockBytes).ToString("X") + ": Lock bytes (R/W)");
            this.memoryTreeView.Nodes[0].Nodes.Add("0x" + memory.userMemoryBegin.ToString("X2") + ((int)ConfigBlock.CapabilityContainer).ToString("X") + ": Capability Container (R/W)");
            
            if(type != TagType.NTAG2KPlus)
            { 
                // Add the user memory nodes
                int shift = 0;
                this.memoryTreeView.Nodes.Add("0x" + (memory.userMemoryBegin + 1).ToString("X2") + "0: User memory (R/W)");
                for (int i = memory.userMemoryBegin + 1; i < memory.userMemoryEnd - 1; i++)
                    this.memoryTreeView.Nodes[1].Nodes.Add("0x" + i.ToString("X2") + "0: User memory (R/W)");
                if (memory.dynLockBytesPos != 0)
                    this.memoryTreeView.Nodes[1].Nodes.Add("0x" + (memory.userMemoryEnd - 1).ToString("X2") + "0: User memory (R/W)");
                // Add the dynamic lock bytes nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.userMemoryEnd - 1).ToString("X2") + "0: Dynamic lock bytes");
                this.memoryTreeView.Nodes[2].Nodes.Add("0x" + (memory.userMemoryEnd - 1).ToString("X2") + memory.dynLockBytesPos.ToString("X") + ": Dynamic lock bytes (R/W)");
                this.memoryTreeView.Nodes[2].Nodes.Add("0x" + (memory.userMemoryEnd - 1).ToString("X2") + (memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes).ToString("X") + ": Fixed data (R)");

                if (type == TagType.NTAG1KPlus)
                {
                    // Add the Memory Protection Registers
                    this.memoryTreeView.Nodes.Add("0x" + (memory.memProtBegin).ToString("X2") + "0: Memory protection registers");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin).ToString("X2") + ((int)AccessReg.AUTH0).ToString("X") + ": AUTH0 (R/W)");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.ACCESS).ToString("X") + ": ACCESS (R/W)");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PWD).ToString("X") + ": PWD (W)");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PACK).ToString("X") + ": PACK (W)");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PT_I2C).ToString("X") + ": PT_I2C (R/W)");
                    this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + "x: RFU (R)");
                    shift = 1;
                }
                
                // Add the configuration registers nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + "0: Configuration registers");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.NC_REG).ToString("X") + ": NC_REG (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.LAST_NDEF_BLOCK).ToString("X") + ": LAST_NDEF_BLOCK (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.SRAM_MIRROR_BLOCK).ToString("X") + ": SRAM_MIRROR_BLOCK (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.WDT_LS).ToString("X") + ": WDT_LS (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.WDT_MS).ToString("X") + ": WDT_MS (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.I2C_CLOCK_STR).ToString("X") + ": I2C_CLOCK_STR (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.REG_LOCK).ToString("X") + ": REG_LOCK (R/W)");
                this.memoryTreeView.Nodes[3 + shift].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + Enum.GetNames(typeof(ConfigReg)).Length.ToString("X") + ": Fixed (R)");
                // Add the SRAM nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.SRAMMemoryBegin).ToString("X2") + "0: SRAM (R/W)");
                for (int i = memory.SRAMMemoryBegin; i < memory.SRAMMemoryEnd; i++)
                    this.memoryTreeView.Nodes[4 + shift].Nodes.Add("0x" + i.ToString("X2") + "0: SRAM (R/W)");
                // Add the session registers nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + "0: Session registers");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.NC_REG).ToString("X") + ": NC_REG (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.LAST_NDEF_BLOCK).ToString("X") + ": LAST_NDEF_BLOCK (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.SRAM_MIRROR_BLOCK).ToString("X") + ": SRAM_MIRROR_BLOCK (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.WDT_LS).ToString("X") + ": WDT_LS (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.WDT_MS).ToString("X") + ": WDT_MS (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.I2C_CLOCK_STR).ToString("X") + ": I2C_CLOCK_STR (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.NS_REG).ToString("X") + ": NS_REG (R/W)");
                this.memoryTreeView.Nodes[5 + shift].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + Enum.GetNames(typeof(SessionReg)).Length.ToString("X") + ": Fixed (R)");
            }
            else
            {
                // Add the user memory nodes Sector 1
                this.memoryTreeView.Nodes.Add("0x" + (memory.userMemoryS1Begin + 1).ToString("X2") + "0: User memory (R/W)");
                for (int i = memory.userMemoryS1Begin + 1; i < memory.userMemoryS1End - 1; i++)
                    this.memoryTreeView.Nodes[1].Nodes.Add("0x" + i.ToString("X2") + "0: User memory (R/W)");
                if (memory.dynLockBytesPos != 0)
                    this.memoryTreeView.Nodes[1].Nodes.Add("0x" + (memory.userMemoryS1End - 1).ToString("X2") + "0: User memory (R/W)");
                // Add the dynamic lock bytes nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.userMemoryS1End - 1).ToString("X2") + "0: Dynamic lock bytes");
                this.memoryTreeView.Nodes[2].Nodes.Add("0x" + (memory.userMemoryS1End - 1).ToString("X2") + memory.dynLockBytesPos.ToString("X") + ": Dynamic lock bytes (R/W)");
                this.memoryTreeView.Nodes[2].Nodes.Add("0x" + (memory.userMemoryS1End - 1).ToString("X2") + (memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes).ToString("X") + ": Fixed data (R)");
                
                // Add the Memory Protection Registers
                this.memoryTreeView.Nodes.Add("0x" + (memory.memProtBegin).ToString("X2") + "0: Memory protection registers");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin).ToString("X2") + ((int)AccessReg.AUTH0).ToString("X") + ": AUTH0 (R/W)");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.ACCESS).ToString("X") + ": ACCESS (R/W)");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PWD).ToString("X") + ": PWD (W)");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PACK).ToString("X") + ": PACK (W)");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + ((int)AccessReg.PT_I2C).ToString("X") + ": PT_I2C (R/W)");
                this.memoryTreeView.Nodes[3].Nodes.Add("0x" + (memory.memProtBegin + 1).ToString("X2") + "x: RFU (R)");
                                
                // Add the configuration registers nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + "0: Configuration registers");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.NC_REG).ToString("X") + ": NC_REG (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.LAST_NDEF_BLOCK).ToString("X") + ": LAST_NDEF_BLOCK (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.SRAM_MIRROR_BLOCK).ToString("X") + ": SRAM_MIRROR_BLOCK (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.WDT_LS).ToString("X") + ": WDT_LS (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.WDT_MS).ToString("X") + ": WDT_MS (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.I2C_CLOCK_STR).ToString("X") + ": I2C_CLOCK_STR (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + ((int)ConfigReg.REG_LOCK).ToString("X") + ": REG_LOCK (R/W)");
                this.memoryTreeView.Nodes[4].Nodes.Add("0x" + (memory.configMemoryBegin).ToString("X2") + Enum.GetNames(typeof(ConfigReg)).Length.ToString("X") + ": Fixed (R)");
                // Add the user memory nodes Sector 2
                this.memoryTreeView.Nodes.Add("0x" + (memory.userMemoryS2Begin).ToString("X2") + "0: User memory (R/W)");
                for (int i = memory.userMemoryS2Begin; i < memory.userMemoryS2End; i++)
                    this.memoryTreeView.Nodes[5].Nodes.Add("0x" + i.ToString("X2") + "0: User memory (R/W)");
                // Add the SRAM nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.SRAMMemoryBegin).ToString("X2") + "0: SRAM (R/W)");
                for (int i = memory.SRAMMemoryBegin; i < memory.SRAMMemoryEnd; i++)
                    this.memoryTreeView.Nodes[6].Nodes.Add("0x" + i.ToString("X2") + "0: SRAM (R/W)");
                // Add the session registers nodes
                this.memoryTreeView.Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + "0: Session registers");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.NC_REG).ToString("X") + ": NC_REG (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.LAST_NDEF_BLOCK).ToString("X") + ": LAST_NDEF_BLOCK (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.SRAM_MIRROR_BLOCK).ToString("X") + ": SRAM_MIRROR_BLOCK (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.WDT_LS).ToString("X") + ": WDT_LS (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.WDT_MS).ToString("X") + ": WDT_MS (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.I2C_CLOCK_STR).ToString("X") + ": I2C_CLOCK_STR (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + ((int)SessionReg.NS_REG).ToString("X") + ": NS_REG (R/W)");
                this.memoryTreeView.Nodes[7].Nodes.Add("0x" + (memory.sessionMemoryBegin).ToString("X2") + Enum.GetNames(typeof(SessionReg)).Length.ToString("X") + ": Fixed (R)");
            }
        }

        // Shows/hides the rows of the data grid views depending on the device type selected
        public void UpdateGrids(TagType type)
        {
            var memory = new NTagMemory(type);

            // Update the grid
            if ((type != TagType.NTAG2KPlus)&&(type != TagType.NTAG1KPlus))
            {
                for (int i = memory.userMemoryBegin; i < memory.userMemoryEnd; i++)   // UID, user memory and lock bytes
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.userMemoryEnd; i < memory.configMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.configMemoryBegin; i < memory.configMemoryEnd; i++)   // Configuration registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.configMemoryEnd; i < memory.SRAMMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.SRAMMemoryBegin; i < memory.SRAMMemoryEnd; i++)   // SRAM memory
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.SRAMMemoryEnd; i < memory.sessionMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.sessionMemoryBegin; i < memory.sessionMemoryEnd; i++)   // Session registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.sessionMemoryEnd; i < NtagI2CDevice.blocks; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
            }
            else if (type == TagType.NTAG1KPlus)
            {
                for (int i = memory.userMemoryBegin; i < memory.userMemoryEnd; i++)   // UID, user memory and lock bytes
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.userMemoryEnd; i < memory.memProtEnd; i++)   // Memory Protection registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.configMemoryBegin; i < memory.configMemoryEnd; i++)   // Configuration registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.configMemoryEnd; i < memory.SRAMMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.SRAMMemoryBegin; i < memory.SRAMMemoryEnd; i++)   // SRAM memory
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.SRAMMemoryEnd; i < memory.sessionMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.sessionMemoryBegin; i < memory.sessionMemoryEnd; i++)   // Session registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.sessionMemoryEnd; i < NtagI2CDevice.blocks; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
            }
            else if (type == TagType.NTAG2KPlus)
            {
                for (int i = memory.userMemoryS1Begin; i < memory.userMemoryS1End; i++)   // UID, user memory and lock bytes
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.userMemoryS1End; i < memory.memProtEnd; i++)   // Memory Protection registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.configMemoryBegin; i < memory.configMemoryEnd; i++)   // Configuration registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.configMemoryEnd; i < memory.userMemoryS2Begin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.userMemoryS2Begin; i < memory.userMemoryS2End; i++)   // User Memory Sector 2
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.userMemoryS2End; i < memory.SRAMMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.SRAMMemoryBegin; i < memory.SRAMMemoryEnd; i++)   // SRAM memory
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.SRAMMemoryEnd; i < memory.sessionMemoryBegin; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
                for (int i = memory.sessionMemoryBegin; i < memory.sessionMemoryEnd; i++)   // Session registers
                {
                    this.hexaTable.Rows[i].Visible = true;
                    this.asciiTable.Rows[i].Visible = true;
                }
                for (int i = memory.sessionMemoryEnd; i < NtagI2CDevice.blocks; i++)   // Invalid access
                {
                    this.hexaTable.Rows[i].Visible = false;
                    this.asciiTable.Rows[i].Visible = false;
                }
            }
            
            // Unmark all the cells
            unmarkAllCells();
        }

        // Selects the right node taking into account the selected cell
        public void SelectNodeInTreeView(TagType type)
        {
            // Get the row and column of the selected cell
            int row = this.hexaTable.CurrentCell.RowIndex;
            int col = this.hexaTable.CurrentCell.ColumnIndex;

            NTagMemory memory = new NTagMemory(type);

            if (type == TagType.NTAG1K || type == TagType.NTAG2K)
            {
                // Find the parent node
                if (row == memory.userMemoryBegin)
                {
                    // Configuration node
                    // Find the node
                    if (col == (int)ConfigBlock.I2Caddress)   // I2C address
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[0];
                    else if (col >= (int)ConfigBlock.SerialNumber && col < (int)ConfigBlock.InternalData)   // Serial Number
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[1];
                    else if (col >= (int)ConfigBlock.InternalData && col < (int)ConfigBlock.LockBytes)  // Internal data
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[2];
                    else if (col >= (int)ConfigBlock.LockBytes && col < (int)ConfigBlock.CapabilityContainer)   // Lock bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[3];
                    else if (col >= (int)ConfigBlock.CapabilityContainer) // Capability Container
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[4];
                }
                else if (row >= memory.userMemoryBegin + 1 && row < memory.userMemoryEnd - 1)
                {
                    // User memory node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryBegin + 1)];
                }
                else if (row == memory.userMemoryEnd - 1)
                {
                    // Dynamic lock bytes node
                    if (memory.dynLockBytesPos != 0)  // 1K device
                    {
                        
                        // Find the node
                        if (col < memory.dynLockBytesPos) // User memory
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryBegin + 1)];
                        else if (col >= memory.dynLockBytesPos && col < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)    // Dynamic lock bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[0];
                        else if (col >= memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)  // Fixed bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[1];
                        
                    }
                    else  // 2K device
                    {
                        // Find the node
                        if (col < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)    // Dynamic lock bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[0];
                        else if (col >= memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)  // Fixed bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[1];
                    }
                }
                else if (row == memory.configMemoryBegin)
                {
                    // Configuration registers node
                    // Find the node
                    int numConfReg = Enum.GetNames(typeof(ConfigReg)).Length;
                    if (col < numConfReg)
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[col];
                    else
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[(int)numConfReg];
                }
                else if (row >= memory.SRAMMemoryBegin && row < memory.SRAMMemoryEnd)
                {
                    // SRAM node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[4].Nodes[row - (memory.SRAMMemoryBegin)];
                }
                else if (row == memory.sessionMemoryBegin)
                {
                    // Session registers node
                    // Find the node
                    int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                    if (col < numSesRegs)  // Session registers
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[5].Nodes[col];
                    else  // Fixed bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[5].Nodes[numSesRegs];
                }
            }

            else if (type == TagType.NTAG1KPlus)        //Routine for NTAG 1K Plus
            {
                // Find the parent node
                if (row == memory.userMemoryBegin)
                {
                    // Configuration node
                    // Find the node
                    if (col == (int)ConfigBlock.I2Caddress)   // I2C address
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[0];
                    else if (col >= (int)ConfigBlock.SerialNumber && col < (int)ConfigBlock.InternalData)   // Serial Number
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[1];
                    else if (col >= (int)ConfigBlock.InternalData && col < (int)ConfigBlock.LockBytes)  // Internal data
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[2];
                    else if (col >= (int)ConfigBlock.LockBytes && col < (int)ConfigBlock.CapabilityContainer)   // Lock bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[3];
                    else if (col >= (int)ConfigBlock.CapabilityContainer) // Capability Container
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[4];
                }
                else if (row >= memory.userMemoryBegin + 1 && row < memory.userMemoryEnd - 1)
                {
                    // User memory node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryBegin + 1)];
                }
                else if (row == memory.userMemoryEnd - 1)
                {
                        // Find the node
                        if (col < memory.dynLockBytesPos) // User memory
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryBegin + 1)];
                        else if (col >= memory.dynLockBytesPos && col < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)    // Dynamic lock bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[0];
                        else if ((col >= memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)&&(col != 15))  // Fixed bytes
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[1];
                        else if (col==15)                                                                   // AUTH0
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[0];
                }
                else if (row == memory.memProtBegin + 1)
                {
                    // Access registers node    (MemProtection)
                    // Find the node
                    switch(col)
                    {
                        case (0):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[1];
                            break;
                        case (4): case (5): case (6): case (7):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[2];
                            break;
                        case (8): case (9):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[3];
                            break;
                        case (12):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[4];
                            break;
                        default:
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[5];
                            break;
                    }
                }
                else if (row == memory.configMemoryBegin)
                {
                    // Configuration registers node
                    // Find the node
                    int numConfReg = Enum.GetNames(typeof(ConfigReg)).Length;
                    if (col < numConfReg)
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[4].Nodes[col];
                    else
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[4].Nodes[(int)numConfReg];
                }
                else if (row >= memory.SRAMMemoryBegin && row < memory.SRAMMemoryEnd)
                {
                    // SRAM node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[5].Nodes[row - (memory.SRAMMemoryBegin)];
                }
                else if (row == memory.sessionMemoryBegin)
                {
                    // Session registers node
                    // Find the node
                    int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                    if (col < numSesRegs)  // Session registers
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[6].Nodes[col];
                    else  // Fixed bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[6].Nodes[numSesRegs];
                }
            }

            else if (type == TagType.NTAG2KPlus)    //Routine for NTAG 2K Plus
            {
                // Find the parent node
                if (row == memory.userMemoryBegin)
                {
                    // Configuration node
                    // Find the node
                    if (col == (int)ConfigBlock.I2Caddress)   // I2C address
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[0];
                    else if (col >= (int)ConfigBlock.SerialNumber && col < (int)ConfigBlock.InternalData)   // Serial Number
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[1];
                    else if (col >= (int)ConfigBlock.InternalData && col < (int)ConfigBlock.LockBytes)  // Internal data
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[2];
                    else if (col >= (int)ConfigBlock.LockBytes && col < (int)ConfigBlock.CapabilityContainer)   // Lock bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[3];
                    else if (col >= (int)ConfigBlock.CapabilityContainer) // Capability Container
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[0].Nodes[4];
                }
                else if (row >= memory.userMemoryS1Begin + 1 && row < memory.userMemoryS1End - 1)
                {
                    // User memory node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryS1Begin + 1)];
                }
                else if (row == memory.userMemoryS1End - 1)
                {
                    // Find the node
                    if (col < memory.dynLockBytesPos) // User memory
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[1].Nodes[row - (memory.userMemoryS1Begin + 1)];
                    else if (col >= memory.dynLockBytesPos && col < memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes)    // Dynamic lock bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[0];
                    else if ((col >= memory.dynLockBytesPos + NtagI2CDevice.dynLockBytes) && (col != 15))  // Fixed bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[2].Nodes[1];
                    else if (col == 15)                                                                   // AUTH0
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[0];
                }
                else if (row == memory.memProtBegin + 1)
                {
                    // Access registers node    (MemProtection)
                    // Find the node
                    switch (col)
                    {
                        case (0):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[1];
                            break;
                        case (4): case (5): case (6): case (7):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[2];
                            break;
                        case (8): case (9):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[3];
                            break;
                        case (12):
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[4];
                            break;
                        default:
                            this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[3].Nodes[5];
                            break;
                    }
                }
                else if (row == memory.configMemoryBegin)
                {
                    // Configuration registers node
                    // Find the node

                    int numConfReg = Enum.GetNames(typeof(ConfigReg)).Length;
                    if (col < numConfReg)
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[4].Nodes[col];
                    else
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[4].Nodes[(int)numConfReg];
                }

                else if (row >= memory.userMemoryS2Begin && row < memory.userMemoryS2End)
                {
                    // User memory node 2
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[5].Nodes[row - ((int)memory.userMemoryS2Begin)];
                }

                else if (row >= memory.SRAMMemoryBegin && row < memory.SRAMMemoryEnd)
                {
                    // SRAM node
                    this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[6].Nodes[row - ((int)memory.SRAMMemoryBegin)];
                }
                else if (row == memory.sessionMemoryBegin)
                {
                    // Session registers node
                    // Find the node
                    int numSesRegs = Enum.GetNames(typeof(SessionReg)).Length;
                    if (col < numSesRegs)  // Session registers
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[7].Nodes[col];
                    else  // Fixed bytes
                        this.memoryTreeView.SelectedNode = this.memoryTreeView.Nodes[7].Nodes[numSesRegs];
                }
            }

            else
            {
                //Issue with the tag type
                MessageBox.Show("No tag type selected");
            }

        }

    }
}
