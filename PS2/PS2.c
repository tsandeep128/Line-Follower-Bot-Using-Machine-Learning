#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//#include "macros.h"
#include "PS2.h"

//#include "LCD.c"
//#include "remote.c"
//#include "initialize.c"



void init_PS2()
{

//    USART_TransmitString("In ps2 init");
//    NewLine();
	// All pins o/p except MISO, Pull up enabled on MISO
	SPI_DDR |= (_BV(MOSI_PIN)) | _BV(SCK_PIN) | _BV(SS_PIN);
	SPI_DDR &= ~(_BV(MISO_PIN));
	SPI_PORT |= _BV(MISO_PIN);
	// SPI interrupt disabled, SPI enable, will be enabled after initialization
	// LSB first, Master Mode,
	// First edge of Clock- Falling
	// Sample on Trailling Edge
	// Clock Frequency 500kHz for 8MHZ crystal
	SPCR= 0b01111101;

// PS2 initiallization
	char  PS2_CONFIGMODE[5]= {0x01, 0x43, 0x00, 0x01, 0x00};
	char  PS2_ANALOGMODE[9]= {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
	char  PS2_SETUPMOTOR[9]= {0x01, 0x4D, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff};
//	char  PS2_RETURNPRES[9]= {0x01, 0x4f, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00};
	char  PS2_EXITCONFIG[9]= {0x01, 0x43, 0x00, 0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};
//    USART_TransmitString("Before config mode");
//    NewLine();
// Enter Config mode
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_CONFIGMODE,5);		
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);
		/*for(spi_display_i=0; spi_display_i<10; spi_display_i++)
		{
			display_hex(data_array[spi_display_i],0,(spi_display_i/5)+1, 3*(spi_display_i%5)+1); //1,4,7,10,13
		}*/

	_delay_ms(1);
//    USART_TransmitString("After Config mode");
//    NewLine();
// Enter Analog Mode
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_ANALOGMODE,9);		
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);
		/*for(spi_display_i=0; spi_display_i<10; spi_display_i++)
		{
			display_hex(data_array[spi_display_i],0,(spi_display_i/5)+1, 3*(spi_display_i%5)+1); //1,4,7,10,13
		}*/
//    USART_TransmitString("After Analog mode");
//    NewLine();
	_delay_ms(1);
//    USART_TransmitString("Before setup motor mode");
//    NewLine();
// Setup Motor
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_SETUPMOTOR,9);		
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);
/*		for(spi_display_i=0; spi_display_i<10; spi_display_i++)
		{
			display_hex(data_array[spi_display_i],0,(spi_display_i/5)+1, 3*(spi_display_i%5)+1); //1,4,7,10,13
		}*/
	_delay_ms(1);
//	    USART_TransmitString("After motor setup");
//	    NewLine();
//		    USART_TransmitString("before exit config mode");
//		    NewLine();
// Exit Config
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_EXITCONFIG,9);
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);
		/*for(spi_display_i=0; spi_display_i<10; spi_display_i++)
		{
			display_hex(data_array[spi_display_i],0,(spi_display_i/5)+1, 3*(spi_display_i%5)+1); //1,4,7,10,13
		}*/
	_delay_ms(1);
//	    USART_TransmitString("After exit config mode");
//	    NewLine();

// Enter values in PS2_POLLBUTTON
	volatile char ps2_init_array[9]= {0x01, 0x42, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00};
	volatile int ps2_init_i;
	for(ps2_init_i=0; ps2_init_i<10; ps2_init_i++)
	{
		PS2_POLLBUTTON[ps2_init_i] = ps2_init_array[ps2_init_i];
	}
}




void scan_PS2()
{
//	    USART_TransmitString("before scan PS2");
//	    NewLine();
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;	
        b=0;
	c=0;
	SPI_send_array(PS2_POLLBUTTON,9);
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(2);	
//	    USART_TransmitString("after scan ps2");
//	    NewLine();
}

void PS2_start_vibrate()
{
	PS2_POLLBUTTON[4]= 0xff;
	PS2_POLLBUTTON[3]= 0xff;
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_POLLBUTTON,9);
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);	
	
}

void PS2_stop_vibrate()
{
	PS2_POLLBUTTON[3]= 0x00;
	PS2_POLLBUTTON[4]= 0x00;
	SPI_PORT &= ~(_BV(SS_PIN));	//ATT held low	
	a=0;
	b=0;
	c=0;
	SPI_send_array(PS2_POLLBUTTON,9);
	SPI_PORT |= _BV(SS_PIN);	// Driving Attention Low
	_delay_ms(1);	
}





char SPI_send(char send_x)
{
	
	SPDR= send_x;
	while(!(SPSR & _BV(SPIF)))
	{
		;
	}		
	_delay_us(30);
	send_x= SPDR;

	return(send_x);
}

void SPI_send_array(char *a, char cmd_length)
{
//	    USART_TransmitString("In SPI send");
//	    NewLine();
	int spi_send_array_i;
	for(spi_send_array_i=0; spi_send_array_i<cmd_length; spi_send_array_i++)
	{
		data_array[spi_send_array_i]= SPI_send(*a);
		a++;
	}
//	    USART_TransmitString("after spi send");
//	    NewLine();
}
