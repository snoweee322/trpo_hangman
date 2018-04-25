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
    int random_line;
    char word_buffer[25]; // ����� ��� �������� ������ (�����) �� �����
    st = fopen("dictionary.txt", "r"); // ������ �����
    while (fscanf(st, "%s", &word_buffer) != EOF) // ���������� ���������� ����� � �����
	{
        lines++;
    }
    random_line = rand() % lines; // ����� ����� (����� ��������� ������)
    rewind(st); // ����������� ��������� � ������ �����
    int i;
    for (i = 0; i < random_line; i++) 
	{
		fscanf(st, "%s", word_buffer); // ���������� �����, ������� ����� ��������
	}
	fclose(st);
	int world_size = strlen(word_buffer);
	printf("%d", world_size);
}

void leaderboard()
{
}
