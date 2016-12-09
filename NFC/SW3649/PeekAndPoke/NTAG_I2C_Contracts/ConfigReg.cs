using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum ConfigReg
    {
        NC_REG = 0,
        LAST_NDEF_BLOCK = 1,
        SRAM_MIRROR_BLOCK = 2,
        WDT_LS = 3,
        WDT_MS = 4,
        I2C_CLOCK_STR = 5,
        REG_LOCK = 6,
    }
}
