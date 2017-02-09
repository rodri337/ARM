#ifndef H_PATTERNS
#define H_PATTERNS

#include "hardware.h"

void worm (uint16_t len);
/* worm creates three independent "worms" that move around in
 the cube. When they intersect new colors are created (if
 red and green intersect the new color is red+green or yellow).

 len controls how many moves the worms will make. */

void flash_rand (uint16_t len);
/* flash_rand fills the entire cube with a random color

len controls how many flashes it will make */

void rain (uint16_t len);
/* rain crates a pattern of random colored "droplets" that fall
in the coloums. Only one droplet can be in a coloum at a time */

void corner_expand (uint16_t len);
/* corner_expand selects a random corner of the cube and expands
along the X, Y, and Z axises.

len controls how many corner/expands it will render */

void plasma (uint16_t len);

void display_colors (uint16_t len);

void serial_control (void);

#endif
