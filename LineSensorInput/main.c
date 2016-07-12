/*
 * MLlinesensor128.cpp
 *
 * Created: 14-12-2015 20:33:00
 *  Author: Sandeep
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "USART_128.h"

uint8_t line[7],i,j;

int main(void)
{
	USART_Init(12,0);
		
	DDRA &= ~(0b11111111);					//line sensor
	//DDRA |= (0b00000011);					//line sensor power
	DDRF |= (0b00000111);					//left motors			0th pin front 
	DDRD |= (0b00000111);					//right motors
	PORTF |= (0b000000000);
	PORTD |= (0b000000000);
	//PORTA |= (0b00000001);
	
	USART_InterruptEnable(0);				//for USART receive
	
	/////////PWM
	
	DDRB |= (1<<PB5 | 1<<PB6 | 1<<PB7);
	TCCR1A |= (1<<COM1A1 | 1<<COM1A0);
	TCCR1A |= (1<<COM1B1 | 1<<COM1B0);
	TCCR1A |= (1<<COM1C1 | 1<<COM1C0);
	TCCR1A |= (1<<WGM11);
	TCCR1A &= ~(1<<WGM10);
	TCCR1B |= (1<<WGM13 | 1<<WGM12);
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11 | 1<<CS12);
	
	ICR1 = 60000;       	//=100%
//	int per = 50;		//power %
//	int k = (per*600);	//taking total=60000
	OCR1A = 30000;		//right motors
	OCR1B = 30000;		//left motors
	OCR1C = 30000;
	
	////////PWM END
	
	
	/*		
	while(1)								//for testing of usart
	{
		USART_TransmitNumber('1',0);
		USART_Transmitchar(0x0D,0);
			
	}
	*/


	while(1)								//For sending input from line sensor
	{
		
		j=6;												
		for(i=0;i<7;i++)
		{
			if(bit_is_set(PINA,i))
			{
				line[j--] = 1;					//1 = white line
			}
			else
			{
				line[j--] = 0;					//0 = black
			}
			
			
		}
		
	/*	
		for(i=0;i<7;i++)
		{
			USART_TransmitNumber(line[i],0);
			USART_Transmitchar(' ',0);
		}
		USART_Transmitchar(0x0D,0);					//0x0D = carriage return
	*/	
	}
	
	/*	
	while(1)
	{}
	*/
		
}

ISR(USART0_RX_vect)								//USART receive and motor run and transmit data
{
	char data = USART_Receive(0);
	//USART_Transmitchar(data, 0);
	//USART_Transmitchar(' ',0);
	
	
	/////////////////////////////////////without PWM
	/*
	if(data == 't')											
	{
		PORTA = (0b00000101);
		PORTD = (0b00000101);
	}
	else if(data == 'x')
	{
		PORTA = (0b00000110);
		PORTD = (0b00000110);
	}
	else if(data == 'o')
	{
		PORTA = (0b00000101);
		PORTD = (0b00000100);
	}
	else if(data == 's')
	{
		PORTA = (0b00000100);
		PORTD = (0b00000101);
	}
	else
	{
		PORTA = (0b00000011);
		PORTD = (0b00000011);
	}
	*/
	
	/////////////////////////////////////with PWM

	if(data == 'o')								//turn right						
	{
		OCR1B = 0;							//right motor off
		PORTA = (0b00000101);
		PORTD = (0b00000101);
		
		USART_TransmitString("0 1~",0);					//transmit motor input
		/*for(i=0;i<7;i++)						//transmit line sensor readings
		{
			USART_TransmitNumber(line[i],0);
			USART_Transmitchar(' ',0);
		}
		*/USART_Transmitchar(0x0D,0);					//0x0D = carriage return
		
	}
	else if(data == 's')
	{
		OCR1A = 0;							//left motor off
		PORTA = (0b00000101);
		PORTD = (0b00000101);
		
		USART_TransmitString("1 0~",0);					//transmit motor input
		/*for(i=0;i<7;i++)						//transmit line sensor readings
		{
			USART_TransmitNumber(line[i],0);
			USART_Transmitchar(' ',0);
		}
		*/USART_Transmitchar(0x0D,0);					//0x0D = carriage return
	}
	else
	{
		OCR1A = 30000;
		OCR1B = 30000;
		OCR1C = 30000;
		PORTA = (0b00000101);
		PORTD = (0b00000101);
		
		USART_TransmitString("1 1~",0);					//transmit motor input
		/*for(i=0;i<7;i++)						//transmit line sensor readings
		{
			USART_TransmitNumber(line[i],0);
			USART_Transmitchar(' ',0);
		}
		*/USART_Transmitchar(0x0D,0);					//0x0D = carriage return
	}
	
}