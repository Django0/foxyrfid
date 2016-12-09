using NTAG_I2C.Contracts;
using System;
using System.Text;
namespace PeekAndPoke
{
    public class NDEFUtils
    {
        private NtagI2CDevice myDevice;

        public NDEFUtils(NtagI2CDevice device)
        {
            this.myDevice = device;
        }
        // When the Write button in the default NDEF groupbox is pressed, the form is closed
        public void CreateNdefText(byte[] text, out byte[] NDEFmessage)
        {
            // Define the NDEF header
            byte[] ndefHeader = new byte[] { 0x03, (byte)(text.Length + 7), 0xD1, 0x01, (byte)(text.Length + 3), 0x54, 0x02, 0x65, 0x6E };

            // Define the whole NDEF message
            NDEFmessage = new byte[ndefHeader.Length + text.Length + 1];
            Array.Copy(ndefHeader, 0, NDEFmessage, 0, ndefHeader.Length);   // header
            Array.Copy(text, 0, NDEFmessage, ndefHeader.Length, text.Length);   // body
            NDEFmessage[ndefHeader.Length + text.Length] = 0xFE;    // terminator
        }

        // Creates the default NDEF message, which contains a smart poster and an AAR
        public void CreateDefaultNdef(out byte[] NDEFmessage)
        {
            byte nfcForumType2 = (byte)0x03;
            // Define the NDEF contents
            byte[] text = Encoding.UTF8.GetBytes("NTAG I2C EXPLORER".ToCharArray());
            byte[] uri = Encoding.UTF8.GetBytes("nxp.com/demoboard/OM5569".ToCharArray());
            byte[] aar = Encoding.UTF8.GetBytes("android.com:pkgcom.nxp.ntagi2cdemo".ToCharArray());
            byte length = (byte)(text.Length + uri.Length + aar.Length + 20);

            byte tnfAndFlags_SP = this.myDevice.api.getNdefTNFandFlagsByte(true, false, false, true, 0x00, TypeNameFormatType.NfcRtd);//0x91
            byte tnfAndFlags_Txt = this.myDevice.api.getNdefTNFandFlagsByte(true, false, false, true, 0x00, TypeNameFormatType.NfcRtd);//0x91
            byte tnfAndFlags_Uri = this.myDevice.api.getNdefTNFandFlagsByte(false, true, false, true, 0x00, TypeNameFormatType.NfcRtd);//0x51
            byte tnfAndFlags_Aar = this.myDevice.api.getNdefTNFandFlagsByte(false, true, false, true, 0x00, TypeNameFormatType.ExternalRtd); //0X54

            byte spTypeField = Convert.ToByte('S');
            byte textTypeField = Convert.ToByte('T');
            byte uriTypeField = Convert.ToByte('U');
            byte typeLength = 0x01;
            byte id = 0x02;

            // Define the NDEF headers
            byte[] generalHeader = new byte[] { nfcForumType2, length };
            byte[] spHeader = new byte[] { tnfAndFlags_SP, 0x02, (byte)(text.Length + uri.Length + 12), spTypeField, 0x70 };
            byte[] textHeader = new byte[] { tnfAndFlags_Txt, typeLength, (byte)(text.Length + 3), textTypeField, id, Convert.ToByte('e'), Convert.ToByte('n') };
            byte[] uriHeader = new byte[] { tnfAndFlags_Uri, typeLength, (byte)(uri.Length + 1), uriTypeField, 0x01 };
            byte[] aarHeader = new byte[] { tnfAndFlags_Aar, 0x0F, 0x13 };

            NDEFmessage = getNdefMsg(text, uri, aar, generalHeader, spHeader, textHeader, uriHeader, aarHeader);
        }

        public static byte[] getNdefMsg(byte[] text, byte[] uri, byte[] aar, byte[] generalHeader, byte[] spHeader, byte[] textHeader, byte[] uriHeader, byte[] aarHeader)
        {
            byte[] NDEFmessage;
            // Define the whole NDEF message
            var ndefMsgLength = generalHeader.Length + spHeader.Length + textHeader.Length + text.Length + uriHeader.Length + uri.Length + aarHeader.Length + aar.Length + 1;
            NDEFmessage = new byte[ndefMsgLength];
            int srcIdx = 0;
            Array.Copy(generalHeader, 0, NDEFmessage, srcIdx, generalHeader.Length);   // Smart Poster header
            srcIdx += generalHeader.Length;
            Array.Copy(spHeader, 0, NDEFmessage, srcIdx, spHeader.Length);   // Smart Poster header
            srcIdx += spHeader.Length;
            Array.Copy(textHeader, 0, NDEFmessage, srcIdx, textHeader.Length);   // text header
            srcIdx += textHeader.Length;
            Array.Copy(text, 0, NDEFmessage, srcIdx, text.Length);   // text
            srcIdx += text.Length;
            Array.Copy(uriHeader, 0, NDEFmessage, srcIdx, uriHeader.Length);   // URI header
            srcIdx += uriHeader.Length;
            Array.Copy(uri, 0, NDEFmessage, srcIdx, uri.Length);   // URI
            srcIdx += uri.Length;
            Array.Copy(aarHeader, 0, NDEFmessage, srcIdx, aarHeader.Length);   // AAR header
            srcIdx += aarHeader.Length;
            Array.Copy(aar, 0, NDEFmessage, srcIdx, aar.Length);   // AAR
            srcIdx += aar.Length;
            NDEFmessage[ndefMsgLength - 1] = 0xFE;  // terminator
            return NDEFmessage;
        }
       
    }
}
