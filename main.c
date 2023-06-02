#include "header.h"

uint8_t is_pressed = FALSE;
uint8_t led = OFF;
uint8_t botstate;
uint8_t option;

int main(void)
{
	init_UART();
	init_IOs();
	print_indentificacao();
	print_menu();
	
	while(TRUE)
	{
		botstate = PIND;
		if(!SHIFT_LEFT_BUTTON && !SHIFT_RIGHT_BUTTON)							//ve se nenhum dos botões estão a ser pressionados
			is_pressed = FALSE;
		if(is_pressed == FALSE)
		{
			option = UART_getc();
			if(option == SHIFT_RIGHT_OPTION)									//ve se o botão da direita está ligado
				shift_led_right();
			else if(option == SHIFT_LEFT_OPTION)								//ve se o botão da esquerda está ligado
				shift_led_left();
			else if(option == TURN_OFF_ALL)
				led = OFF;
			else if(option == TURN_ON_ALL)
				led = ALL_LED_VALUE;
			else if(option == SHOW_MENU)
				print_menu();

			PORTB = led;
		}
	}
}
