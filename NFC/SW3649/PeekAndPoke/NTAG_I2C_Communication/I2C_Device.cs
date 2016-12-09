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
    /// This class represents the i2c device connected.
    ///
    ///
    public class I2C_Device
    {
        private int productID; /**< Product Identification of the Ntag I2C. */
        private int vendorID; /**< Vendor Identification of the Ntag I2C. */
        public bool waslastTimePresent; /**< Indicates if it was connected at the last check. */
        private HidDevice hidDevice; /**< Representatoin of the human interface device to deal with a device connected by USB. The library HidLibrary is used.*/
        private String FWversion; /**< It holds the firmware version on the Ntag I2C.*/
        
        public I2C_Device() {
            setProductID(null);
            setVendorID(null);
            this.waslastTimePresent = false;
        }

        public I2C_Device(int? productId, int? vendorId)
        {
            setVendorID(vendorId);
            setProductID(productId);
            this.waslastTimePresent = false;
        }

       
        internal void setProductID(int? value)
        {            
            if (value != null)
            {
                this.productID = (int)value;
                return;
            }

            try
            {
                var pID = ConfigurationSettings.AppSettings["readerProductID"];
                this.productID = Int32.Parse(pID);
            }
            catch (Exception)
            {
                this.productID = 0x0088;
            }
        }

        internal void setVendorID(int? value)
        {
            if (value != null)
            {
                this.vendorID = (int)value;
                return;
            }
            try
            {
                var vID = ConfigurationSettings.AppSettings["readerVendorID"];
                this.vendorID = Int32.Parse(vID);
            }
            catch (Exception)
            {
                this.vendorID = 0x1FC9;
            }
        }

        /** @brief Closes the connection with the device.
         * 
         * It closes the connection with the device in case this one 
         * is not connected.
         * 
         */
        public void closeIfDeviceNotConnected()
        {
            if (this.hidDevice != null && !this.hidDevice.IsConnected)
                closeDeviceConnection();
        }

        /** @brief Connects with the I2C Device.
         * 
         * It looks for the device connected by USB with
         * the specified vendorID and productID. If this is found
         * it opens a connection with this one.
         *  
         */
        public void connect()
        {
            HidDevice[] deviceList = getHidDevicesConnected();
            searchOurDeviceAndSetIt(deviceList);

            if (this.hidDevice != null)
                openDeviceConnection();
        }

        internal void openDeviceConnection()
        {            
            this.hidDevice.OpenDevice();
            this.waslastTimePresent = true;
        }

        internal void searchOurDeviceAndSetIt(HidDevice[] deviceList)
        {
            foreach (HidDevice device in deviceList)
                if (device.Attributes.VendorId == vendorID && device.Attributes.ProductId == productID)
                    this.hidDevice = device;
        }

        internal static HidDevice[] getHidDevicesConnected()
        {
            HidDevice[] deviceList = HidDevices.Enumerate().ToArray();
            return deviceList;
        }

        internal void closeDeviceConnection()
        {
            this.waslastTimePresent = false;
            this.hidDevice.CloseDevice();
            this.hidDevice = null;
            this.FWversion = "";
        }


        /** @brief Reads the response of the device through USB      .          
         * 
         * It is used after writing a content on the device
         * to read the response.
         * 
         * @return the report from the HidLibrary with the read data
         */
        internal I2C_Report Read()
        {
            if (hidDevice != null)
            {
                HidReport report = this.hidDevice.ReadReport();
                return new I2C_Report(report);
            }
            else
                return null;
        }

        /** @brief Sends data to the device through USB.      
         * 
         * @return the report from the HidLibrary with the response data
         */
        internal I2C_Report Write(byte[] data)
        {
            if (hidDevice != null)
            {
                HidReport HID_I2C_OutputReport = this.hidDevice.CreateReport();
                HID_I2C_OutputReport.ReportId = 0;
                for (int idx = 0; idx < data.Length; idx++)
                    HID_I2C_OutputReport.Data[idx] = data[idx];

                this.hidDevice.WriteReport(HID_I2C_OutputReport);
                return new I2C_Report(HID_I2C_OutputReport);
            }
            else
                return null;
        }

        /** @brief Indicates if the device is connected.      
         * 
         * @return the true if the device was connected last time checked.
         */
        public bool isConnected()
        {
            return this.waslastTimePresent;
        }


        /** @brief Indicates the firmware version of the device.
         * 
         * @return a string with the firmware version.
         */
        public String getFWVersion()
        {
            return FWversion;
        }

        /** @brief Check if the device is connected and sets the connection
         * 
         * It checks if the connected device is still connected. In case is not
         * anymore, it closes the connection. In case, there was still not a device connected, 
         * it looks for a device and if it finds it, connects to it.
         * 
         * @return true if the device is connected.
         */
        public bool checkAndSetConnection()
        {
            if (this.waslastTimePresent)
            {
                closeIfDeviceNotConnected();
            }
            else
            {
                connect();
            }
            return this.waslastTimePresent;
        }

        /** @brief Performs a transaction of data with the device
         * 
         * It sends data to the device. It reads the response and the 
         * data specified by the readDataLength.
         * 
         * @param sentData is the data to send to the device
         * @param readDataLength is the length of the data requested to get           
         * @return the response of the transaction
         */
        public I2CData performTransaction(byte[] sentData, int readDataLength = 0)
        {
            I2CData returned = null;
            var reportSent = Write(sentData);
            if (reportSent != null && reportSent.IsStatusSuccess())
            {
                var reportRead = Read();
                if (reportRead != null && reportRead.IsStatusSuccess())
                {
                    returned = reportRead.getI2CDataFromReport(readDataLength);
                }
            }
            return returned;
        }
    }
}
