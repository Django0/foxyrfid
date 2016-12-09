using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public class I2CData
    {
        public byte[] data;
        public I2CError error;
        public bool flag;
        public string log;
    }
}
