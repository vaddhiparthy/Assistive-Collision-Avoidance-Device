/* lcd.c */

#define LCD_DATA P1

#define lcd_clr  lcd_cmd(0x01)

sbit RS = P2^6;
sbit EN = P2^7;

void lcd_init();
void lcd_cmd(char ch);
void lcd_data(char ch);
void lcd_chr(char l,char p,char ch);
void lcd_str(char l,char p,char *str);

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_cmd(char ch)
{
    LCD_DATA = ch;
    RS = 0;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_data(char ch)
{
    LCD_DATA = ch;
    RS = 1;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_chr(char l,char p,char ch)
{
    if(l == 1)
        lcd_cmd(0x7F + p);
    else if(l == 2)
        lcd_cmd(0xBF + p);
    lcd_data(ch);
}

void lcd_str(char l,char p,char *str)
{
    if(l == 1)
        lcd_cmd(0x7F + p);
    else if(l == 2)
        lcd_cmd(0xBF + p);
    while(*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}
