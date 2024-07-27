
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

#include <xc.h> //include nesccery header file
#define _XTAL_FREQ 6000000  //intialize the clock frequency
void init(void);    //function declaration
void pwmchange(void);   //function declaration
    unsigned char lsb20,msb20; //intialize variable
    unsigned char lsb60,msb60; //intialize variable
    unsigned char lsb90,msb90; //intialize variable
    void main() {
        init(); //call init function
        while(1) //while loop
            pwmchange(); //call the pwmchge
    }
    void init() //init function
    {
        TRISC=0xFB; //portc rc2/ccp1 pen set as output
        CCP1CON=0x3C;//to enter to pwm mode
        CCPR1L=0x2E;
        T2CON=0x06; //timer 2 turn on and set pre scaler as 16
        PR2=0x2E;   //period will set as 0010 1111
        lsb20=0x20; //store the calculated lsb value to lsb 20 
        msb20=0x09; //store the calculate msb value to msb 20
        lsb60=0x10; //store the calculated lsb value to lsb 60
        msb60=0x1C; //store the calculate msb value to msb 60
        lsb90=0x10; //store the calculated lsb value to lsb 90
        msb90=0x2A; //store the calculate msb value to msb 90
    }
    void pwmchange() //pwmchange function
    {
    CCPR1L=msb20;    //the msb value will be set to the CCPR1L
    CCP1CON=((CCP1CON&0xCF)|lsb20); //clear the ccp1con 5th and 4th bit and store lsb20 data 
    __delay_ms(3000); //delay
    CCPR1L=msb60; //the msb value will be set to the CCPR1L
    CCP1CON=((CCP1CON&0xCF)|lsb60); //clear the ccp1con 5th and 4th bit and store lsb60 data
    __delay_ms(3000); //delay
    CCPR1L=msb90; //the msb value will be set to the CCPR1L
    CCP1CON=((CCP1CON&0xCF)|lsb90); //clear the ccp1con 5th and 4th bit and store lsb90 data
    __delay_ms(3000); //delay
    }