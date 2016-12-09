using NTAG_I2C.Contracts;
using I2C_Communication;

///
/// Namespace for the classes dealing with the I2C commands.
///
namespace NTAG_I2C.Commands
{
    ///
    /// This class includes the NTag I2C Commands
    ///
    ///
    public class NTAG_I2C_Command
    {
        public I2C_Comm ntag { get; set; } /**< Object representing the USB communication with the device. */
        private byte transactionIdentifier; 
        private byte sessionIdentifier; 
        private byte i2cReadWriteRequest; 
        private byte withoutOptions; 
        private const byte sessionMemoryBegin = (byte)NTAG1K.SessionMemoryBegin;

        public NTAG_I2C_Command() {
            ntag = new I2C_Comm();
            transactionIdentifier = 0x01;
            sessionIdentifier = 0x29;
            i2cReadWriteRequest = 0x05;
            withoutOptions = 0x00;
        }

        /** @brief It writes a block to the Ntag I2C memory
         * 
         * @param I2Caddress is the address of the device to be found on the i2c bus
         * @param memoryAddress is the address on the Ntag I2C memory
         * @param writeBytes is the data to be written
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeBlock(byte I2Caddress, byte memoryAddress, byte[] writeBytes)
        {
            byte[] command;
            I2CData responseWrite;
            byte totalBytes = 0x19;
            byte txLength = 0x11;
            byte rxLength = 0x00;      
            
            command = createTransactionCommandToI2C(totalBytes, transactionIdentifier, sessionIdentifier, 
                i2cReadWriteRequest, txLength, rxLength, withoutOptions, I2Caddress, memoryAddress);
            command = addBytesToWriteToCommand(writeBytes, command);
            responseWrite = ntag.performTransaction(command);
            return responseWrite;
        }

        /** @brief It reads a block from the Ntag I2C memory
         * 
         * @param I2Caddress is the address of the device to be found on the i2c bus
         * @param memoryAddress is the address on the Ntag I2C memory
         * 
         *  @return the response of the transaction.
         */
        public I2CData readBlock(byte I2Caddress, byte memoryAddress)
        {
            byte[] command;
            byte totalBytes = 0x09;
            byte txLength = 0x01;
            byte rxLength = 0x10;
            command = createTransactionCommandToI2C(totalBytes, transactionIdentifier, sessionIdentifier, 
                i2cReadWriteRequest, txLength, rxLength, withoutOptions, I2Caddress, memoryAddress);
            return ntag.performTransactionAndGetData(command, 16);
        }

        /** @brief Writes a register to the Ntag I2C
         * 
         * @param I2Caddress is the address of the device to be found on the i2c bus
         * @param memoryAddress is the block address on the Ntag I2C memory where the registers are
         * @param registerAddress is the specific register address memory
         * @param registerValue is the value of the register 
         * 
         *  @return the response of the transaction.
         */
        public I2CData writeRegister(byte I2Caddress, byte memoryAddress, byte registerAddress, byte registerValue, byte mask = 0xFF)
        {
            byte[] command;
            I2CData responseWrite;
            byte[] writeBytes = { registerAddress, mask, registerValue };
            byte totalBytes = 0x12;
            byte txLength = 0x04;
            byte rxLength = 0x00;

            command = createTransactionCommandToI2C(totalBytes, transactionIdentifier, sessionIdentifier,
                i2cReadWriteRequest, txLength, rxLength, withoutOptions, I2Caddress, memoryAddress); //TODO: sessionMemoryBegin is equal for 1k and 2k but this should be enter as parameter

            command = addBytesToWriteToCommand(writeBytes, command);

            responseWrite = ntag.performTransaction(command);
            responseWrite.log += getExtraLogForWriteRegister(registerAddress, registerValue);

            return responseWrite;
        }

        /** @brief It reads a register from the Ntag I2C
         * 
         * @param I2Caddress is the address of the device to be found on the i2c bus
         * @param memoryAddress is the address on the Ntag I2C memory
         * @param registerAddress is the specific register address memory
         *  @return the response of the transaction.
         */
        public I2CData readRegister(byte I2Caddress, byte memoryAddress, byte registerAddress)
        {
            I2CData response;
            byte[] command;            
            int readRegisterIdx = 0;
            byte[] writeBytes = { registerAddress };
            byte totalBytes = 0x0A;
            byte txLength = 0x02;
            byte rxLength = 0x01;

            command = createTransactionCommandToI2C(totalBytes, transactionIdentifier, sessionIdentifier,
                i2cReadWriteRequest, txLength, rxLength, withoutOptions, I2Caddress, sessionMemoryBegin);

            command = addBytesToWriteToCommand(writeBytes, command);
            response = ntag.performTransactionAndGetData(command, 1);

            response.log += getExtraLogForWriteRegister(registerAddress, response.data[readRegisterIdx]);
            return response;
        }

       
        /*
         * 
         * Total Bytes—the number of actual data bytes used for the message = 0x19 or 25d
	         - Transaction identifier—value is not critical and is not used
	         - Session identifier—value is not critical and is not used
	         - HID I2C Request—use 0x05, which is an I2C serial bus write/read request
	         - I2C txLength—number of data bytes to write to the I2C serial bus
	         - I2C rxLength—number of data bytes to read from the I2C serial bus
	         - Options—0x00. No special options required
	         - I2C Address—displays the I2C serial bus address of the NTAG I2C tag chip. Note that this is a 7-bit address with the read/write bit appended
	         - I2C Subaddress—displays the memory block address of the NTAG I2C tag chip
	         - I2C Data[0]..Data[15]—there are always 16 data bytes provided whenever data is sent to the NTAG I2C tag chip, except when programming the Session Register.
         *
         */
        private byte[] createTransactionCommandToI2C(byte numberOfBytes,
                                                   byte transactionIdentifier,
                                                   byte sessionIdentifier,
                                                   byte hid_I2C_req_device_xfer,
                                                   byte writeBytes,
                                                   byte readBytes,
                                                   byte options,
                                                   byte I2Caddress,
                                                   byte address)
        {
            byte[] _data = new byte[numberOfBytes];
            _data[0] = numberOfBytes;
            _data[1] = transactionIdentifier;
            _data[2] = sessionIdentifier;
            _data[3] = hid_I2C_req_device_xfer;
            _data[4] = writeBytes;
            _data[5] = readBytes;
            _data[6] = options;
            _data[7] = (byte)(I2Caddress >> 1);
            _data[8] = address;
            return _data;
        }

       
        private string getExtraLogForWriteBlock(byte[] data) {
            string logInfo;

            logInfo = "\r\nI²C Data[0]..Data[" + data.Length + "]:";
            for (int i = 0; i < data.Length; i++)
            {
                if ((i - 9) % 4 == 0)
                    logInfo += "\r\n";
                logInfo += " 0x" + data[i].ToString("X2");
            }
            return logInfo;
        }

        private string getExtraLogForWriteRegister(byte registerAddress, byte registerValue) {
            string logInfo;
            logInfo = "\r\nRegister address:     0x" + registerAddress.ToString("X2");
            logInfo += "\r\nMask:                 0xFF";
            logInfo += "\r\nData:                 0x" + registerValue.ToString("X2");
            return logInfo;
        }
     
        private static byte[] addBytesToWriteToCommand(byte[] writeBytes, byte[] cmd)
        {
            for (int i = 0; i < writeBytes.Length; i++)
                cmd[i + 9] = writeBytes[i];
            return cmd;
        }

        /** @brief Get the speed of the I2C Bus.
         * 
         *  @return the speed of the bus
         */
        public int getBusSpeed() 
        {
            return ntag.getBusSpeed();
        }

        /** @brief Set the speed of the I2C Bus.
         *  @param speed is the speed of the I2C Bus
         */
        public void setBusSpeed(int value) 
        {
            ntag.setBusSpeed(value);
        }

        /** @brief Reinitialize the communication with the port
        * 
        *  @param busSpeedInKHz is the bus speed on the bus for the communication
        */
        public void reinitPort(int busSpeedKhz)
        {
            ntag.reinitPort(busSpeedKhz);
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
        public bool checkDevPresentAndConnect()
        {
            return ntag.checkPresenceAndConnect();
        }

        /** @brief Indicates if the device is connected.      
        * 
        * @return the true if the device is connected.
        */
        public bool isDeviceConnected()
        {
            return ntag.device.isConnected();
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
            return ntag.device.waslastTimePresent;
        }

        /** @brief Closes the connection with the device in case the device has been disconnected.
         * 
         */
        public void disconnectDevice()
        {
            ntag.closeIfNoConnection();
        }
    }
}
