#include "header.h"
#define F_CPU 1000000UL
#include <util/delay.h>

u16 ldr;
u8 UART_option;
u8 mode = MANUAL;
u8 input;
u8 output = OFF;
u8 test = 0;
u8 is_pressed = OFF;

int main(void)
{
	IO_init();
	UART_init();
	ADC_init();
	print_menu();
	while(TRUE)
	{
		input = PIND;
		if(!GET_BIT(input, CHANGE_MODE_PIN))
			RESET_BIT(is_pressed, CHANGE_MODE_PIN);
		if(!GET_BIT(input, MANUAL_PIN))
			RESET_BIT(is_pressed, MANUAL_PIN);
		ldr = read_ADC(ADC_PIN); //ler ldr aqui
		if(UCSR0A & (1 << RXC0))
			UART_option = get_option();
		else if(UART_option == MANUAL_MODE_OPTION)
			mode = MANUAL;
		else if(UART_option == AUTO_MODE_OPTION)
			mode = AUTO;
		else
			UART_option = OFF;
		change_mode();
		if(mode == MANUAL)
			do_manual_stuff();
		else if(mode == AUTO)
			do_auto_stuff();
		set_colours();
		if(UART_option == MENU_OPTION)
			print_menu();
		PORTB = output;
	}
}
