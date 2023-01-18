/*
 * File:   LCD_Screens.c
 * Author: mahmo
 *
 */


#include "LCD_Screens.h"

void Screen_Date_Time() 
{
    RTC_Get_Time(RTC); /*gives second,minute and hour*/
    RTC_Get_Date(RTC);
    
    RTC->sec  = BcdToDec(RTC->sec);
    RTC->min  = BcdToDec(RTC->min);
    RTC->hour = BcdToDec(RTC->hour);
    //sec  = BcdToDec(33); //21
    //min  = BcdToDec(33); //21
    //hour = BcdToDec(33); //21

    if(RTC->sec < 10) sprintf(secs, "0%d ", RTC->sec);
    else sprintf(secs, "%d ", RTC->sec); /*%x for reading BCD format from RTC DS1307*/
    
    if(RTC->min < 10) sprintf(mins, "0%d:", RTC->min);
    else sprintf(mins, "%d:", RTC->min);
    
    if(RTC->hour < 10) sprintf(hours, "Time: 0%d:", RTC->hour);
    else sprintf(hours, "Time: %d:", RTC->hour);


    LCD_goto_xy(0, 0);
    LCD_write_string(hours);
    LCD_write_string(mins);
    LCD_write_string(secs);
    
    
    if(RTC->date < 10) sprintf(date, "Date: 0%x-", RTC->date);
    else sprintf(date, "Date: %x-", RTC->date);
    
    if(RTC->month < 10) sprintf(month, "0%x-", RTC->month);
    else sprintf(month, "%x-", RTC->month);
    
    sprintf(year, "%x ", RTC->year);
    

    LCD_goto_xy(1, 0);
    LCD_write_string(date);
    LCD_write_string(month);
    LCD_write_string(year);

}

void Screen_Device_1() 
{
    LCD_goto_xy(0, 0);
    LCD_write_string("Start1: ");
    
    for (int i = 0; i < 8; i++) 
    {
        LCD_write(time1[0][i]);
    }

    LCD_goto_xy(1, 0);
    LCD_write_string("Finish: ");
    
    for (int i = 0; i < 8; i++) 
    {
        LCD_write(time1[1][i]);
    }
    __delay_ms(50);
    
    if(IS_PRESSED_PIN(Push_Buttons_Pins, Button_2))
    {
        __delay_ms(5);
        while(IS_PRESSED_PIN(Push_Buttons_Pins, Button_2));
        
        if(Place1<9)
        {
            Place1++;
        }
        else Place2++;
    
        if(Place1==3) Place1=4;
        if(Place1==6) Place1=7;
        if(Place2==3) Place2=4;   
        if(Place2==6) Place2=7;
 
        if(Place2>8)
        {
            Place1=0;
            Place2=0;
        }
    }
        
        if (Place1 > 0 && Place1 < 9) {
        Set_Time(0, Place1);
    }
    else if (Place2 > 0 && Place2 < 9) {
        Set_Time(1, Place2);
    }

    switch (Place1) {
        case 1: Flash(1, Place1);
            break;
        case 2: Flash(2, Place1);
            break;
        case 4: Flash(4, Place1);
            break;
        case 5: Flash(5, Place1);
            break;
        case 7: Flash(7, Place1);
            break;
        case 8: Flash(8, Place1);
            break;
    }

    switch (Place2) {
        case 1: Flash(1, Place1);
            break;
        case 2: Flash(2, Place1);
            break;
        case 4: Flash(4, Place1);
            break;
        case 5: Flash(5, Place1);
            break;
        case 7: Flash(7, Place1);
            break;
        case 8: Flash(8, Place1);
            break;
    }
    
}

void Screen_Device_2() 
{
    LCD_goto_xy(0, 0);
    LCD_write_string("Start2: ");
    
    for (int i = 0; i < 8; i++) 
    {
        LCD_write(time1[2][i]);
    }

    LCD_goto_xy(1, 0);
    LCD_write_string("Finish: ");
    
    for (int i = 0; i < 8; i++) 
    {
        LCD_write(time1[3][i]);
    }
    __delay_ms(50);
    
    if(IS_PRESSED_PIN(Push_Buttons_Pins, Button_2))
    {
        __delay_ms(5);
        while(IS_PRESSED_PIN(Push_Buttons_Pins, Button_2));
        
        if(Place3<9)
        {
            Place3++;
        }
        else Place4++;
    
        if(Place3==3) Place3=4;
        if(Place3==6) Place3=7;
        if(Place4==3) Place4=4;   
        if(Place4==6) Place4=7;
 
        if(Place4>8)
        {
            Place3=0;
            Place4=0;
        }
    }
        
        if (Place3 > 0 && Place3 < 9) {
        Set_Time(2, Place3);
    }
    else if (Place4 > 0 && Place4 < 9) {
        Set_Time(3, Place4);
    }

    switch (Place3) {
        case 1: Flash(1, Place3);
            break;
        case 2: Flash(2, Place3);
            break;
        case 4: Flash(4, Place3);
            break;
        case 5: Flash(5, Place3);
            break;
        case 7: Flash(7, Place3);
            break;
        case 8: Flash(8, Place3);
            break;
    }

    switch (Place4) {
        case 1: Flash(1, Place3);
            break;
        case 2: Flash(2, Place3);
            break;
        case 4: Flash(4, Place3);
            break;
        case 5: Flash(5, Place3);
            break;
        case 7: Flash(7, Place3);
            break;
        case 8: Flash(8, Place3);
            break;
    }
    

}
