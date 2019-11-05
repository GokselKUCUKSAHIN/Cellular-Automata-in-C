#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BLC 254

void gotoxy(int x, int y);
void drawBorder(void);
int getRandom(void);
void setRandomSeed(void);

int state[78][28];


int main(void)
{
	setRandomSeed();
	drawBorder();
	printf("%c",BLC);
	int i,j;
	for(i = 1; i < 79; i++)
	{
		for(j = 1; j < 29; j++)
		{
			state[i-1][j-1] = getRandom();
		}
	}
	for(i = 1; i < 79; i++)
	{
		for(j = 1;j < 29; j++)
		{
			gotoxy(i,j);
			if(state[i-1][1-j] < 2)
			{
				printf("%c",BLC);
			}
		}
	}
    getch();
    return 0;
}
 
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorder(void)
{
	int i,j;
    printf("%c",201);
    for(i = 0; i < 78; i++)
    {
    	printf("%c",205);
    }
    printf("%c\n",187);
    for(i = 1; i < 29; i++)
    {
    	gotoxy(0,i);
		printf("%c",186);
		gotoxy(79,i);
		printf("%c",186);
    }
    gotoxy(0,29);
    printf("%c",200);
    for(i = 0; i < 78; i++)
    {
    	printf("%c",205);
    }
    printf("%c\n",188);
}

void setRandomSeed()
{
	srand(time(NULL));
}

int getRandom(void)
{
	return rand()%8;
}
