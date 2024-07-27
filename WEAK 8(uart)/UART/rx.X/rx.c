
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

#include <xc.h> //incled the header file
#define _XTAL_FREQ 6000000 //itialize the clock speed
void receivee_init(void); //function declaration
void lcdcmd(unsigned char); //function declaration
void lcddata(unsigned char); //function declaration
unsigned char i,recval,rx[10]={"RX DATA="},tx[10]={"TX DATA="}; //declare the varible
void main()
{
	receivee_init(); //call the recive init function
    lcdcmd(0x80); //set the location of the lcd
    for(i=0;i!=8;i++)
        lcddata(rx[i]); //send the data to lcd
    lcdcmd(0xC0); //set the location of the lcd
    for(i=0;i!=8;i++)
        lcddata(tx[i]); //send the data to lcd
	while(1)
	{
		if(PIR1 & 0x20) //check the rcif bit will 1
		{
		recval = RCREG; //rcreg data will be stored in recval
		switch(recval)
		{
			case 'A':
				lcdcmd(0x88); //set the location of the lcd
                lcddata(recval); //send the data to lcd
                TXREG=recval+32; //to conver the capital to smaller
                lcdcmd(0xC8); //set the location of the lcd
                lcddata(recval+32); //send the data to lcd
			break;
			case 'B':
				lcdcmd(0x88); //set the location of the lcd
                lcddata(recval); //send the data to lcd
                TXREG=recval+32; //to conver the capital to smaller
                lcdcmd(0xC8); //set the location of the lcd
                lcddata(recval+32); //send the data to lcd
			break;
			case 'C':
				lcdcmd(0x88); //set the location of the lcd
                lcddata(recval); //send the data to lcd
                TXREG=recval+32; //to conver the capital to smaller
                lcdcmd(0xC8); //set the location of the lcd
                lcddata(recval+32); //send the data to lcd
			break;
			case 'D':
				lcdcmd(0x88); //set the location of the lcd
                lcddata(recval); //send the data to lcd
                TXREG=recval+32; //to conver the capital to smaller
                lcdcmd(0xC8); //set the location of the lcd
                lcddata(recval+32); //send the data to lcd
			break;	
			}	
		}
	}
	
	
}

void receivee_init()
{
	TRISD=0x00; //set pord d as output
	TRISB=0x00; //set the portb all as output
	TRISC=0xC0;  //set the tx and rx pin as 1
	RCSTA=0x90; //serial port enable and continous recive mode
	TXSTA=0x20; //transmitt enable bit and asynchronus mode boud rate will be set as low speed
	SPBRG=0x09; //set the boud rate
    lcdcmd(0x30); //lcd intialization
    __delay_ms(100);
    lcdcmd(0x30); //lcd intialization
    __delay_ms(100);
    lcdcmd(0x30); //lcd intialization
    __delay_ms(100);
    lcdcmd(0x38); //select the twoline and font of the display
    lcdcmd(0x0C); //for display on and cursear off
    lcdcmd(0x01); //desplay clear
    __delay_ms(100);
	
}

void lcdcmd(unsigned char j)
{
    PORTB&=~0x08; //rs pin will set as 0
    PORTD=j; //sent the j value to the portd
    PORTB|=0x04; //enable pin set 1
    __delay_ms(50);
    PORTB&=~0x04; //enable pin set 0
}

void lcddata(unsigned char j)
{
    PORTB|=0x08; //rs pin will set as 1
    PORTD=j; //sent the data to the portd
    PORTB|=0x04; //enable pin set as 1
    __delay_ms(50);
    PORTB&=~0x04; //enable pin set as 0
    //__delay_ms(100); //delay
}