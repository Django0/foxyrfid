using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NTAG_I2C.Contracts
{
    public class NTagMemory
    {
        public byte userMemoryBegin { get; set; }
        public byte userMemoryEnd { get; set; }
        public byte accessMemoryBegin { get; set; }
        public byte accessMemoryEnd { get; set; }
        public byte configMemoryBegin { get; set; }
        public byte configMemoryEnd { get; set; }
        public byte SRAMMemoryBegin { get; set; }
        public byte SRAMMemoryEnd { get; set; }
        public byte sessionMemoryBegin { get; set; }
        public byte sessionMemoryEnd { get; set; }
        public byte dynLockBytesPos { get; set; }

        // Plus family specific
        public byte memProtBegin { get; set; }
        public byte memProtEnd { get; set; }

        // Plus 2K specific
        public byte userMemoryS1Begin { get; set; }
        public byte userMemoryS1End { get; set; }
        public byte userMemoryS2Begin { get; set; }
        public byte userMemoryS2End { get; set; }


        public NTagMemory(TagType type)
        {
            fill(type);
        }

        private void fill(TagType type)
        {
            if (type == TagType.NTAG1K)
            {
                userMemoryBegin = (int)NTAG1K.UserMemoryBegin;
                userMemoryEnd = (int)NTAG1K.UserMemoryEnd;
                configMemoryBegin = (int)NTAG1K.ConfigMemoryBegin;
                configMemoryEnd = (int)NTAG1K.ConfigMemoryEnd;
                SRAMMemoryBegin = (int)NTAG1K.SRAMMemoryBegin;
                SRAMMemoryEnd = (int)NTAG1K.SRAMMemoryEnd;
                sessionMemoryBegin = (int)NTAG1K.SessionMemoryBegin;
                sessionMemoryEnd = (int)NTAG1K.SessionMemoryEnd;
                dynLockBytesPos = (int)NTAG1K.DynLockBytesPos;
            }
            else if (type == TagType.NTAG2K)
            {
                userMemoryBegin = (int)NTAG2K.UserMemoryBegin;
                userMemoryEnd = (int)NTAG2K.UserMemoryEnd;
                configMemoryBegin = (int)NTAG2K.ConfigMemoryBegin;
                configMemoryEnd = (int)NTAG2K.ConfigMemoryEnd;
                SRAMMemoryBegin = (int)NTAG2K.SRAMMemoryBegin;
                SRAMMemoryEnd = (int)NTAG2K.SRAMMemoryEnd;
                sessionMemoryBegin = (int)NTAG2K.SessionMemoryBegin;
                sessionMemoryEnd = (int)NTAG2K.SessionMemoryEnd;
                dynLockBytesPos = (int)NTAG2K.DynLockBytesPos;
            }
            else if (type == TagType.NTAG1KPlus)
            {
                userMemoryBegin = (int)NTAG1KPlus.UserMemoryBegin;
                userMemoryEnd = (int)NTAG1KPlus.UserMemoryEnd;
                accessMemoryBegin = (int)NTAG1KPlus.MemProtBegin;
                accessMemoryEnd = (int)NTAG1KPlus.MemProtEnd;
                configMemoryBegin = (int)NTAG1KPlus.ConfigMemoryBegin;
                configMemoryEnd = (int)NTAG1KPlus.ConfigMemoryEnd;
                SRAMMemoryBegin = (int)NTAG1KPlus.SRAMMemoryBegin;
                SRAMMemoryEnd = (int)NTAG1KPlus.SRAMMemoryEnd;
                sessionMemoryBegin = (int)NTAG1KPlus.SessionMemoryBegin;
                sessionMemoryEnd = (int)NTAG1KPlus.SessionMemoryEnd;
                dynLockBytesPos = (int)NTAG1KPlus.DynLockBytesPos;
                memProtBegin = (int)NTAG1KPlus.MemProtBegin;
                memProtEnd = (int)NTAG1KPlus.MemProtEnd;
            }
            else if (type == TagType.NTAG2KPlus)
            {
                userMemoryBegin = (int)NTAG2KPlus.UserMemoryBegin;
                userMemoryEnd = (int)NTAG2KPlus.UserMemoryEnd;
                accessMemoryBegin = (int)NTAG2KPlus.MemProtBegin;
                accessMemoryEnd = (int)NTAG2KPlus.MemProtEnd;
                configMemoryBegin = (int)NTAG2KPlus.ConfigMemoryBegin;
                configMemoryEnd = (int)NTAG2KPlus.ConfigMemoryEnd;
                SRAMMemoryBegin = (int)NTAG2KPlus.SRAMMemoryBegin;
                SRAMMemoryEnd = (int)NTAG2KPlus.SRAMMemoryEnd;
                sessionMemoryBegin = (int)NTAG2KPlus.SessionMemoryBegin;
                sessionMemoryEnd = (int)NTAG2KPlus.SessionMemoryEnd;
                dynLockBytesPos = (int)NTAG2KPlus.DynLockBytesPos;
                userMemoryS1Begin = (int)NTAG2KPlus.UserMemoryS1Begin;
                userMemoryS1End = (int)NTAG2KPlus.UserMemoryS1End;
                userMemoryS2Begin = (int)NTAG2KPlus.UserMemoryS2Begin;
                userMemoryS2End = (int)NTAG2KPlus.UserMemoryS2End;
                memProtBegin = (int)NTAG2KPlus.MemProtBegin;
                memProtEnd = (int)NTAG2KPlus.MemProtEnd;
            }
            else
            {
                throw new Exception("Ntag type not valid.");
            }
        }        
    }
}
