
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

#include <xc.h> //include the neccessary header file
#include"guard_1.h" //include the guard user difined file
#define _XTAL_FREQ 6000000 //intialize the frequency

void main(void)
{
    i2c_master_init(100000); //call th init function
    eprom_write(0x0023,'A'); //sent the address and data to the eeprom
    __delay_ms(10);
    eprom_write(0x0028,'B'); //sent the address and data to the eeprom
    __delay_ms(10);
    eprom_write(0x0036,'C'); //sent the address and data to the eeprom
    __delay_ms(10);
    TRISD=0x00; //set the portd as output
    PORTD=eprom_read(0x0023); //read the data in eeprom
    __delay_ms(1000);
    PORTD=eprom_read(0x0028); //read the data in eeprom
    __delay_ms(1000);
    PORTD=eprom_read(0x0036); //read the data in eeprom
    __delay_ms(1000);
    while(1);  
}
