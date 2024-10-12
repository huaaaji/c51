#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"
unsigned char a,at;
char ii;
unsigned char password[4] = {0x00,0x00,0x00,0x00},pass[4]={2,0,2,3};

void main()
{	
	LCD_Init();
	LCD_ShowString(1,1,"Passwords:");
	for(ii=0;ii<4;ii++)
	{
		a = m_key();
		if(KeyNumber(a)==11)//实现退格
		{
			LCD_ShowString(2,ii," ");
			ii-=2;
		}
		else
		{
			password[ii]=(KeyNumber(a))%10;
			LCD_ShowNum(2,ii+1,password[ii],1);
		}
	}
	while(1)//输入结束
	{
		a = m_key();
		if (KeyNumber(a)==11)//重启下轮输入
		{
			break;
		}
		if (KeyNumber(a)==12)//检查密码
		{
			for(ii=0;ii<4;ii++)
			{
				if ((password[ii]&0x0F)!=pass[ii])
				{
					LCD_ShowString(1,13,"ERR");
					break;
				}
				LCD_ShowString(1,13,"   ");
				LCD_ShowString(1,13,"GO");
			}
		}
	}
}