//引用外部头文件
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define ulong unsigned long
#define uint unsigned int
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
//键盘部分
#define uchar unsigned char
#define TRUE  1     
#define FALSE   0
uchar  key_code[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
uchar b_code[]={0,1,2,3,4,5,6,7,8};
bit flag=0;
uchar key_value;
uchar b;
sbit Music_out=P3^2;
code uchar song[]={4, 5, 6, 7, 8, 9, 10, 11, 0};
code unsigned  int note[]={0x0000,0xFB03,0xFB8E,0xFC0B,0xFC43,0xFCAB,0xFD08,0xFD32,
                           0xFD81,0xFDC7,0xFE05,0xFE21,0xFE55,0xFE83,0xFE99,0xFEC0};
uchar i=0;
uchar hi_note, low_note;
/************************************************************************************
// 子函数声明
*************************************************************************************/
void delay(void);
bit CheckState(void);
uchar GetKeys();
void delay_ms(uchar ch);
void timer1_INIT(void);
void singing(void);
/************************************************************************************
// 主程序 
*************************************************************************************/
void main()
{     
   uchar ch;
   P1=0xFF;
   while(1)
    {
      ch=GetKeys();
      B=ch;
	  timer1_INIT();  //定时器1初始化
      singing();
	}
}
/************************************************************************************
// 子函数
*************************************************************************************/
//定时器1初始化程序
void timer1_INIT(void)
{
  EA=0;
  TR1=0;
  TMOD=0x10;
  ET1=1;
  EA=1;
}

//定时器1中断程序
void TIMER1_ISR(void) interrupt 3  //定时器1工作
{
  TR1=0;
  TL1=low_note;
  TH1=hi_note;
  TR1=1;
  Music_out=~Music_out;
}
//键盘延时去抖动程序
void delay(void)
{
   uchar m, n;
   for (n=0;n<10;n++)
   for (m=0;m<255;m++);
}
//按键扫描程序
bit CheckState(void)
{
	bit state=0;				
	if(P1!=0xFF)               //判断是否有键按下
        state=TRUE; 
	else 
		state=FALSE;
	return(state);
}
//按键判断，返回uchar
uchar GetKeys()
{
  uchar r;  
  {    
       if(CheckState())                      //检查是否有键按下
	   {
			delay();                    //延时去抖动		
			if(CheckState())
			{
			  key_value=P1;             //读取键盘值
              for(r=0;r<8;r++)              
               	if(key_value==key_code[r])
				return(r);                			    
             } 
		 }
   }
}

//读节拍码
void singing(void)
{
    uchar  temp;
    i=B;
    temp=song[i];       //读出乐谱的一个字节
	hi_note=note[temp]>>8;   //根据音符的频率得到Timer1的计数值
	low_note=note[temp]&0x00FF;
    if (P1!=0xFF)	
	TR1=1;
	else TR1=0;                   //启动定时器
}
