
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
#define _XTAL_FREQ 6000000 //Define the Oscilator 6MHz
void init();//Declare the inti function with its return type              
void lcdcmd(unsigned char);  //Declare the lcdcmd function with its return type   
void lcddata(unsigned char);//Declare the lcddata function with its return type  
char x,i,j;//Declare the required variables     
unsigned char array[18]={"MAGESH"};//Declare the String in the array{} array
unsigned char cmd1[6]={0x82,0x83,0x84,0x85,0x86,0x87};//Declare the array for the POsition 
unsigned char cmd2[6]={0xCD,0xCC,0xCB,0xCA,0xC9,0xC8};//Declare the array for the POsition 
void main()//Definition for main function
{
    init(); //calling the init function
    for(x=0;x<6;x++)//intialize the for loop with condition 
    {
     lcdcmd(cmd1[x]);/*send the character in the cmd1[] 
                      to the lcdcmd as arugement*/
     __delay_ms(100);//delay
     lcddata(array[x]);/*send the character in the cmd[] Array
                      to the lcdcmd as arugement*/
      __delay_ms(100);
      
    }
    for(j=0;j<6;j++)//intialize the for loop with condition 
    {
     lcdcmd(cmd2[j]);/*send the cmd2 array character as argument to
                      * lcdcmd function*/
     __delay_ms(100);
     lcddata(array[j]);/*send the Array array character as argument to
                      * lcdcmd function*/
      __delay_ms(100);
    }
      while(1)
      {
      lcdcmd(0x1F);    
      }
}
void init()          
{
    TRISC=0x00;//Setting PORTC as a OUTPUT   
    TRISD=0x00;//Setting PORTD as a OUTPUT         
    lcdcmd(0x30);/*initialize the lcd as a
                  * 8 bit Mode*/ 
    __delay_ms(100); 
     lcdcmd(0x30);/*initialize the lcd as a
                  * 8 bit Mode*/    
    __delay_ms(100); 
     lcdcmd(0x30);  /*initialize the lcd as a
                  * 8 bit Mode*/  
     lcdcmd(0x38);  
     lcdcmd(0x0C);/*Turn OFF the cursor */
}
void lcdcmd(unsigned char i)
{
    RC3=0;//Setting RS pin as a 0           
    PORTD=i;//Allocate the data to the PORTD       
    RC0=1;//Enabling enable pin       
    __delay_ms(10);  
    RC0=0;//Disabling enable pin             
    __delay_ms(10);  
}
void lcddata(unsigned char i)   
{
    RC3=1;//Setting RS pin as a 1       
    PORTD=i;//Allocate the data to the PORTD          
    RC0=1;//Enabling enable pin           
    __delay_ms(10);  
    RC0=0;//Disabling enable pin          
    __delay_ms(10);  
}

