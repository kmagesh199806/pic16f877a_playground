#include"guard.h"
unsigned char count =0; //declare the global declaration
void timerinit() //timerinit function
{
	TRISC=0x00; //set portc as output
	PORTC=0x00; //clear the portc
	TRISD=0x00; //set portd as output
	PORTD=0x00; //clear the portd
	INTCON = 0xC0; //enable the global interrupt ad pheripheral interrupt
	PIR1 &= 0xFE; //clear the PIR1 register
	PIE1=0x01;  //turn on time 1 overflow interrupt
	T1CON=0x01;  //enable timer 1 and prescale 1:1
    TMR1=5475; //set the calibrater value to tmr1
}

void __interrupt() isr() //isr function
{
	if( PIR1 & 0x01) //check the flag
	{
        count++; //increment the count
        if(count == 25) //check the count==25
        {
		PORTD=~PORTD; //till the portd
        count=0; //reset the count
        }
        TMR1=5475; //set the timer pre loading value
      PIR1 &= 0xFE; //clear the flag
	}
	
	
}