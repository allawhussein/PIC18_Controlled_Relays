/*
 * File:   EEPROM_Driver.c
 * Author: mahmo
 *
 * Created on December 31, 2022, 6:54 AM
 */


#include <xc.h>
#include "EEPROM_Driver.h"

void EEPROM_Write(char address,char data)
{
    /*Write Operation*/
    EEADR=address;               /*Write address to the EEADR register*/
    EEDATA=data;                 /*copy data to the EEDATA register for write to EEPROM location*/
    EECON1bits.EEPGD=0;          /*Access data EEPROM memory*/
    EECON1bits.CFGS=0;           /*Access flash program or data memory*/
    EECON1bits.WREN=1;           /*Allow write to the memory*/
    INTCONbits.GIE=0;            /*Disable global interrupt*/
    
    /*below sequence in EECON2 Register is necessary to write data to EEPROM memory*/
    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;             /*Start writing data to EEPROM memory*/
    INTCONbits.GIE=1;            /*Enable interrupt*/
    
    while(PIR2bits.EEIF==0);     /*EEIF bit is set when write operation is completed*/
                                 /*monitor this bit for write operation*/  
    PIR2bits.EEIF=0;             /*Reset EEIF for further write operation*/
    
}

void EEPROM_WriteString(char address,char *data)
{
    /*Write Operation for String*/
    while(*data!=0)
    {
        EEPROM_Write(address,*data);
        address++;
        *data++;
    }    
}

char EEPROM_Read(char address)
{
    /*Read operation*/
    EEADR=address;               /*Read data at location 0x00*/
    EECON1bits.WREN=0;           /*WREN bit is clear for Read operation*/  
    EECON1bits.EEPGD=0;          /*Access data EEPROM memory*/
    EECON1bits.RD=1;             /*To Read data of EEPROM memory set RD=1*/
    return(EEDATA);
}

