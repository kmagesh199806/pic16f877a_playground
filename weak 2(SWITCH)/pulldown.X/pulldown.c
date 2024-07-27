
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000 //intialize the clock speed
unsigned char v;        //decleare a variable
void main()
{
    TRISD=0x00;  //0000 0000
    TRISC=0x0F;  //0000 1111
    PORTC=0x00;  //0000 0000
    while(1)
    {
        v=PORTC; //portc data will be assign to v
        switch(v) //switch case
        {
            case 0x01:  //case1: 0000 0001
                PORTD=0x20;  //set portd=0010 0000
                break;    //exit the switch case
            case 0x02:  //case 2: 0000 0010
                PORTD=0x08; //set portd=0000 1000
                break;
            case 0x04:    //case 3: 0000 0100
                PORTD=0x28; //set portd=0010 1000
                break;
            case 0x08:  //case 4: 0000 1000
                PORTD=0x00; //set portd=0000 0000
                break;
            default:PORTD=0x00; //default switch case is 0000 0000
            
        }
    }
}


