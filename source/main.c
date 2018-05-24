#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void game();
void survival();
void leaderboard();

int main(int argc, char *argv[])
{
	srand(time(NULL));
	char c;
	while (1) // switch-меню
	{
		system("clear");
		printf(" 1. Start game\n");
		printf(" 2. Leaderboard\n");
		printf(" 3. Exit\n");
		c = getchar();
		switch(c)
		{
			case '1':
			{
				system("clear");
				printf(" 1. Normal mode\n");
				printf(" 2. Survival mode\n");
				scanf("%s", &c);
				switch(c)
				{
					case '1': game(); break; // вызов game()
					case '2': survival(); break; // вызов survival()
				}
			} break;
			case '2': leaderboard(); break; // вызов leaderboard()
			case '3': return 0; // выход
			default : puts("Wrong key");
		}
	}
	return 0;
}
