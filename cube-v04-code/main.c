#include "hardware.h"
#include "driver.h"
#include "patterns.h"

extern volatile uint8_t cube[3][27];

int main (void)
{
    init_ports();
    USART_Init(21); //baud 115200
    init_timer1(); //set up the timer and start the main interrupt
    display_colors(3000);
    while (1)
    {
        //serial_control();
        plasma(750);
        corner_expand(35);
        rain(500);
        worm(150);
        flash_rand(100);
    }
    return 0;
}
