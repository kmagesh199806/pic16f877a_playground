#include<xc.h> //include the neccessary header file
#include"guard.h" //include the user defined header file
#define _XTAL_FREQ 6000000 //intialize the clock
char msg1[5]={"TIME:"}; //declare the char array and inatialization
char msg2[5]={"DATE:"}; //decalare the char array and inatialization
char am[2]={"AM"},pm[2]={"PM"}; //decalare the char array and inatialization
int i,j,k,l,var; //declare the variable
int sec=55,min=59,hour=11,date=8,month=04,year=24,day=2; //declaration of variable
char sec1,sec2,min1,min2,hour1,hour2,date1,date2,month1,month2,year1,year2;

void init(void)
{
    TRISD=0x00; //set the portd as output
    TRISC=0x18; //set the porc input and output
    PORTD=0x00; //clear the portd 
    lcdcmd(0x30); //function set  command 8bit intialization
      __delay_ms(5);
      lcdcmd(0x30); //function set  command 8bit intialization
      __delay_ms(5);
      lcdcmd(0x30); //function set  command 8bit intialization
      lcdcmd(0x38); //function set and no line in diasplay
      lcdcmd(0x0C); //display on curser and blink will turn off
      lcdcmd(0x01); //clear the display
}
void lcdcmd(unsigned char i)
{
    PORTC&=~0x04; //set Rs pin as 0
    PORTD=i; //i data will be sent to PORTD
    PORTC|=0x02; //enable set as 1
    __delay_ms(5); 
    PORTC&=~0x02; //enable set as 0
    __delay_ms(5);
}
void lcddata(unsigned char i)
{
    PORTC|=0x04; //rs pin will set as 1
    PORTD=i; //i data will be sent to the port d
    PORTC|=0x02; //enable pin will be set to 1
    __delay_ms(5);
   PORTC&=~0x02; //enable pin set as 0
    __delay_ms(5);
}
void i2cinit(const unsigned long feq_k)
{
    SSPCON=0x28; //intialize the 0010 1000 to sspcon register
    SSPSTAT=0x00; //clear the sspstat register
    SSPCON2=0x00; //clear the sspcon2 register
   SSPADD = (_XTAL_FREQ/(4*feq_k*100))-1; //set the baurd rate
}
void i2cwait()
{
    while(SSPCON2 & 0x1F || SSPSTAT & 0x04); //check the comunnication line
}
void i2cstart()
{
   i2cwait(); //wait for any opration going for bus line
   SSPCON2|=0x01; //set the SEN for start bit
}
void i2cstop()
{ 
    i2cwait(); //wait for any opration going for bus line
    SSPCON2|=0x04; //enable the PEN for stop bit
}
void i2cwrite(unsigned char temp)
{
    i2cwait(); 
    SSPBUF=temp; //the data will be sent to the SSPBUF
}
int i2cread(int ack)
{
    int value; //variable declaration
    i2cwait(); 
    SSPCON2|=0x08; //enable reciver mode for I2c
    i2cwait();
    value=SSPBUF; //the buffer data for rtc eill store in the value
    i2cwait();
    ACKDT=(ack)?0:1; //check the ack
    SSPCON2|=0x10; //Initiate Acknowledge sequence on SDA and SCL pins
    return value; //return the value
    
}
int dec2bcd(int temp)
{ 
return ((temp/10)<<4)+(temp%10); //seprate the lsb and msb msb will be left shift 
                                 //four times and add to the lsb

}
int bcd2dec(int temp)
{ 
return ((temp>>4)*10)+(temp&0x0F); //right shift the data four times 
                                   //and operat with value of 0000 1111
                                   //add the msb and lsb
}
void timeset(void)
{
    i2cstart(); //call the start bit
    i2cwrite(0xD0); //write the address of RTC
    i2cwrite(0); //set the mode as a write for the write
    i2cwrite(dec2bcd(sec)); //convert to decimal to binary and write
    i2cwrite(dec2bcd(min)); //convert to decimal to binary and write
    i2cwrite(0x60|(dec2bcd(hour))); //convert to decimal to binary and write
                                    //and set the AM/PM 12/24
    i2cwrite(dec2bcd(day)); //convert to decimal to binary and write
    i2cwrite(dec2bcd(date)); //convert to decimal to binary and write
    i2cwrite(dec2bcd(month)); //convert to decimal to binary and write
    i2cwrite(dec2bcd(year)); //convert to decimal to binary and write
    i2cstop(); //call the stop bit
}
void update(void)
{
    i2cstart(); //call the start bit
    i2cwrite(0xD0); //set the address
    i2cwrite(0); //set the mode of write
    i2cstop(); //call the stop bit
    i2cstart(); //call the start bit
    i2cwrite(0xD1); //set the address
    sec=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    min=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    var=i2cread(1); //read the data and store in the variable
    hour=(bcd2dec(0x1F&var)); //read the data conv to and store in variable
    day=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    date=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    month=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    year=(bcd2dec(i2cread(1))); //read the data conv to and store in variable
    i2cstop(); //call the stop bit
    i2cstart(); //call the start bit
    i2cwrite(0xD1); //set the address
    i2cread(1); //call the read function ack
    i2cstop(); //call the stop bit
}
void lcd()
{
          update(); //call the update function 
        sec1=sec/10; //seperate msb from the data
        sec2=sec%10; //seperate the lsb from the data
        min1=min/10; //seperate msb from the data
        min2=min%10; //seperate the lsb from the data
        hour1=hour/10; //seperate msb from the data
        hour2=hour%10; //seperate the lsb from the data
        date1=date/10; //seperate msb from the data
        date2=date%10; //seperate the lsb from the data
        month1=month/10; //seperate msb from the data
        month2=month%10; //seperate the lsb from the data
        year1=year/10; //seperate msb from the data
        year2=year%10;  //seperate the lsb from the data
        
        lcdcmd(0x80); //set the location of the lcd
        for(i=0;i<5;i++) 
            lcddata(msg1[i]); //print "TIME" in lcd
        lcddata(hour1+'0'); //print hour on lcd
        lcddata(hour2+'0'); //print hour on lcd
        lcddata(0x2D); //print '-' symbol
        lcddata(min1+'0'); //print minute on lcd
        lcddata(min2+'0'); //print minute on lcd
        lcddata(0x2D); //print '-' symbol
        lcddata(sec1+'0'); //print second on lcd
        lcddata(sec2+'0'); //print second on lcd
        lcddata(' '); //print the white space
        if (var&0x20) //check for AM/PM
        {
            for(i=0;i<2;i++) 
            {
                lcddata(pm[i]); //print the pm
            }
        }
        else
        {
            for(i=0;i<2;i++)
            {
                lcddata(am[i]); //print am
            }
        }
        lcdcmd(0xC0); //set the location of the lcd
        for(i=0;i<5;i++) 
            lcddata(msg2[i]); //print the "TIME:" in lcd
        lcddata(date1+'0'); //print the data on lcd
        lcddata(date2+'0'); //print the data on lcd
        lcddata(0x2D); //print the '-' symbol
        lcddata(month1+'0'); //print the data on lcd
        lcddata(month2+'0'); //print the data on lcd
        lcddata(0x2D); //print the '-' symbol
        lcddata(year1+'0'); //print the data on lcd
        lcddata(year2+'0'); //print the data on lcd
        lcddata(' '); //print the space
        switch(day){
                case 1:lcddata('S'); //switch case for DAY print in the lcd
                break; 
                case 2:lcddata('M');
                break;
                case 3:lcddata('T');
                break;
                case 4:lcddata('W');
                break;
                case 5:lcddata('T');
                break;
                case 6:lcddata('F');
                break;
                case 7:lcddata('S');
                break;
        }
}