#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7


#include <avr/io.h>
#include <stdio.h>
#include "lcd/lcd.h"

volatile unsigned int result;


int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFf;
		
	
	ADMUX = 0b01000101;
	ADCSRA = 0b10000000;
	int result = 1;
	float voltage;
	char cs[30] ;
	
	Lcd4_Init();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("Voltage: ");
	
	
    while (1) 
    {
		
		ADCSRA |= (1 << ADSC);
		
		while(ADCSRA & (1 << ADSC)){;}
			
		result = (ADCL) | (ADCH << 8);
		
		voltage = result*5.0/1024;
		
		Lcd4_Set_Cursor(1,10);
		sprintf(cs, "%.2f", voltage);
		
		
		Lcd4_Write_String(cs);
    }
}

