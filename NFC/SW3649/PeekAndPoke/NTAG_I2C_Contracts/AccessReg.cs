using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum AccessReg
    {
        AUTH0 = 15,
        ACCESS = 0,
        RFU1 = 1,
        PWD = 4,
        PACK = 8,
        RFU2 = 10,
        PT_I2C = 12,
        RFU3 = 13
    }
}
