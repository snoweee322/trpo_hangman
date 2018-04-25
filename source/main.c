#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void game();
void leaderboard();

int main()
{
	char c;
	while (1) // switch-меню
	{
    	puts(" 1. Start game");
    	puts(" 2. Leaderboard");
    	puts(" 3. Exit");
    	c = getch();
    	switch(c)
    	{
			case '1': game(); break; // вызов game()
			case '2': leaderboard(); break; // вызов leaderboard()
			case '3': return 0; // выход
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
    char word_buffer[25]; // буфер для хранения строки (слова) из файла
    st = fopen("dictionary.txt", "r"); // чтение файла
    while (fscanf(st, "%s", &word_buffer) != EOF) // вычисление количества строк в файле
	{
        lines++;
    }
    random_line = rand() % lines; // выбор слова (выбор случайной строки)
    rewind(st); // перемещение указателя в начало файла
    int i;
    for (i = 0; i < random_line; i++) 
	{
		fscanf(st, "%s", word_buffer); // считывание слова, которое будет загадано
	}
	fclose(st);
	int world_size = strlen(word_buffer);
	printf("%d", world_size);
}

void leaderboard()
{
}
