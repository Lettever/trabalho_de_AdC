/*
	* CFile1.c
	*
	* Created: 14/06/2023 18:55:09
	*  Author: jrafa
	*/ 
#define F_CPU 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
 
#include "header.h"
 
char *line = "**********************************************************\n";
char *id[2] ={"*** Eng. Informatica, Arquitetura de Computadores, TP3 ***\n",
				"*** Turma 02, Grupo 09, 2023/23                        ***\n"};
char *options[5] = {"\t1:   Modo MANUAL\n",
					"\t2:   Ligar relé\n",
					"\t3:   Desligar relé\n",
					"\t4:   Modo Automático\n",
					"\t9:   Imprimir MENU\n"};
 
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
u8 UART_getc()
{
	// wait for data
	while(!(UCSR0A & (1 << RXC0)));
	// return data
	return UDR0;
}
void print_menu()
{
	UART_puts(line);
	for(u8 i = 0; i < 2; i++)
		UART_puts(id[i]);
	UART_puts(line);
	for(u8 i = 0; i < 5; i++)
		UART_puts(options[i]);
	UART_puts(line);
	UART_puts(">> ");
}
u8 get_option()
{
	u8 result = UART_getc();
	UART_putc(result);
	if(('1' <= result && result <= '4') || (result == '9'))
		UART_puts("\nOK\n");
	else
		UART_puts("\nComando invalido\n");
	if(result != MENU_OPTION)
		UART_puts(">> ");
	return result;
}
void IO_init()
{
	DDRD = INPUT;
	DDRB = OUTPUT;
}
void UART_init()
{
	USART_Init(MYUBRR);
}
void change_mode()
{
	if(UART_option == MANUAL_MODE_OPTION)
		mode = MANUAL;
	if(UART_option == AUTO_MODE_OPTION)
		mode = AUTO;
	else
	if(GET_BIT(input, CHANGE_MODE_PIN))
		if(!GET_BIT(is_pressed, CHANGE_MODE_PIN))
		{
			SET_BIT(is_pressed, CHANGE_MODE_PIN);
			if(mode == MANUAL)
			mode = AUTO;
			else
			mode = MANUAL;
		}
}
void do_manual_stuff()
{
	if(GET_BIT(input, MANUAL_PIN))
	{
		if(!GET_BIT(is_pressed, MANUAL_PIN))
		{
			FLIP_BIT(output, RELE_PIN);
			SET_BIT(is_pressed, MANUAL_PIN);
		}
	}
	else if(UART_option == TURN_ON_OPTION)						//valor obtido no get_option()
		SET_BIT(output, RELE_PIN);
	else if(UART_option == TURN_OFF_OPTION)						//valor obtido no get_option()
		RESET_BIT(output, RELE_PIN);
}
void do_auto_stuff()
{
	if(ldr < SET_POINT - (H / 2))
		SET_BIT(output, RELE_PIN);
	else if(ldr > SET_POINT + (H / 2))
		RESET_BIT(output, RELE_PIN);		
}
void set_colours()
{
	if(mode == MANUAL)
	{
		SET_BIT(output, BLUE_PIN);
		RESET_BIT(output, RED_PIN);
	}
	else if(mode == AUTO)
	{
		SET_BIT(output, RED_PIN);
		RESET_BIT(output, BLUE_PIN);
	}
	if(GET_BIT(output, RELE_PIN))
		SET_BIT(output, GREEN_PIN);
	else
		RESET_BIT(output, GREEN_PIN);
}
void ADC_init()
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
u16 read_ADC(u8 channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);		// Select ADC channel
	ADCSRA |= (1<<ADSC);							// Single conversion mode
	while(ADCSRA & (1<<ADSC));						// Wait ADC conversion
	ADCSRA |= (1<<ADIF);							// Clear interrupt flag
	return ADC;										// ADC = ADCH<<8 | ADCL;
}
