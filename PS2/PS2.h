//-- PS2 button configuration in analog mode without any pressure return--//
/*
Byte no		   Return Value
0			 FF
1			 73
2			 5A

3.0(0000 000x)		SELECT
3.1(0000 00x0)		L Joystick Switch
3.2(0000 0x00)		R Joystick Switch
3.3(0000 x000)		START
3.4(000x 0000)		(Left) UP
3.5(00x0 0000)		(Left) Right
3.6(0x00 0000)		(Left) Down
3.7(x000 0000)		(Left) Left

4.0(0000 000x)		Left Front- 2
4.1(0000 00x0)		Right Front- 2
4.2(0000 0x00)		Left Front- 1
4.3(0000 x000)		Right Front- 1
4.4(000x 0000)		(Right) UP 'Triangle'
4.5(00x0 0000)		(Right) Right 'Circle'
4.6(0x00 0000)		(Right) Down 'Cross X'
4.7(x000 0000)		(Right) Left 'Square'

5 			Right Joystick- X axis
6			Right Joystick- Y axis
7			Left Joystick- X axis
8			Left Joystick- Y axis
				
*/
void init_PS2();
void scan_PS2();
void PS2_start_vibrate();
void PS2_stop_vibrate();
//volatile char cmd_array[21];
volatile char data_array[21];
volatile char a,b,c;

char  PS2_POLLBUTTON[9];// = {0x01, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//---- SPI Pins----- /
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SS_PIN		PB2
#define SCK_PIN		PB5
#define MOSI_PIN	PB3
#define MISO_PIN	PB4


//void SPI_init();
char SPI_send(char);
volatile int spi_display_i;
volatile int spi_i;
void SPI_send_array(char *a, char cmd_length);


