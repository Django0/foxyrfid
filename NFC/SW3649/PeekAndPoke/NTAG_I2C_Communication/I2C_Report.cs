using System;
using HidLibrary;
using NTAG_I2C.Contracts;

namespace I2C_Communication
{
    ///
    /// This class represents the Report of the HidLibrary adjusted to our application
    ///
    ///
    public class I2C_Report 
    {
        public HidReport report; /**< Report from the HidLibrary. */

        public I2C_Report(int reportSize)        
        {
            report = new HidReport(reportSize);
        }

        public I2C_Report(HidReport hidReport)
        {
            report = hidReport;
        }

        /** @brief Extracts the error information from the report.
         * 
         *  @return the error information.
         */
        public I2CError getReportErrorInformation()
        {
            return (I2CError)report.Data[3];
        }

        /** @brief Extracts the flag information from the report.
         * 
         *  @return the flag.
         */
        public bool getReportFlag()
        {
            return report.Data[1] != 0;
        }

        /** @brief Extracts the requested data to read from the report.
         * 
         *  @param dataLength is the length of data to read
         *  @return the read data.
         */
        public byte[] getReadData(int dataLength)
        {
            byte[] readBytes = new byte[dataLength];
            for (int i = 0; i < dataLength; i++)
                readBytes[i] = report.Data[i + 4];
            return readBytes;
        }

        /** @brief Extracts the firmware version of the device from the report.
         * 
         *  @return a string with the firmware version.
         */
        public String getFWversion()
        {
            String FWversion = "";
            for (int i = 0; i < 32; i++)
                FWversion += (char)report.Data[i + 4];
            return FWversion;
        }

        /** @brief Extracts the data from the report.
         * 
         * It extracts the interesting data from the report
         * like the flag, error and log information. This data 
         * is encapsulated in a I2CData object.
         * 
         *  @return an object witht a set of informatoin of the report.
         */
        public I2CData getI2CDataFromReport(int dataLength)
        {
            var _data = new I2CData
            {
                flag = getReportFlag(),
                error = getReportErrorInformation(),
                log = getI2CReportLog()
            };

            if (dataLength > 0)
                _data.data = getReadData(dataLength);
            return _data;
        }

        private String getI2CReportLog()
        {
            var data = report.Data;
            String s;

            s = "\r\n";
            s += "Report Output Report ID:  " + report.ReportId + "\r\n";
            s += "Total Bytes:              0x" + data[0].ToString("X2") + "\r\n";
            s += "Transaction identifier:   0x" + data[1].ToString("X2") + "\r\n";
            s += "Session identifier:       0x" + data[2].ToString("X2") + "\r\n";
            s += "HID I²C Request:          0x" + data[3].ToString("X2") + "\r\n";
            s += "I²C txLength:             0x" + data[4].ToString("X2") + "\r\n";
            s += "I²C rxlength:             0x" + data[5].ToString("X2") + "\r\n";
            s += "Options:                  0x" + data[6].ToString("X2") + "\r\n";
            s += "I²C Address:              0x" + (data[7] << 1).ToString("X2") + "\r\n";
            s += "I²C Subaddress:           0x" + data[8].ToString("X2");      
            return s;
        }

        /** @brief Checks if the status value is successful.
         * 
         *  @return true if it is successful.
         */
        public bool IsStatusSuccess()
        {
            return report.ReadStatus == HidDeviceData.ReadStatus.Success;
        }

    }
}
