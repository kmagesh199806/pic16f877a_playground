
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
#define _XTAL_FREQ 6000000
void init(void); //declar the function
void lcdcmd(unsigned char); //declar the function
void lcddata(unsigned char); //declar the function
void lcdoutput2(unsigned long);
void delay(unsigned int);//declar the function
void lcdoutput1(unsigned long); //declar the function
unsigned char n,j; //declar ethe variable
unsigned char k[10],l[4],o[4]; //declare the char array
unsigned char a[10]={"CHANNEL 0:"},b[10]={"CHANNEL 1:"}; //declare the compile time char array
unsigned int lowvalue,highvalue,m,delaycount,fr,c; 
unsigned long value,voltage; //declar the lon variable

void main()
{
    init();
    while(1)
    {
        ADCON0&=0xC7;
        ADCON0|=0x04; //start the adc converstion
        while(ADCON0&0x04); //check the condition 0
        lowvalue=ADRESL; //store the ADRESL value to the low value
        highvalue=ADRESH; //store the ADRESH value to the high value
        value=((unsigned long)highvalue<<8)+(unsigned long)lowvalue; //lift shift the high value and add store in the value
        lcdcmd(0x80); //intializ the location of the display to start print
        for(fr=0;fr!=10;fr++) //for loop untill fr not equal to 9
        {
            lcddata(a[fr]); //data will be sent to the lcddata
        }
        lcdoutput1(value); //value will be sent to the lcdoutput1
        for(fr=0;fr!=4;fr++) //for lopp for untill th fr not equal to 4
        {
            if(l[fr]==' ') //check thee l of fr equal to space
                lcddata(l[fr]); //directly sent to the lcddata
            else
                lcddata((0x30)+l[fr]); //the data will convert int char and sent to print
        }
        delay(1000); //delay
        
        ADCON0|=0x10;
        ADCON0|=0x04; //start the adc converstion
        while(ADCON0&0x04); //check the condition 0
        lowvalue=ADRESL; //store the ADRESL value to the low value
        highvalue=ADRESH; //store the ADRESH value to the high value
        value=((unsigned long)highvalue<<8)+(unsigned long)lowvalue; //lift shift the high value and add store in the value
        lcdcmd(0xC0); //intializ the location of the display to start print
        for(fr=0;fr!=10;fr++) //for loop untill fr not equal to 9
        {
            lcddata(b[fr]); //data will be sent to the lcddata
        }
        voltage=value*337/1023; //calibrate the value
        lcdoutput2(voltage); //voltage value will be sent to the lcdoutput function
        CCPR1L=(voltage)>>2;
        CCP1CON=(CCP1CON&0x0C)+((voltage&0x30)<<4);
        for(fr=0;fr!=4;fr++) //for lopp for untill th fr not equal to 4
            if(o[fr]==' ')
                lcddata(o[fr]);
            else
            lcddata((0x30)+o[fr]); //the data will convert int char and sent to print
        delay(1000);  //delay
        
    }
}

void init(void)
{
    TRISA=0x05; //set the AN2 will be set as input
    TRISC=0x00; //PORTC will be set as output
    TRISD=0x00; //PORTD will be set as output
    ADCON0=0x81; //ADCONo will be turn on the adc and select the channel and clock convertion
    ADCON1=0x82; //ADCON1 will be used for formet select and port config
    CCP1CON=0x3C; //to enter to pwm mode
    CCPR1L=0x2E; //to set the 2 bit value and 
    T2CON=0x06; //timer 2 turn on and set pre scaler as 16
    PR2=0x05E; //period will set as 0010 1111
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    delay(100);
    lcdcmd(0x30); //intialize the lcd
    lcdcmd(0x38); //select the font and no of line will be used.
    lcdcmd(0x0C); //to turn on the display and turn off the curser 
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
if(l[0]==0) //l[0] will assign space
{
    l[0]=' '; //l[0] will assign space
    if(l[1]==0) //check l of 1 equal to 0
    {
        l[1]=' '; //l[1] will assign space
        if(l[2]==0) //check l of 2 equal to 0
        {
            l[2]=' '; //l[2] will assign space
        } 
    }
}
}

void lcdoutput2(unsigned long i) 
{
o[3]=i%10; //i will be modulo by 10
i/=10; //i will be divided by 10
o[2]=i%10; //i will be modulo by 1
i/=10; //i will be divided by 10
o[1]=i%10; //i will be modulo by 1
i/=10; //i will be divided by 10
o[0]=i; //i will be modulo by 1
if(o[0]==0) //o[0] will check 0
{
    o[0]=' '; //o[0] will assign space
    if(o[1]==0) //o[1] will check 0
    {
        o[1]=' '; //o[1] will assign space
        if(o[2]==0) //o[2] will check 0
        {
            o[2]=' '; //o[2] will assign space
        } 
    }
}
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