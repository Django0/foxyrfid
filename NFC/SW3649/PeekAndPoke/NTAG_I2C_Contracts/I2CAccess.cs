using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public enum AccessType {readandwrite, onlyread, noaccess};
    public class I2CAccess
    {
        public AccessType accessRights;
        public byte protAreaBegin;
        public int byteOffset;
        public bool sector1prot;

        public I2CAccess()
        {
            accessRights = AccessType.readandwrite;
            protAreaBegin = 0xFF;
            byteOffset = 0;
            sector1prot = false;
        }
    }
}
