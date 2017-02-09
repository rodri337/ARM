#ifndef H_HARDWARE
#define H_HARDWARE

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Hardware Functions */
void init_ports(void);
void init_timer1(void);
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

/* Macros */
#define set_pin(type) type ## _PORT|=type ## _MASK
#define res_pin(type) type ## _PORT&=~type ## _MASK

#define dir_out(type) type ## _DDR|=type ## _MASK
#define dir_in(type) type ## _DDR&=~type ## _MASK

#define set(type,data) type ## _PORT=((type ## _PORT &~ (type ## _MASK))|data)

/* Color Definitions */
#define MAX_COLOR 50
#define ISR_TIMEOUT 500
#define OFF_DELAY 150

/* Pin Definitions */
#define RX_PORT PORTD
#define RX_DDR DDRD
#define RX_MASK (1<<0)

#define TX_PORT PORTD
#define TX_DDR DDRD
#define TX_MASK (1<<1)

#define DA_PORT PORTC
#define DA_DDR DDRC
#define DA_MASK (1<<2)

#define DB_PORT PORTC
#define DB_DDR DDRC
#define DB_MASK (1<<3)

#define DC_PORT PORTC
#define DC_DDR DDRC
#define DC_MASK (1<<4)

#define MUL_PORT DA_PORT
#define MUL_DDR DA_DDR
#define MUL_MASK (DA_MASK|DB_MASK|DC_MASK)

#define D_EN_PORT PORTB
#define D_EN_DDR DDRB
#define D_EN_MASK (1<<0)

#define COM_PORT PORTC
#define COM_DDR DDRC
#define COM_MASK (1<<1)

#define R1_PORT PORTB
#define R1_DDR DDRB
#define R1_MASK (1<<1)

#define R2_PORT PORTB
#define R2_DDR DDRB
#define R2_MASK (1<<2)

#define R3_PORT PORTD
#define R3_DDR DDRD
#define R3_MASK (1<<2)

#define G1_PORT PORTD
#define G1_DDR DDRD
#define G1_MASK (1<<3)

#define G2_PORT PORTD
#define G2_DDR DDRD
#define G2_MASK (1<<4)

#define G3_PORT PORTD
#define G3_DDR DDRD
#define G3_MASK (1<<5)

#define B1_PORT PORTD
#define B1_DDR DDRD
#define B1_MASK (1<<6)

#define B2_PORT PORTD
#define B2_DDR DDRD
#define B2_MASK (1<<7)

#define B3_PORT PORTC
#define B3_DDR DDRC
#define B3_MASK (1<<5)

/* Serial commands */

#define EXIT 51
#define START_COL 52

#endif
