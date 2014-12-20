/****************************************************
	Author: Zhu Qiming

	Time:2014年5月13日18:23:07

功能说明：
	本程序采用7920显示屏，为主函数部分提供显示函数的接口
连线说明：
	P0----D0-7
	P2----D8-15

*****************************************************/
#include <reg51.h>
#include <7920.h>

void Delay1us(int i)
{ 
	int j;
	while(i--){
		for(j=0;j<100;j++) ;
	}
}

void Check_ST7920_State(void)
{
	RS = 0;
	RW = 1;
	P0 = 0xFF;
	do
	{
		E = 0;
		E = 1;
		Delay1us(3);
	}while(P0&0x80);
	E = 0;
}

void Write_ST7920_Com(Uchar command)
{
	Check_ST7920_State();
	RS = 0;
	RW = 0;
	P0 = command;
	E = 1;
	E = 0;
}

void Write_ST7920_Dat(Uchar data1)
{
	Check_ST7920_State();
	RS = 1;
	RW = 0;
	P0 = data1;
	E = 1;
	E = 0;
}

Uchar Read_ST7920_Dat(void)
{
	Check_ST7920_State();
	RS = 1;
	RW = 1;
	P0 = 0xFF;					                           
	E = 0;
	E = 1;		                                                  
	Delay1us(3);
	return P0;
	E = 0;
}

void init_ST7920(void)
{
	Write_ST7920_Com(0x30);
	Write_ST7920_Com(0x0c);
	Write_ST7920_Com(0x01);
	Write_ST7920_Com(0x06);
}

void Disp_ST7920_String(Uchar x,Uchar y,Uchar *str)
{
	switch(y)
	{
		case 0: Write_ST7920_Com(0x80+x);break;
		case 1: Write_ST7920_Com(0x90+x);break;
		case 2: Write_ST7920_Com(0x88+x);break;
		case 3: Write_ST7920_Com(0x98+x);break;
	}
	while(*str)
	Write_ST7920_Dat(*str++);
}