#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define N 20
#define M 40

int field[N][M];
int head, tail, game, frogs;
int var, dir, score, speed;
int i, j, x, y, gy, a, b;

void GameOver();
void snake()
{
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			field[i][j] = 0;
	}

	x = N / 2; // snake's coordinates in the centre
	y = M / 2; // snake's coordinates in the centre
	gy = y;    // it holds the value of 20
	head = 5;  // snake's body
	tail = 1;  // snake's tail
	game = 0;  // 0 means - game is running
	frogs = 0; // 0 means - frog is alive
	dir = 'd'; // starts moving from right direction
	score = 0;
	speed = 99;


	for (i = 0; i < head; i++)   // for moving of snake
	{
		gy++;
		field[x][gy - head] = i + 1;
	}
}

void print_field()
{
	for (i = 0; i <= M + 1; i++) // top
	{
		if (i == 0)
			printf("%c", 201);
		else if (i == M + 1) 
			printf("%c", 187);
		else
			printf("%c", 205);
	}
	printf("   Your score: %d", score);
	puts(" ");

	for (i = 0; i < N; i++) // edges 
	{
		printf("%c", 186);
		for (j = 0; j < M; j++)
		{
			if (field[i][j] == 0)
				printf(" ");
			if (field[i][j] > 0 && field[i][j] != head) // made body
				printf("%c", 176);
			if (field[i][j] == head) // made head
				printf("%c", 178);
			if (field[i][j] == -1)  // if this position is a frog
				printf("%c", 254);
			if (j == M - 1)
				printf("%c\n", 186);
		}
	}

	for (i = 0; i <= M + 1; i++) // bottom
	{
		if (i == 0)
			printf("%c", 200);
		else if (i == M + 1)
			printf("%c", 188);
		else
			printf("%c", 205);
	}
	puts(" ");
}

void ResetScreenPosition() // it fixs snake's frame during cycles in coordinates (0, 0)
{
	HANDLE hout;    // to handle to the console
	COORD Position; // we defined a position coordinates (it holds X and Y)
	hout = GetStdHandle(STD_OUTPUT_HANDLE);  // standart handle of output
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hout, Position);
}

void random()   // to generate frogs
{
	srand(time(0));  // to generate frogs in random positions
	a = 1 + rand() % 18;
	b = 1 + rand() % 38;

	// checking frogs (we need 1 frog on the screen)
	if (frogs == 0 && field[a][b] == 0)
	{
		field[a][b] = -1;
		frogs = 1;
		if (speed > 10 && score != 0)  // to increase snake's speed
			speed = speed - 10;
	}
}

int getch_noblock()  // to control keybord and limit characters
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

void movement()
{
	var = getch_noblock();
	var = tolower(var);  // to convert it to lowercase (if we have capslock)
	
	// (abs(dir - var) > 5) it means we limit wrong directions ('w' and 's', 'a' and 'd')
	if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5))  
		dir = var;

	if (dir == 'd')
	{
		y++;
		if (field[x][y] != 0 && field[x][y] != -1) // game over
			GameOver();
		if (y == M - 1)  // to fix moving ('d' -> 'a')
			y = 0;
		if (field[x][y] == -1)
		{
			frogs = 0;  // to generate frogs each time again
			score += 1;
			tail -= 2;  // to increase tail after eating
		}
		head++;
		field[x][y] = head;
	}

	if (dir == 'a') 
	{
		y--;
		if (field[x][y] != 0 && field[x][y] != -1) // game over
			GameOver();
		if (y == 0)      // to fix moving ('a' -> 'd')
			y = M - 1;
		if (field[x][y] == -1)
		{
			frogs = 0;  // to generate frogs each time again
			score += 1;
			tail -= 2;  // to increase tail after eating
		}
		head++;
		field[x][y] = head;
	}

	if (dir == 'w')
	{
		x--;
		if (field[x][y] != 0 && field[x][y] != -1) // game over
			GameOver();
		if (x == -1)      // to fix moving ('w' -> 's')
			x = N - 1;
		if (field[x][y] == -1)
		{
			frogs = 0;  // to generate frogs each time again
			score += 1;
			tail -= 2;  // to increase tail after eating
		}
		head++;
		field[x][y] = head;
	}

	if (dir == 's')
	{
		x++;
		if (field[x][y] != 0 && field[x][y] != -1) // game over
			GameOver();
		if (x == N - 1)  // to fix moving ('s' -> 'w')
			x = 0;
		if (field[x][y] == -1)
		{
			frogs = 0;  // to generate frogs each time again
			score += 1;
			tail -= 2;  // to increase tail after eating
		}
		head++;
		field[x][y] = head;
	}
}

void TailRemove()  // to limit tail from constant increasing
{
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (field[i][j] == tail)
			{
				field[i][j] = 0;
			}
		}
	}
	tail++;
}

void GameOver()
{
	printf("\a");
	Sleep(500);
	system("CLS");
	//printf("\n\n\n\n\n             GAME OVER\n\n");
	printf("\n\n\n\n\n             GAME OVER\n\n");
	printf("             Score: %d\n", score);
	printf("             Press ENTER to play again or ESC to exit\n");
	while (1)   // to continue the game or to end the game
	{
		var = getch_noblock();
		if (var == 13)
		{	
			game = 0;
			snake();
			break;
		}
		else if (var == 27)
		{
			game = 1;
			break;
		}
	}
	system("CLS");
}

void main()
{
	snake();
	while (game == 0)
	{
		print_field();
		ResetScreenPosition();
		random();
		movement();
		TailRemove();
		Sleep(speed); 
	}
}