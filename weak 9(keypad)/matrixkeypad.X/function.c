/*
 * File:   function.c
 * A111uthor: SURIYA111RA111J
 *
 * Created on 10 February 2024, 11:02
 */


#include <xc.h> //inclde the header file
#include"matrixguard.h" //include the userdifined headerfile
#define _XTAL_FREQ 6000000 //intialize the clock speed
#define I1 RB0 //Rb0 is named as I1
#define I2 RB1 //Rb1 is named as I2
#define I3 RB2  //Rb2 is named as I3
#define A RB3 //Rb3 is named as a
#define B RB4 //Rb4 is named as b
#define C RB5 //Rb5 is named as c
#define D RB6 //Rb6 is named as d

unsigned char d[15]={"MATRIX KEYPAD"}; //campile time array assign

void init(void)
{
    TRISB=0x07; //set the darection of portb
    OPTION_REG=0x7F; //intialize th inbuild pull up ressister
    PORTB=0x00; //clear the PoRTB
    TRISC=0x00; //PORTC will be set as output
    TRISD=0x00; //PORTD will be set as output
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    lcdcmd(0x38); //select the font and no of line will be used.
    lcdcmd(0x0C); //to turn on the display and turn off the curser 
    lcddata(0x00); //clear the lcd
            lcdcmd(0x80); //set the location of display
    for(int i=0;i<13;i++) //for loop
        lcddata(d[i]); //print the data
        lcdcmd(0xC0); //set the cursear
}
void lcdcmd(unsigned char i)
{
    PORTC&=~0x01; //RS pin will be set as 0
    PORTD=i; //i will be give to the PORTD
    PORTC|=0x02; //enable pin will set as 1
    PORTC&=~0x02; //enable pin will set as 0
    delay(100); //delay
}

void lcddata(unsigned char i)
{
    PORTC|=0x01; //RS pin will be set as 1
    PORTD=i; //i will be sent to the PORTD
    PORTC|=0x02; //enable pin will set as 1
    PORTC&=~0x02; //enable pin will set as 0
    delay(100);
}

void delay(unsigned int delaycount)
{
    while(--delaycount); //delay count
}
char keyscan()
{
 A=0,B=1,C=1,D=1; //a will be set as 0
 delay(10); //delay
    if(I1==0){delay(100);while(I1==0);return '1';} //check the key will press
    if(I2==0){delay(100);while(I2==0);return '2';} //check the key will press
    if(I3==0){delay(100);while(I3==0);return '3';} //check the key will press

    
    A=1,B=0,C=1,D=1; //b will be set as 0
    delay(10);
    if(I1==0){delay(100);while(I1==0);return '4';} //check the key will press
    if(I2==0){delay(100);while(I2==0);return '5';} //check the key will press
    if(I3==0){delay(100);while(I3==0);return '6';} //check the key will press

    A=1,B=1,C=0,D=1; //c will be set as 0
    delay(10);
    if(I1==0){delay(100);while(I1==0);return '7';} //check the key will press
    if(I2==0){delay(100);while(I2==0);return '8';} //check the key will press
    if(I3==0){delay(100);while(I3==0);return '9';} //check the key will press

    A=1,B=1,C=1,D=0; //d will be set as 0
    delay(10);
    if(I1==0){delay(100);while(I1==0);return'*';} //check the key will press
    if(I2==0){delay(100);while(I2==0);return '0';} //check the key will press
    if(I3==0){delay(100);while(I3==0);return '#';} //check the key will press
   return NULL; //will not key press send the null value

}