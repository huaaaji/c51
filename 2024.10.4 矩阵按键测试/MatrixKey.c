#include <REGX52.H>
unsigned char h,c,Mkey,keyl,keyc,key;
char ij;
const unsigned char MASK=0x01;
unsigned char i,j;

void Delay(unsigned int xms)//为了方便塞了一个delay函数进来，但好像不规范
{
	while (xms--)
	{
		

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

unsigned char m_key()  //逐行扫描，输出高低电位反转得出的八位二进制数
{
	while(1)
	{
		c=0;
		h=0;
		P1 = 0xF0;
		//四行分别为P14-P17；四列分别为P10-P13
		if (P1!=0xF0)
		{
			Delay(5);
			if(P1!=0xF0)
			{
				c = P1;
				P1 = 0x0F;
				if(P1 != 0x0F)
				{
					h = P1;
					while(1)
					{
						if(P1==0x0F)
						{
							return c+h;//返回值形式为行数+列数
						}
					}
				}
			}
		}
	}
}

unsigned char KeyNumber(unsigned char mkeyout)//转化为1-16的编号
{
	Mkey = 0;
	key = ~mkeyout;
	//key = ~key;
	keyc = key<<4;
	keyc >>= 4;
	keyl = key>>4;
	/*取得高低点位翻转法输出的八位二进制数的后四位（列数keyc）和
	前四位（行数keyl）*/
	for(ij=13;ij>=0;ij-=4)
	{
		Mkey += (keyl&MASK)*ij;
		keyl >>= 1;
	}
	for(ij=3;ij>=0;ij--)
	{
		Mkey += (keyc&MASK)*ij;
		keyc = keyc>>1;
	}
	return Mkey;
}
