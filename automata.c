#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BLC 219
//254 219

#define MAX_X 78
#define MAX_Y 28

void gotoxy(int x, int y);
void drawBorder(void);
int getRandom(void);
void setRandomSeed(void);
int countNeighbours(int x,int y);
void printAutomata(void);
void nextGeneration(void);


int state[78][28];
int next[78][28]; //next
int switcher = 0;

int main(void)
{
	setRandomSeed();
	drawBorder();
	
	int i,j;
	for(i = 0; i < 78; i++)
	{
		for(j = 0; j < 28; j++)
		{
			// Fill state with random numbers
			if(getRandom() < 2)
			{
				state[i][j] = 1;
			}
			else
			{
				state[i][j] = 0;
			}
			next[i][j] = 0;
		}
	}
	//
	for(i = 0; i< 1030522874 ; i++)
	{
		printAutomata();
		nextGeneration();
	}
    getch(); // wait user input just before close
    return 0;
}

void nextGeneration()
{
	int i,j;
	if(switcher)
	{
		//next
		for(i = 0; i < MAX_X - 1; i++)
		{
			for(j = 0; j < MAX_Y - 1; j++)
			{
				int neighbors = countNeighbours(i,j);
				if(next[i][j] == 0 && neighbors == 3)
				{
					//live on next gen
					state[i][j] = 1;
				}
				else if (next[i][j] && (neighbors < 2 || neighbors > 3))
				{
					//die on next gen
					state[i][j] = 0;
				}
				else
				{
					state[i][j] = next[i][j];
				}
			}
		}
		switcher = 0;
	}
	else
	{
		//state
		for(i = 0; i < MAX_X - 1; i++)
		{
			for(j = 0; j < MAX_Y - 1; j++)
			{
				int neighbors = countNeighbours(i,j);
				if(state[i][j] == 0 && neighbors == 3)
				{
					//live on next gen
					next[i][j] = 1;
				}
				else if (state[i][j] && (neighbors < 2 || neighbors > 3))
				{
					//die on next gen
					next[i][j] = 0;
				}
				else
				{
					next[i][j] = state[i][j];
				}
			}
		}
		switcher = 1;
	}
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
			if(switcher == 1)
			{
				if(next[i-1][j-1] == 1)
				{
					if(state[i-1][j-1] == 0)
					{
						printf("%c",BLC);
					}
				}
				else
				{
					if(state[i-1][j-1] == 1)
					{
						printf("%c",' ');
					}
				}
			}
			else
			{
				if(state[i-1][j-1])
				{
					if(next[i-1][j-1] == 0)
					{
						printf("%c",BLC);
					}
				}
				else
				{
					if(next[i-1][j-1])
					{
						printf("%c",' ');
					}
				}
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
/*JELLBEANCI (c)*/
