#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void game();
void leaderboard();

int main()
{
	char c;
	while (1) // switch-����
	{
    	puts(" 1. Start game");
    	puts(" 2. Leaderboard");
    	puts(" 3. Exit");
    	c = getch();
    	switch(c)
    	{
			case '1': game(); break; // ����� game()
			case '2': leaderboard(); break; // ����� leaderboard()
			case '3': return 0; // �����
			default : puts("Wrong key");
		}
	}
	return 0;
}

void game()
{
    FILE *st;
    int lines = 0;
    char word_buffer[25]; // ����� ��� �������� ������ �� �����
    st = fopen("dictionary.txt", "r"); // ������ �����
    while (fscanf(st, "%s", &word_buffer) != EOF) // ���������� ���������� ����� � �����
	{
        lines++;
    }
    printf("%d",lines);
} 

void leaderboard()
{
}
