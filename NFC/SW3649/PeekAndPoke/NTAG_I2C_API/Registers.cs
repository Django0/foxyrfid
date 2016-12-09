using System;
using System.Collections.Generic;
using NTAG_I2C.Contracts;
using NTAG_I2C.Commands;

namespace NTAG_I2C.API
{
    public class Registers
    {
        public NTAG_I2C_Command i2cCommand;
        public BlockMemory blockMem;

        public Registers(NTAG_I2C_Command cmdInstance, BlockMemory memory)
        {
            i2cCommand = cmdInstance;
            blockMem = memory;
        }

        /** @brief Read a configuration register from the Ntag I2C.
         * 
         * It reads all configuration registers block and returns only
         * the requested registesr.
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  @param registerAddress is the specific register address memory
         *  
         * @return the result of the transaction 
         */
        public I2CData readConfigRegister(byte i2cAddress, TagType ntagType, byte registerAddress)
        {
            var allRegisters = readAllConfigRegister(i2cAddress, ntagType);
            var reg = allRegisters.data[(int)registerAddress];

            return new I2CData() {
                error = allRegisters.error,
                data = new byte[1]{reg}, 
                flag = allRegisters.flag
            };
        }

        /** @brief Writes a configuration register to the Ntag I2C
         * 
         * @param i2cAddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registerAddress is the specific register address memory
         * @param registerValue is the value of the register 
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeConfigRegister(byte i2cAddress, TagType ntagType, byte registerAddress, byte registerValue)
        {
            I2CData configRegister = null;

            byte memoryBegin = getConfigMemoryBegin(ntagType);
            var allRegisters = readAllConfigRegister(i2cAddress, ntagType);

            byte[] registers = allRegisters.data;
            registers[(int)registerAddress] = registerValue;

            configRegister = i2cCommand.writeBlock(i2cAddress, (byte)(memoryBegin), registers);
            return configRegister;
        }

        /** @brief Read all configuration registers from the Ntag I2C.
         * 
         * @param i2cAddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * 
         *  @return the response of the transaction.
         */
        public I2CData readAllConfigRegister(byte i2cAddress, TagType ntagType)
        {
            int memoryAddress = (int)(new NTagMemory(ntagType)).configMemoryBegin;
            var readBlock = i2cCommand.readBlock(i2cAddress, (byte)memoryAddress);
            return readBlock;       
        }

        /** @brief Write all configuration registers to the Ntag I2C.
         * 
         * @param i2cAddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registers is a byte array with the block of the registers value
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeAllConfigRegister(byte i2cAddress, byte[] registers, TagType ntagType)
        {
            int numRegs = Enum.GetNames(typeof(ConfigReg)).Length;
            I2CData output = null;

            byte memoryBegin = getConfigMemoryBegin(ntagType);

            output = i2cCommand.writeBlock(i2cAddress, memoryBegin, registers);
            return output;
        }

        /** @brief Read a session register.
         * 
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  @param registerAddress is the specific register address memory
         *  
         * @return the result of the transaction 
         */
        public I2CData readSessionRegister(byte i2cAddress, TagType ntagType, byte registerAddress)
        {
            I2CData SessionRegister = null;
            byte memoryBegin = getSessionMemoryBegin(ntagType);
            SessionRegister = i2cCommand.readRegister(i2cAddress, memoryBegin, registerAddress);
            return SessionRegister;
        }

        /** @brief Writes a session register to the Ntag I2C
         * 
         * @param i2caddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registerAddress is the specific register address memory
         * @param registerValue is the value of the register 
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeSessionRegister(byte i2cAddress, TagType ntagType, byte registerAddress, byte registerValue)
        {
            I2CData sessionRegister = null;
            byte memoryBegin = getSessionMemoryBegin(ntagType);
            sessionRegister = i2cCommand.writeRegister(i2cAddress, memoryBegin, registerAddress, registerValue);
            return sessionRegister;
        }

        /** @brief Read all session registers.
         * 
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  
         * @return the result of the transaction 
         */
        public List<I2CData> readAllSessionRegister(byte i2cAddress, TagType ntagType, Action<I2CData> callback = null)
        {
            List<I2CData> readRegisters = new List<I2CData>();
            int numRegs = Enum.GetNames(typeof(SessionReg)).Length;
            int i = 0;
            I2CData readOutput;
            do
            {
                readOutput = readSessionRegister(i2cAddress, ntagType, (byte)i);
                readRegisters.Add(readOutput);
                if(callback != null)
                    callback(readOutput);
                i++;
            } while (i < numRegs && readOutput.error == I2CError.Success);

            

            return readRegisters;
        }

        /** @brief Writes all session registers to the Ntag I2C
         * 
         * @param i2caddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registers is a byte array with the block of the registers value
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeAllSessionRegister(byte i2cAddress, byte[] registers, TagType ntagType)
        {
            int numRegs = Enum.GetNames(typeof(SessionReg)).Length;
            int i = 0;
            I2CData writeOutput = new I2CData(){ error = I2CError.Success }; 
            do
            {
                var regOut = writeSessionRegister(i2cAddress, ntagType, (byte)i, registers[i]);
                if(regOut.error != I2CError.Success)
                    writeOutput.error = regOut.error;       
                i++;
            } while (i < numRegs && writeOutput.error == I2CError.Success);

            return writeOutput;
        }

        private byte getConfigMemoryBegin(TagType ntagType)
        {
            byte address = 0x00;
            if (ntagType == TagType.NTAG1K)
            {
                address = (byte)NTAG1K.ConfigMemoryBegin;
            }
            else
            {
                if (ntagType == TagType.NTAG2K)
                {
                    address = (byte)NTAG2K.ConfigMemoryBegin;
                }
                else
                {
                    throw new Exception("Tag type not valid.");
                }

            }
            return address;
        }

        private byte getSessionMemoryBegin(TagType ntagType)
        {
            byte address = 0x00;
            if (ntagType == TagType.NTAG1K)
            {
                address = (byte)NTAG1K.SessionMemoryBegin;
            }
            else if (ntagType == TagType.NTAG2K)
            {
                    address = (byte)NTAG2K.SessionMemoryBegin;
            }
            else if (ntagType == TagType.NTAG1KPlus)
            {
                address = (byte)NTAG1KPlus.SessionMemoryBegin;
            }
            else if (ntagType == TagType.NTAG2KPlus)
            {
                address = (byte)NTAG2KPlus.SessionMemoryBegin;
            }
            else
            {
                throw new Exception("Tag type not valid.");
            }
            return address;
        }
    }
}
