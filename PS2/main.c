#define F_CPU 8000000UL

#include <avr/io.h>
#include "USART_32.h"
#include "PS2.h"

#define maxRPM 500

enum {select, leftStick, rightStick, start, up, right, down, left}; //3rd byte
enum {leftFront2, rightFront2, leftFront1, rightFront1, triangle_up, circle_right, cross_down, square_left}; // 4th byte

int isPressed(uint8_t dataByte, uint8_t dataBit) {
	return ((dataByte & (1 << dataBit)) ? 1 : 0);
}

int main(void) {
	USART_Init(12);
	USART_TransmitString("Up and running");
	init_PS2();
	uint8_t x,y;
	
	uint8_t i=0;
		USART_Transmitchar(0xFF);
    while (1) {
		scan_PS2();
		//while(i<100)
		//{
			USART_Transmitchar(0xFF);
			//i++;
		//}
		 
		x =~ data_array[3];
		y =~ data_array[4];		
				
		 //////////////////////////////////////////////////                                 
		if(isPressed(x, up))						//For up,left,right,left
		{
			USART_Transmitchar ('u');
			//USART_Transmitchar(' ');
		} 
		else if(isPressed(x, down)) 
		{
			USART_Transmitchar('d');
			//USART_Transmitchar(' ');
		} 
		else if(isPressed(x, right)) 
		{
			USART_Transmitchar('r');
			//USART_Transmitchar(' ');
		} 
		else if(isPressed(x, left)) 
		{
			USART_Transmitchar('l');
			//USART_Transmitchar(' ');
		}
		
		//////////////////////////////////////////////////////////
		
		else if(isPressed(x, select))							//For select,leftstick,rightstick,start
		{
			USART_TransmitString("sel");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(x, leftStick))
		{
			USART_TransmitString("lS");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(x, rightStick))
		{
			USART_TransmitString("rS");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(x, start))
		{
			USART_TransmitString("str");
			//USART_Transmitchar(' ');
		}
		
		///////////////////////////////////////////////////////
		
		else if(isPressed(y, triangle_up))							//For triangle,circle,cross and square
		{
			USART_Transmitchar('t');
			////USART_Transmitchar(' ');
		}
		else if(isPressed(y, circle_right)) 
		{
			USART_Transmitchar('o');
			//USART_Transmitchar(' ');
		}
		else if(isPressed(y, cross_down))
		{
			USART_Transmitchar('x');
			//USART_Transmitchar(' ');
		}
		else if(isPressed(y, square_left))
		{
			USART_Transmitchar('s');
			//USART_Transmitchar(' ');
		}
		
		//////////////////////////////////////////////////////////
		
		else if(isPressed(y, leftFront1))							//For leftfront1,leftfront2,rightfront1,rightfront2
		{
			USART_TransmitString("lf1");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(y, leftFront2))
		{
			USART_TransmitString("lf2");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(y, rightFront1))
		{
			USART_TransmitString("rf1");
			//USART_Transmitchar(' ');
		}
		else if(isPressed(y, rightFront2))
		{
			USART_TransmitString("rf2");
			//USART_Transmitchar(' ');
		}
 
 	}
}


