/*
 * File:   Push_Buttons.c
 * Author: mahmo
 *
 */


#include "Push_Buttons.h"

void Push_Buttons_Init()
{
    MAKE_PIN_INPUT(Push_Buttons_Direction, Button_1);
    MAKE_PIN_INPUT(Push_Buttons_Direction, Button_2);
    MAKE_PIN_INPUT(Push_Buttons_Direction, Button_3);
    MAKE_PIN_INPUT(Push_Buttons_Direction, Button_4);
}
