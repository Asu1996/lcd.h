#ifndef lcd
# warning lcd not defined
# define lcd PORTD
#endif
void lcd_string(char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}
void lcd_number(int x)
{
	int t=0,a=0,b=0;
	if(x==0)
	lcd_data(48);
	while(x!=0)
	{
		if(((x%10)==0)&&(b==0))
		a++;
		else
		b=1;
		t=(t*10)+(x%10);
		x=x/10;
	}
	while(t!=0)
	{
		lcd_data((t%10)+48);
		t=t/10;
	}
	if(a>0)
	{
		for(int k=0;k<a;k++)
		lcd_data(48);
	}
}
void lcd_goto(int r,int c)
{
	if(r==1)
	lcd_cmd(0x80+(c-1));
	else if(r==2)
	lcd_cmd(0xc0+(c-1));
}
void lcd_cmd(int n)
{
	lcd=n&0xf0;
	lcd+=0x02;
	_delay_ms(2);
	lcd-=0x02;
	lcd=(n<<4)&0xf0;
	lcd+=0x02;
	_delay_ms(2);
	lcd-=0x02;
}
void lcd_data(int n)
{
	lcd=n&0xf0;
	lcd+=0x03;
	_delay_ms(2);
	lcd-=0x02;
	lcd=(n<<4)&0xf0;
	lcd+=0x03;
	_delay_ms(2);
	lcd-=0x02;
}
void lcd_begin()
{
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x28);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
}