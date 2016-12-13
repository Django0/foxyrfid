

char Hunter_ID = 5;  // ---- Hunter Number --------


char Fox_Number = 0x00 ;
unsigned short data = 0, ro = 0;
unsigned short *rec;
unsigned short j=0;
char data_received[5];
char EEP_data;
char Retry_Flg = 0;
char Rx_CRC = 0;

// ----------- Reset Micro After DiagRequest -----------------------
//void Reset()
//{
//PCLATH = 0x00;
//PCL = 0x00;
//}



//========================= Start Main Program ==============================
void main() {

  // -------------init Micro ------------
  //OSCCON = 0xF1;
  TRISIO = 0xFE;

  CMCON0 = 0x07;
  WDA = 0x00;
  WPUDA = 0x02;


  Soft_Uart_Init(GPIO, 1, 0, 4800, 0);   // Initialize Soft UART at 4800 bps
  delay_ms(1000);

while(Retry_Flg == 0)
{

  // ---------- Send Hunter ID / Read Rx data -------------------------------------
  Soft_Uart_Write(Hunter_ID);             // Send Hunter ID
  delay_ms(1);
  Soft_Uart_Write(Hunter_ID);             // Send Hunter ID
  
  
  for(j=0;j<5;j++)      // Receive from Fox the Time
  {
   data_received[j] = Soft_Uart_Read(rec); // Receive data
  }
  
  Rx_CRC = (data_received[0] + data_received[1] + data_received[2] + data_received[3]) ;

  Fox_Number = Eeprom_Read(0x7F);        // Read Fox Counter
   if (Fox_Number==0xFF) Fox_Number=0;


   // -------------- Read/Clear EEPROM  -------------------------------------
      if((data_received[0] == 0x8A) & (data_received[2] == 0x24) & (data_received[3] == 0x01) & (data_received[4] == 0x01))
       {
       if(data_received[1] == 0x2F)     // Read Fox Data
        {
        Soft_Uart_Write(Hunter_ID);
        delay_ms(5);
         for(j=0;j<80;j++)
           {
            EEP_data = Eeprom_Read(j);
            Soft_Uart_Write(EEP_data);
            delay_ms(5);
           }
        }
        
        else if(data_received[1] == 0xED)  // Clear Fox Data
        {
           for(j=0;j<80;j++)
            {
             Eeprom_Write(j,0x00);
             delay_ms(5);
            }
        Eeprom_Write(0x7F,0x00);
        delay_ms(50);
        
        Soft_Uart_Write(0x6F);  // Positive response
         }
        delay_ms(2000);
       }
  // -------------------------------------------------------------------------

  // ------------------------ Write Data in EEPROM ---------------------------
      else if((data_received[0] < 0x60) & (data_received[4] == Rx_CRC) & (data_received[0] > 0))
      {

        for(j=(Fox_Number*4);j<((Fox_Number*4)+4);j++)         // Write to EEPROM
        {
          Eeprom_Write(j, data_received[(j-(Fox_Number*4))]);
          delay_ms(20);
        }

        Fox_Number++;
        Eeprom_Write(0x7F,Fox_Number);
        delay_ms(10);
        
        Soft_Uart_Write(0x6F);    // Send positive response
        Retry_Flg = 1;
      }
      
    // ------------------------ Do not record if the Hunter Punch the same Fox ---------------------------
      else if((data_received[0] == 0x7D)&(data_received[1] == 0x22) & (data_received[2] == 0xE2))
      {
      delay_ms(20);
      Soft_Uart_Write(0x6F);
      Retry_Flg = 1;
      }
      
    // ------------------------ Retry if was bad data ---------------------------
      else
      {
      Retry_Flg = 0;
      delay_ms(20);
      }
      
  // -------------------------------------------------------------------------
}

// Wait If the transfer is finish
 for(j=0;j<200;j++)
 {
 delay_ms(3000);
 }

}
