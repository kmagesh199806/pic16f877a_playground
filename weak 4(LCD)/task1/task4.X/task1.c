
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

#include <xc.h>     //import headder file
#define _XTAL_FREQ 6000000      //intialize the clock speed
void init(void);        //declaration of function
void lcdcmd(unsigned char); //declaration of function
void lcddata(unsigned char);    //declaration of function
void lcdoutput(unsigned int); //declaration of function
unsigned char j,k[10],equal,plus,min,n;     //declare the charector variable
unsigned int num1,num2,m,sum;       // declare the int variable
void main()
{
    init();         //call the init function
    num1=100;      //store the 100 value to the num1
    num2=200;       //store the 200 value toi the num2
    equal='=';      //assien the car = to the equal
    plus='+';   //assign the char + to the plus variable
    min='-';    //assign the  char - to the min
    lcdcmd(0x80);   //call the lcdcmd function and give the argument of 0x80
    lcdoutput(num1);    //call the lcdoutput function and give the argument of num1
    lcddata(min);   //call the lcdddata function and give the argument of min
    lcdoutput(num2);    //num2 will be given to the lvdoutput
    lcddata(equal);     //equla will be given the the lcddata
    if(num1>=num2)  //check the conditon num1 greater the num2
    {   //will true
     sum=num1-num2; //num1-num2 and store in the sum
     lcddata(plus); //char plus will be give to the lcddata
     lcdoutput(sum);    //sum willbe sent to the lcdoutput
    }
    else         //else
    {
        sum=num2-num1;  //sub num2-num1 and store in sum   
        lcddata(min);   //min will be sent to the lcddata
        lcdoutput(sum); //sum will be sent to the lcdoutput
    }
    while(1);
}
void init()
{
TRISC=0x00; //set TRISC set as output
TRISD=0x00; //set TRISD set as output
lcdcmd(0x30);   //function set command
__delay_ms(100);    //delay
lcdcmd(0x30);   //function set command
__delay_ms(100);    //delay
lcdcmd(0x30);   //function set command
lcdcmd(0x30);   //set number line of display and font
lcdcmd(0x0C);   //set for curser off and display on
}
void lcdoutput(unsigned int i)  //lcdoutput function
{
    unsigned char s,j=1;    //intiallize the local variable
    m=i;    //i valu store in the m
    while(m!=0)     //while loop for untill m not equal 0
    {
        s=m-((m/10)*10);    //separate the last integer value
        k[j]=s;     //store the seperated value to the k[j] array
        j++;    //post increment
        m=m/10; //remove the last intiger of the whole integer
    }
    k[j]='\0';  //last array of the k[j] will be set as null]
    j-=1;   //j will be minus 1 and store in the j
    while(j!=0) //wile loop for untill the j not equal to 0
    {
        n=0x30+k[j];    //the separated integer will be convert into ascii
        lcddata(n);     //that ascii value will be give to the lcddata
        j--;        //post decrement
    }
}
void lcdcmd(unsigned char i)    //lcd command function
{
    PORTC&=~(0x08); //RC3 will be set as 0
    PORTD=i;    //i will be sent to the PORTD
    PORTC|=(0x01);  //enable pin will be set as high
    __delay_ms(100); //delay
    PORTC&=~(0x01);//enable pin will be seat as low
   
}
void lcddata(unsigned char i)   //lcddata function
{
    PORTC|=(0x08);  //rc3 will be set as 1
    PORTD=i;    //i will be sent to the port D
    PORTC|=(0x01);  //enable pin will be set as 1
    __delay_ms(100);    //delay
    PORTC&=~(0x01);     //enable pin will be set as 0
    
}
