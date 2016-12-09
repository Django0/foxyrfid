using System;
using Xunit;
using NTAG_I2C.Contracts;
using NTAG_I2C.API;
using System.Collections.Generic;
using PeekAndPoke;
using System.Diagnostics;

namespace NTAG_I2C_Commands_Test
{    
    public class API_Test
    {
        private byte i2cAdress;
        private NtagI2C ntag;
        public API_Test(){
            i2cAdress = Utils.HexToByte("AA");
            ntag = new NtagI2C();
        }


        [Fact]
        public void testGetBusSpeed()
        {
            //arrange
            int expectedDefaultBusSpeed = 100000;

            //act            
            int actualBusSpeed = ntag.getBusSpeed();

            //asserrt
            Assert.Equal(expectedDefaultBusSpeed, actualBusSpeed);
        }

        [Fact]
        public void testReadAllMemory_1kTag()
        {
            //arrange
            I2CError expectedError = I2CError.Success;

            //act
            List<I2CData> actualOutputs = ntag.readAllMemory(TagType.NTAG1K, i2cAdress);

            //assert
            foreach (var actualRead in actualOutputs)
            {
                foreach(var data in actualRead.data)
                    Debug.Write(" 0x" + data.ToString("X2"));
                Debug.WriteLine("");
                Assert.Equal(expectedError, actualRead.error);
                Assert.True(actualRead.data.Length > 0);
            }
        }

        [Fact]
        public void testWriteAllMemory_1KTag()
        {
            //arrange
            I2CError expectedError = I2CError.Success;
            List<I2CData> read = ntag.readAllMemory(TagType.NTAG1K, i2cAdress);
            byte[][] writeBytes = new byte[read.Count][];
            int idx = 0;

            foreach (var o in read)
            {
                writeBytes[idx] = o.data;
                idx++;
            }

            //act
            List<I2CData> actualOutputs = ntag.writeAllMemory(TagType.NTAG1K, i2cAdress, writeBytes);

            //assert
            foreach (var write in actualOutputs)
            {
                Assert.Equal(expectedError, write.error);
            }
        }

        [Fact]
        public void testReadAllMemory_2kTag()
        {
            //arrange
            I2CError expectedError = I2CError.Success;

            //act
            List<I2CData> actualOutputs = ntag.readAllMemory(TagType.NTAG2K, i2cAdress);

            //assert
            foreach (var actualRead in actualOutputs)
            {

                Assert.Equal(expectedError, actualRead.error);
                Assert.True(actualRead.data.Length > 0);
            }
        }

        [Fact]
        public void testWriteAllMemory_2KTag()
        {
            //arrange
            I2CError expectedError = I2CError.Success;
            List<I2CData> read = ntag.readAllMemory(TagType.NTAG2K, i2cAdress);
            byte[][] writeBytes = new byte[read.Count][];
            int idx = 0;

            foreach (var o in read)
            {
                writeBytes[idx] = o.data;
                idx++;
            }

            //act
            List<I2CData> actualOutputs = ntag.writeAllMemory(TagType.NTAG1K, i2cAdress, writeBytes);

            //assert
            foreach (var write in actualOutputs)
            {
                Assert.Equal(expectedError, write.error);
            }
        }

        [Fact]
        public void readAllConfigRegisters_1KTag() {
            //arrange
            I2CError expectedError = I2CError.Success;
            
           
            //act
            var actualRegister = ntag.readAllConfigRegister(i2cAdress, TagType.NTAG1K);

            //assert          
            foreach (var data in actualRegister.data)
                Debug.Write(" 0x" + data.ToString("X2"));
            Assert.Equal(expectedError, actualRegister.error);
            
   
            
        }

        [Fact]
        public void writeAllConfigRegisters_1KTag()
        {
            //arrange
            int configRegCount = Enum.GetNames(typeof(SessionReg)).Length;
            I2CError expectedError = I2CError.Success;
            int blockSize = 16;
            byte[] mockUpRegisters = new byte[16];
            int i = 0;

            mockUpRegisters[(int)ConfigReg.NC_REG] =  Utils.HexToByte("41");
            mockUpRegisters[(int)ConfigReg.LAST_NDEF_BLOCK] = Utils.HexToByte("00");
            mockUpRegisters[(int)ConfigReg.SRAM_MIRROR_BLOCK] = Utils.HexToByte("f8");
            mockUpRegisters[(int)ConfigReg.WDT_LS] = Utils.HexToByte("48");
            mockUpRegisters[(int)ConfigReg.WDT_MS] = Utils.HexToByte("08");
            mockUpRegisters[(int)ConfigReg.I2C_CLOCK_STR] = Utils.HexToByte("01");
            mockUpRegisters[(int)ConfigReg.REG_LOCK] = Utils.HexToByte("00");

            for (int j = 7; j < blockSize; j++)
                mockUpRegisters[j] = (byte)0;

            //act
            var actualWritten = ntag.writeAllConfigRegister(i2cAdress, mockUpRegisters, TagType.NTAG1K);
            var readOutput = ntag.readAllConfigRegister(i2cAdress, TagType.NTAG1K);

                    
            

            //assert
            Assert.Equal(expectedError, actualWritten.error);
            Assert.Equal(expectedError, readOutput.error);
            for (i = 0; i < configRegCount; i++)
            {
                Debug.Write(" 0x" + readOutput.data[i].ToString("X2"));
                Assert.Equal(mockUpRegisters[i], readOutput.data[i]);                
            }
        }

        [Fact]
        public void readAllSessionRegisters_1KTag()
        {
            //arrange
            I2CError expectedError = I2CError.Success;
            
            //act
            var actualRegisters = ntag.readAllSessionRegister(i2cAdress, TagType.NTAG1K);

            //assert
            foreach (var data in actualRegisters)
            {
                foreach (var d in data.data)
                    Debug.Write(" 0x" + d.ToString("X2"));
                Assert.Equal(expectedError, data.error);
            }
        }

        [Fact]
        public void writeAllSessionRegisters_1KTag()
        {
            //arrange
            int sessionRegCount = Enum.GetNames(typeof(SessionReg)).Length;
            I2CError expectedError = I2CError.Success;
            int blockSize = 16;
            byte[] mockUpRegisters = new byte[16];
            int i = 0;

            mockUpRegisters[(int)ConfigReg.NC_REG] =  Utils.HexToByte("03");
            mockUpRegisters[(int)ConfigReg.LAST_NDEF_BLOCK] = Utils.HexToByte("00");
            mockUpRegisters[(int)ConfigReg.SRAM_MIRROR_BLOCK] = Utils.HexToByte("f8");
            mockUpRegisters[(int)ConfigReg.WDT_LS] = Utils.HexToByte("48");
            mockUpRegisters[(int)ConfigReg.WDT_MS] = Utils.HexToByte("08");
            mockUpRegisters[(int)ConfigReg.I2C_CLOCK_STR] = Utils.HexToByte("01");
            mockUpRegisters[(int)ConfigReg.REG_LOCK] = Utils.HexToByte("00");

            for (int j = 7; j < blockSize; j++)
                mockUpRegisters[j] = (byte)0;

            //act
            var actualWritten = ntag.writeAllSessionRegister(i2cAdress, mockUpRegisters, TagType.NTAG1K);
            var readOutput = ntag.readAllSessionRegister(i2cAdress, TagType.NTAG1K);

            byte[] actualRegisters = new byte[sessionRegCount];
            for (i = 0; i < sessionRegCount; i++)
                actualRegisters[i] = readOutput[i].data[0];            

            //assert
            Assert.Equal(expectedError, actualWritten.error);
            for (i = 0; i < sessionRegCount; i++)
            {     
                Assert.Equal(expectedError, readOutput[i].error);
                Assert.True(readOutput[i].data.Length == 1);
                Assert.Equal(mockUpRegisters[i], readOutput[i].data[0]);                
            }
        }

        [Fact]
        public void writeAllSessionRegisters_2KTag()
        {
            //arrange
            int sessionRegCount = Enum.GetNames(typeof(SessionReg)).Length;
            I2CError expectedError = I2CError.Success;
            int blockSize = 16;
            byte[] mockUpRegisters = new byte[16];
            int i = 0;

            mockUpRegisters[(int)ConfigReg.NC_REG] = Utils.HexToByte("03");
            mockUpRegisters[(int)ConfigReg.LAST_NDEF_BLOCK] = Utils.HexToByte("00");
            mockUpRegisters[(int)ConfigReg.SRAM_MIRROR_BLOCK] = Utils.HexToByte("f8");
            mockUpRegisters[(int)ConfigReg.WDT_LS] = Utils.HexToByte("48");
            mockUpRegisters[(int)ConfigReg.WDT_MS] = Utils.HexToByte("08");
            mockUpRegisters[(int)ConfigReg.I2C_CLOCK_STR] = Utils.HexToByte("01");
            mockUpRegisters[(int)ConfigReg.REG_LOCK] = Utils.HexToByte("00");

            for (int j = 7; j < blockSize; j++)
                mockUpRegisters[j] = (byte)0;

            //act
            var actualWritten = ntag.writeAllSessionRegister(i2cAdress, mockUpRegisters, TagType.NTAG2K);
            var readOutput = ntag.readAllSessionRegister(i2cAdress, TagType.NTAG2K);

            byte[] actualRegisters = new byte[sessionRegCount];
            for (i = 0; i < sessionRegCount; i++)
                actualRegisters[i] = readOutput[i].data[0];

            //assert
            Assert.Equal(expectedError, actualWritten.error);
            for (i = 0; i < sessionRegCount; i++)
            {
                Assert.Equal(expectedError, readOutput[i].error);
                Assert.True(readOutput[i].data.Length == 1);
                Assert.Equal(mockUpRegisters[i], readOutput[i].data[0]);
            }
        }
    }
}
