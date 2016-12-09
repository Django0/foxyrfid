using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum NTAG2KPlus 
    {
        UserMemoryBegin = 0x00,         
        UserMemoryEnd = 0X80,
        MemProtBegin = 0x38,
        MemProtEnd = 0x3A,
        ConfigMemoryBegin = 0x3A,       
        ConfigMemoryEnd = 0x3B,         
        SRAMMemoryBegin = 0xF8,         
        SRAMMemoryEnd = 0xFC,           
        SessionMemoryBegin = 0xFE,      
        SessionMemoryEnd = 0xFF,        
        DynLockBytesPos = 0x08,
        UserMemoryS1Begin = 0x00,
        UserMemoryS1End = 0x39,
        UserMemoryS2Begin = 0x40,
        UserMemoryS2End = 0x80,
    }
}
