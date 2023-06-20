#include "header.h"
 
u16 ldr;
u8 UART_option;
u8 mode = MANUAL;
u8 input;
u8 output = OFF;
 
int main(void)
{
	IO_init();
	UART_init();
	ADC_init();
	print_menu();
	while(TRUE)
	{
		ldr = read_ADC(ADC_PIN); //ler ldr aqui
		input = PIND;
		if(UCSR0A & (1 << RXC0))
			UART_option = get_option();
		else if(GET_BIT(input, CHANGE_MODE_PIN))
			change_mode();
		else
			UART_option = OFF;
		if(mode == MANUAL)
			do_manual_stuff();
		else if(mode == AUTO)
			do_auto_stuff();
		set_colours();
		PORTB = output;
		if(UART_option == MENU_OPTION)
			print_menu();
	}
}

