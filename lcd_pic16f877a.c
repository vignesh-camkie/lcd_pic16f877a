#include <xc.h>

#pragma config FOSC = HS      
#pragma config WDTE = OFF      
#pragma config PWRTE = OFF     
#pragma config BOREN = ON      
#pragma config LVP = OFF      
#pragma config CPD = OFF       
#pragma config WRT = OFF      
#pragma config CP = OFF   

#define _XTAL_FREQ 4000000

#define RS RD2          
#define EN RD3          
#define D4 RD4        
#define D5 RD5
#define D6 RD6
#define D7 RD7

void init(void);
void Lcd_command(unsigned char);
void Lcd_Data(unsigned char);
void delay_ms(unsigned int);
void LcdOutput(unsigned int);

void main() {
    unsigned char num1 = 221,num2 = 95;
    int sum;

    init();

    Lcd_command(0x80);         
    LcdOutput(num1);
    Lcd_command(0x83);       
    Lcd_Data('+');
    Lcd_command(0x84);        
    LcdOutput(num2);
    Lcd_command(0x87);        
    Lcd_Data('=');
    Lcd_command(0x88);        
    sum = num1 + num2;
    LcdOutput(sum);
    while (1);                
}

void init(void) {
    TRISD = 0x00;              
    Lcd_command(0x02);        
    Lcd_command(0x28);        
    Lcd_command(0x0C);         
    Lcd_command(0x06);       
    Lcd_command(0x01);        
    delay_ms(10);
}

void Lcd_command(unsigned char cmd) {
    RS = 0;                  
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0);
    EN = 1;                 
    __delay_ms(2);             
    EN = 0;
    PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0); 
    EN = 1;                   
    __delay_ms(2);
    EN = 0;
}

void Lcd_Data(unsigned char data) {
    RS = 1;                   
    PORTD = (PORTD & 0x0F) | (data & 0xF0); 
    EN = 1;                   
    __delay_ms(2);
    EN = 0;
    PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0); 
    EN = 1;                  
    __delay_ms(2);
    EN = 0;
}

void LcdOutput(unsigned int num) {
    unsigned char digits[5];
    unsigned char i = 0;

    if (num == 0) {
        Lcd_Data('0');
        return;
    }
    while (num > 0) {
        digits[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0) {
        Lcd_Data(digits[--i]); 
    }
}

void delay_ms(unsigned int ms) {
    while (ms--) {
        __delay_ms(1);
    }
}

