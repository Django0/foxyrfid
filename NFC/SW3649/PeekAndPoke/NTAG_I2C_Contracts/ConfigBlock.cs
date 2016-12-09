using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

///
/// Namespace for the data model classes. 
///
namespace NTAG_I2C.Contracts
{
    public enum ConfigBlock
    {
        I2Caddress = 0,
        SerialNumber = 1,
        InternalData = 7,
        LockBytes = 10,
        CapabilityContainer = 12
    }
}
