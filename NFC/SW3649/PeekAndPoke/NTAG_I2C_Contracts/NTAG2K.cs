using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum NTAG2K
    {
        UserMemoryBegin = 0x00,
        UserMemoryEnd = 0X79,
        ConfigMemoryBegin = 0x7A,
        ConfigMemoryEnd = 0x7B,
        SRAMMemoryBegin = 0xF8,
        SRAMMemoryEnd = 0xFC,
        SessionMemoryBegin = 0xFE,
        SessionMemoryEnd = 0xFF,
        DynLockBytesPos = 0x00
    }
}
