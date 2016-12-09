using System;
using System.Linq;
using HidLibrary;
using NTAG_I2C.Contracts;
using NTAG_I2C.API;


namespace PeekAndPoke
{
    public class NtagI2CDevice
    {       
        public const int bytesInBlock = 16;
        public const int blocks = 256;
        public const int dynLockBytes = 3;
        

        //Access Registers const
        public const int accessbytes = 1;
        public const int pwdbytes = 4;
        public const int packbytes = 2;
        public const int pti2cbytes = 1;
        public const int rfu1bytes = 3;
        public const int rfu2bytes = 2;
        public const int rfu3bytes = 3;



        private HidDevice hidDevice = null;
        public bool isPresent;
        public String FWversion;
        public bool flag;
        public I2CError error;
        public int busSpeed = 100000;
        public byte i2cAddress = 0xAA;
        public NtagI2C api { get; set; }

        // Constructor
        public NtagI2CDevice()
        {
            api = new NtagI2C();
        }

        // Destructor
        ~NtagI2CDevice()
        {
            api.disconnectDevice();
        }

        // Reinitializes the I2C port with the bus speed indicated
        public void reinitPort(int busSpeedKhz)
        {
            api.reinitPort(busSpeedKhz);
        }
       
        public bool checkIfPresent()
        {
            this.isPresent = api.checkPresenceAndConnect();
            return this.isPresent;
        }

        public I2CError readBlock(byte I2Caddress, byte address, out byte[] readBytes, out String log)
        {
            var read = api.readBlockMemory(I2Caddress, address);
            readBytes = read.data;
            log = read.log;
            setFlag(read);
            return read.error;
        }

        private void setFlag(I2CData read)
        {
            this.flag = read.flag;
        }

        public I2CError writeBlock(byte I2Caddress, byte address, byte[] writeBytes, out String log)
        {
            var read = api.writeBlockMemory(I2Caddress, address, writeBytes);            
            log = read.log;
            setFlag(read);
            return read.error;
        }

        public I2CError readSessionRegister(byte I2Caddress, byte subAddress, out byte readRegister, out String log)
        {
            var read = api.readSessionRegister(I2Caddress, TagType.NTAG1K, subAddress); //TODO:Refactor and check tag type
            readRegister = read.data[0];
            log = read.log;
            setFlag(read);
            return read.error;
        }

        public I2CError readSessionRegisters(byte I2Caddress, TagType type, out byte[] readRegisters, out String log)
        {
            log = "";
            this.error = I2CError.Undefined;    
            int numRegs = Enum.GetNames(typeof(SessionReg)).Length;
        
            var read = api.readAllSessionRegister(I2Caddress, type); //TODO:Refactor and check tag type
            readRegisters = new byte[numRegs];

            if (read != null && read.Count == numRegs)
                this.error = I2CError.Success;
            
         
            for(var i = 0; i< numRegs; i++)
            {
                readRegisters[i] = read[i].data[0];
                setFlag(read[i]);
                log += Environment.NewLine + read[i].log;
                if (read[i].error == I2CError.Undefined || read[i].error != I2CError.Success)
                    error = read[i].error;
                i++;
            }            
            return error;
        }

        public I2CError writeSessionRegister(byte I2Caddress, byte subAddress, byte writeRegister, out String log)
        {
            log = "";
            this.error = I2CError.Undefined;
            var write = api.writeSessionRegister(I2Caddress, TagType.NTAG1K, subAddress, writeRegister);
            log = write.log;
            setFlag(write);
            return this.error;
        }

        // Writes the session registers
        public I2CError writeSessionRegisters(byte I2Caddress, byte[] writeRegisters, out String log)
        {
            log = "";
            this.error = I2CError.Undefined;
            var write = api.writeAllSessionRegister(I2Caddress, writeRegisters, TagType.NTAG1K);
            this.error = write.error;
            setFlag(write);
            return error;
        }

        // Writes all the blocks of an NDEF message
        public I2CData writeNdef(byte I2Caddress, byte[] ndef)
        {
            return this.api.writeTextNdef(I2Caddress, ndef);
        }

        public I2CData writeMessage(byte I2Caddress, byte[] payload)
        {
            return api.writeMessage(I2Caddress, payload);
        }

        /*private static byte[] getNthBlock(byte[] ndef, int i)
        {
            byte[] block = new byte[bytesInBlock];
            Array.Copy(ndef, i * bytesInBlock, block, 0, Math.Min(bytesInBlock, ndef.Length - i * bytesInBlock));
            return block;
        }

        private static int getNumberOfMsgBlocks(byte[] ndef)
        {
            int numBlocks = (int)Math.Ceiling(((double)ndef.Length) / bytesInBlock);
            return numBlocks;
        } */      
    }
}
