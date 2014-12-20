//�����ⲿͷ�ļ�
#include <reg51.h>
#include <intrins.h>
#include <string.h>
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define uchar unsigned char
#define TRUE  1     
#define FALSE   0
uchar  key_code[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
bit flag=0;
uchar key_value;
unsigned char xdata value[100];
unsigned long xdata time[100];
uchar n=0;
sbit Music_out=P3^2;
sbit input=P3^1;
uchar i;
uchar l;
uchar j;
uchar k;
//song[]�д�����ף����и�4λ���������ĸߵͣ�Ƶ�ʣ���ͨ����note[]�в�ѯ�õ�����4λ��ʾ�����Ľ��ģ�����ʱ�䣩
code uchar song[]={3,4, 5, 6, 7, 8, 9, 10, 11};      
//note[]�д��ÿһ����Ƶ������Ӧ�Ķ�ʱ���ĳ�ֵ
code unsigned  int note[]={0x0000,0xFB03,0xFB8E,0xFC0B,0xFC43,0xFCAB,0xFD08,0xFD32,
                           0xFD81,0xFDC7,0xFE05,0xFE21,0xFE55,0xFE83,0xFE99,0xFEC0};
uchar hi_note, low_note;
unsigned long timer_tick=0;
/************************************************************************************
// �Ӻ�������
*************************************************************************************/
void delay(void);
bit checkstate(void);
uchar getkeys(void);
void timer1_init(void);
void timer0_init(void);
void singing(void);
bit checkstate0(void);
void delay_ms(uchar ch);
void singed(void);

/************************************************************************************
// ������ 
*************************************************************************************/
void main()
{
	uchar ch;
	P1=0xFF;
	P0=0xFF; 
	
	while(1)
	{		
		if(checkstate())
		{
			delay();
			if(checkstate())	//ÿһ�ΰ�����ִ�����´��룬��������ѭ���ȴ�����
			{			              
				ch=getkeys()+1;
				B=ch;
				timer1_init();
				singing();       	
				while(checkstate())		 //�����̰���ʱ��ִ��ѭ����ֱ�������ɿ�
				{	
					delay_ms(1);	
					timer_tick++;	 //��ʱ50ms��������һ
				}
				TR1=0;	
				value[n]=B;
				B=0;			//�����������Bֵ�����n��ѭ����value[n]��
				time[n]=timer_tick;
				timer_tick=0;	 //��ʱ�������timer_tick�����n��ѭ����time[n]��
				n++;
				value[n]='\0';
			}
		}
		if(checkstate0())
		{
			
			delay();
			if(checkstate0())
			{	
				timer1_init();
				n=0;
				singed();
			}
		}
	}
}
///////�Ӻ���/////////
void singed(void)
{
	uchar beat,temp;
	l=strlen(value);
	for(i=0;i<=l+1;i++)
	{
		j=value[i];
		temp=song[j];
		if(value[i]==0)
		{
			TR1=0;
			return;
		}
		beat=time[i];
		hi_note=note[temp]>>8;
		low_note=note[temp]&0x00ff;
		TR1=1;
		delay_ms(beat);
		TR1=0;
		}
	
}

void delay_ms(uchar ch)	 
{
  uchar m, j, k;
  for(m=0;m<ch;m++)
  {
   for(j=0;j<125;j++)
   {
    for(k=0;k<100;k++)
       ;
   }
  }
}

uchar getkeys(void)	///////////////////����ֵ��ȡ
{
	uchar r;
	key_value=P1;           
	for(r=0;r<8;r++)
    {
    	if(key_value==key_code[r])
			return(r);
	}
} 
void delay(void)   //////////////////������ʱȥ����
{
    uchar m, n;
    for (n=0;n<10;n++)
		for (m=0;m<255;m++);
}
bit checkstate(void)  ///////////////////�������
{
	bit state=0;
	P1=0xFF;                   					
	if(P1!=0xFF)               
        state=TRUE; 
	else state=FALSE;
	return(state);
}
void singing(void)/////////////���ֲ���
{
     uchar  temp;
     i=B;				  //Ϊʲôһ��Ҫ�ӼĴ���B�����ֵ�����ã�������chֱ�Ӹ���i�Ͳ��У�����
     temp=song[i];       
	 hi_note=note[temp]>>8;   
	 low_note=note[temp]&0x00FF;	
	 TR1=1;
}
void timer1_init(void)////////////////��ʱ��1��ʼ��
{
    TR1=0;
    TMOD=0x11;
    ET1=1;
    EA=1;
}
void TIMER1_ISR(void) interrupt 3  //��ʱ��1�ж���ڳ���
{
	TR1=0;
    TL1=low_note;
    TH1=hi_note;
    TR1=1;
    Music_out=~Music_out;	
}
bit checkstate0(void)	//////////���Ű������
{
	bit state0=0;                  				
	if(input!=1)               
        state0=TRUE; 
	else state0=FALSE;
	return(state0);
}				
	