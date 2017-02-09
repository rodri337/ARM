#include "hardware.h"

void init_ports(void)
{
    dir_out(DA);
    dir_out(DB);
    dir_out(DC);
    dir_out(D_EN);
    dir_out(COM);
    dir_out(R1);
    dir_out(R2);
    dir_out(R3);
    dir_out(G1);
    dir_out(G2);
    dir_out(G3);
    dir_out(B1);
    dir_out(B2);
    dir_out(B3);

    dir_out(TX);
    dir_in(RX);
}

void init_timer1(void)
{
    TCCR1B=1; //set no prescaller
    TIMSK1=(1<<TOIE1); //enable timer1 over-flow interrupt
    sei(); //enable global interrupts
}

void USART_Init( unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable double speed */
UCSR0A = (1<<U2X0);
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 1stop bit */
UCSR0C = (3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}
