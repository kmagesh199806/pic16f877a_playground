#include "guard.h" //include the header file
#define INC RB0 //define RBO
#define DEC RB1 //define RB1
#define SEND RB2 //define RB2
unsigned int data; //declare the variable

void spi_intialize() 
{
CKE=0; //set SKE as 0
SMP=0; //Set the smp as 0
SSPCON=0x20; //enable sspen and enable master mode fosc/4
TRISC=0x10; //set SDI as input and scl and sco as output
TRISB=0x07; //set the port b as input
PORTB=0x00; //clear the portb
TRISD=0x00; //set pord d as output
PORTD=0x00; //clear the portd
}
void switchp()
{

if(INC) 
{
data++; //post increment of data
__delay_ms(50); //delay
} 
if(DEC)
{
data--; //post increment of data
__delay_ms(50); //delay
}
if(SEND)
{
spiwrite(data); //send the data to the spi write
__delay_ms(50);
}
PORTD=data; //send the data to portd as indicator
}

void spiwrite(unsigned int i)
{
SSPBUF=i; //data will be sent to sspbuf
__delay_ms(20); //delay
}