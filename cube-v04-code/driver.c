#include "driver.h"

volatile uint8_t cube[3][27]={{0}}; //actual display RAM
volatile uint8_t cube_buf[3][27]={{0}}; //display buffer
volatile uint32_t vblank_ctr=0; //used in delay_vblank()

ISR (TIMER1_OVF_vect)
{
    static uint8_t ct=0, state=0, mode=0, ct_row, ct_1, ct_2;

    if (mode)
    {
        TCNT1=(0xFFFF-OFF_DELAY);

        if (vblank_ctr)--vblank_ctr;//timer

        ct++; //increase the row
        state+=3; //increase the color
        //state is increade by three to remove updating patters that causes it to show the wrong color
        if (ct>8) ct=0; //reset
        if (state>MAX_COLOR)state-=MAX_COLOR; //compare color overflow
        //since state is increaded by two it needs to wrap around instead of being set to zero or it will miss some states

        res_pin(R1);
        res_pin(R2);
        res_pin(R3);
        res_pin(G1);
        res_pin(G2);
        res_pin(G3);
        res_pin(B1);
        res_pin(B2);
        res_pin(B3);

        res_pin(D_EN); //turn off the cube so we don't see the changes yet
        res_pin(COM);

        if (ct!=8) set(MUL,ct<<2);

        ct_row=ct*3; //save some time by calculating this once
        ct_1=ct_row+1; //instead of three times
        ct_2=ct_row+2;

        mode=0;
    }
    else
    {
        TCNT1=(0xFFFF-ISR_TIMEOUT); //set the timer so it overflows faster

    /*  Here we test all the selected LED to see if they should light or not
        if the value in cube is grater to the current state of the cube
        then we light that LED. This make it so it the value is 15 (0x0F) then
        it will always be on. If it is 8 then it will be on about 1/2 the time
        making it seem dim. 0 it will always be off. */

        if (cube[0][ct_row]>state)
            set_pin(R1);
        if (cube[0][ct_1]>state)
            set_pin(R2);
        if (cube[0][ct_2]>state)
            set_pin(R3);

        if (cube[1][ct_row]>state)
            set_pin(G1);
        if (cube[1][ct_1]>state)
            set_pin(G2);
        if (cube[1][ct_2]>state)
            set_pin(G3);

        if (cube[2][ct_row]>state)
            set_pin(B1);
        if (cube[2][ct_1]>state)
            set_pin(B2);
        if (cube[2][ct_2]>state)
            set_pin(B3);

        if (ct==8) //turn the cube back on
        {
            //the non muliplexer pin
            set_pin(COM);

        }
        else
        {
            //the regular multiplexer pins
            set_pin(D_EN);
        }
        mode=1;
    }
}

void clear_buffer (void)
{
    uint8_t ct=0;
    for (ct=0;ct<27;++ct)
    {
        cube_buf[0][ct]=0;
        cube_buf[1][ct]=0;
        cube_buf[2][ct]=0;
    }
}

void fill_buffer (uint8_t r,uint8_t g,uint8_t b)
{
    uint8_t ct=0;
    for (ct=0;ct<27;++ct)
    {
        cube_buf[0][ct]=r;
        cube_buf[1][ct]=g;
        cube_buf[2][ct]=b;
    }
}

void tint_buffer (uint8_t r,uint8_t g,uint8_t b)
{
    uint8_t ct=0;
    for (ct=0;ct<27;++ct)
    {
        cube_buf[0][ct]+=r;
        cube_buf[1][ct]+=g;
        cube_buf[2][ct]+=b;
    }
}

void display_buffer (void)
{
    uint8_t ct=0;
    for (ct=0;ct<27;++ct)
    {
        cube[0][ct]=cube_buf[0][ct];
        cube[1][ct]=cube_buf[1][ct];
        cube[2][ct]=cube_buf[2][ct];
    }
}

uint8_t put_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t r,uint8_t g,uint8_t b)
{
    uint8_t pixel;

    if (x>2) return 1;
    if (y>2) return 2;
    if (z>2) return 3;

    pixel=(x)+((2-y)*3)+(z*9);

    cube_buf[0][pixel]=r;
    cube_buf[1][pixel]=g;
    cube_buf[2][pixel]=b;
    return 0;
}

uint8_t mix_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t r,uint8_t g,uint8_t b)
{
    uint8_t pixel;

    if (x>2) return 1;
    if (y>2) return 2;
    if (z>2) return 3;

    pixel=(x)+((2-y)*3)+(z*9);

    cube_buf[0][pixel]+=r;
    cube_buf[1][pixel]+=g;
    cube_buf[2][pixel]+=b;
    return 0;
}

uint8_t single_XYZ (uint8_t x,uint8_t y,uint8_t z,uint8_t color,uint8_t value)
{
    uint8_t pixel;

    if (x>2) return 1;
    if (y>2) return 2;
    if (z>2) return 3;

    pixel=(x)+((2-y)*3)+(z*9);

    cube_buf[color][pixel]+=value;
    return 0;
}

void delay_ms(uint16_t ms)
{
    vblank_ctr=(uint32_t)ms*((F_CPU/1000)/(ISR_TIMEOUT+OFF_DELAY));
    while (vblank_ctr);//wait for that many blanks
}

void delay_vblank(uint16_t blanks)
{
    vblank_ctr=blanks*MAX_COLOR*9;//MAX_COLOR*9 IRS per full frame
    while (vblank_ctr);//wait for that many blanks
}

void start_vblank(uint16_t blanks)
{
    vblank_ctr=blanks*MAX_COLOR*9;//MAX_COLOR*9 IRS per full frame
}

void end_vblank(void)
{
    while (vblank_ctr);//wait for remaining blanks
}
