using NTAG_I2C.Contracts;

///
/// Namespace for the classes dealing with the I2C communication.
///
namespace I2C_Communication
{
    ///
    /// This class contains the main functionalities to perform the whole communication.
    ///
    ///
    public class I2C_Comm
    {
        public I2C_Device device { get; set; } /**< Representation of the I2C device connected */
        public I2C_Port port { get; set; }/**< Representation of the i2c port */

        public I2C_Comm() 
        {
            device = new I2C_Device();
            port = new I2C_Port();

            checkPresenceAndConnect();
        }       

        public I2C_Comm(int deviceProductId, int deviceVendorId, int busSpeed) 
        {
            device = new I2C_Device(deviceProductId, deviceVendorId);
            port = new I2C_Port(busSpeed);

            checkPresenceAndConnect();
        } 

        /** @brief Get the speed of the I2C Bus.
         * 
         *  @return the speed of the bus
         */
        public int getBusSpeed()
        {
            return port.getBusSpeedInHz();
        }

        /** @brief Set the speed of the I2C Bus.
         *  @param speed is the speed of the I2C Bus
         */
        public void setBusSpeed(int speed)
        {
            if (port.getBusSpeedInHz() != speed)
            {
                port.setBusSpeedInHz(speed);
            }
        }

        /** @brief Send a command to the I2C device. 
         * 
         * It sends the command and reads the response sent by the device.
         * 
         *  @param command is the command to send to the i2c device
         *  @return the response of the command
         */
        public I2CData performTransaction(byte[] command)
        {
            return device.performTransaction(command);
        }

        /** @brief Send a command to the I2C device. 
         * 
         * It sends the command. It reads the response to the command
         *  sent by the device and the read the data requested by
         *  the command.
         * 
         *  @param sentData is the command to send to the i2c device
         *  @param readDataLength is the length of the data requested to read.
         *  @return the response of the command and the data requested.
         */
        public I2CData performTransactionAndGetData(byte[] sentData, int readDataLength)
        {
            return device.performTransaction(sentData, readDataLength);
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
            var result = device.checkAndSetConnection();
            if (device.waslastTimePresent && !port.initialised)
                port.init(device);
            return result;
        }



        /** @brief Closes the connection with the device in case the device has been disconnected.
         * 
         */
        public void closeIfNoConnection()
        {
            device.closeIfDeviceNotConnected();
        }

        /** @brief Reinitializes the connection with the i2c port.
         * 
         * It sets a new speed for the bus and reinitializes
         * the port connection.
         * 
         * @param busSpeedKhz is the new speed for the bus in Khz.
         */
        public void reinitPort(int busSpeedKhz)
        {
            port.reinit(busSpeedKhz, device);
        } 

    }
}
