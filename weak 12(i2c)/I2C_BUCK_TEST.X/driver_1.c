#include"guard_1.h" //include the guard file
#define _XTAL_FREQ 6000000 //intialze the clock speed
#define EEPROM_Address_R 0xA1 //macro
#define EEPROM_Address_W 0xA0 //macro
 void i2c_master_init(const unsigned long baud)
 {
     SSPCON=0x28; //enable the i2c masteer mode and the seraial port sda & scl
     SSPCON2=0x00; //ready in idel postion
     SSPADD=(_XTAL_FREQ/(4*baud))-1; //baud rate generation
     SSPSTAT=0x00; //clearr the ssp status bit
     TRISC|=0x18; //set the rc3 and rc4 as input
 }
 void i2c_master_start()
 {
     i2c_master_wait(); //call the function
     SSPCON2|=0x01; //intiate start condition
 }
 void i2c_master_stop()
 {
     i2c_master_wait(); //function call
     SSPCON2|=0x04; //stop condition enable bit
 }
 void i2c_master_wait()
 {
     while((SSPSTAT&0x04)||(SSPCON2&0x1F));//check for ack or nack 
 }
 void i2c_nack(void)
 {
     ACKDT=1; //to set not acknoledge
     i2c_master_wait(); //function call
     ACKEN=1; //enable the  Acknowledge Sequence Enable bit
 }
 void i2c_master_repeatedstart()
 {
     i2c_master_wait(); //function call
          SSPCON2|=0x02; //enable the repeated start
 }
 unsigned char i2c_read_byte(void)
 {
     i2c_master_wait(); //function call
     SSPCON2|=0x08; // Initiate Repeated Start condition
     while(!SSPIF); //wait for flag set
     SSPIF=0; //clear the flag
     i2c_master_wait(); //function call
     return SSPBUF;  //return the buffer data
 }
 unsigned char i2c_master_write(unsigned char data)
 {
     i2c_master_wait(); //function call
     SSPBUF=data; //data will be sent to the buffer
     while(!SSPIF); //check the buffer flag
     SSPIF=0; //clear the flag
     return ACKSTAT; //return the acknoledgment status
 }
 void eprom_write(unsigned int ad,unsigned char data)
 {
     i2c_master_start(); //function call
     while(i2c_master_write(EEPROM_Address_W)) //function call with argument of slave address 
        i2c_master_repeatedstart(); //function call
     while(i2c_master_write(ad>>8)); //right shift the data and send the lsb data
     while(i2c_master_write((unsigned char)ad)); //sent the msb address data
     while(i2c_master_write(data)); //function call and the argument of data 
     i2c_master_stop(); //function call
 }
 unsigned char eprom_read(unsigned int add)
 {
     unsigned char data; //declre the varable
     i2c_master_start(); //function call 
     while(i2c_master_write(EEPROM_Address_W)) //call the function argument of slave address
        i2c_master_repeatedstart(); //function call
     while(i2c_master_write(add>>8)); //sent the msb data
     while(i2c_master_write((unsigned char)add)); //sent the lsb data
     i2c_master_repeatedstart(); //function call
     while(i2c_master_write(EEPROM_Address_R)); //call the function of slave address
     data=i2c_read_byte(); //call the function and return will be store in the data varable
     i2c_nack(); //sent the not acknoledgment to the slave
     i2c_master_stop(); //stop bit
     return data;  //return the data to main
 }
 