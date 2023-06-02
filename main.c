#include "header.h"

uint8_t is_pressed = FALSE;
uint8_t led = OFF;
uint8_t botstate;
char option;
uint8_t manual = TRUE;

int main(void)
{
	init_UART();
	init_IOs();
	print_indentificacao();
	print_menu();
	UART_puts(">> ");
	
	while(TRUE)
	{
		option = OFF;
		botstate = PIND;
		if(!SHIFT_LEFT_BUTTON && !SHIFT_RIGHT_BUTTON)							//ve se nenhum dos botões estão a ser pressionados
			is_pressed = FALSE;
		if(is_pressed == FALSE)
		{
			if((UCSR0A & (1 << RXC0)))
			{
				
				option = UART_getc();
				if('1' <= option && option <= '5')
				{
					UART_putc(option);	
					UART_puts("\nOK\n");
				}
				else
				{
					UART_putc(option);
					UART_puts("\nOpcão invalida\n");
				}
				if(option != '5')
					UART_puts(">> ");
			}
				
			else if(SHIFT_LEFT_BUTTON)
			{
				is_pressed = TRUE;
				option = SHIFT_LEFT_OPTION;
			}
			else if(SHIFT_RIGHT_BUTTON)
			{
				is_pressed = TRUE;
				option = SHIFT_RIGHT_OPTION;
			}
				

			if(option == SHIFT_RIGHT_OPTION)									//ve se o botão da direita está ligado
				shift_led_right();
			else if(option == SHIFT_LEFT_OPTION)								//ve se o botão da esquerda está ligado
				shift_led_left();
			else if(option == TURN_OFF_ALL)
				led = OFF;
			else if(option == TURN_ON_ALL)
				led = ALL_LED_VALUE;
			else if(option == SHOW_MENU)
			{
				print_menu();
				UART_puts(">> ");
			}
				
			PORTB = led;
		}
	}
}