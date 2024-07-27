
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

#include <xc.h>
#define _XTAL_FREQ 6000000 //intialize the clock speed
unsigned char val;   //declear the variable
void main()

{
    TRISD=0x00; //0000 0000
    TRISC=0x0F; //0000 1111
    PORTC=0X00; //0000 0000
    while(1)    //loop for continous operation
    {
        val=PORTC; //store the portc data to val
        switch(val) //val will be given to the switch case
        {
            case 0x0E:  //case1: 0000 1110
                    PORTD=0x20;  //0010 0000
                    break;       //to exit the switch case
            case 0x0D:   //case2: 0000 1101
                        PORTD=0x08; //0000 1000
                        break;
            case 0x0B:  //case3:0000 1011
                            PORTD=0x28; //0010 1000
                            break;
            case 0x07:  //case4:0000 0111
                                PORTD=0x00; //0000 0000
                                break;
                               default:PORTD=0x00; //0000 0000
        }
    }
}
