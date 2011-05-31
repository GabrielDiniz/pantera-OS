#include <system.h>
#include <lib/colors.h>

#ifndef __SCREEN_H
#define __SCREEN_H

extern int csr_x;
extern int csr_y;

void putlc(unsigned char *text,int y, int x)
{
	int old_x = csr_x;
	int old_y = csr_y;
	csr_x = x;
	csr_y = y;
	puts(text);
	csr_x = old_x;
	csr_y = old_y;
	move_csr();	
}

void box2(int lIni, int cIni, int lFin, int cFin){
	int i,j;
	for(i=lIni;i<=lFin;i++)
	{
		for(j=cIni;j<=cFin;j++)
		{
			if((i==lIni)||(i==lFin)||(j==cIni)||(j==cFin))
			{
				putlc("*",i,j);
			}
		}
	}
}

void box(int lIni, int cIni, int lFin, int cFin){
	int i,j;
	char *c;
	for(i=lIni;i<=lFin;i++)
	{
		for(j=cIni;j<=cFin;j++)
		{
			if(i==lIni && j==cIni)
				*c=218;
			else if(i==lFin && j==cIni)
				*c=192;
			else if(i==lIni && j==cFin)
				*c=191;
			else if(i==lFin && j==cFin)
				*c=217;
			else if(!((i!=lIni)&&(i!=lFin)&&(j!=cIni)&&(j!=cFin)))
			{
				if(i==lIni||i==lFin)
					*c=196;
				else if(j==cFin||j==cIni)
					*c=179;
			}else{
				*c=' ';
			}
			putlc(c,i,j);
			
			
		}
	}
}

#endif