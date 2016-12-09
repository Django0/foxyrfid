using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NTAG_I2C.Contracts;
using NTAG_I2C.Commands;

namespace NTAG_I2C.API
{
    ///
    /// This class includes the functionalities related to the memory of the NTag I2C seen as a set of blocks.
    ///
    ///
    public class BlockMemory
    {
        private NTAG_I2C_Command i2cCommand; /**< Object to interact with the NTag I2C using the I2C commands. */
        public int bytesInBlock; /**< It indicates the number of bytes contained in a block. */

        public BlockMemory(NTAG_I2C_Command cmdInstance)
        {
            init(16, cmdInstance);
        }

        public BlockMemory(int bytesInABlock, NTAG_I2C_Command cmdInstance) 
        {
            init(bytesInABlock, cmdInstance);

        }

        private void init(int bytesInABlock, NTAG_I2C_Command cmdInstance)
        {
            bytesInBlock = bytesInABlock;
            i2cCommand = cmdInstance;
        }

        /** @brief Read all blocks in the memory of the NTag I2C.
         * 
         * It reads the blocks in the user memory, configuration registers block, the
         * SRAM blocks and the session registers. 
         * 
         *  @param type indicates if the NTag I2C is 1k or 2k version
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param callback is the function to be called with the result of the read on each block
         *  
         * @return a list with the result on each read block
         */
        public List<I2CData> readAll(TagType type, byte i2cAddress, Action<I2CData> callback = null)
        {
            List<I2CData> data = new List<I2CData>();

            var tagMem = new NTagMemory(type);

            if((type == TagType.NTAG1K)||(type==TagType.NTAG2K))
            { 
                data.AddRange(readRange(i2cAddress, tagMem.userMemoryBegin, 
                    tagMem.userMemoryEnd, callback));

                if (data.Last().error == I2CError.Success) 
                {
                    data.AddRange(readRange(i2cAddress, tagMem.configMemoryBegin, 
                        tagMem.configMemoryEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    var sessionReg = new Registers(i2cCommand, null);
                    data.AddRange(sessionReg.readAllSessionRegister(i2cAddress, type, callback));              
                }
            }
            else if(type == TagType.NTAG1KPlus)
            {
                data.AddRange(readRange(i2cAddress, tagMem.userMemoryBegin,
                                    tagMem.userMemoryEnd - 1, callback));
                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.memProtBegin,
                        tagMem.memProtEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.configMemoryBegin,
                        tagMem.configMemoryEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    var sessionReg = new Registers(i2cCommand, null);
                    data.AddRange(sessionReg.readAllSessionRegister(i2cAddress, type, callback));
                }
            }
            else if(type == TagType.NTAG2KPlus)
            {
                data.AddRange(readRange(i2cAddress, tagMem.userMemoryS1Begin,
                    tagMem.userMemoryS1End - 1, callback));
                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.memProtBegin,
                        tagMem.memProtEnd, callback));
                }
                
                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.configMemoryBegin,
                        tagMem.configMemoryEnd, callback));
                }
                
                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.userMemoryS2Begin,
                        tagMem.userMemoryS2End, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    data.AddRange(readRange(i2cAddress, tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (data.Last().error == I2CError.Success)
                {
                    var sessionReg = new Registers(i2cCommand, null);
                    data.AddRange(sessionReg.readAllSessionRegister(i2cAddress, type, callback));
                }
            }
            return data;
        }      

        private List<I2CData> readRange(byte i2CAddress, int beginAddress, int endAddress, Action<I2CData> callback = null)
        {
            int i = beginAddress;
            I2CData lastBlock = new I2CData() { error = I2CError.Success };
            List<I2CData> range = new List<I2CData>();

            while (i < endAddress && lastBlock.error == I2CError.Success)
            {
                lastBlock = read(i2CAddress, (byte)i);

                if (lastBlock == null)
                {
                    throw new Exception("Device may not be connected. Read could not be performed.");
                }

                range.Add(lastBlock);
                if(callback != null)
                    callback(lastBlock);
                i++;
            }

            return range;
        }

        /** @brief Write all blocks in the memory of the NTag I2C.
         * 
         * It writes the  writeBytes on the NTag I2C memory. The writeBytes matrix
         * does not have the blocks on the real memory index but it have the memory data 
         * consecutively stored. It writes on the user memory, SRAM, configuration 
         * registers and session registers.
         * 
         * 
         *  @param type indicates if the NTag I2C is 1k or 2k version
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param writeBytes is the matrix with the bytes to write on each block for the whole memory
         *  @param callback is the function to be called with the result of the write on each block
         *  
         * @return a list with the result on each write block
         */
        public List<I2CData> writeAll(TagType type, byte i2cAddress, byte[][] writeBytes, Action<I2CData> callback = null)
        {

            int i2cAddressLength = 1;
             List<I2CData> output = new List<I2CData>();
             var tagMem = new NTagMemory(type);

                      
            if((type != TagType.NTAG2KPlus)&(type!=TagType.NTAG1KPlus))
            {
                int userMemInit = tagMem.userMemoryBegin + i2cAddressLength;

                int startIdx = 0;

                output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                    userMemInit, tagMem.userMemoryEnd, callback));
            
                if (output.Last().error == I2CError.Success) 
                {
                    startIdx += tagMem.userMemoryEnd - userMemInit;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.configMemoryBegin, tagMem.configMemoryEnd, callback));                
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.configMemoryEnd - tagMem.configMemoryBegin;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.SRAMMemoryEnd - tagMem.SRAMMemoryBegin;

                    byte[][] _wB = new byte[bytesInBlock][];
                    Array.Copy(writeBytes, startIdx, _wB, 0, 1);
                    var reg = new Registers(i2cCommand, this); 
                    var result = reg.writeAllSessionRegister(i2cAddress, _wB[0], type);
                    output.Add(result);
                    if (callback != null)
                        callback(result);
                }
            }
            else if(type == TagType.NTAG1KPlus)
            {
                int userMemInit = tagMem.userMemoryBegin + i2cAddressLength;

                int startIdx = 0;

                output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                    userMemInit, tagMem.userMemoryEnd - 1, callback));

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += (tagMem.userMemoryEnd - 1) - userMemInit;
                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.memProtBegin, tagMem.memProtEnd, callback));

                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.memProtEnd - tagMem.memProtBegin;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.configMemoryBegin, tagMem.configMemoryEnd, callback));
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.configMemoryEnd - tagMem.configMemoryBegin;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.SRAMMemoryEnd - tagMem.SRAMMemoryBegin;

                    byte[][] _wB = new byte[bytesInBlock][];
                    Array.Copy(writeBytes, startIdx, _wB, 0, 1);
                    var reg = new Registers(i2cCommand, this);
                    var result = reg.writeAllSessionRegister(i2cAddress, _wB[0], type);
                    output.Add(result);
                    if (callback != null)
                        callback(result);
                }
            }

            else if(type == TagType.NTAG2KPlus)
            {
                int userMemInit = tagMem.userMemoryS1Begin + i2cAddressLength;

                int startIdx = 0;

                output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                userMemInit, tagMem.userMemoryS1End - 1, callback));

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += (tagMem.userMemoryS1End - 1) - userMemInit;
                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.memProtBegin, tagMem.memProtEnd, callback));

                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.memProtEnd - tagMem.memProtBegin;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.configMemoryBegin, tagMem.configMemoryEnd, callback));
                }


                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.configMemoryEnd - tagMem.configMemoryBegin;
                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.userMemoryS2Begin, tagMem.userMemoryS2End, callback));
 
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.userMemoryS2End - tagMem.userMemoryS2Begin;

                    output.AddRange(writeRange(i2cAddress, writeBytes, startIdx,
                        tagMem.SRAMMemoryBegin, tagMem.SRAMMemoryEnd, callback));
                }

                if (output.Last().error == I2CError.Success)
                {
                    startIdx += tagMem.SRAMMemoryEnd - tagMem.SRAMMemoryBegin;

                    byte[][] _wB = new byte[bytesInBlock][];
                    Array.Copy(writeBytes, startIdx, _wB, 0, 1);
                    var reg = new Registers(i2cCommand, this);
                    var result = reg.writeAllSessionRegister(i2cAddress, _wB[0], type);
                    output.Add(result);
                    if (callback != null)
                        callback(result);
                }
            }
            return output;
        }

        private byte[][] getWriteBytesArray(byte[][] writeBytes, int outArray_initIdx, int outArray_endIdx)
        {
            byte[][] userMemory = new byte[outArray_endIdx][];
            int j = 0;
            for (int i = outArray_initIdx; i < (outArray_endIdx); i++)
            {
                userMemory[i] = writeBytes[j];
                j++;
            }
            return userMemory;
        }

        private List<I2CData> writeRange(byte i2cAddress, byte[][] writeBytes, int writeStartIdx, int beginAddress, int endAddress, Action<I2CData> callback = null)
        {            
            int memoryIdx = beginAddress;             
            I2CData lastBlock = new I2CData() { error = I2CError.Success };
            List<I2CData> data = new List<I2CData>();            
            int length = endAddress - beginAddress;
            int j = 0;
            byte[][] _wB = new byte[length][];

            Array.Copy(writeBytes, writeStartIdx, _wB, 0, length);
            
            while (memoryIdx < endAddress && lastBlock.error == I2CError.Success)
            {
                lastBlock = write(i2cAddress, (byte)memoryIdx, _wB[j]);
                data.Add(lastBlock);
                if (callback != null)
                {
                    callback(lastBlock);
                }
                memoryIdx++;
                j++;
            }

            return data;
        }

        /** @brief Read a block of the memory of the NTag I2C.
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param address is the block address on the Ntag I2C memory
         *  
         * @return the result of the transaction with the read data included
         */
        public I2CData read(byte I2Caddress, byte address)
        {
            I2CData read;
            read = i2cCommand.readBlock(I2Caddress, address);
            return read;
        }

        /** @brief Write a block of the memory of the NTag I2C.
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param address is the block address on the Ntag I2C memory
         *  @param writeBytes is the byte array with the data to be written
         *  
         * @return the result of the transaction 
         */
        public I2CData write(byte I2Caddress, byte address, byte[] writeBytes)
        {
            I2CData write;
            write = i2cCommand.writeBlock(I2Caddress, address, writeBytes);
            return write;
        }

        /** @brief Write the data on the user memory.
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param payload is the byte array with the data to be written 
         *  
         * @return the result of the transaction 
         */
        public I2CData writeMessage(byte I2Caddress, byte[] msg)
        {
            I2CData writeOutput;
            int i = 0;
            int numBlocks = calculateBlocks(msg);
                        
            do
            {
                byte[] msgBlock = getNthMessageBlock(msg, i);
                byte address = (byte)(1 + i);
                writeOutput = write(I2Caddress, address, msgBlock);
                i++;
            }
            while (i < numBlocks && writeOutput.error == I2CError.Success);

            return writeOutput;
        }

        private byte[] getNthMessageBlock(byte[] msg, int i)
        {
            byte[] _block = new byte[bytesInBlock];
            Array.Copy(msg, i * bytesInBlock, _block, 0, Math.Min(bytesInBlock, msg.Length - i * bytesInBlock));
            return _block;
        }

        private int calculateBlocks(byte[] msg)
        {
            int numBlocks = (int)Math.Ceiling(((double)msg.Length) / bytesInBlock);
            return numBlocks;
        }
    }
}
