#include"guard.h"
#define _XTAL_FREQ 16000000
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0
 void i2c_master_init(const unsigned long baud)
 {
     SSPCON=0x28;
     SSPCON2=0x00;
     SSPADD=(_XTAL_FREQ/(4*baud))-1;
     SSPSTAT=0x00;
     TRISC3=1;
     TRISC4=1;    
 }
 void i2c_master_start()
 {
     i2c_master_wait();
     SEN=1;
 }
 void i2c_master_stop()
 {
     i2c_master_wait();
     PEN=1;
 }
 void i2c_master_wait()
 {
     while((SSPSTAT&0x04)||(SSPCON2&0x1F));
 }
 void i2c_nack(void)
 {
     ACKDT=1;
     i2c_master_wait();
     ACKEN=1;
 }
 void i2c_ack(void)
 {
     ACKDT=0;
     i2c_master_wait();
     ACKEN=1;
 }
 void i2c_master_repeatedstart()
 {
     i2c_master_wait();
     RSEN=1;
 }
 unsigned char i2c_read_byte(void)
 {
     i2c_master_wait();
     RCEN=1;
     while(!SSPIF);
     SSPIF=0;
     i2c_master_wait();
     return SSPBUF; 
 }
 unsigned char i2c_master_write(unsigned char data)
 {
     i2c_master_wait();
     SSPBUF=data;
     while(!SSPIF);
     SSPIF=0;
     return ACKSTAT;
 }
 void eeprom_write(unsigned int ad,unsigned char data)
 {
     i2c_master_start();
     while(i2c_master_write(EEPROM_Address_W));
        i2c_master_repeatedstart();
     while(i2c_master_write(ad>>8));
     while(i2c_master_write((unsigned char)ad));
     while(i2c_master_write(data));
     i2c_master_stop();
 } 
 unsigned char eeprom_read(unsigned int add)
 {
     unsigned char data;
     i2c_master_start();
     while(i2c_master_write(EEPROM_Address_W));
         
     while(i2c_master_write(add>>8));
     while(i2c_master_write((unsigned char)add));
     i2c_master_repeatedstart();
     while(i2c_master_write(EEPROM_Address_R));
     data=i2c_read_byte();
     i2c_nack();
     i2c_master_stop();
     return data; 
 }
 