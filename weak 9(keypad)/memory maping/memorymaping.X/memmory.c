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
#include"config.h" //include the user difined header file
//#include <xc.h>
#include "leddriver.h" //include the driver file
#define _XTAL_FREQ 6000000 //intialize the clock speed
unsigned char *prb=0x06; //creat a pinter variable and store the address of portb
void main()
{
    init(); //call the init function
    
    while(1)
        swh(*prb); //call the swh function with argument of portb adress
}
