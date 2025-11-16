/* distance_sensor_app.c */

sbit echo = P2^1;
sbit pulser = P2^0; // trigger

sbit DIS_BLW_50CMS  = P3^0;
sbit DIS_BLW_100CMS = P3^1;
sbit DIS_BLW_150CMS = P3^2;
sbit DIS_BLW_200CMS = P3^3;
sbit DIS_BLW_250CMS = P3^4;
sbit DIS_BLW_300CMS = P3^5;
sbit DIS_BLW_350CMS = P3^6;
sbit DIS_ABV_350CMS = P3^7;

bit f;
char flag;

Timer0_init();
Pulse_Delay(unsigned int);
Pulse();
Find_Distance();
Distance_Measure();
Voice_Alert();

Timer0_init()
{
    TMOD = 0x11;
    TH0  = 0x00;
    TL0  = 0x00;
    IE   = 0x82;
}

Timer0() interrupt 1
{
    TR0 = 0;
    TF0 = 0;
    TH0 = 0x00;
    TL0 = 0x00;
    count = count + 1;
    if(count > 2)
    {
        Timer_flag = 1;
    }
}

Distance_Measure()
{
    Pulse();
    while(echo != 1);
    TR0 = 1;
    while(echo != 0 && Timer_flag != 1);
    {
        if(Timer_flag == 1)
        {
            TR0 = 0;
            TF0 = 0;
            TH0 = 0x00;
            TL0 = 0x00;
            Timer_flag = 0;
        }
        if(Timer_flag == 0)
        {
            Find_Distance();
            echo = 1;
        }
    }
}

Find_Distance()
{
    TR0      = 0;
    time     = (TH0 * 256) + TL0;
    time_us  = (time * 1.0856);
    Distance_cm = time_us / 58;
    if(Distance_cm <= 351 && Distance_cm > 1 && flag != 8)
    {
        flag = 8;
        if(f == 0)
            lcd_str(1,1,"Obj at          ");
        lcd_chr(1,8,(Distance_cm/100) + 48);
        lcd_data(((Distance_cm % 100)/10) + 48);
        lcd_data((Distance_cm % 10) + 48);
        if(f == 0)
            lcd_str(0,0,"Cm");
        Voice_Alert();
        TH0 = 0x00;
        TL0 = 0x00;
        f   = 1;
    }
    else
    {
        flag = 0;
        TH0  = 0x00;
        TL0  = 0x00;
        f    = 0;
        lcd_str(1,1,"Obj Out of Range");
        DIS_ABV_350CMS = 0;
        delay(50);
        DIS_ABV_350CMS = 1;
        delay(400);
    }
}

Pulse()
{
    pulser = 1;
    Pulse_Delay(10);
    pulser = 0;
}

Pulse_Delay(unsigned int k)
{
    int j;
    for(j = 0; j <= k; j++);
}

Voice_Alert()
{
    if(Distance_cm >= 0 && Distance_cm < 50 && flag != 1)
    {
        flag = 1;
        DIS_BLW_50CMS = 0;
        delay(50);
        DIS_BLW_50CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 50 && Distance_cm < 100 && flag != 2)
    {
        flag = 2;
        DIS_BLW_100CMS = 0;
        delay(50);
        DIS_BLW_100CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 100 && Distance_cm < 150 && flag != 3)
    {
        flag = 3;
        DIS_BLW_150CMS = 0;
        delay(50);
        DIS_BLW_150CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 150 && Distance_cm < 200 && flag != 4)
    {
        flag = 4;
        DIS_BLW_200CMS = 0;
        delay(50);
        DIS_BLW_200CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 200 && Distance_cm < 250 && flag != 5)
    {
        flag = 5;
        DIS_BLW_250CMS = 0;
        delay(50);
        DIS_BLW_250CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 250 && Distance_cm < 300 && flag != 6)
    {
        flag = 6;
        DIS_BLW_300CMS = 0;
        delay(50);
        DIS_BLW_300CMS = 1;
        delay(400);
    }
    if(Distance_cm >= 300 && Distance_cm < 350 && flag != 7)
    {
        flag = 7;
        DIS_BLW_350CMS = 0;
        delay(50);
        DIS_BLW_350CMS = 1;
        delay(400);
    }
}
