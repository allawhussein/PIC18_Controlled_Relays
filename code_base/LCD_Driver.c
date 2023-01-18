/*
 * File:   LCD_Driver.c
 * Author: mahmo
 *
 */


#include <xc.h>

#include "LCD_Driver.h"

/*
void swap(int *xp, int *yp)
{
    int temp; 
    temp = *xp;
 *xp = *yp;
 *yp = temp;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int Base)
{
    int i = 0;
    bool isNegative = false;
 
    // Handle 0 explicitly, otherwise empty string is printed for 0 
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && Base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % Base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/Base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

 */



void LCD_cmd(char cmd) {
    CLEAR_PIN(LCD_pins, LCD_RS);
    //Clear_pin(LCD_pins , LCD_RW);

    LCD_pins &= 0xC3;
    LCD_pins |= (0x3C & (cmd >> 2));

    SET_PIN(LCD_pins, LCD_Enable);
    __delay_us(1);
    CLEAR_PIN(LCD_pins, LCD_Enable);

    LCD_pins &= 0xC3;
    LCD_pins |= (0x3C & (cmd) << 2);

    SET_PIN(LCD_pins, LCD_Enable);
    __delay_us(1);
    CLEAR_PIN(LCD_pins, LCD_Enable);
    SET_PIN(LCD_pins, LCD_RS);

    __delay_us(40);
}

void LCD_cmd_High(uint8_t cmd) {
    CLEAR_PIN(LCD_pins, LCD_RS);
    LCD_pins &= 0xC3;
    LCD_pins |= (0x3C & (cmd >> 2));
    SET_PIN(LCD_pins, LCD_Enable);
    __delay_us(1);
    CLEAR_PIN(LCD_pins, LCD_Enable);
    SET_PIN(LCD_pins, LCD_RS);
}

void LCD_4bit_mode() {
    __delay_ms(15);
    LCD_cmd_High(0x30);
    __delay_ms(5);
    LCD_cmd_High(0x30);
    __delay_us(100);
    LCD_cmd_High(0x30);
    __delay_us(40);
    LCD_cmd_High(0x20);
    __delay_us(40);
    LCD_cmd(0x28);
    LCD_cmd(0x0C);
    LCD_cmd(0x01);
    __delay_ms(2);
    LCD_cmd(0x06);
}

void LCD_clear() {
    LCD_cmd(Clear);
    __delay_ms(2);
}

void LCD_init() {
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_D4);
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_D5);
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_D6);
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_D7);
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_Enable);
    MAKE_PIN_OUTPUT(LCD_pins_direction, LCD_RS);
    //MAKE_PIN_OUTPUT(LCD_pins_direction , LCD_RW);


    //LCD_cmd(four_bits_two_lines_mode); // 4-bits Mode.
    LCD_4bit_mode();


}

void LCD_write(char data) {
    SET_PIN(LCD_pins, LCD_RS);
    //Clear_pin(LCD_pins , LCD_RW);

    LCD_pins &= 0xC3;
    LCD_pins |= (0x3C & (data >> 2));

    SET_PIN(LCD_pins, LCD_Enable);
    __delay_ms(1);
    CLEAR_PIN(LCD_pins, LCD_Enable);

    LCD_pins &= 0xC3;
    LCD_pins |= (0x3C & (data << 2));

    SET_PIN(LCD_pins, LCD_Enable);
    __delay_ms(1);
    CLEAR_PIN(LCD_pins, LCD_Enable);

}

void LCD_write_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        LCD_write(str[i]);
    }

}

/*
void LCD_write_number(int num)
{
    char num_str [8];
    itoa(num , num_str , 10); // convert number to array of char
	
    LCD_write_string (num_str);
	
}
 */

void LCD_goto_xy(int x, int y) {
    if ((x == 0) && (y < 16)) {
        LCD_cmd(First_line);
        for (int i = 0; i < y; i++) {
            LCD_cmd(Move_cursor_right);

        }
    } else if ((x == 1) && (y < 16)) {
        LCD_cmd(Second_line);
        for (int i = 0; i < y; i++) {
            LCD_cmd(Move_cursor_right);
        }
    }

}
