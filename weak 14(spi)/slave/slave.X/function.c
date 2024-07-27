#include "guard.h" //include the guard header
#define RS RC0 //define the RC0
#define EN RC1 //define the RC1
int rdata; //declare the variable
void spi_intialize() //function call
{
TRISB=0x00; //set portb as output
PORTB=0x00; //clear the port b
SSPCON=0x24; //enable sspen and spi slave mode and ss pin controll enable
TRISC=0x18; //set as scl and sdi as input other or output
TRISA=0x20; //set A5 as input for chip select
ADCON1|=0x0E; //A/D port configuration
CKE=0; //cke set as 0
SMP=0; //smp set as o
SSPIE=1; //enable Synchronous Serial Port Interrupt Enable bit
PEIE=1; //enable  Peripheral Interrupt Enable bit
GIE=1; //enable  Global Interrupt Enable bit
}

void __interrupt() _ISR() //isr
{
if(SSPIF) //if data in buffer
{
rdata=SSPBUF; //the buffer data store in rdata
SSPIF=0; //clear the flag
}
}
void display()
{
    PORTB=rdata; //rdata will send to the portd
}
