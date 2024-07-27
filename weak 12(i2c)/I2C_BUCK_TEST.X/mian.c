
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
#include"guard.h"
#define _XTAL_FREQ 16000000

void main(void)
{
    i2c_master_init(100000);
    eeprom_write(0x0023,'A');
    eeprom_write(0x0028,'B');
    eeprom_write(0x0036,'C');
    __delay_ms(100);
    TRISD=0x00;
    PORTD=eeprom_read(0x0023);
    __delay_ms(1000);
    PORTD=eeprom_read(0x0028);
    __delay_ms(1000);
    PORTD=eeprom_read(0x0036);
    __delay_ms(1000);
    while(1);
    return;   
}
