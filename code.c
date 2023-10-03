#include&quot;c8051F340.h&quot;
#include&quot;string.h&quot;
#define LCD P2
#define SYSCLK 12000000

float value;
sbit pH_value = P3^1;
/*LCD interfacing*/
sbit rs= P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit relay=P3^3;
void LCD_CMD(unsigned char);
void LCD_data(unsigned char);
void LCD_writestr(unsigned char s[]);
void delay();
int convert();
void ADC();
void main()
{
int k;
XBR1= 0X40;
P1MDOUT=0XE0;
LCD_CMD(0X38);
delay();
LCD_CMD(0X01);
delay();
LCD_CMD(0X0C);
delay();
LCD_CMD(0X06);
delay();
LCD_CMD(0X80);
delay();
LCD_writestr(&quot;pH detector&quot;);
LCD_CMD(0XC0);
delay();
LCD_writestr(&quot;and sprinkler&quot;);
k=convert();
if((k&lt;=14)&amp;&amp;(k&gt;7))
{
LCD_CMD(0X80);
delay();
LCD_writestr(&quot;Soil is Alkaline&quot;);
LCD_CMD(0XC0);
delay();
LCD_writestr(&quot;Motor is on&quot;);
relay=0;
}
else{
relay=1;
}

}
void LCD_CMD(unsigned char x)
{
rs=0;
LCD=x;
en=1;
delay();
en=0;
}
void lcd_writestr(char str[50])
{
int p;
for (p=0;str[p]!=&#39;\0&#39;;p++)
{
LCD = str[p];
rw = 0;
rs = 1;
en = 1;
delay();
en = 0;
}
return;
}
void LCD_data(unsigned char y)
{
rs=1;
LCD=y;
en=1;
delay();
en=0;
}
void delay()
{
int i,j;
for(i=0;i&lt;20;i++)
{
for(j=0;j&lt;100;j++);
}
}
void ADC()
{
OSCICN=0X83;
P3MDOUT=0X08;
P3MDIN=0XFE;
P2SKIP=0X01;
REF0CN=0X08;
AMX0P=0X04;
AMX0N=0X1F;

ADC0CF=(((SYSCLK/3000000)-1)&lt;&lt;3);
AD0EN=1;
{
ADC0CN=0X90;
while(AD0BUSY==1);
delay();
}
}
int convert()
{
int d;
d=
return d;
}