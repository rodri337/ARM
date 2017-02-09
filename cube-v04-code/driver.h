#ifndef H_DRIVER
#define H_DRIVER

#include "hardware.h"

ISR (TIMER1_OVF_vect);
/* This is the most used function. It handles the task of turning
the variable cube into the colors on the display. It is an
interrupt so you never call it. It is called when needed automatically. */

void clear_buffer (void);
/* clear_buffer simply writes 0 to all of cube_buf */

void fill_buffer (uint8_t r,uint8_t g,uint8_t b);
/* fill_buffer fills the buffer with the color defined by r g and b */

void tint_buffer (uint8_t r,uint8_t g,uint8_t b);
/* tint_buffer adds r g and b to the whole buffer */

void display_buffer (void);
/* dispaly_buffer copies cube_buf to clear_buf */

uint8_t put_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t r,uint8_t g,uint8_t b);
/* put_XYZ changes the color of the LED at the 3D cordinate defined by
x y and z to the color defined by r g and b. */

uint8_t mix_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t r,uint8_t g,uint8_t b);
/* mix_XYZ does the same thing as put_XYZ but it adds the color to the
existing color in cube_buf instead of over writing it */

uint8_t single_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t color,uint8_t value);
/* single_XYZ is the same as mix_XYZ but it only changes one color defined
by color, 0=red 1=green and 2=blue. The value added is defined by value. */

void delay_ms(uint16_t ms);
/* delay_ms delays for "ms" amount of ms. This is more accurate than _delay_ms() as
it is based off the ISR timer. */

void delay_vblank(uint16_t blanks);
/* delay_vblank gives an easy way to make sure the full image was displayed before
updating the buffer.

blanks is the number of frames to wait before returning. 60 is around 1 second */

void start_vblank(uint16_t blanks);
/* start_vblank is used to set how many blanks should happen once end_vblank is called.
By having two seperate functions you can start the delay, generate the frame, then
delay the remaining time so you get the same delay regaurdless of the time it takes
to generate the frame */

void end_vblank(void);
/* waits out the remaining time from start_vblank */

#endif
