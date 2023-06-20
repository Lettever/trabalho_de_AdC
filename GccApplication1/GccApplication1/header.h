#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>

#define FALSE 0
#define TRUE 1

#define OFF 0
#define ON 1

#define INPUT 0x00
#define OUTPUT 0xFF

#define GET_BIT(var, bit) ((var >> bit) & 0x01)
#define SET_BIT(var, bit) (var |= (1 << bit))
#define RESET_BIT(var, bit) (var &= ~(1 << bit))
#define FLIP_BIT(var, bit) (var ^= (1 << bit))

#define AUTO 0x00
#define MANUAL 0x01

#define ADC_PIN 0

#define CHANGE_MODE_PIN 2
#define MANUAL_PIN 3

#define RED_PIN 2
#define GREEN_PIN 3
#define BLUE_PIN 4
#define RELE_PIN 5

#define MANUAL_MODE_OPTION '1'
#define TURN_ON_OPTION '2'
#define TURN_OFF_OPTION '3'
#define AUTO_MODE_OPTION '4'
#define MENU_OPTION '9'

#define SET_POINT 512
#define H 200

//primeiro botao muda o modo entre manual e automatico
//o segundo botao lida/desliga o rele quando no modo manual

typedef uint8_t u8;
typedef uint16_t u16;

extern u8 mode;
extern u8 output;
extern u8 UART_option;
extern u16 ldr;
extern u8 input;
extern u8 is_pressed;

void USART_Init(u16 ubrr);
void UART_putc(u8 data);
void UART_puts(char* s);
void UART_put_u16(u16);
u8 UART_getc();
void print_menu();
u8 get_option();
void IO_init();
void UART_init();
void ADC_init();
void change_mode();
void do_manual_stuff();
void do_auto_stuff();
void set_colours();
u16 read_ADC(u8);

#endif /* HEADER_H_ */
