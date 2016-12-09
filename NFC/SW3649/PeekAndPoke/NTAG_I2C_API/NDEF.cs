using NTAG_I2C.Contracts;
using System;


namespace NTAG_I2C.API
{
    public static class NDEF
    {
        private const int maxShortLength = 255;
        private const byte nfcForumType2 = 0x03;

        private static byte[] toBytes(int i)
        {
            byte[] result = new byte[4];

            result[0] = (byte)(i >> 24);
            result[1] = (byte)(i >> 16);
            result[2] = (byte)(i >> 8);
            result[3] = (byte)(i);

            return result;
        }

        /** @brief Creates a NDEF formatted message 
         * 
         * @param payload is the text data contained in the NDEF message
         * 
         *  @return the NDEF message
         */
        public static byte[] createTextNdefMessage(byte[] payload)
        {
            bool msgBegin = true;
            bool msgEnd = true;
            bool chunkFlag = false;
            int _payload = payload.Length + 3; // 3 = 2 (EN language +1)
            bool shortRecord = (_payload > maxShortLength ? false : true);
            byte idLength = 0x00;


            byte tnfAndFlags = getTNFandFlagsByte(msgBegin, msgEnd, chunkFlag, shortRecord, idLength, TypeNameFormatType.NfcRtd);

            byte id = 0x02;
            byte[] generalHeader = getNDEFgeneralHeader(payload);
            byte[] recordHeader = getTextNDEFrecordHeader(_payload, shortRecord, tnfAndFlags, id);
            byte[] NDEFmessage = getNDEFmsg(payload, generalHeader, recordHeader);

            return NDEFmessage;
        }

        private static byte[] getNDEFmsg(byte[] payload, byte[] generalHeader, byte[] recordHeader)
        {
            byte[] NDEFmessage = new byte[generalHeader.Length + recordHeader.Length + payload.Length + 1];

            Array.Copy(generalHeader, 0, NDEFmessage, 0, generalHeader.Length);   // general header

            Array.Copy(recordHeader, 0, NDEFmessage, generalHeader.Length, recordHeader.Length);   // record header

            Array.Copy(payload, 0, NDEFmessage, generalHeader.Length + recordHeader.Length, payload.Length);   // body

            NDEFmessage[generalHeader.Length + recordHeader.Length + payload.Length] = 0xFE;    // terminator
            return NDEFmessage;
        }

        /** @brief Creates the header of a text NDEF record 
         * 
         *  @param payload is the text data contained in the NDEF record
         *  @param shortRecord indicates if the payload length is higuer than 2^8-1
         *  @param tnfAndFlags is the byte on the header containing the characterisitics of the headers
         * 
         *  @return the record header
         */
        public static  byte[] getTextNDEFrecordHeader(int payload, bool shortRecord, byte tnfAndFlags, byte id)
        {
            byte[] recordHeader;
            byte textTypeField = Convert.ToByte('T');
            byte typeLength = 0x01;
            if (shortRecord)
            {
                byte recordLength = (byte)(payload);
                recordHeader = new byte[] { tnfAndFlags, typeLength, recordLength, 
                    textTypeField, id, Convert.ToByte('e'), Convert.ToByte('n') };
            }
            else
            {
                byte[] recordLength = toBytes(payload);
                recordHeader = new byte[] { tnfAndFlags, typeLength, 
                    recordLength[0], recordLength[1], recordLength[2], recordLength[3], 
                    textTypeField, id, Convert.ToByte('e'), Convert.ToByte('n') };
            }
            return recordHeader;
        }

        private static byte[] getNDEFgeneralHeader(byte[] payload)
        {
            int minHeaderLenght = 7;
            bool shortHeader = (payload.Length + minHeaderLenght > maxShortLength ? false : true);
            byte[] generalHeader;

            if (shortHeader)
            {
                byte totalLength = (byte)(payload.Length + 7);
                generalHeader = new byte[] { nfcForumType2, totalLength };
            }
            else
            {
                byte[] totalLength = toBytes(payload.Length + 10);
                totalLength[1] = (byte)0xFF; // NDEF formatting
                generalHeader = new byte[] { nfcForumType2, totalLength[1], totalLength[2], totalLength[3] };
            }
            return generalHeader;
        }

        /** @brief Creates and returns the TNF and Flags byte.
         * 
         *  @param msgBegin is the flag indicating if the NDEF Record is the first
         *  @param msgEnd is the flag indicating if the NDEF Record is the last
         *  @param chunkFlag is the flag indicating if it is a chunked message part
         *  @param shortRecord is the flag indicating if the message is shorter than 2^8-1
         *  @param idLength indicates the length of the id
         *  @param type indicats the name format type
         *  
         * @return the TNF and Flag byte
         */
        public static byte getTNFandFlagsByte(bool msgBegin, bool msgEnd, bool chunkFlag, bool shortRecord, byte idLength, TypeNameFormatType type)
        {
            byte tnfAndFlags = 0x00;
            tnfAndFlags |= (byte)(Convert.ToByte(msgBegin) << 7);
            tnfAndFlags |= (byte)(Convert.ToByte(msgEnd) << 6);
            tnfAndFlags |= (byte)(Convert.ToByte(chunkFlag) << 5);
            tnfAndFlags |= (byte)(Convert.ToByte(shortRecord) << 4);
            tnfAndFlags |= (byte)(idLength << 3);
            tnfAndFlags |= (byte)type;
            return tnfAndFlags;
        }

    }
}
