
char Select = 0;
char Menu = 0;
char Menu_Back = 0;
unsigned short Data = 0;
char BTN_Press_Flg = 0;
char Block = 0;


unsigned short DelayTime = 12;     // 120 min until start
unsigned short Hr_DelayTime = 0;
unsigned short Mn_DelayTime = 0;
unsigned short HuntTime = 9;       // 90 min Hunt time
unsigned short Hr_HuntTime = 0;
unsigned short Mn_HuntTime = 0;
unsigned short HuntType = 1;       // Hunt type 1
unsigned short Frequency = 0;      // Frequency 3.5
unsigned short i = 0;
unsigned short Prog_Ent = 0;

char txt[4];
char Eq = '=';
char TP = ':';
char Sel = '-';
char text_1 = 0;    //"Starting";  8
char text_2 = 8;    //"PRAL";      4
char text_3 = 12;   //"Delay";     5
char text_3_1 = 17; //"Time";      4
char text_4 = 21;   //"Hunt";      4
char text_3_4 = 25; //"[x10min]";  8
char text_5 = 33;   //"Type";      4
char text_5_1 = 37; //"[1-15]";    6
char text_6 = 43;   //"Frequency"; 9
char text_7 = 52;   //"Program";   7
char text_8 = 59;   //"Sync";     4
char text_10 = 64;  //"Done";      4
char text_11 = 68;  //"Read";      4
char text_11_1 = 72;//"Fox";       3
char text_11_2 = 75;//"Puncher";   7
char text_13 = 90;  //" 3,5 MHz";  8
char text_14 = 98;  //" 144 MHz";  8
char text_15 = 106; //" Both   ";  8
char text_16 = 114; //"Error";     5
char text_17 = 119; //"Clear Memory"; 12
char text_18 = 144; //"Clear Program"; 13
char text_19 = 160; //"[H:M]"; 5
char text_20 = 176; //"Block"; 5

char UART_Read_Dta[80]; // = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char First_Number_Read = 0;

char UART_Read_Cnt = 0;
char UART_Rear_Flg = 0;

unsigned short EEP_Data;

char Fox_Nr = 0;
char Hr = 0;
char Min_ = 0;
char Sec = 0;





// ----------------------------- Inttrerupt ----------------------------------
void Interrupt()
{
UART_Read_Dta[UART_Read_Cnt]= Usart_Read();
UART_Read_Cnt++;

if(UART_Read_Cnt > 79)
{
  if(Block == 3) UART_Read_Cnt = 0, Block--;
  else if(Block == 2) UART_Read_Cnt = 0, Block--;
  else UART_Read_Cnt = 79;
}

if((UART_Read_Cnt == 1)&(First_Number_Read == 0)) First_Number_Read = UART_Read_Dta[0], UART_Read_Cnt=0;
}







// ----------------------  Display From EEPROM --------------------------------
void Lcd_Out_EEP(int Address,int Length,int Row, int Start)
{
  for(i=0;i<Length;i++)
  {
  EEP_Data =  Eeprom_Read(Address+i);
  Lcd_Chr(Row, (Start+i), EEP_Data);
  }
}

// ----------------------  Display Text --------------------------------
void Lcd_Out_Text(int Row_, int Char_, int Text_)
{
  ByteToStr(Text_, txt);
  Lcd_Out(Row_, Char_, txt);
}



// ------------------------ Read Buttons ---------------------------------------
void Read_Button()
{


  if ((PORTB.F4 == 0) || (PORTB.F0 == 0))
  {
    Menu_Back = Menu;

    if(PORTB.F4 == 0)                    // ->
    {
     Select++;
     delay_ms(400);
     if((PORTB.F4 == 0)& (Menu == 0))
     {
      delay_ms(1000);
      if(PORTB.F4 == 0) Menu = Select, Select=0;
     }

    }
    
    else if(PORTB.F0 == 0)               // <-
    {
     Select--;
     delay_ms(400);
     if((PORTB.F0 == 0)& (Menu > 0))
      {
      delay_ms(1000);
      if(PORTB.F0 == 0) Select=(Menu-1),  Menu = 0 ;
      }
    }

     Data=0;
     UART_Rear_Flg = 0;
     Prog_Ent = 0;
     Lcd_Cmd(LCD_CLEAR);


// ------------------------- Function Menu Display ------------------

// --------------------- 1. Program -----------

  if(Menu == 1)
  {
  
    if(Select > 200) Select=5;
    else if(Select > 5) Select=0;
    
    if(Select == 0)            // Delay Time
      {
      Lcd_Chr(1, 1, '1');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_3,5,1,4);
      Lcd_Out_EEP(text_3_1,4,1,10);
      Lcd_Out_EEP(text_19,5,2,12);
      Lcd_Chr(2, 1, Eq);
      
     if(DelayTime > 0)Data = DelayTime;
      }

    else if(Select == 1)       // Hunt Time
      {
      Lcd_Chr(1, 1, '2');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_4,4,1,4);
      Lcd_Out_EEP(text_3_1,4,1,9);
      Lcd_Out_EEP(text_19,5,2,12);
      Lcd_Chr(2, 1, Eq);
      if(HuntTime > 0)  Data = HuntTime;
      }

    else if(Select == 2)       // Hunt Type
      {
      Lcd_Chr(1, 1, '3');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_4,4,1,4);
      Lcd_Out_EEP(text_5,4,1,9);
      Lcd_Out_EEP(text_5_1,6,2,11);
      Lcd_Chr(2, 1, Eq);
      if(HuntType > 0)  Data = HuntType;
      }

    else if(Select == 3)       // Hunt Frequency
      {
      Lcd_Chr(1, 1, '4');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_6,9,1,4);
      Lcd_Chr(2, 1, Eq);
      if(Frequency > 0) Data = Frequency;
      }

    else if(Select == 4)      // Program Fox
      {
      Lcd_Chr(1, 1, '5');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_7,7,1,4);
      Lcd_Out_EEP(text_11_1,3,1,12);
      }

    else if(Select == 5)        // Clear Program
      {
      Lcd_Chr(1, 1, '6');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_18,13,1,4);
      }
  }


// ------------------ 2. Read -----------
 else if(Menu == 2)
  {
    if(Select > 200) Select=3;
    if(Select > 3) Select=0;
    
     if(Select == 0)      // Read Puncher
      {
      Lcd_Chr(1, 1, '1');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_11,4,1,4);
      Lcd_Out_EEP(text_11_2,7,1,9);
      }

     else if(Select == 1)      // Read Fox  Block 1
      {
      Lcd_Chr(1, 1, '2');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_11,4,1,4);
      Lcd_Out_EEP(text_11_1,3,1,9);
      Lcd_Out_EEP(text_20,2,1,13);
      Lcd_Chr(1, 16, '1');
      Block = 1;
      }
      
    else if(Select == 2)      // Read Fox  Block 2
      {
      Lcd_Chr(1, 1, '3');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_11,4,1,4);
      Lcd_Out_EEP(text_11_1,3,1,9);
      Lcd_Out_EEP(text_20,2,1,13);
      Lcd_Chr(1, 16, '2');
      Block = 2;
      }
     else if(Select == 3)      // Read Fox  Block 3
      {
      Lcd_Chr(1, 1, '4');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_11,4,1,4);
      Lcd_Out_EEP(text_11_1,3,1,9);
      Lcd_Out_EEP(text_20,2,1,13);
      Lcd_Chr(1, 16, '3');
      Block = 3;
      }


  }
 // ------------------- 3. Clear Memory ----
  else if(Menu == 3)              //Clear Memory
  {     //Clear Puncher
      Lcd_Chr(1, 1, '1');
      Lcd_Chr(1, 2, '.');
      Lcd_Out_EEP(text_17,5,1,4);
      Lcd_Out_EEP(text_11_2,7,1,10);
  }
  
}
  
  
  
  
// ------------------------- Main Menu Display ---------------------------------
if(Menu == 0)
  {
      if(Select >200) Select=2;
      else if (Select >2) Select=0;
      
      if(Select == 0)
      {
       Lcd_Chr(1, 1, '1');
       Lcd_Chr(1, 2, '.');
       Lcd_Out_EEP(text_7,7,1,4);        // Program Fox
      }
      else if(Select == 1)
      {
        Lcd_Chr(1, 1, '2');
        Lcd_Chr(1, 2, '.');
        Lcd_Out_EEP(text_11,4,1,4);       //Read
       }
      else if(Select == 2)
      {
       Lcd_Chr(1, 1, '3');
       Lcd_Chr(1, 2, '.');
       Lcd_Out_EEP(text_17,12,1,4);     //"Clear Memory"; 12 Fox
      }
  }




// ----------  Read buttons UP - Down -----------------------------

   if(BTN_Press_Flg == 1) delay_ms(500), BTN_Press_Flg=0;
   if(PORTB.F3 == 0)               // Up
    {
     Data++;
     if((Menu == 1) & (Select ==4)&(Prog_Ent==0)) Prog_Ent = 1;
     BTN_Press_Flg = 1;
    }
    else if(PORTB.F1 == 0)         // Down
    {
     Data--;
     BTN_Press_Flg = 1;
    }


}




// ==================== Start Main Program =====================================
void main() {


  TRISA = 0x00;
  TRISB = 0x1F;
  ANSEL = 0x00;
  ADCON0 = 0x00;
  OSCCON =0x7A;
  
  Lcd_Config(&PORTA, 2, 4, 3, 6, 7, 0, 1);  // Initialize LCD on PORTB
  Lcd_Cmd(LCD_CURSOR_OFF);
  Usart_Init(4800);
  

  INTCON = 0xC0;          // Activate Interrupt - PEIE: Peripheral Interrupt Enable bit
  PIE1 = 0x20;            // RCIE: EUSART Receive Interrupt Enable
  
Lcd_Out_EEP(text_1,8,1,5);
delay_ms(500);
Lcd_Chr(2, 6, Sel);
Lcd_Out_EEP(text_2,4,2,7);
Lcd_Chr(2, 11, Sel);
delay_ms(1500);
Lcd_Cmd(LCD_CLEAR);


while(1)
{

Read_Button();

  

// ------------------------------ Functions -----------------------------
    
// -----------------------------  Program -------------------------------
    if(Menu == 1)
    {
      if(Select == 0)            // Delay Time
      {
      DelayTime = Data;
      Hr_DelayTime = (DelayTime/6);
      Mn_DelayTime = ((DelayTime%6)*10);
      Lcd_Out_Text(2,2,Hr_DelayTime);
      Lcd_Chr(2,5,TP);
      Lcd_Out_Text(2,6,Mn_DelayTime);
      }

      else if(Select == 1)       // Hunt Time
      {
      HuntTime = Data;
      Hr_HuntTime = (HuntTime/6);
      Mn_HuntTime = ((HuntTime%6)*10);
      Lcd_Out_Text(2,2,Hr_HuntTime);
      Lcd_Chr(2,5,TP);
      Lcd_Out_Text(2,6,Mn_HuntTime);
      }

      else if(Select == 2)       // Hunt Type
      {
      if(Data > 15) Data = 1;
      else if(Data < 1) Data = 15;
      HuntType = Data;
      Lcd_Out_Text(2,2,HuntType);
      }

      else if(Select == 3)       // Hunt Frequency
      {
      if(Frequency > 2)  Data=0;
      Frequency = Data;
      if(Frequency == 0) Lcd_Out_EEP(text_13,8,2,3);
      else if(Frequency == 1) Lcd_Out_EEP(text_14,8,2,3);
      else if(Frequency == 2) Lcd_Out_EEP(text_15,8,2,3);
      }

      else if(Select == 4)      // Program Fox
      {
        if(Prog_Ent == 1)
        {
          UART_Read_Cnt = 0;
          Lcd_Chr(2, 1, 0xFF); delay_ms(70);
          Usart_Write(0x50);
          Lcd_Chr(2, 2, 0xFF); delay_ms(70);
          Usart_Write(0x3F);
          Lcd_Chr(2, 3, 0xFF); delay_ms(70);
          Usart_Write(DelayTime);
          Lcd_Chr(2, 4, 0xFF); delay_ms(70);
          Usart_Write(HuntTime);
          Lcd_Chr(2, 5, 0xFF); delay_ms(70);
          Usart_Write(HuntType);
          Lcd_Chr(2, 6, 0xFF); delay_ms(70);
          Usart_Write(Frequency);
          Lcd_Chr(2, 7, 0xFF); delay_ms(80);
          Usart_Write(0x00);                   // Clear Hunt Flag
          delay_ms(2500);
          Lcd_Out_EEP(text_10,4,2,9);
          Prog_Ent = 2;
        }

      }

      else if(Select == 5)        // Clear Program
      {
      if(Data > 0)
        {
        for(i=1;i<9;i++) Lcd_Chr(2, i, ' ');
        UART_Read_Cnt = 0;
        Usart_Write(0x50);
        delay_ms(30);
        Usart_Write(0x4F);
        Data=0;
        delay_ms(50);
        Lcd_Chr(2, 1, 0xFF);
        Lcd_Out_EEP(text_10,4,2,2);
        }
      }
    }

// --------------------------  Read --------------------------------------------

    if(Menu == 2)
    {
    
 // ------------------- Read Puncher -----------------
     if(Select == 0)
      {
      if((Data > 0) & (UART_Rear_Flg == 0))
        {
        Block = 0;
        First_Number_Read=0;
        UART_Read_Cnt = 0;
        Usart_Write(0x60);
        Usart_Write(0x2F);
        Usart_Write(0x00);
        Usart_Write(0x01);
        for(i=1;i<12;i++)
          {
          Lcd_Chr(2, i, 0xFF);
          delay_ms(190);
          }
        Lcd_Out_EEP(text_10,4,2,13);
        delay_ms(200);
        UART_Rear_Flg = 1;
        Lcd_Cmd(LCD_CLEAR);
        Data=20;
        }


       else if (UART_Rear_Flg == 1)
       {
        Lcd_Out_EEP(text_11_2,7,1,1);
        Lcd_Chr(1,8,TP);
        Lcd_Out_Text(1,10,First_Number_Read);

        if(Data > 200) Data = 0;
        else if(Data > 20) Data = 20;

        Fox_Nr = UART_Read_Dta[(4*(20-Data))];
        Hr =  UART_Read_Dta[(4*(20-Data))+1];
        Min_ = UART_Read_Dta[(4*(20-Data))+2];
        Sec = UART_Read_Dta[(4*(20-Data))+3];

        Lcd_Out_Text(2,1,Fox_Nr);
        Lcd_Chr(2,4,'-');
        Lcd_Out_Text(2,5,Hr);
        Lcd_Chr(2,8,TP);
        Lcd_Out_Text(2,9,Min_);
        Lcd_Chr(2,12,TP);
        Lcd_Out_Text(2,13,Sec);

       }
      }

 // -------------------------- Read Fox -----------------------------
     else
      {
      if((Data > 0) &  (UART_Rear_Flg == 0))
        {
        First_Number_Read=0;
        UART_Read_Cnt = 0;
        Usart_Write(0x50);
        Usart_Write(0x2F);
        for(i=1;i<12;i++)
          {
          Lcd_Chr(2, i, 0xFF);
          delay_ms(190);
          }
        Lcd_Out_EEP(text_10,4,2,13);
        delay_ms(200);
        UART_Rear_Flg = 1;
        Lcd_Cmd(LCD_CLEAR);
        Data=20;
        }
       else if (UART_Rear_Flg == 1)
       {
        Lcd_Out_EEP(text_11_1,3,1,1);
        Lcd_Chr(1,4,TP);
        Lcd_Out_Text(1,6,First_Number_Read);

        if(Data > 200) Data = 0;
        else if(Data > 20) Data = 20;

        Fox_Nr = UART_Read_Dta[(4*(20-Data))];
        Hr =  UART_Read_Dta[(4*(20-Data))+1];
        Min_ = UART_Read_Dta[(4*(20-Data))+2];
        Sec = UART_Read_Dta[(4*(20-Data))+3];


        Lcd_Out_Text(2,1,Fox_Nr);
        Lcd_Chr(2,4,'-');
        Lcd_Out_Text(2,5,Hr);
        Lcd_Chr(2,8,TP);
        Lcd_Out_Text(2,9,Min_);
        Lcd_Chr(2,12,TP);
        Lcd_Out_Text(2,13,Sec);

       }
      }
     }


//------------------------Clear Memory Puncher ---------------------------------

    if(Menu == 3)
    {
      if(Data > 0)
        {
        for(i=1;i<17;i++) Lcd_Chr(2, i, ' ');
        First_Number_Read=0;
        UART_Read_Cnt = 0;
        UART_Read_Dta[0] = 0x00;
        Usart_Write(0x60);
        delay_ms(50);
        Usart_Write(0xFF);
        delay_ms(50);
        Usart_Write(0x00);
        delay_ms(50);
        Usart_Write(0xFF);
        Data=0;
        for(i=1;i<12;i++)
          {
          Lcd_Chr(2, i, 0xFF);
          delay_ms(200);
          }
       if(First_Number_Read == 0x6F) Lcd_Out_EEP(text_10,4,2,13);
       else Lcd_Out_EEP(text_16,5,2,12);

      }
    }
    
// ----------- Wait after enter in each Menu -----------------------------------

    if(Menu_Back != Menu)
    {
     delay_ms(700);
     Menu_Back = Menu;
    }

 } // End while
}