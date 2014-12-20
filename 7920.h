#ifndef __7920_H__
#define __7920_H__

#ifndef Uchar
#define Uchar unsigned char
#endif

sbit RS = P2^0;
sbit RW = P2^1;
sbit E = P2^2;

extern void Delay1us(int i);
extern void Check_ST7920_State(void);
extern void Write_ST7920_Com(Uchar command);
extern void Write_ST7920_Dat(Uchar data1);
extern Uchar Read_ST7920_Dat(void);
extern void init_ST7920(void);
extern void Disp_ST7920_String(Uchar x,Uchar y,Uchar *str);

#endif