
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

#include <xc.h> //INCLUDE THE NECCESSARY HEADER FILE
#define _XTAL_FREQ 6000000 //intialize the clock frequency
void init(void); //declar the function
void lcdcmd(unsigned char); //declar the function
void lcddata(unsigned char); //declar the function
void lcdoutput(unsigned int); //declar the function
void delay(unsigned int);//declar the function
void lcdoutput1(unsigned long); //declar the function
unsigned char n,j; //declar ethe variable
unsigned char k[10],l[4]; //declare the char array
unsigned char a[10]={"CALIB:"},b[10]={"ORG DATA:"}; //declare the compile time char array
unsigned int lowvalue,highvalue,m,delaycount,fr,thousand,hundred,tens,ones,c; 
unsigned long value,voltage; //declar the lon variable

void main()
{
    init(); //call the init function
        
    while(1) //infinate while loop
    { 
        ADCON0|=0x04; //start the adc converstion
        while(ADCON0&0x04); //check the condition 0
        lowvalue=ADRESL; //store the ADRESL value to the low value
        highvalue=ADRESH; //store the ADRESH value to the high value
        value=((unsigned long)highvalue<<8)+(unsigned long)lowvalue; //lift shift the high value and add store in the value
        lcdcmd(0x80); //intializ the location of the display to start print
        for(fr=0;fr!=9;fr++) //for loop untill fr not equal to 9
        {
            lcddata(b[fr]); //data will be sent to the lcddata
        }
        lcdoutput1(value); //value will be sent to the lcdoutput1
        for(fr=0;fr!=4;fr++) //for lopp for untill th fr not equal to 4
            lcddata((0x30)+l[fr]); //the data will convert int char and sent to print
        delay(1000); //delay
        voltage=value*100/1023; //calibration
        lcdcmd(0xC0); //intialize the location of the display
        for(fr=0;fr!=6;fr++) //for loop untill the fr not equal to 6
        {
            lcddata(a[fr]); //a[] will be sent to the lcd data
        }
        lcdoutput(voltage); //votage will be sent to convert
        delay(1000);
    }
}

void init(void)
{
    TRISA=0x04; //set the AN2 will be set as input
    TRISC=0x00; //PORTC will be set as output
    TRISD=0x00; //PORTD will be set as output
    ADCON0=0x91; //ADCONo will be turn on the adc and select the channel and clock convertion
    ADCON1=0x82; //ADCON1 will be used for formet select and port config
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    lcdcmd(0x38); //select the font and no of line will be used.
    lcdcmd(0x0C); //to turn on the display and turn off the curser 
}

void lcdoutput(unsigned int i)
{
    unsigned char s; //local variable of s
    j=1; //j will be set as 1
    m=i; //i will store in the m
    while(m!=0) //while loop untill the m not equal to 0
    {
        s=m-(m/10)*10; //calculate and store in the s
        k[j]=s; //s value will be store in the array of k
        j++; //pre increment
        m=m/10; //m will be divided by 10 and store in the m
    }
    k[j]='\0'; //k[last] will set as null 
    j--; //pre decriment
    if(k[2]>0) //condition untill the k[2] bigger the 0
    {
        n=0x30+k[2]; //k of 2 will be convert to char
        lcddata(n); //k of n will be send to print
    }
    else
    {
        lcddata(0x20); //0x20 is equlant value of space
    }
        n=0x30+k[1]; //k of 1 will be converted into char
        lcddata(n); //n will sent to lcddata
        n=0x56; //this is a 0x56 is equalent HEX value of V
        lcddata(n); //n will be sent to the lcddata
}

void lcdoutput1(unsigned long i) 
{
l[3]=i%10; //i will be modulo by 10
i/=10; //i will be divided by 10
l[2]=i%10; //i will be modulo by 1
i/=10; //i will be divided by 10
l[1]=i%10; //i will be modulo by 1
i/=10; //i will be divided by 10
l[0]=i; //i will be modulo by 1
}


void lcdcmd(unsigned char i)
{
    PORTC&=~0x08; //RS pin will be set as 0
    PORTD=i; //i will be give to the PORTD
    PORTC|=0x01; //enable pin will set as 1
    PORTC&=~0x01; //enable pin will set as 0
    delay(100); //delay
}

void lcddata(unsigned char i)
{
    PORTC|=0x08; //RS pin will be set as 1
    PORTD=i; //i will be sent to the PORTD
    PORTC|=0x01; //enable pin will set as 1
    PORTC&=~0x01; //enable pin will set as 0
    delay(100);
}

void delay(unsigned int delaycount)
{
    while(--delaycount); //delay count
}