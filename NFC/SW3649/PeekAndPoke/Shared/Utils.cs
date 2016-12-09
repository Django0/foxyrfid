using System;

namespace NTAG_I2C.Shared
{
    public class Utils
    {
        public static byte HexToByte(String hex)
        {
            byte B = 0;

            char[] hexTable = new char[16]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            char[] hexTable2 = new char[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

            if (hex.Length > 0)
            {
                for (int i = 0; i < 16; i++)
                    if (hex.ToCharArray()[0] == hexTable[i] || hex.ToCharArray()[0] == hexTable2[i])
                        B += (byte)i;
                if (hex.Length > 1)
                {
                    B = (byte)(B << 4);
                    for (int i = 0; i < 16; i++)
                        if (hex.ToCharArray()[1] == hexTable[i] || hex.ToCharArray()[1] == hexTable2[i])
                            B += (byte)(i);
                }
            }
                
            return B;
        }

        public static byte[] HexToByteArray(String hex)
        {
            byte[] B = new byte[hex.Length / 2];

            for (int i = 0; i < hex.Length / 2; i++)
                B[i] = Utils.HexToByte(hex.Substring(i * 2, 2));

            return B;
        }
    }
}
