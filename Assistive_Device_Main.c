/*  Assistive_Device_Main.c */

#include <reg51.h>

unsigned long time;
float time_us;
int Distance_cm;
bit Timer_flag = 0;
unsigned char count;

void delay(unsigned int val);

#include "lcd.c"
#include "distance_sensor_app.c"

void main()
{
    lcd_init();
    Timer0_init();
    lcd_str(1,1,"OBSTACLE FINDER ");
    while(1)
    {
        Distance_Measure();
    }
}

void delay(unsigned int val)
{
    unsigned int i, j;
    for(i = 0; i < val; i++)
        for(j = 0; j < 1275; j++);
}
