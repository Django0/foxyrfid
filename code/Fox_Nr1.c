/* ----  Project Desription -----

Project Name = FoxHunt
Oscilator = 8 MHz

=================================== SNIP =======================================

 MORSE ENCODING ...

 One morse character per BYTE, bitwise, LSB to MSB.

 0 = dit, 1 = dah.  The byte is shifted to the right bit by bit, until the
 last 1 is left, this 1 is an END OF CHARACTER indicator.
 A maximum of 7 elements can be encoded, (error) is excluded.



 KN -.--.   00101101       EOM       11111111   U ..-     00001100
 SK ...-.-  01101000       SPACE     00000000   V ...-    00011000
 AR .-.-.   00101010       D -..     00001001   W .--     00001110
 BT -...-   00110001       E .       00000010   X -..-    00011001
 AS .-...   00100010       F ..-.    00010100   Y -.--    00011101
  / -..-.   00101001       G --.     00001011   Z --..    00010011
  0 -----   00111111       H ....    00010000
  1 .----   00111110       I ..      00000100   1 .       00000010
  2 ..---   00111100       J .---    00011110   2 ..      00000100
  3 ...--   00111000       K -.-     00001101   3 ...     00001000
  4 ....-   00110000       L .-..    00010010   4 ....    00010000
  5 .....   00100000       M --      00000111   5 .....   00100000
  6 -....   00100001       N -.      00000101   6 -.      00000101
  7 --...   00100011       O ---     00001111   7 -..     00001001
  8 ---..   00100111       P .--.    00010110   8 -...    00010001
  9 ----.   00101111       Q --.-    00011011   9 -....   00100001
  A .-      00000110       R .-.     00001010   0 -.....  01000001
  B -...    00010001       S ...     00001000
  C -.-.    00010101       T -       00000011

============================ SNIP ============================================*/

// ----------------------------- Define Global Variables -----------------------------



char Message_to_Send_Wrd_1 = 0b00000111; // M    10
char Message_to_Send_Wrd_2 = 0b00001111; // 0    14
//...............................................................................
char Message_to_Send_Wrd_3 = 0b00000010;         // Fox Number 1
char data_lgt_fox = 4;                           // Length of the Morse Fox Count  4
char FoxHuntNumber = 1;         // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00000100;         // Fox Number 2
//char data_lgt_fox = 6;                           // Length of the Morse Fox Count  6
//char FoxHuntNumber = 2;          // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00001000;         // Fox Number 3
//char data_lgt_fox = 8;                           // Length of the Morse Fox Count  8
//char FoxHuntNumber = 3;                  // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00010000;         // Fox Number 4
//char data_lgt_fox = 10;                           // Length of the Morse Fox Count  10
//char FoxHuntNumber = 4;                  // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00100000;         // Fox Number 5
//char data_lgt_fox = 12;                           // Length of the Morse Fox Count  12
//char FoxHuntNumber = 5;                       // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00000101;         // Fox Number 6
//char data_lgt_fox = 8;                           // Length of the Morse Fox Count  8
//char FoxHuntNumber = 6;                    // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00001001;         // Fox Number 7
//char data_lgt_fox = 10;                           // Length of the Morse Fox Count  10
//char FoxHuntNumber = 7;                       // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00010001;         // Fox Number 8
//char data_lgt_fox = 12;                           // Length of the Morse Fox Count  12
//char FoxHuntNumber = 8;                       // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b00100001;         // Fox Number 9
//char data_lgt_fox = 14;                           // Length of the Morse Fox Count  14
//char FoxHuntNumber = 9;                       // Fox Hunt Number  - max foxes 254
//...............................................................................
//char Message_to_Send_Wrd_3 = 0b01000001;         // Fox Number 10
//char data_lgt_fox = 16;                           // Length of the Morse Fox Count  16
//char FoxHuntNumber = 10;                       // Fox Hunt Number  - max foxes 254
//...............................................................................

char Message_to_Send_Wrd_4 = 0b00001000; // S    Fox ID        8
char Message_to_Send_Wrd_5 = 0b00000111; // M    Fox ID        10
char Message_to_Send_Wrd_6 = 0b00100001; // 6    Fox ID        14
char Message_to_Send_Wrd_7 = 0b00001010; // R    Fox ID        10
char Message_to_Send_Wrd_8 = 0b00011001; // X    Fox ID        14
char Message_to_Send_Wrd_9 = 0b00010011; // Z    Fox ID        14
char Message_to_Send_FoxHunters_1 = 0x00;
char Message_to_Send_FoxHunters_2 = 0x00;
char data_lgt = 0;

char  Delay_to_Start = 0;     // Min*10
char  Max_Time = 10;          // Min*10
int   Delay_to_Start_Led = 0;
int   Max_Time_Var = 100;
char  Hunt_Type = 1;          // Hunt type (1 - 15)
char  Frequency = 3;          // Frequency (3,5 ; 144 ; both) 3 = 3,5  144 = 144  255 = both
//Speed of CW 5 WPM   1200/5 = 240 ms   Based upon a 50 dot duration standard word such as PARIS
unsigned  WPM_data = 5;              // WPM sending normal data MOx
unsigned  WPM_data_ID = 20;          // WPM sending ID
char FoxHunters_Enable = 0;          // Enable Sending FoxHunters number
char FoxSndID_Enable = 1;            // Enable Sending Fox ID
unsigned Foxes = 5;                      // Number of Foxes
unsigned Cycle = 5;                      // Min of a Cycle
unsigned ms_FoxCycle = 0;               // sec of a ms_FoxCycle
unsigned s_FoxCycle = 0;               // sec of a s_FoxCycle
char FoxNumber = 0;

char MinuteToEnd = 0;
char Time = 0;
char Sec = 0;
char Minute = 0;
char Hour = 0;
char SecToTx = 61;

char Program_Flg = 0xFF;            // Programming Flag
//char Sync_Flg = 0;

char Programming_Fox = 0;
char Programming_Fox_Data[7];
char Programming_Fox_Cnt = 0;
char ClearParam =0;
char ReadMode_Flg =0;

char HunterNumer = 0;
char HunterNumer_CRC = 0;
char HunterSec = 0;
char HunterMinute = 0;
char HunterHour = 0;
char FoxFinderNumer = 0;

int  CW_Speed_1 = 0;
int  CW_Speed_2 = 0;
char EEP_data = 0;
char UART_Read_Data = 0;
char EEP_Data_Read_Write = 0;
int i=0;
int j=0;
int k=0;

int  TimeToEnd=0;
int  TimeDev = 0;
int  TimeToSend = 0;
char TimeHntNr_1 = 0;
char TimeHntNr_2 = 0;
int  Wait_Time = 0;
int  s_End_Wait_Time = 0;

int cycles_MOx=0;
int cycle_Corection=0;
int WPM_Sliding=0;
int MOx_Length=0;
int ms_TimSnd_MOx=0;

char HuntersIDs[60];
char HuntersIDs_Flag = 0;

int TimeOut=5000;

char Rx_CRC = 0;
char Tx_CRC = 0;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////-- Interrupt--///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// PORTA.F1 =  LED_Mode;
// PORTA.F0 =  LED_R_W;
// PORTA.F4 =  CW_Keying;      // Sending Morse
// PORTA.F3 =  En_144;
// PORTA.F2 =  En_3,5 ;
// PORTB.F7 =  Crystal 1;
// PORTB.F6 =  Crystal 2;
// PORTB.F4 =  Low Pow;
// PORTB.F3 =  PWM ;
// PORTB.F2 =  Rx;
// PORTB.F5 =  Tx ;






// ---------------Reset Function -----------------------------------------------
void Reset()
{
Programming_Fox=0;
PCLATH = 0x00;
PCL = 0x00;
}


// ------------- EEPROM Read Function ---------------------------------------------------------------------------------
char EEP_Read(char Address)
{
EEADR = Address;   // Write the address
EECON1.EEPGD = 0;  // Data EEPROM Select bit
EECON1.RD = 1;
return EEDATA;
}


// ------------- EEPROM Write Function ---------------------------------------------------------------------------------
void EEP_Write(char Address, char Data)
{

while(EECON1.WR == 1) {delay_us(1);}  // Wait if another write is in process

EEADR = Address;
EEDATA = Data;
EECON1.EEPGD = 0;
EECON1.WREN = 1;
EECON2 = 0x55;
EECON2 = 0xAA;
EECON1.WR = 1;
EECON1.WREN = 0;
}


 // ------- Read all EEP data ---
void ReadMode()
{

   Usart_Write(FoxNumber);
   delay_ms(10);
   for(i=1;i<241;i++)
    {
       EEP_data = EEP_Read(i);
       Usart_Write(EEP_data);
       delay_ms(10);
     }
ReadMode_Flg = 0;
PORTA.F0 = 0;
Programming_Fox = 0;
}


// ------------- Serial Read Write Mode Function ---------------------------------------------------------------------------------
void ProgMode()
{
// -----  Program / Read / Erase Fox ---

Programming_Fox_Cnt=0;
for(k=0;k<TimeOut;k++)
{

  // Read all Rx data
  if (Usart_Data_Ready())
  {
  Programming_Fox_Data[Programming_Fox_Cnt] = Usart_Read() ;
  Programming_Fox_Cnt++;
  k=0;
  }


  if (Programming_Fox_Cnt == 6)
  {
    // Calculate CRC
    Rx_CRC = (Programming_Fox_Data[0] +  Programming_Fox_Data[1] +  Programming_Fox_Data[2] +  Programming_Fox_Data[3] +  Programming_Fox_Data[4]);

    // Check if the second byte is 0x3F and the CRC received is the same as the calcutalte one
    if(Rx_CRC == Programming_Fox_Data[5])
          {
             Delay_to_Start = Programming_Fox_Data[0];     // Scaling 10 Min
             Max_Time = Programming_Fox_Data[1];           // Scaling 10 Min
             Hunt_Type = Programming_Fox_Data[2];          // Hunt type (1 - 15)
             Frequency = Programming_Fox_Data[3];          // Frequency (3,5 ; 144 ; both) 3 = 3,5  14 = 144  25 = both
             Program_Flg = Programming_Fox_Data[4];

             if(FoxHuntNumber == 1) Max_Time_Var = (Max_Time*10);   //
             else Max_Time_Var = ((Max_Time*10)+1);

             Delay_to_Start_Led = Delay_to_Start*10;

             for(i=0;i<60;i++)  HuntersIDs[i] = 0 ;
             
             for(i=1;i<250;i++)  EEP_Write(i,0x00);         // Erase EEPROM
             EEP_Write(0,FoxNumber);

             Time = 0;  Sec = 1; Minute = 0; Hour = 0;
         }

   k = TimeOut;
   Programming_Fox_Cnt = 0;
   }
   
delay_us(100);
}

PORTA.F0 = 0;
Programming_Fox_Cnt = 0;
Programming_Fox = 0;
}









// ------------- Puncher Mode Function ---------------------------------------------------------------------------------
void Puncher()
{

// -----  Send to Puncher the Time ---

  delay_ms(4);
  if (Usart_Data_Ready()) { HunterNumer_CRC = Usart_Read();}   // Get CRC

  if(HunterNumer_CRC == HunterNumer)  // Check CRC
  {
     // Check if the hunter punch the same fox
     for(i=0;i<60;i++) { if (HunterNumer == HuntersIDs[i]) HuntersIDs_Flag = 1 ; }

     if(HuntersIDs_Flag == 1)
     {
       Usart_Write(0x7D);                 // Write dummy data
       Usart_Write(0x22);
       Usart_Write(0xE2);
       Usart_Write(0x00);
       Usart_Write(0x00);
       HuntersIDs_Flag = 0;
     }

     else
     {
       Usart_Write(FoxNumber);             // and send data via UART
       Usart_Write(HunterHour);                // and send data via UART
       Usart_Write(HunterMinute);              // and send data via UART
       Usart_Write(HunterSec);                 // and send data via UART
       Tx_CRC = (FoxNumber + HunterHour + HunterMinute + HunterSec);
       Usart_Write(Tx_CRC);             // and send CRC via UART
       
       EEP_Write(((4*FoxFinderNumer)+1),HunterNumer);
       EEP_Write(((4*FoxFinderNumer)+2),HunterHour);
       EEP_Write(((4*FoxFinderNumer)+3),HunterMinute);
       EEP_Write(((4*FoxFinderNumer)+4),HunterSec);

       HuntersIDs[FoxFinderNumer] = HunterNumer;
       FoxFinderNumer++;
      }
      HunterNumer = 0;
  }
  else
  {
       Usart_Write(0xD3);                 // Write dummy data
       Usart_Write(0xA1);
       Usart_Write(0xA2);
       Usart_Write(0xA3);
       Usart_Write(0xA4);
       HunterNumer = 0;
       HunterNumer_CRC = 0;
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
//---------------------------- Interrupt Program ---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------

void Interrupt()
{


//---------- Read UART Data -----------
   if(PIR1.RCIF == 1)   //     Interrupt generated at 250 ms
      {
      
       UART_Read_Data =  Usart_Read();     // If data is received

       if((UART_Read_Data >0)&(UART_Read_Data < 0x3D)&(Programming_Fox==0)&(Max_Time_Var>0)&(Program_Flg<0xFF)&(Delay_to_Start_Led==0)) // Verify if is Puncher
       {
        PORTA.F0 = 1;
        SecToTx = 0;
        HunterNumer = UART_Read_Data;
        HunterSec = Sec;
        HunterMinute = Minute;
        HunterHour  = Hour;
        Puncher();
       }

      else     // Else - read diagnosis commands
        {
          if(UART_Read_Data == 0x5A) Programming_Fox = 1;
          else if((UART_Read_Data == 0x2B) & (Program_Flg == 0xFF) & (Programming_Fox == 1)) PORTA.F0 = 1, ReadMode();  // Read only after reset
          else if((UART_Read_Data == 0x3D) & (Program_Flg == 0xFF) & (Programming_Fox == 1)) PORTA.F0 = 1, ProgMode();  // Program only after reset
          else if((UART_Read_Data == 0x4E) & (Program_Flg != 0xFF) & (Programming_Fox == 1)) PORTA.F0 = 1, Reset();     // Clear/Reset only if Hunt is Running
          else  Programming_Fox = 0;
        }
     }



//---------- Timer Function -----------
   if(PIR1.TMR1IF == 1)
   {

       TMR1H = 0x0B;
       TMR1L = 0xDC;
       PIR1.TMR1IF =0;

       Time++;



       if(Time >= 4 )
       {
        Sec++;                                   // Increase Seconds
        if(s_End_Wait_Time > 0) s_End_Wait_Time--;
        if(Wait_Time > 0)  Wait_Time--;
        if(TimeToSend > 0) TimeToSend--;
        if((Delay_to_Start_Led > 0)&(Program_Flg != 0xFF)&(Programming_Fox==0)) PORTA.F0 =!PORTA.F0;
        if(Sec >= 60 )
         {
           Minute++;
           if(Delay_to_Start_Led > 0) Delay_to_Start_Led--;
           if((Max_Time_Var > 0)&(Delay_to_Start_Led == 0)) Max_Time_Var--;
           if(Minute >= 60 ) Hour++, Minute=0;
           Sec=0;
         }

        Time=0;
        }
    }

  if(SecToTx < 16) SecToTx++;
  if( ((SecToTx == 16) || (UART_Read_Data == 0x6F))  & (SecToTx > 4)  & (Programming_Fox==0) & (Program_Flg != 0xFF) & (Max_Time_Var > 0) & (Delay_to_Start_Led == 0)) SecToTx = 16, PORTA.F0 = 0;
  




} // End Interrupt






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////-----------------MAIN--------------------////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// ----------------------- Init ECU Function -----------------------------------------------------------------------------------------------------
void init()
{
//OSCCON= 0x75;          // Alex Fox only
//TRISB  = 0xC4;       //  Alex Fox only


ANSEL  = 0x00;         // Configure AN pins as digital  ANSELH = 0;
ADCON0 = 0x00;         // Configure AN pins as digital  ANSELH = 0;
CMCON  = 0x07;       // Disable Compators
TRISA  = 0xC0;       // Configure PORT A as Input

TRISB  = 0x04;       // Configure PORT B as Input

PORTA = 0x00;       // Set PORT A to 0x00;
PORTB = 0x00;       // Set PORT B to 0x00;

PORTA.F0 = 1;     // Set LED NO for initialization
delay_ms(1000);    // Wait to have the power stable

INTCON = 0xC0;         // Activate Interrupt - PEIE: Peripheral Interrupt Enable bit   - T0IE: Timer0 Overflow Interrupt Enable bit
PIE1   = 0x21;         // RCIE: EUSART Receive Interrupt Enable and TMR 1
T1CON  = 0xF1;         // Activate 16 bit Timer 1 - Prescaler Rate 8   count at 4 us - 65536 - > max time  262,144  ms

Usart_Init(4800);       // Initialize UART module at 4800 bps

Pwm_Init(700);
Pwm_Start();
Pwm_Change_Duty(0);
FoxNumber = FoxHuntNumber;

PORTA = 0x00;       // Set PORT A to 0x00;
PORTB = 0x00;       // Set PORT B to 0x00;


// Check Configuration - if is not configured , reset the Unit
//if((INTCON != 0xC0) || (PIE1 != 0x21) || (TXSTA.TXEN != 1) || (RCSTA.SPEN != 1))
//{
//Reset();
//}


}



// ----------------------- Type Function ---------------------------------------------------------------------------------------------------
void Type(int Hunt_Type)
{

PORTB.F6 = 0;  // Enable cristal 1 by default
PORTB.F7 = 1;

PORTB.F4 = 1; // High Power
WPM_data = 5;
FoxSndID_Enable = 1;
FoxHunters_Enable = 1;


if     (Hunt_Type == 0x01)  Cycle = 1,  Foxes = 1; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 1 1
else if(Hunt_Type == 0x02)  Cycle = 2,  Foxes = 2; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 1 2
else if(Hunt_Type == 0x03)  Cycle = 3,  Foxes = 3; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 1 3
else if(Hunt_Type == 0x04)  Cycle = 4,  Foxes = 4; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 1 4
else if(Hunt_Type == 0x05)  Cycle = 5,  Foxes = 5; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 1
else if(Hunt_Type == 0x06)  Cycle = 7,  Foxes = 7; // FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 2
else if(Hunt_Type == 0x07)  Cycle = 10, Foxes = 10;// FoxHunters_Enable = 1, FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // GRJ 3
else if(Hunt_Type == 0x08)  Cycle = 5,  Foxes = 5,  FoxHunters_Enable = 0; // FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // SM Night
else if(Hunt_Type == 0x09)  Cycle = 7,  Foxes = 7,  FoxHunters_Enable = 0; // FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;    // SM Day
else if(Hunt_Type == 0x0A)  Cycle = 10, Foxes = 10, FoxHunters_Enable = 0; // FoxSndID_Enable = 1, High_Pow(1), WPM_data=5;

else if(Hunt_Type == 0x0B)  Cycle = 0,  Foxes = 99, FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 0, WPM_data=8;    // Beginners training/show or Foxoring 1
else if(Hunt_Type == 0x0C)  Cycle = 0,  Foxes = 99, FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 1, WPM_data=8;

//else if(Hunt_Type == 0x0D)  Cycle = 0,  Foxes = 1,  FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 1, WPM_data=14;    // Beacon for Sprint  send MO(S)
//else if(Hunt_Type == 0x0E)  Cycle = 0,  Foxes = 5,  FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 1, WPM_data=10;    // Finish Beacon for Sprint and Foxoring    send just MO

else if(Hunt_Type == 0x0D)  Cycle = 1,  Foxes = 5,  FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 0, WPM_data=10;    // Sprint

else if(Hunt_Type == 0x0E)  Cycle = 2,  Foxes = 10, FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 1, WPM_data=16;    // Renberg-hunt
else if(Hunt_Type == 0x0F)  Cycle = 5,  Foxes = 5,  FoxHunters_Enable = 0, FoxSndID_Enable = 0, PORTB.F4 = 1, WPM_data=8;     // National





  
if (Hunt_Type == 0x0D)   // Sprint - 14WPM -  1,2,3,4,5 - Crystal 2   the Foxes 6,7,8,9,10 will be changed (6-1, 7-2, 8-3, 9-4, 10-5)
{
  if (FoxHuntNumber == 6)
  {
    Message_to_Send_Wrd_3 = 0b00000010;         // Fox Number 1
    data_lgt_fox = 4;                           // Length of the Morse Fox Count  4
    FoxHuntNumber = 0x01;                       // Fox Hunt Number  - max foxes 254
    WPM_data=14;
    PORTB.F6 = 1, PORTB.F7 = 0;                 // Enable cristal 2
  }
   else if (FoxHuntNumber == 7)
  {
    Message_to_Send_Wrd_3 = 0b00000100;         // Fox Number 2
    data_lgt_fox = 6;                           // Length of the Morse Fox Count  6
    FoxHuntNumber = 0x02;                       // Fox Hunt Number  - max foxes 254
    WPM_data=14;
    PORTB.F6 = 1, PORTB.F7 = 0;                 // Enable cristal 2
  }
   else if (FoxHuntNumber == 8)
  {
    Message_to_Send_Wrd_3 = 0b00001000;         // Fox Number 3
    data_lgt_fox = 8;                           // Length of the Morse Fox Count  8
    FoxHuntNumber = 0x03;                       // Fox Hunt Number  - max foxes 254
    WPM_data=14;
    PORTB.F6 = 1, PORTB.F7 = 0;                 // Enable cristal 2
  }
   else if (FoxHuntNumber == 9)
  {
    Message_to_Send_Wrd_3 = 0b00010000;         // Fox Number 4
    data_lgt_fox = 10;                          // Length of the Morse Fox Count  10
    FoxHuntNumber = 0x04;                       // Fox Hunt Number  - max foxes 254
    WPM_data=14;
    PORTB.F6 = 1, PORTB.F7 = 0;                 // Enable cristal 2
  }
   else if (FoxHuntNumber == 10)
  {
    Message_to_Send_Wrd_3 = 0b00100000;         // Fox Number 5
    data_lgt_fox = 12;                           // Length of the Morse Fox Count  12
    FoxHuntNumber = 0x05;                       // Fox Hunt Number  - max foxes 254
    WPM_data=14;
    PORTB.F6 = 1, PORTB.F7 = 0;                 // Enable cristal 2
  }
}

else if (Hunt_Type == 0x0F)    //  National  -  6 and 7 send as 4 and 5 - on Crystal 2
{
  if (FoxHuntNumber == 6)
  {
    Message_to_Send_Wrd_3 = 0b00010000;  //6 -> 4
    data_lgt_fox=10;
    FoxHuntNumber = 0x04;
    PORTB.F6 = 1, PORTB.F7 = 0;               // Enable cristal 2
  }
  else if (FoxHuntNumber == 7)
  {
    Message_to_Send_Wrd_3 = 0b00100000;  //7 -> 5
    data_lgt_fox=12;
    FoxHuntNumber = 0x05;
    PORTB.F6 = 1, PORTB.F7 = 0;             // Enable cristal 2
  }
}


CW_Speed_1 = 1200 / WPM_data;           // Calculate WPM in ms
CW_Speed_2 = 1200 / WPM_data_ID;        // Calculate WPM in ms

s_FoxCycle = (Cycle * 60) / Foxes;
ms_FoxCycle = s_FoxCycle*1000;

}


 // --------------------------- Convert To Morse ------------------------------------------------------------------------------------------------
char ConvertToMorse(char lettre_cw)
{
char Conv_Data = 0;

 switch(lettre_cw)
 {
 case 0: Conv_Data = 0b00111111, data_lgt= 22; break;
 case 1: Conv_Data = 0b00111110, data_lgt= 20; break;
 case 2: Conv_Data = 0b00111100, data_lgt= 18; break;
 case 3: Conv_Data = 0b00111000, data_lgt= 16; break;
 case 4: Conv_Data = 0b00110000, data_lgt= 14; break;
 case 5: Conv_Data = 0b00100000, data_lgt= 12; break;
 case 6: Conv_Data = 0b00100001, data_lgt= 14; break;
 case 7: Conv_Data = 0b00100011, data_lgt= 16; break;
 case 8: Conv_Data = 0b00100111, data_lgt= 18; break;
 case 9: Conv_Data = 0b00101111, data_lgt= 20; break;
 }
 return Conv_Data;
}



// --------------------------- Send MORSE Data Out Function ---------------------------------------------------------------------------------------------
void CW_Keying(char data)
{
  if(data==1)
  {
    if(PORTA.F2==1) PORTA.F4 = 1;
    if(PORTA.F3==1) Pwm_Change_Duty(127);
    PORTA.F1 = 1;
  }
  else
  {
    PORTA.F4 = 0;
    Pwm_Change_Duty(0);
    PORTA.F1 = 0;
  }
}




// --------------------------- Send Word Function ---------------------------------------------------------------------------------------------
 void Send_Word(int Speed, int Word)
 {
  if (Word == 0) VDelay_ms(Speed*2);   // Word Space time 5 dots
  if (Word == 0xFF) {}
  else
  {
   while(Word>1)
   {
     if((Word & 0x01) == 0x01)
       {
        CW_Keying(1);          // Dash            3 dots
        VDelay_ms(Speed*3);
        CW_Keying(0);
        }
     else
        {
        CW_Keying(1);         // Dot               1 dot
        VDelay_ms(Speed);
        CW_Keying(0);
        }
     Word = Word >> 1;
     VDelay_ms(Speed);        // Inter Dot Space    1 dot
   }
   VDelay_ms(Speed*2);        // Inter Char Space   3 dots

   while(Programming_Fox == 1)
   {
    CW_Keying(0);
   }
  }
 }



//__________________________________________________________________________________________________________________________________________
//______________________________ Start Main Program _______________________________________________________
//__________________________________________________________________________________________________________________________________________


void main()
{

  // ------- Initialize the Micro --------
  init();
  CW_Keying(0);

// ------- Verify if not Prog --------
  while(Program_Flg == 0xFF)
  {
   Vdelay_ms(120);
   PORTA.F0 = !PORTA.F0;
  }


  // ------- Configure Hunt type - Delay to start - Reset time -------
  Type(Hunt_Type);


    // ------- Wait startup delay -----
  while(Delay_to_Start_Led > 0){delay_us(10);}  // Wait
  while(Delay_to_Start_Led > 0){delay_us(10);}  // Wait   backup
  
  Time = 0;                        // Reset Time
  Sec = 0;
  Minute = 0;
  Hour = 0;
  PORTA.F0 = 0;                     // LED OFF


  // ------- Wait time if the Fox is not number 1 -------
  if(Cycle != 0x00)
  {
    Wait_Time =((FoxHuntNumber-1) * s_FoxCycle);
    while( Wait_Time > 0 ) {delay_us(10);}
  }


  // -----------------------  Start Sendin Morse Data Program ------------------------
    while(1)
      {

          // --- enable the frequency befor transmission
          if(Frequency == 0x00)      PORTA.F3 = 0, PORTA.F2 = 1;  // Enable 3,5
          else if(Frequency == 0x01) PORTA.F3 = 1, PORTA.F2 = 0;  // Enable 144
          else if(Frequency == 0x02) PORTA.F3 = 1, PORTA.F2 = 1;  // Enable both
          else  PORTA.F3 = 0, PORTA.F2 = 0;                       // Disable both

          // --- If the Hunt is finish - send Fox ID
          while(Max_Time_Var == 0)
          {
             PORTA.F0 = 1;
             Send_Word(CW_Speed_1, Message_to_Send_Wrd_3);  // 2*  dot  x
             Vdelay_ms(1000);
          }



          if(Cycle != 0x00)  // If Cycle is not 0 - calculate WPM Sliding
          {
            // --- Convert Hunter number in Morse code ---
            Message_to_Send_FoxHunters_1 = ConvertToMorse(FoxFinderNumer/10);
            TimeHntNr_1 = data_lgt;
            Message_to_Send_FoxHunters_2 = ConvertToMorse(FoxFinderNumer - ((FoxFinderNumer/10)*10));
            if(Message_to_Send_FoxHunters_1 == 63) TimeHntNr_1 = 0, Message_to_Send_FoxHunters_1=0xFF;
            TimeHntNr_2 = data_lgt;

            // --- Add End Time for different configurations ---
            if((FoxHunters_Enable == 1) & (FoxSndID_Enable == 1)) TimeDev = ((TimeHntNr_1 + TimeHntNr_2 + 8)*CW_Speed_1) + 8830;
            else if(FoxSndID_Enable == 1) TimeDev = 6830;
            else TimeDev = 2500 ;

            TimeToSend = s_FoxCycle;                     // Calculate Time to send in s
            MOx_Length = data_lgt_fox + 26;              // Calculate MOx length 38
            ms_TimSnd_MOx = (CW_Speed_1*MOx_Length);     // Calculate Time to send MOx in ms  = 1200/5 * 38 =  240 * 38 = 9120


            // calculate WPM Drifting-------------------
            cycles_MOx =  (ms_FoxCycle - TimeDev) / ms_TimSnd_MOx;        //  TimeDev = 0;  cycles_MOx = 60000/9120 = 6.578
            cycle_Corection =  ((ms_FoxCycle - TimeDev) % ms_TimSnd_MOx);   //  TimeDev = 0;  cycle_Corection = 60000%9120 =  5280

            // if the  cycle_Corection < ms_TimSnd_MOx/2  than keep the cycles_MOx and increas the WPM
            if( cycle_Corection < (ms_TimSnd_MOx/2)) WPM_Sliding = CW_Speed_1 + (cycle_Corection / MOx_Length / cycles_MOx);
            // else add 1 to cycles_MOx and decreas the WPM.
            else cycles_MOx = cycles_MOx+1, WPM_Sliding = (CW_Speed_1 - ((ms_TimSnd_MOx - cycle_Corection )/MOx_Length / cycles_MOx));
            //----------------------------------------------
          }

          else    // Else - set the WPM Sliding to Default WPM value
          {
           WPM_Sliding = CW_Speed_1;
           cycles_MOx = 5;                // MOX cycles befor sending the Hunter counter or/and FoxSender ID
          }



          while(cycles_MOx > 0)          // Send MOx
          {
            Send_Word(WPM_Sliding, Message_to_Send_Wrd_1);  // 10 dot
            Send_Word(WPM_Sliding, Message_to_Send_Wrd_2);  // 14 dot
            Send_Word(WPM_Sliding, Message_to_Send_Wrd_3);  // 2*  dot  x
            Send_Word(WPM_Sliding, 0);                      // 2 dot
            cycles_MOx--;
          }

          if(FoxSndID_Enable == 1)   // Send Fox ID   SM6RXZ
          {
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_4); //  8 dot
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_5); //  10  dot
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_6); //   14 dot
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_7); //   10 dot
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_8); //   14 dot
            Send_Word(CW_Speed_2, Message_to_Send_Wrd_9); //   14 dot
            Send_Word(CW_Speed_2, 0);                     //   2 dot
          }                                               //  ______________
                                                          //     72 dots
          if(FoxHunters_Enable == 1)  // If FoxHounters count enable, send the Hunters Number
          {
            Send_Word(CW_Speed_1,Message_to_Send_FoxHunters_1);   //0
            Send_Word(CW_Speed_1,Message_to_Send_FoxHunters_2);   // 22
            Send_Word(CW_Speed_1, 0);                             // 5 dot

            CW_Keying(1);                          // Send Long Tone
            while(TimeToSend > 0){delay_us(10);}                // Wait cycle to end time
            CW_Keying(0);                          // Stop Long Tone
          }



         if(Cycle != 0x00)    // If Cycle is not 0 - Wait for the fox number cycle
         {
          PORTA.F3 = 0, PORTA.F2 = 0;                    // disable the transmission for both Frq
          while(TimeToSend > 0){delay_us(10);}                        // Wait cycle to end time
          s_End_Wait_Time = ((Foxes-1) * s_FoxCycle);    // Wait untill next Tx
          if(s_End_Wait_Time == 0) Send_Word(CW_Speed_1, 0); // Wait inter Cycle space
          while(s_End_Wait_Time > 0){delay_us(10);}
         }
     } // End While

} // End Main

//__________________________________________________________________________________________________________________________________________
//______________________________ End Main Program ____________________________________________________________
//__________________________________________________________________________________________________________________________________________
















