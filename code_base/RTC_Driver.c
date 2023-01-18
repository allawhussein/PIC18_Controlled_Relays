/*
 * File:   RTC_Driver.c
 * Author: mahmo
 *
 */


#include "RTC_Driver.h"

void RTC_Set_Time(char sec, char min, char hour)					/* function for clock */
{
    I2C_Init();
    //hour = (hour | AM_PM);        /* whether it is AM or PM */
	I2C_Start(device_id_write);	  /* start I2C communication with device slave address */	
	I2C_Write(0);			      /* write on 0 location for second value */
	I2C_Write(decToBcd(sec));			      /* write second value on 00 location */
	I2C_Write(decToBcd(min));			      /* write min value on 01 location */
	I2C_Write(decToBcd(hour));		      /* write hour value on 02 location */
	I2C_Stop();				      /* stop I2C communication */
}



void RTC_Set_Date(char day, char date, char month, char year)	/* function for calendar */
{
	I2C_Start(device_id_write);	  /* start I2C communication with device slave address */
	I2C_Write(3);			      /* write on 3 location for day value */
	I2C_Write(decToBcd(day));			      /* write day value on 03 location */
	I2C_Write(decToBcd(date));		      /* write date value on 04 location */
	I2C_Write(decToBcd(month));		      /* write month value on 05 location */
	I2C_Write(decToBcd(year));		      /* write year value on 06 location */
	I2C_Stop();
}


void RTC_Get_Time(RTC_t *RTC)
{
    I2C_Start(device_id_write);
    I2C_Write(0);     /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    RTC->sec = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    RTC->min = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    RTC->hour= I2C_Read(1);                 /*read data and send nack for indicating stop reading*/
    I2C_Stop();
    
}

void RTC_Get_Date(RTC_t *RTC)
{   
    I2C_Start(device_id_write);
    I2C_Write(3); /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    RTC->Day = I2C_Read(0);                /*read data and send ack for continuous reading*/
    RTC->date = I2C_Read(0);               /*read data and send ack for continuous reading*/
    RTC->month = I2C_Read(0);              /*read data and send ack for continuous reading*/
    RTC->year = I2C_Read(1);               /*read data and send nack for indicating stop reading*/
    I2C_Stop();
}
