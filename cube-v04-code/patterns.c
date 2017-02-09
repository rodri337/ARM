#include "patterns.h"
#include "driver.h"

extern volatile uint8_t cube[3][27];
extern volatile uint8_t cube_buf[3][27];

void worm (uint16_t len)
{
    static uint8_t worms[3][4][3]={{{0}}};
    uint8_t test[3]={0}, direction=0, p_m=0, ct=0, collision, colorct=0;
    uint16_t ctr=0;
    for (ctr=0;ctr<len;++ctr)
    {
        clear_buffer();
        for (colorct=0;colorct<3;++colorct) // for RGB worms
        {
            collision=1;
            while (collision)
            {
                collision=0;
                test[0]=worms[colorct][0][0];
                test[1]=worms[colorct][0][1];
                test[2]=worms[colorct][0][2];
                direction=rand() % 3; //choose X,Y, or Z
                p_m=rand() % 2; //choose +/- on the axis
                if (p_m) test[direction]++;
                else test[direction]--;
                if (test[direction]>2) collision=1; //are we outside the cube? if so we need a new direction
                else
                //does the new point interset with any part of the same color worm?
                if (((test[0]==worms[colorct][1][0])&&(test[1]==worms[colorct][1][1])&&(test[2]==worms[colorct][1][2]))||
                    ((test[0]==worms[colorct][2][0])&&(test[1]==worms[colorct][2][1])&&(test[2]==worms[colorct][2][2]))||
                    ((test[0]==worms[colorct][3][0])&&(test[1]==worms[colorct][3][1])&&(test[2]==worms[colorct][3][2]))) collision=1;
            }

            for (ct=3;ct>0;--ct)
            {
                //update the tail
                worms[colorct][ct][0]=worms[colorct][ct-1][0];
                worms[colorct][ct][1]=worms[colorct][ct-1][1];
                worms[colorct][ct][2]=worms[colorct][ct-1][2];
            }

            //set the leading point
            worms[colorct][0][0]=test[0];
            worms[colorct][0][1]=test[1];
            worms[colorct][0][2]=test[2];

            //display the worm
            single_XYZ(worms[colorct][3][0],worms[colorct][3][1],worms[colorct][3][2],colorct,MAX_COLOR/8);
            single_XYZ(worms[colorct][2][0],worms[colorct][2][1],worms[colorct][2][2],colorct,MAX_COLOR/4);
            single_XYZ(worms[colorct][1][0],worms[colorct][1][1],worms[colorct][1][2],colorct,MAX_COLOR/2);
            single_XYZ(worms[colorct][0][0],worms[colorct][0][1],worms[colorct][0][2],colorct,MAX_COLOR);
        }

        display_buffer();
        delay_ms(100); //slow them down
    }
}

void flash_rand (uint16_t len)
{
    uint16_t ctr=0;
    for (ctr=0;ctr<len;++ctr)
    {
        fill_buffer(rand() % MAX_COLOR,rand() % MAX_COLOR,rand() % MAX_COLOR);
        display_buffer();
        delay_ms(300);
    }
}

void rain (uint16_t len)
{
    static uint8_t col[3][3]={{0}},color[3][3][3]={{{0}}};
    uint8_t set_x=0,set_z=0;
    uint16_t ctr=0;
    for (ctr=0;ctr<len;++ctr)
    {
        clear_buffer();
        if (col[set_x = rand() % 3][set_z = rand() % 3]<2)
        {
            col[set_x][set_z]++;
        }
        else
        {
            col[set_x][set_z]=0;
            color[set_x][set_z][0]=rand() % MAX_COLOR;
            color[set_x][set_z][1]=rand() % MAX_COLOR;
            color[set_x][set_z][2]=rand() % MAX_COLOR;
        }
        for (set_x=0;set_x<3;++set_x)
        {
            for (set_z=0;set_z<3;++set_z)
            {
                put_XYZ(set_x,col[set_x][set_z],set_z,
                        color[set_x][set_z][0],
                        color[set_x][set_z][1],
                        color[set_x][set_z][2]);
            }
        }
        display_buffer();
        delay_ms(30);
    }
}

void corner_expand (uint16_t len)
{
    uint8_t corner[3]={0}, color[3]={0}, ct=0;
    uint16_t ctr=0;
    for (ctr=0;ctr<len;++ctr)
    {
        clear_buffer();
        color[0]=rand() % MAX_COLOR;
        color[1]=rand() % MAX_COLOR;
        color[2]=rand() % MAX_COLOR;

        for (ct=0;ct<3;++ct)
        {
            corner[ct]=(rand() % 2)*2;
        }

        put_XYZ(corner[0],corner[1],corner[2],color[0],color[1],color[2]);
        display_buffer();
        delay_vblank(5);

        if (corner[0]+1<=2)
        put_XYZ(corner[0]+1,corner[1],corner[2],color[0],color[1],color[2]);
        else
        put_XYZ(corner[0]-1,corner[1],corner[2],color[0],color[1],color[2]);

        if (corner[1]+1<=2)
        put_XYZ(corner[0],corner[1]+1,corner[2],color[0],color[1],color[2]);
        else
        put_XYZ(corner[0],corner[1]-1,corner[2],color[0],color[1],color[2]);

        if (corner[2]+1<=2)
        put_XYZ(corner[0],corner[1],corner[2]+1,color[0],color[1],color[2]);
        else
        put_XYZ(corner[0],corner[1],corner[2]-1,color[0],color[1],color[2]);

        display_buffer();
        delay_vblank(5);

        if (corner[0]+2<=2)
        put_XYZ(corner[0]+2,corner[1],corner[2],color[0],color[1],color[2]);
        else
        put_XYZ(corner[0]-2,corner[1],corner[2],color[0],color[1],color[2]);

        if (corner[1]+2<=2)
        put_XYZ(corner[0],corner[1]+2,corner[2],color[0],color[1],color[2]);
        else
        put_XYZ(corner[0],corner[1]-2,corner[2],color[0],color[1],color[2]);

        if (corner[2]+2<=2)
        put_XYZ(corner[0],corner[1],corner[2]+2,color[0],color[1],color[2]);
        else
        put_XYZ(corner[0],corner[1],corner[2]-2,color[0],color[1],color[2]);

        display_buffer();
        delay_ms(150);
    }
}

void plasma (uint16_t len)
{
    uint16_t ctr=0;
    uint8_t lx=0,ly=0,lz=0;
    static float radian_r=0,radian_g=0,radian_b=0;
    for (ctr=0;ctr<len;++ctr)
    {
        start_vblank(1);
        clear_buffer();
        radian_r+=0.073;
        if (radian_r>=3.141592654)
            radian_r-=3.141592654;

        radian_g+=0.068;
        if (radian_g>=3.141592654)
            radian_g-=3.141592654;

        radian_b+=0.043;
        if (radian_b>=3.141592654)
            radian_b-=3.141592654;

        for (lx=0;lx<3;++lx)
        {
            for (ly=0;ly<3;++ly)
            {
                for (lz=0;lz<3;++lz)
                {
                    put_XYZ(lx,ly,lz,
                    (uint8_t)abs((sin(radian_r+0.2*(lx-ly+lz))*MAX_COLOR)),
                    (uint8_t)abs((sin(radian_g+0.2*(ly-lz+lx))*MAX_COLOR)),
                    (uint8_t)abs((sin(radian_b+0.2*(lz-lx+ly))*MAX_COLOR)));
                }
            }
        }
        display_buffer();
        end_vblank();
    }
}

void display_colors (uint16_t len)
{
    uint8_t lx=0,ly=0,lz=0;
    clear_buffer();
    for (lx=0;lx<3;++lx)
    {
        for (ly=0;ly<3;++ly)
        {
            for (lz=0;lz<3;++lz)
            {
                put_XYZ(lx,ly,lz,
                (uint8_t)abs((sin(0.5*lx)*MAX_COLOR)),
                (uint8_t)abs((sin(0.5*ly)*MAX_COLOR)),
                (uint8_t)abs((sin(0.5*lz)*MAX_COLOR)));
            }
        }
    }
    display_buffer();
    delay_ms(len);
}

void serial_control (void)
{
    uint8_t ser_buf, lx=0, ly=0, lz=0, col_flag=0, rgbc=0, rgb[2];
    while ((ser_buf=USART_Receive())!=EXIT)
    {
        if (ser_buf==START_COL)
        {
            col_flag=1;
            clear_buffer();
            lx=0;ly=0;lz=0;rgbc=0;
        }
        else if (col_flag && ser_buf<=MAX_COLOR)
        {
            rgb[rgbc]=ser_buf;
            rgbc++;
            if (rgbc>1)
            {
                put_XYZ(lx,ly,lz,rgb[0],rgb[1],0);
                rgbc=0;
                ly++;
                if (ly>2)
                {
                    ly=0;
                    lx++;
                    if(lx>2)
                    {
                        lx=0;
                        lz++;
                        if(lz>2)
                        {
                            col_flag=0;
                            display_buffer();
                            clear_buffer();
                            lx=0;ly=0;lz=0;rgbc=0;
                        }
                    }
                }
            }
        }
    }
}

