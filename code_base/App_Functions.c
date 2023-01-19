/*
 * File:   App_Functions.c
 * Author: mahmo
 *
 */


#include <xc.h>
#include "App_Functions.h"



void Set_Time(int Num, int Place) 
{
    if(IS_PRESSED_PIN(Push_Buttons_Pins, Button_3) && Place > 0)
    {
        __delay_ms(5);
        while(IS_PRESSED_PIN(Push_Buttons_Pins, Button_3));
        
        if (time1[Num][Place - 1] >= '0' && time1[Num][Place - 1] < '9') 
        {
            time1[Num][Place - 1] = time1[Num][Place - 1] + 1;
        }
    }

    if(IS_PRESSED_PIN(Push_Buttons_Pins, Button_4) && Place > 0)
    {
        __delay_ms(5);
        while(IS_PRESSED_PIN(Push_Buttons_Pins, Button_4));
        
        if (time1[Num][Place - 1] > '0' && time1[Num][Place - 1] <= '9') 
        {
            time1[Num][Place - 1] = time1[Num][Place - 1] - 1;
        }
    }
    if (time1[Num][0] > '2') 
    {
        time1[Num][0] = '2';
    }
    if (time1[Num][0] == '2' && time1[Num][1] > '3') 
    {
        time1[Num][1] = '3';
    }
    if (time1[Num][0] == '0' && time1[Num][1] > '9') 
    {
        time1[Num][1] = '9';
    }

    if (time1[Num][3] > '5') 
    {
        time1[Num][3] = '5';
    }
    if (time1[Num][4] > '9') 
    {
        time1[Num][4] = '9';
    }
    if (time1[Num][6] > '5') 
    {
        time1[Num][6] = '5';
    }
    if (time1[Num][7] > '9') 
    {
        time1[Num][7] = '9';
    }
}


void Check(int Num)
{
  hour2[Num] = ( 10 * (time1[Num][0] - '0' ) ) + time1[Num][1] - '0';
  min2[Num] = ( 10 * (time1[Num][3] - '0' ) ) + time1[Num][4] - '0';
  sec2[Num] = ( 10 * (time1[Num][6] - '0' ) ) + time1[Num][7] - '0';
}


void Compare(int Num1, int Num2)
{
  total=(uint32_t) (RTC->hour)*3600+(uint32_t) (RTC->min)*60+(uint32_t) (RTC->sec);
  total1[Num1]=(uint32_t) hour2[Num1]*3600+(uint32_t) min2[Num1]*60+(uint32_t) sec2[Num1];
  total2[Num1]=(uint32_t) 3600*hour2[Num2]+(uint32_t) min2[Num2]*60 +(uint32_t) sec2[Num2];

  Action();
}


void Action()
{
  
  //For First Screen Action
  if(total>=total1[0])
  {
    mask[0]=1;
  }
   
  if( (total2[0]>total&&mask[0]==1) || flag1) 
  {
    //This part you can Add as you want to execute it
    SET_PIN(PORTB, 6);// ****************
  }
  else
  {
     if(!flag1)
     {
         CLEAR_PIN(PORTB, 6);// *****************
         mask[0]=0;
     }
    
  }
  

  if(total>=total1[2])
  {
    mask[1]=1;
  }
   
  if( (total2[2]>total&&mask[1]==1) || flag2)
  {
    //This part you can Add as you want to execute it
    SET_PIN(PORTB, 7);  // ****************
  }else
  {
      if(!flag2)
      {
         CLEAR_PIN(PORTB, 7);  // *****************
         mask[1]=0; 
      }
    
    
  }

}


void Flash(int inc, int PlaceN)
{
  if(PlaceN>=9)
  {
      LCD_goto_xy(1, inc+7);
  }
  else 
  {
      LCD_goto_xy(0, inc+7);
  }
  
  LCD_write(' ');
  __delay_ms(50);
}