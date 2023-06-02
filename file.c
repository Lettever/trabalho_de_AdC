#include "header.h"

#define F_CPU 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

char *line = "**********************************************************\n";
char *messages[] = {"*** Eng. Informatica, Arquitetura de Computadores, TP2 ***\n",
					"*** Turma 02, Grupo 09                                 ***\n"};

char *options[]	 = {"(1) Movimento para DIREITA\n",
					"(2) Movimento para ESQUERDA\n",
					"(3) Apagar LEDs\n",
					"(4) Acender TODOS\n",
					"(5) Imprimir MENU\n"};

void USART_Init(uint16_t ubrr)
{
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)(ubrr & 0xFF);
	// enable the transmitter and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}
void UART_putc(uint8_t data)
{
	// wait for transmit buffer to be empty
	while(!(UCSR0A & (1 << UDRE0)));
	// load data into transmit register
	UDR0 = data;
}
void UART_puts(char* s)
{
	// transmit character until NULL is reached
	while(*s > 0)
		UART_putc(*s++);
}
void UART_putU8(uint8_t val)
{
	uint8_t dig1 = '0', dig2 = '0';
	// count value in 100s place
	while(val >= 100)
	{
		val -= 100; dig1++;
	}
	// count value in 10s place
	while(val >= 10)
	{
		val -= 10; dig2++;
	}
}
uint8_t UART_getc(void)
{
	// wait for data
	while(!(UCSR0A & (1 << RXC0)))
	{
		if(SHIFT_RIGHT_BUTTON)														//se o botao da direita for ativo
			return '1';																//retorna o char '1'
		if(SHIFT_LEFT_BUTTON)														//se o botao da esquerda for ativo
			return '2';																//retorna o char '2'
	}
	UART_puts("ECO: ");
	UART_putU8(UDR0);
	UART_puts("\nOK\n");															//se um char for escrito, escreve "OK!"
	return UDR0;																	//e retorna esse char
}
void print_indentificacao()
{
	UART_puts(line);
	for(uint8_t i = 0; i < 2; i++)
		UART_puts(messages[i]);
	UART_puts(line);
}
void print_menu()
{
	for(uint8_t i = 0; i < 5; i++)
		UART_puts(options[i]);
	UART_puts(line);
}
void init_UART()
{
	USART_Init(MYUBRR);																//inicializa o UART
}
void init_IOs()
{
	DDRB = OUTPUT;																	//configuração dos portos
	DDRD = INPUT;
}
void shift_led_left()
{
	is_pressed = TRUE;
	if(led == OFF)																	//se nenhum led estiver ligado
		led = LAST_LED_VALUE;														//liga o ultimo led
	else
		led = SHIFT_LED_LEFT;														//desliga o led ligado e liga o led da esquerda
}
void shift_led_right()
{
	is_pressed = TRUE;
	if(led == LAST_LED_VALUE)														//se o ultimo led estiver ligado
		led = OFF;																	//desliga os leds
	else if(led == OFF)																//se nenhum led estiver ligado
		led = FIRST_LED_VALUE;														//liga o primeiro led
	else
		led = SHIFT_LED_RIGHT;														//desliga o led ligado e liga o led da direita
}