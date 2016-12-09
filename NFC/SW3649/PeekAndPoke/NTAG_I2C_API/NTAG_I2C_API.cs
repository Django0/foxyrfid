using System.Collections.Generic;
using NTAG_I2C.Contracts;
using NTAG_I2C.Commands;
using System;
///
/// Namespace for the top level classes dealing with the NTag I2C API
///
namespace NTAG_I2C.API
{
    ///
    /// This class includes the NTag I2C API functionalities
    ///
    ///
    public class NtagI2C
    {
        private NTAG_I2C_Command i2cCommand { get; set; } /**< Object representing the basic NTag I2C Commands. */
        private Registers reg;
        private BlockMemory block;
        private I2CAddress address;         

        public NtagI2C() {
            i2cCommand = new NTAG_I2C_Command();
            
            block = new BlockMemory(i2cCommand);
            reg = new Registers(i2cCommand, block);
            address = new I2CAddress(block);
        }

        /** @brief Check if a device is present and connects.
         * 
         * It checks if the connected device is still connected. In case is not
         * anymore, it closes the connection. In case, there was still not a device connected, 
         * it looks for a device and if it finds it, connects to it.
         * In case, a device is connected and the port is not initialize, 
         * it sets the port connection as well.
         * 
         *  @return if there is a device present or not
         */
        public bool checkPresenceAndConnect()
        {
            return i2cCommand.checkDevPresentAndConnect();
        }

        /** @brief Indicates if the device is connected.      
                * 
                * @return the true if the device is connected.
                */
        public bool isDeviceConnected()
        {
            return i2cCommand.isDeviceConnected();
        }

        /** @brief Indicates if the device was connected.
         * 
         * It checks the attribute indicating if on the last check
         * the device was connected.
        * 
        * @return the true if the device was connected last time checked.
        */
        public bool wasDevPresentLasTime()
        {
            return i2cCommand.wasDevPresentLasTime();
        }

        /** @brief Closes the connection with the device in case the device has been disconnected.
         * 
         */
        public void disconnectDevice()
        {
            i2cCommand.disconnectDevice();
        }

        /** @brief Reinitialize the communication with the port
        * 
        *  @param busSpeedInKHz is the bus speed on the bus for the communication
        */
        public void reinitPort(int busSpeedKhz) {
            i2cCommand.reinitPort(busSpeedKhz);
        }

        /** @brief Get the speed of the I2C Bus.
         * 
         *  @return the speed of the bus
         */
        public int getBusSpeed() {
            return i2cCommand.getBusSpeed();
        }

        /** @brief Set the speed of the I2C Bus.
         *  @param speed is the speed of the I2C Bus
         */
        public void setBusSpeed(int value) 
        {
            i2cCommand.setBusSpeed(value);
        }

        /** @brief Read all memory of the NTag I2C.
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param callback is the function to be called with the result of the read on each block
         *  
         * @return a list with the result on each read block
         */
        public List<I2CData> readAllMemory(TagType ntagType, byte i2cAddress, Action<I2CData> callback = null) 
        {
            return block.readAll(ntagType, i2cAddress, callback);
        }

        /** @brief Write all memory of the NTag I2C.
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param writeBytes is the matrix with the bytes to write on each block for the whole memory
         *  @param callback is the function to be called with the result of the write on each block
         *  
         * @return a list with the result on each write block
         */
        public List<I2CData> writeAllMemory(TagType ntagType, byte i2cAddress, byte[][] writeBytes, Action<I2CData> callback = null) 
        {
            return block.writeAll(ntagType, i2cAddress, writeBytes, callback);
        }

        /** @brief Read a block of the memory of the NTag I2C.
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param address is the block address on the Ntag I2C memory
         *  
         * @return 
         */
        public I2CData readBlockMemory(byte I2Caddress, byte address) 
        {
            return block.read(I2Caddress, address);
        }

        /** @brief Write a block of the memory of the NTag I2C.
        *  @param i2cAddress is the address of the device to be found on the i2c bus 
        *  @param address is the block address on the Ntag I2C memory
        *  @param writeBytes is the byte array with the data to be written
        *  
        * @return the result of the transaction 
        */
        public I2CData writeBlockMemory(byte I2Caddress, byte address, byte[] writeBytes)
        {
            return block.write(I2Caddress, address, writeBytes);
        }

        /** @brief Write the data on the user memory formatted as a text NDEF message.
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param payload is the byte array with the data to be written as payload of the NDEF message
         *  
         * @return the result of the transaction 
         */
        public I2CData writeTextNdef(byte I2Caddress, byte[] payload)
        {
            byte[] ndef = NDEF.createTextNdefMessage(payload);
            return writeMessage(I2Caddress, ndef);
        }

        /** @brief Creates and returns the TNF and Flags byte.
         * 
         *  @param msgBegin is the flag indicating if the NDEF Record is the first
         *  @param msgEnd is the flag indicating if the NDEF Record is the last
         *  @param chunkFlag is the flag indicating if it is a chunked message part
         *  @param shortRecord is the flag indicating if the message is shorter than 2^8-1
         *  @param idLength indicates the length of the id
         *  @param type indicats the name format type
         *  
         * @return the TNF and Flag byte
         */
        public byte getNdefTNFandFlagsByte(bool msgBegin, bool msgEnd, bool chunkFlag, bool 
            shortRecord, byte idLength, TypeNameFormatType type)
        {
            return NDEF.getTNFandFlagsByte(msgBegin, msgEnd, 
                chunkFlag, shortRecord, idLength, type);
        }

        /** @brief Write the data on the user memory.
         * 
         * It writes data bigger than a block on the user memory.
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param payload is the byte array with the data to be written 
         *  
         * @return the result of the transaction 
         */
        public I2CData writeMessage(byte I2Caddress, byte[] payload)
        {
            var result = block.writeMessage(I2Caddress, payload);
            result.data = payload;
            return result;
        }

        /** @brief Read a configuration register.
         * 
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  @param registerAddress is the specific register address memory
         *  
         * @return the result of the transaction 
         */
        public I2CData readConfigRegister(byte i2caddress, TagType ntagType, byte registerAddress)
        {
            return reg.readConfigRegister(i2caddress, ntagType, registerAddress);
        }
        /** @brief Writes a configuration register to the Ntag I2C
         * 
         * @param i2caddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registerAddress is the specific register address memory
         * @param registerValue is the value of the register 
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeConfigRegister(byte i2caddress, TagType ntagType, byte registerAddress, byte registerValue)
        {
            return reg.writeConfigRegister(i2caddress, ntagType, registerAddress, registerValue);  
        }

        /** @brief Read all configuration registers.
         * 
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  
         * @return the result of the transaction 
         */
        public I2CData readAllConfigRegister(byte i2caddress, TagType ntagType)
        {
            return reg.readAllConfigRegister(i2caddress, ntagType);
        }
        /** @brief Writes all configuration registers to the Ntag I2C
         * 
         * @param i2caddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registers is a byte array with the block of the registers value
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeAllConfigRegister(byte i2caddress, byte[] registers, TagType ntagType) 
        {
            return reg.writeAllConfigRegister(i2caddress, registers, ntagType);
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
        public I2CData readSessionRegister(byte i2caddress, TagType ntagType, byte registerAddress)
        {
            return reg.readSessionRegister(i2caddress, ntagType, registerAddress);
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
        public I2CData writeSessionRegister(byte i2caddress, TagType ntagType, byte registerAddress, byte registerValue)
        {
            return reg.writeSessionRegister(i2caddress, ntagType, registerAddress, registerValue);
        }

        /** @brief Read all session registers.
         * 
         * 
         *  @param i2cAddress is the address of the device to be found on the i2c bus 
         *  @param ntagType indicates if the NTag I2C is 1k or 2k version
         *  
         * @return the result of the transaction 
         */
        public List<I2CData> readAllSessionRegister(byte i2caddress, TagType ntagType)
        {
            return reg.readAllSessionRegister(i2caddress, ntagType);
        }
        /** @brief Writes all session registers to the Ntag I2C
         * 
         * @param i2caddress is the address of the device to be found on the i2c bus
         * @param ntagType indicates if the NTag I2C is 1k or 2k version
         * @param registers is a byte array with the block of the registers value
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeAllSessionRegister(byte i2caddress, byte[] registers, TagType ntagType)
        {
            return reg.writeAllSessionRegister(i2caddress, registers, ntagType);
        }
        /** @brief Scans all I2C address to find the one with a connected device.
         * 
         * @param callback is a function to be called after each address check with its result
         * 
         *  @return a list with the result of each checking 
         */
        public List<I2CData> ScanI2CAddress(Action<I2CData> callback = null)
        {
            var empty = new List<int>();
            return ScanI2CAddress(empty, callback);
        }
        /** @brief Scans all I2C address to find the one with a connected device.
         * 
         * @param toDiscard is a list of addressess to be ommitted on the scanning. It is
         * useful to exclude LCD or temperature sensor addresses
         * @param callback is a function to be called after each address check with its result
         * 
         *  @return a list with the result of each checking 
         */
        public List<I2CData> ScanI2CAddress(List<int> toDiscard, Action<I2CData> callback = null)
        {
            var addressScanLog = address.scanning(toDiscard, callback);
            return addressScanLog;
        }
    }
}
