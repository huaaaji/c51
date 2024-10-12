#include <REGX52.H>
#include "delytime.h"

void main()
{
	P2 = 0xFE;
	while(~P2)
	{
		delytime(10);
		P2=P2<<1;
		P2++;
	}
}