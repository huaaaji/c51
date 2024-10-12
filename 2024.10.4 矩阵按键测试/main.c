#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"
unsigned char a,at;
char ii;
unsigned char password[4] = {0x00,0x00,0x00,0x00},pass[4]={2,0,2,3};

/*
2024.10.6晚，现补充对于该项目的一些说明
由于该项目为测试矩阵按键是否正常而匆忙创建，导致创建时直接使用项目“2024.10.1密码锁”
的main.c文件作为本项目的main文件，而由于keil软件没有将该main.c文件复制，进而导致两项
目共用同一main.c文件，事后我在2024.10.1项目中发现了main.c的更改问题，并重新完成了密
码锁项目，但也因此更改了矩阵按键测试项目的代码。现矩阵按键测试与密码锁两项目的代码已
经处理完毕，不再具有冲突。
*/
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