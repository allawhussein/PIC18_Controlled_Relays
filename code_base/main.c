/*
 * File:   main.c
 * Author: mahmo
 *
 */


#include <xc.h>
#include "Config_Bits.h"
#include "GPIO_Driver.h"
#include "I2C_Driver.h"
#include "LCD_Driver.h"
#include "LCD_Screens.h"
#include "Push_Buttons.h"
#include "RTC_Driver.h"
#include "EEPROM_Driver.h"
#include "UART_Driver.h"

void __interrupt() ISR (void);
//__interrupt() void ISR(void);
volatile uint8_t Destination;

void main(void) {
    
    Screen_Num = 1;
    
    Push_Buttons_Init();
    MAKE_PIN_OUTPUT(TRISB, 6);
    MAKE_PIN_OUTPUT(TRISB, 7);
    LCD_init();
    I2C_Init();
    USART_init(9600);
    Active_Receiver_Interrupt();
    
    //RTC_Set_Time(decToBcd(30), decToBcd(30), decToBcd(8));
    //RTC_Set_Date(decToBcd(5), decToBcd(30), decToBcd(12), decToBcd(22));
    RTC_Set_Time(30, 30, 12);
    RTC_Set_Date(5, 30, 12, 22);
    
    
    for(char i=0; i<32; i++)
    {
        if(EEPROM_Read(i) == 0xFF) EEPROM_Write(i, 48);
    }
    
    
    
    
    for(char i=0; i<4; i++)
    {
        for(char j=0; j<8; j++)
        {
            if(j==2 || j==5) continue;
            switch (i)
            {
                case 0 : time1[i][j] = EEPROM_Read(i+j);    break;
                case 1 : time1[i][j] = EEPROM_Read(i+j+7);  break;
                case 2 : time1[i][j] = EEPROM_Read(i+j+14); break;
                case 3 : time1[i][j] = EEPROM_Read(i+j+21); break;
                default: ;
            }
            
        }
    }
     
    
    while(1)
    {
        
        if(Destination)
        {
            switch (Destination)
            {
                case 65: SET_PIN(PORTB, 6);   flag = 1;   break;
                case 66: CLEAR_PIN(PORTB, 6); flag = 0;   break;
                case 67: SET_PIN(PORTB, 7);   flag = 1;   break;
                case 68: CLEAR_PIN(PORTB, 7); flag = 0;   break;
                default: ;
            }
            Destination = 0;
        }
        
        if(IS_PRESSED_PIN(Push_Buttons_Pins, Button_1))
        {
            __delay_ms(5);
            while(IS_PRESSED_PIN(Push_Buttons_Pins, Button_1));
            
            LCD_clear();
            
            Screen_Num ++;
            if(Screen_Num > 3) Screen_Num = 1;
        }
        
        switch(Screen_Num)
        {
            case 1: Screen_Date_Time(); break;
            case 2: Screen_Device_1() ; break;
            case 3: Screen_Device_2() ; break;
            default:Screen_Date_Time();        
        }
        
        for (char i = 0; i < 4; i++) 
        {
            for (char j = 0; j < 8; j++) 
            {
                if (j == 2 || j == 5) continue;
                switch (i) 
                {
                    case 0: EEPROM_Write((i + j), time1[i][j]);      break;
                    case 1: EEPROM_Write((i + j + 7), time1[i][j]);  break;
                    case 2: EEPROM_Write((i + j + 14), time1[i][j]); break;
                    case 3: EEPROM_Write((i + j + 21), time1[i][j]); break;
                    default:;
                }

            }
        }
        
        Check(0);
        Check(1);
        Compare(0, 1);
        Check(2);
        Check(3);
        Compare(2, 3);
        
        
    }
    
    
    return;
}

void __interrupt() ISR (void)
{

  if (RCIF == 1)
  {
      RCIF = 0;             // Clear The Flag
      Destination = RCREG;  // Read The Received Data Buffer 
  }
  
  
}
