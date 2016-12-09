using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HidLibrary;
using NTAG_I2C.Contracts;


namespace I2C_Communication
{
    ///
    /// This class represents the I2C Port communication
    ///
    ///
    public class I2C_Port
    {
        private int busSpeed; /**< Bus speed for the communication in Hz. */
        public bool initialised; /**< Indicates if the port connection has been already initialised. */

        public I2C_Port()
        {
            setBusSpeedInHz(null);
            initialised = false;
        }

        public I2C_Port(int busSpeedInHz)
        {
            setBusSpeedInHz(busSpeedInHz);
            initialised = false;
        }

        internal void setBusSpeedInHz(int? value)
        {
            if (value != null)
            {
                this.busSpeed = (int)value;
                return;
            }
            try
            {
                var speed = ConfigurationSettings.AppSettings["defaultBusSpeed"];
                this.busSpeed = Int32.Parse(speed);
            }
            catch (Exception)
            {
                this.busSpeed = 100000;
            }
        }

        public int getBusSpeedInHz() 
        {
            return (int)busSpeed;
        }

        
        private byte[] CreateCommandToInitoI2CPort()
        {
            byte[] data = new byte[16];
            data[0] = 0x0C;    // total number of bytes
            data[1] = 0x00;    // Transaction identifier
            data[2] = 0x29;    // Session identifier
            data[3] = 0x01;	// HID_I2C_REQ_INIT_PORT
            data[4] = (byte)(this.busSpeed & 0xFF);    // I2C bus speed
            data[5] = (byte)((this.busSpeed >> 8) & 0xFF);
            data[6] = (byte)((this.busSpeed >> 16) & 0xFF);
            data[7] = (byte)((this.busSpeed >> 24) & 0xFF);
            data[8] = 0x00;
            data[9] = 0x00;
            data[10] = 0x00;
            data[11] = 0x00;
            data[12] = 0x00;
            data[13] = 0x00;
            data[14] = 0x00;
            data[15] = 0x00;
            return data;
        }

        /** @brief Initialize the communication with the port
         * 
         *  @param device is the object representing the device to connect with.
         *  @return the response from the command to init the port.
         */
        public I2CData init(I2C_Device device)
        {
            var command = CreateCommandToInitoI2CPort();
            var returnVal = device.performTransaction(command);
            initialised = true;
            return returnVal;
        }

        /** @brief Reinitialize the communication with the port
         * 
         *  @param device is the object representing the device to connect with.
         *  @param busSpeedInKHz is the bus speed on the bus for the communication
         *  @return the response from the command to init the port.
         */
        public I2CData reinit(int busSpeedInKHz, I2C_Device device)
        {
            I2CData result = null;
            setBusSpeedInHz(busSpeedInKHz * 1000);
            if (device.isConnected())
            {
                result = init(device);
            }
            return result;
        }
    }
}