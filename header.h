#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>

#define INPUT 0x00
#define OUTPUT 0xFF

#define TRUE 0x01
#define FALSE 0x00

#define ON 0x01
#define OFF 0x00

#define SHIFT_LED_LEFT (led >> 1)
#define SHIFT_LED_RIGHT (led << 1)

#define FIRST_LED_VALUE 0x01
#define LAST_LED_VALUE 0x08
#define ALL_LED_VALUE 0x0F

#define SHIFT_LEFT_BUTTON ((botstate >> 2) & ON)
#define SHIFT_RIGHT_BUTTON ((botstate >> 3) & ON)

#define SHIFT_RIGHT_OPTION '1'
#define SHIFT_LEFT_OPTION '2'
#define TURN_OFF_ALL '3'
#define TURN_ON_ALL '4'
#define SHOW_MENU '5'

extern uint8_t is_pressed;
extern uint8_t led;
extern uint8_t botstate;

void USART_Init(uint16_t ubrr);
uint8_t UART_getc(void);
void UART_putc(uint8_t data);
void UART_puts(char* s);
void print_indentificacao();
void print_menu();

void init_UART();
void init_IOs();

void shift_led_left();
void shift_led_right();
#endif /* HEADER_H_ */