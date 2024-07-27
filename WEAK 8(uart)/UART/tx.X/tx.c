
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
void init(void); //function declaration
void lcdcmd(unsigned char); //function declaration
void lcddata(unsigned char); //function declaration
unsigned char i,val,rxval,j,tx[10]={"TX DATA="},rx[10]={"RX DATA="}; //declare the varable
void transmit_init(); //function declaration
 

void main()
{
init(); //call the init function
lcdcmd(0x80); //set the location in lcd1
for(i=0;i!=8;i++) 
    lcddata(tx[i]); //sent the tx data to print in the lcd
lcdcmd(0xC0); //set the location of the lcd
for(i=0;i!=8;i++)
    lcddata(rx[i]); //sent the rx data to print in the lcd
while(1)
{
val=PORTB; //port b data will be sent to the val variable
lcdcmd(0x88); //set the location of the lcd
switch(val) //val will be given to the switch case
{
	case 0xE0: //case1 1110 0000
		TXREG='A'; //csapital A will be sent to the TXREG rigister
        lcddata('A'); //sent the A to the lcd
	break;
	case 0xD0: //case2 1101 0000
		TXREG='B'; //csapital B will be sent to the TXREG rigister
        lcddata('B'); //sent the B to the lcd
	break;
	case 0xB0: //case3 1011 0000
		TXREG='C'; //csapital C will be sent to the TXREG rigister
        lcddata('C'); //sent the C to the lcd
	break;
	case 0x70: //case4 0111 0000
		TXREG='D'; //csapital D will be sent to the TXREG rigister
        lcddata('D'); //sent the D to the lcd
	break;	
	
	}	

if(PIR1 & 0x20) //to check the rcif bit as 1
	{
    lcdcmd(0xC8); //send the location of the display
    rxval = RCREG; //rcreg value to rxval variable
    lcddata(rxval); //sent the data to lcd
   
    }

}
}

void init()
{
	TRISB=0xF0; //intialize the msb nibble as input
    PORTB=0x00; //clear the port b
    TRISD=0x00; //trisd set as output
	OPTION_REG&=0x7F; //enable the internall pull up resister
	TRISC=0xC0;  //set the rx and tx pen as 1
	RCSTA=0x90; //serial port enable and continous recive mode
	TXSTA=0x20; //transmitt enable bit and asynchronus mode boud rate will be set as low speed
	SPBRG=0x09;  //set the boud rate   
	    lcdcmd(0x30); //lcd intalization
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
    PORTB&=~0x01; //rs pin will set as 0
    PORTD=j; //sent the j value to the portd
    PORTB|=0x02; //enable pin set 1
    __delay_ms(50);
    PORTB&=~0x02; //enable pin set 0
}
void lcddata(unsigned char j)
{
    PORTB|=0x01; //rs pin will set as 1
    PORTD=j; //sent the data to the portd
    PORTB|=0x02; //enable pin set as 1
    __delay_ms(50);
    PORTB&=~0x02; //enable pin set as 0
    //__delay_ms(100); //delay
}