/*
 * File:   driver.c
 * Author: SURIYARAJ
 *
 * Created on 21 February 2024, 18:46
 */


#include <xc.h> //include the neccesser header
#include"intguard.h" //include the guard file
#define _XTAL_FREQ 6000000 //intialize the clock speed
volatile unsigned char val; //declare the variable

void init() //function
{ 
    TRISB=0x01; //set the darection of the portb
    PORTB=0x00; //clear the portb
    TRISD=0xFE; //set the darection of the portD
    PORTD=0x00; //clear the portd
    TRISC=0x00; //set the darection of the portc
    PORTC=0x00; //clear the portc
    //OPTION_REG=0X7F;
    INTCON|=0x90; //turn on the global interrupt and external interrupt
    
}
void __interrupt() ISR() //interrupt function 
{
    if(INTCON & 0x02) //check the external interrupt flag will set
    {
         PORTD |= 0x01; //turn on the RD0
         while(PORTB!=0); //wait until release the button
         PORTD &=~0x01; //turn of the led
    }
    INTCON&=~0x02; //clear the interrupt flag
}