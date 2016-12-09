using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NTAG_I2C.Contracts;

namespace NTAG_I2C.API
{
    ///
    /// This class represents the address of the Ntag I2C with the functionalities related to it
    ///
    ///
    public class I2CAddress
    {
        private const int MAX_ADDRESS = 255;
        private const int BYTES_LENGTH = 2;
        private BlockMemory mem;

        public I2CAddress(BlockMemory memory) 
        {
            mem = memory;
        }

        /** @brief Checks in all possible I2C address if there is a device connected there.
         * 
         * @param addressToDiscard is a list of addressess to be ommitted on the scanning. It is
         * useful to exclude LCD or temperature sensor addresses
         * @param callback is a function to be called after each address check with its result
         * 
         *  @return a list with the result of each checking 
         */
        public List<I2CData> scanning(List<int> addressToDiscard, Action<I2CData> callback = null)
        {
            List<I2CData> addressLog = new List<I2CData>();

            for (int i = 0; i < MAX_ADDRESS; i+= BYTES_LENGTH) 
            {
                if (!addressToDiscard.Contains(i))
                {
                    var res = checkNthDevice(i);
                    addressLog.Add(res);
                    if(callback != null)
                        callback(res);
                }
                else
                {
                    I2CData output = new I2CData() { error = I2CError.Nak, log = "This address has been omitted. Another device may be connected there." };
                    addressLog.Add(output);
                    callback(output);
                }
               
            }
            return addressLog;
        }


        private I2CData checkNthDevice(int i)
        {
            string log = "Scan for I²C Address: 0x" + i.ToString("X2") + Environment.NewLine + i.ToString("X2");
            
            I2CData scanOutput = readAddressOnNthDevice(i);
            if (scanOutput != null)
            {
                log += scanOutput.log;

                if (scanOutput.error == I2CError.Success)
                {

                    log += "I²C device found at address 0x" + i.ToString("X2");
                    log += "I²C Success" + Environment.NewLine + i.ToString("X2");
                }
                else
                {
                    log += "I²C device not found";
                }
            }
            return scanOutput;
        }

        private I2CData readAddressOnNthDevice(int i2cAddressValue)
        {
            I2CData scanOutput;
            byte i2cAddressMemPos = 0x00;          
            scanOutput = mem.read((byte)i2cAddressValue, i2cAddressMemPos);
            return scanOutput;
        }
    }
} 
