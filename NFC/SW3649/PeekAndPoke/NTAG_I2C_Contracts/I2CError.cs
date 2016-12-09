using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum I2CError
    {
        Success = 0,
        Unknown = 1,
        Nak = 2,
        BusError = 3,
        NakAfterSla = 4,
        ArbitrationLost = 5,
        TimeOut = 16,
        InvalidRequest = 17,
        InvalidParameters = 18,
        PartialCompleted = 19,
        NoHw = 20,
        Undefined = 200
    }
}
