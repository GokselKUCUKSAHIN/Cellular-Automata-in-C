#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BLC 219
//254

#define MAX_X 78
#define MAX_Y 28

void gotoxy(int x, int y);
void drawBorder(void);
int getRandom(void);
void setRandomSeed(void);
int countNeighbours(int x,int y);
void printAutomata(void);

int state[78][28];
int next[78][28]; //next
int switcher = 0;

int main(void)
{
	setRandomSeed();
	drawBorder();
	
	int i,j;
	for(i = 1; i < 79; i++)
	{
		for(j = 1; j < 29; j++)
		{
			// Fill state with random numbers
			if(getRandom() < 2)
			{
				state[i-1][j-1] = 1;
			}
			else
			{
				state[i-1][j-1] = 0;
			}
		}
	}
	//
	for(i = 1; i < 79; i++)
	{
		for(j = 1; j < 29; j++)
		{
			// Fill state with random numbers
			if(getRandom() < 2)
			{
				state[i-1][j-1] = 1;
			}
			else
			{
				state[i-1][j-1] = 0;
			}
		}
	}
	
	//printAutomata();
    getch(); // wait user input just before close
    return 0;
}
 
int countNeighbours(int x, int y)
{
	int neighborCount = 0;
	if (x > 0 && y < MAX_Y - 1)
    {
        // upper left
        if(switcher)
        {
        	if (next[x - 1][y + 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x - 1][y + 1])
        	{
            	neighborCount++;
        	}
		}
    }
        //
    if (y < MAX_Y - 1)
    {
        // up
        if(switcher)
        {
        	if (next[x][y + 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x][y + 1])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (x < MAX_X - 1 && y < MAX_Y - 1)
    {
    	// upper right
        if(switcher)
        {
        	if (next[x + 1][y + 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x + 1][y + 1])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (x > 0)
    {
        // left
        if(switcher)
        {
        	if (next[x - 1][y])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x - 1][y])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (x < MAX_X - 1)
    {
        // right
       	if(switcher)
        {
        	if (next[x + 1][y])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x + 1][y])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (x > 0 && y > 0)
    {
        // down left
        if(switcher)
        {
        	if (next[x - 1][y - 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x - 1][y - 1])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (y > 0)
    {
        // down
        if(switcher)
        {
        	if (next[x][y - 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x][y - 1])
        	{
            	neighborCount++;
        	}
		}
    }
    //
    if (x < MAX_X - 1 && y > 0)
    {
        // down right
        if(switcher)
        {
        	if (next[x + 1][y - 1])
        	{
            	neighborCount++;
        	}
		}
		else
		{
			if (state[x + 1][y - 1])
        	{
            	neighborCount++;
        	}
		}
    }
    return neighborCount;
}
 
void printAutomata(void)
{
	int i,j;
	for(i = 1; i < 79; i++)
	{
		for(j = 1;j < 29; j++)
		{
			gotoxy(i,j);
			if(switcher)
			{
				if(next[i-1][j-1])
				{
					printf("%c",BLC);
				}
				switcher = 0;
			}
			else
			{
				if(state[i-1][j-1])
				{
					printf("%c",BLC);
				}
				switcher = 1;
			}
		}
	}
} 

void gotoxy(int x, int y)
{
    COORD coord; // new Coord var
    coord.X = x; // set x
    coord.Y = y; // set y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // just goto there
}

void drawBorder(void)
{
	int i,j;
    printf("%c",201); // Upper Left Corner
    for(i = 0; i < 78; i++)
    {
    	printf("%c",205); // Upper Band
    }
    printf("%c\n",187); // Upper Right Corner
    for(i = 1; i < 29; i++)
    {
    	//Side Bands
    	gotoxy(0,i);
		printf("%c",186); // Left
		gotoxy(79,i);
		printf("%c",186); // Right 
    }
    gotoxy(0,29); 
    printf("%c",200); // Bottom Left Corner
    for(i = 0; i < 78; i++)
    {
    	printf("%c",205); // Bottom Band
    }
    printf("%c\n",188); // Bottom Right Corner
}

void setRandomSeed()
{
	// set Random seed for random number generator
	srand(time(NULL));
}

int getRandom(void)
{
	// get random int between [0-7] 
	return rand()%8;
}
