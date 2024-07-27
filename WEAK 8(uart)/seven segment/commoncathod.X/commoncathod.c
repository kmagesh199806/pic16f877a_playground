
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h> //include neccacary header file
#define _XTAL_FREQ 6000000 //intialize the clock speed


void main()
{
    unsigned char SEG[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0xFD,0x07,0xFF,0x67}; //to turn on the portc pins
int i;
    TRISC=0x00; //set the trisc all as output pins
    PORTC=0x00; //clear the portc pins
   while(1)
   {
       for(i=0;i<=9;i++) //for loop 
       {
           PORTC=SEG[i]; //send the data to SEg of i to portc
           __delay_ms(1000); //delay
       }
   }
}