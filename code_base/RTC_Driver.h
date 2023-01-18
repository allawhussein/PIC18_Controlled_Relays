/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RTC_DRIVER_H
#define	RTC_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "I2C_Driver.h"

#define device_id_write   0xD0
#define device_id_read    0xD1
//#define hour_12_PM        0x60
//#define hour_12_AM        0x40

#define value_once(value)           (value % 10)
#define value_tanth(value)          (value /10)
#define decToBcd(value)             ((value_once(value) & (0x0F)) + ((value_tanth(value) << 4 ) & (0xF0)))
#define BcdToDec(value)              ((value & 0x0F) + (((value>>4) & (0x0F)) * 10))

typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t Day;
  uint8_t date;
  uint8_t month;
  uint8_t year;  
}RTC_t;

//void RTC_Set_Time(char sec, char min, char hour, char AM_PM);
void RTC_Set_Time(char sec, char min, char hour);                       /* function for Time Setting */
void RTC_Set_Date(char day, char date, char month, char year);      	/* function for Date Setting */
void RTC_Get_Time(RTC_t *RTC);
void RTC_Get_Date(RTC_t *RTC);

//static int sec,min,hour;
//static int Day,Date,Month,Year;



#endif	/* XC_HEADER_TEMPLATE_H */

