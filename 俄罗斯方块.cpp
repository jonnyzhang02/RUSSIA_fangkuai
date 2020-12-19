#define XIN(n) for(int i=0;i<n;i++ )
#define YIN(n) for(int j=0;j<n;j++ )
#include <easyx.h>			
#include <conio.h>
#include<iostream>
#include <ctime> 
#include<stdlib.h>
/*
BY: ZY @ Beijing Univeisity of Posts and Telecommunications
2020/12/19
*/
using namespace std;
int base[22][42];
int flag = 4; 
int score = 0;
void move(int** now, int** now1, int** now2, int** now3);
void init();
void freshscreen();
void drop(int* now);
void scan();

void init()
{
	XIN(22)
	{
		YIN(42)
		{
			if (i == 0 || j == 0 || i == 21 || j == 41) base[i][j] = 1;
			else base[i][j] = 0;
		}
	}
	int x = 380;
	int y = 420;
	initgraph(x, y);
	setlinecolor(BLUE);
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
}
void freshscreen()
{
	XIN(22)
	{
		YIN(42)
		{
			if (base[i][j])
			{
				int x = i+1;
				int y = 42 - j;
				fillrectangle(10 * (x - 1), 10 * (y - 1), 10 * x, 10 * y);
			}
		}
	}
	settextstyle(16, 0, _T("Consolas"));
	settextcolor(YELLOW);
	TCHAR l1[] = _T("score:");
	outtextxy(220, 0,l1 );
	TCHAR l2[] = _T("a:左移");
	outtextxy(220, 20, l2);
	TCHAR l3[] = _T("d:右移");
	outtextxy(220, 40, l3);
	TCHAR l4[] = _T("w:变形");
	outtextxy(220, 60, l4);
	TCHAR l5[] = _T("s:下落更快");
	outtextxy(220, 80, l5);
	TCHAR l6[] = _T("BY：Zhangyang @ BUPT");
	outtextxy(220, 100, l6);
	TCHAR l = char(score+48);
	outtextxy(265, 0, l);
	Sleep(200);
	keybd_event(66, 0, 0, 0);
	cleardevice();
}
void drop(int* now)
{
	if (now == NULL)
	{
		srand(time(NULL));
		flag = rand() % 5 + 1;
		now = &base[10][38];
		drop(now);
	}
	else
	{
		int* now1 = now + 1;
		int* now2 = now + 42;
		int* now3 = now + 43;
		switch (flag)
		{
		case 1:
			now1 = now + 1;
			now2 = now + 42;
			now3 = now + 43;
			break;
		case 2:
			now1 = now + 1;
			now2 = now + 44;
			now3 = now + 43;
			break;
		case 3:
			now1 = now + 84;
			now2 = now + 43;
		    now3 = now + 42;
			break;
		case 4:
			now1 = now + 1;
			now2 = now - 1;
			now3 = now - 2;
			break;
		case 5:
			now1 = now + 1;
			now2 = now + 42;
			now3 = now + 41; break;
		case 6:
			now1 = now + 42;
			now2 = now + 41;
			now3 = now + 83; break;
		case 7:
			now1 = now + 42;
			now2 = now + 43;
			now3 = now + 85; break;
		case 8:
			now1 = now -1;
			now2 = now -2;
			now3 = now +41; break;
		case 9:
			now1 = now +42;
			now2 = now +43;
			now3 = now + 41; break;
		case 10:
			now1 = now + 42;
			now2 = now + 84;
			now3 = now + 41; break;
		case 11:
			now1 = now + 42;
			now2 = now + 84;
			now3 = now + 126; break;
		default:break;
		}
		*now = 2;
		*now1 = 2;
		*now2 = 2;
		*now3 = 2;
		freshscreen();
		move(&now, &now1, &now2, &now3);
		if (*(now-1) == 1 || *(now2-1) == 1|| *(now3 - 1)==1||*(now1-1)==1)
		{
			*now = 1;
			*now1 = 1;
			*now2 = 1;
			*now3 = 1;
			scan();
			drop(NULL);
		}
		else
		{
			*now = 0;
			*now1= 0;
			*now2 = 0;
			*now3 = 0;
			now--;
			drop(now);
		}
	}
}
void move(int** now,int **now1, int** now2, int** now3)
{
	char f = char(_getch());
	switch (f)
	{
	case 'a':
		if (*(*now - 42) == 1 
			|| *(*now2 - 42) == 1 
			|| *(*now3 - 42) == 1
			|| *(*now1 - 42) == 1) break;
		**now = 0;
		**now1 = 0;
		**now2 = 0;
		**now3 = 0;
		*now = *now - 42;
		break;
	case 'd':
		if (*(*now + 42) == 1 
			|| *(*now2 + 42) == 1 
			|| *(*now3 + 42) == 1 
			|| *(*now1 + 42) == 1) break;
		**now = 0;
		**now1 = 0;
		**now2 = 0;
		**now3 = 0;
		*now = *now + 42;
		break;
	case 'w':
		switch (flag)
		{
		case 2:
			flag = 6; break;
		case 6:
			flag = 2; break;
		case 5:
			flag = 7; break;
		case 7:
			flag = 5; break;
		case 3:
			flag = 8; break;
		case 8:
			flag = 10; break;
		case 10:
			flag = 9; break;
		case 9:
			flag = 3; break;
		case 4:
			flag = 11; break;
		case 11:
			flag = 4; break;
		default:
			flag = 1; break;
		}
		break;
	case 's':
		if (*(*now - 2) == 1 || *(*now2 - 2) == 1
			|| *(*now3 - 2) == 1 || *(*now1 - 2) == 1
			||*(*now - 1) == 1 || *(*now2 - 1) == 1 
			|| *(*now3 - 1) == 1 || *(*now1 - 1) == 1
			) break;
		**now = 0;
		**now1 = 0;
		**now2 = 0;
		**now3 = 0;
		*now = *now - 2;
		break;
	default:
		break;
	}
}
void scan()
{
	int fullline =0;
	int no = 0;
	YIN(40)
	{
		XIN(20)
		{
			if (base[1 + i][1 + j] != 1) break;
			if (i == 19) fullline = j + 1;
		}
		if (fullline) break;
	}
	if (fullline)
	{	
		score++;
		XIN(20) base[i][fullline] = 0;
	    YIN(39 - fullline)
		{
			XIN(20)
			{
				if (base[i][fullline + 1 + j])
				{
					base[i][fullline + 1 + j] = 0;
					base[i][fullline + j] = 1;
				}
			}
		}
    }
}
int main()
{
	init();
	drop(NULL);
	return 0;
}