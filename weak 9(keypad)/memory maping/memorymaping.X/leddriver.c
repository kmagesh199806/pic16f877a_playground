/*
 * File:   leddriver.c
 * Author: SURIYARAJ
 *
 * Created on 05 February 2024, 20:13
 */


//#include <xc.h>
#include"leddriver.h" //inclue the user difined header file
unsigned char *trb=0x86,*trc=0x87,*prb=0x06,*prc=0x07,*opreg=0x81; //create a pointer variable


void init()
{
    *trb=0xF0; //set the deraction of the port b
 *opreg&=0x7F; //enable the pull up ressistor
    *prb=0x00; //clear the portb
    *trc=0x00; //set portc all as output
    *prc=0x00; //clear the portc
}
void swh(int i) 
{
    switch(i) //switch case pass the i
    {
        case 0xE0:
            *prc=0x04; //to turn on or turn off the led
            break;
        case 0xD0:
            *prc=0x02; //to turn on or turn off the led
            break;
        case 0xB0:
            *prc=0x00; //to turn on or turn off the led
            break;
        case 0x70:
            *prc=0x06; //to turn on or turn off the led
            break;
    }
}
