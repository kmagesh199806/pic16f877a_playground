
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
void main(void) {
    
    I2C_Master_Init(100000);
    unsigned int Address = 0x0020; // Some Random Address
          unsigned char Data[5] ={'A','B','C','D','E'};     // Some Random Data To Write
        unsigned int len = 5;
    EEPROM_Write_Page(Address, Data, len); // Write 0x04 @ 0x0020
  __delay_ms(100);
     Address = 0x0020; // Some Random Address
     unsigned char data[5];
         
         TRISD=0X00;
    EEPROM_Read_Page(Address,data,len); // Write 0x04 @ 0x0020
   

    while(1);
}