#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include <stdbool.h>

void hangman(int n);

struct records
{
	char name[10];
	int sc;
} t1;

bool victory_check(int guessed_letters, char *word_buffer, char *hidden_word)
{
	if (guessed_letters == 0) // условие победы
	{
		printf("%s", word_buffer);
		printf("\nYou won!\nPrint any key to countinue.\n\n");
		free(hidden_word);
		getchar();
		return true;
	}
	return false;
}

bool defeat_check(int wrong_letters, char *word_buffer, char *hidden_word)
{
	if (wrong_letters == 9) // условие поражения
	{
		printf("%s", word_buffer);
		printf("\nYou lost!\nPrint any key to countinue.\n\n");
		free(hidden_word);
		getchar();
		return true;
	}
	return false;
}

bool wrong_letter_check(int flag, int *wrong_letters)
{
	if (flag == 1) // неотгаданная буква
	{
		(*wrong_letters)++;
		return true;
	}
	return false;
}

bool printed_letters(char *letter_array, char letter, int *letter_count)
{
	if (!(strchr(letter_array, letter) || letter <= 96 || letter >= 123)) // запись ПРАВИЛЬНО введённой буквы
	{
		letter_array[(*letter_count)++] = letter;
		return true;
	}
	return false;
}

bool letter_guessed(char *hidden_word, int i, char letter, int *flag, int *guessed_letters, char *word_buffer)
{
	if (!(strchr(hidden_word + i, letter))) // если буква ещё не была отгадана
	{
		*flag = 0;
		(*guessed_letters)--;
		hidden_word[i] = word_buffer[i];
		return true;
	}
	return false;
}

bool wrong_input(char *letter_array, char letter, int *flag)
{
	if (strchr(letter_array, letter) || letter <= 96 || letter >= 123) // повторный ввод или неправильный ввод (a = 97 z = 122 по ASCII)
	{
		*flag = 0;
		return true;
	}
	return false;
}

void game()
{
	FILE *st;
	int lines = 0;
	int random_line;
	char word_buffer[25]; // буфер для хранения строки (слова) из файла
	st = fopen("dictionary.txt", "r"); // чтение файла
	while (fscanf(st, "%s", word_buffer) != EOF) // вычисление количества строк в файле
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
	int word_size = strlen(word_buffer); // кол-во символов в слове
	char *hidden_word = (char*)malloc(word_size); // дин.массив с отгаданными буквами
	for (i = 0; i < word_size; i++) // заполнение массива прочерками (неизветные буквы)
	{
		hidden_word[i] = '_';
		hidden_word[i+1] = '\0';
	}
	int guessed_letters = word_size; // кол-во неотгаданных букв (счётчик)
	int wrong_letters = 0; // неправильно отгаданные буквы (до 9)
	char letter_array[50] = {0}; // массив, куда будут вводиться отгадываемые буквы
	int letter_count = 0;
	int flag = 0;
	while (guessed_letters >= 0 && wrong_letters <= 9)
	{
		wrong_letter_check(flag, &wrong_letters);
		flag = 1;
		system("clear");
		printf("A WORD: >> %s <<\n", word_buffer); // ОТЛАДКА
		printf("GUESSED LETTERS: >> %d <<\n", guessed_letters); // ОТЛАДКА
		printf("WRONG LETTERS: >> %d <<\n", wrong_letters); // ОТЛАДКА
		hangman(wrong_letters);
		if (victory_check(guessed_letters, word_buffer, hidden_word) == true) return; // условие победы
		if (defeat_check(wrong_letters, word_buffer, hidden_word) == true) return; // условие поражения
		printf("%s", hidden_word); // скрытое слово
		printf("\nEntered letters:\n");
		printf("%s", letter_array); // введенные буквы
		printf("\nPrint a letter: ");
		char letter = -1;
		scanf(" %c", &letter);
		for (i = 0; i < word_size; i++) // проверка введеных букв
		{
			if (word_buffer[i] == letter)
			{
				letter_guessed(hidden_word, i, letter, &flag, &guessed_letters, word_buffer);
			} 
			else wrong_input(letter_array, letter, &flag);
		}
		printed_letters(letter_array, letter, &letter_count);
	}
	free(hidden_word);
	return;
}

bool random_line_check(int *prov, int random_line)
{
	if (prov[random_line])
	{
		prov[random_line] = 0;
		return true;
	}
	return false;
}

void survival()
{
	FILE *st;
	int lines = 0; // кол-во строк
	int random_line; // случайная строка
	int i; // счетчик
	int word_size; // кол-во символов в слове
	int guessed_letters; // кол-во неотгаданных букв (счетчик)
	char word_buffer[25]; // буфер для хранения строки (слова)  из файла
	char letter_array[50]; // массив использованных букв
	int letter_count = 0;
	int lives = 9;
	int flag = 0;
	int score = 0; // очки
	char letter;
	st = fopen("dictionary.txt", "r"); // чтение файла
	while (fscanf(st, "%s", word_buffer) != EOF) // вычисление кол-ва строк в файле
	{
		lines++;
	}
	int *prov = (int*)malloc(4*lines); // массив под проверку встречающихся слов
	for (i = 0; i < lines; i++) prov[i] = 1;
	fclose(st);
	while (1)
	{
		while (!(score == lines*100)) // проверка на повторяющиеся слова
		{
			random_line = rand() % lines; // выбор случайной строки
			if (random_line_check(prov, random_line) == true)
			break;
		}
		st = fopen("dictionary.txt", "r"); // чтение файла
		rewind(st); // перемещение указателя в начало файла
		for (i = 0; i < random_line; i++)
		{
			fscanf(st, "%s", word_buffer); // считывание слова, которое будет загадано
		}
		fclose(st);
		word_size = strlen(word_buffer); // длина слова
		char *hidden_word = (char*)malloc(word_size); // дин массив с отгаданными буквами
		for (i = 0; i < word_size; i++) // заполнение массива звездочками (неизвестные буквы)
		{
			hidden_word[i] = '*';
			hidden_word[i+1] = '\0';
		}
		hidden_word[0] = word_buffer[0];
		hidden_word[word_size - 1] = word_buffer[word_size - 1];
		guessed_letters = word_size - 2; // кол-во неотгаданных букв (счетчик)
		for (i = 0; i < 50; i++) letter_array[i] = 0; // массив использованных букв
		if (word_buffer[word_size - 1] == word_buffer[0]) // проверка первой и последней буквы, чтобы в массиве использованных букв не было двух одинаковых символов
		{
			letter_array[0] = word_buffer[0];
		}
		else
		{
			letter_array[1] = word_buffer[word_size - 1];
			letter_array[0] = word_buffer[0];
		}
		for (i = 1; i < word_size - 1; i++) // проверка не встречаются ли еще в слове первая или последняя буквы
		{
			if (word_buffer[i] == word_buffer[0])
			{
				hidden_word[i] = word_buffer[0];
				guessed_letters--;
			}
			if (word_buffer[i] == word_buffer[word_size - 1])
			{
				hidden_word[i] = word_buffer[word_size - 1];
				guessed_letters--;
			}
		}
		letter_count = 2;
		flag = 0;
		while (guessed_letters > 0) // пока кол-во неотгаданных букв
		{
			if (flag == 1) // неотгаданная буква
			{
				lives--;
			}
			flag = 1;
			system("clear");
			printf("A WORD: >> %s <<\n", word_buffer); // ОТЛАДКА
			printf("GUESSED LETTERS: >> %d <<\n", guessed_letters); // ОТЛАДКА
			printf("Your lives: %d\n",lives);
			printf("Score: %d\n",score);
			hangman(9 - lives);
			printf("%s", hidden_word); // скрытое слово
			printf("\nEntered letters:\n");
			printf("%s", letter_array); // введенные буквы
			printf("\nPrint '0' to exit.");
			printf("\nPrint a letter: ");
			letter = -1;
			if (!lives == 0) scanf(" %c", &letter);
			if (letter == 48) lives = 0;
			if (lives == 0) // условия окончания игры
			{
				free(hidden_word);
				system("clear");
				printf("%s", word_buffer);
				printf("\nYour score = %d\nDo you want to save your result y/n?\n\n",score);
				char k;
				scanf("%s", &k);
				if(k == 'y')
				{
					st = fopen("records.dat","ab"); // открытие бинарного файла для записи рекордов
					printf("\n Name:"); scanf("%s", t1.name);
					t1.sc = score;
					fwrite(&t1, sizeof(t1), 1, st); // записсь структуры в файл
					fclose(st);
				}
				return; // выход в меню
			}
			for (i = 1; i < word_size - 1; i++) // проверка введенных букв
			{
				if (word_buffer[i] == letter)
				{
					letter_guessed(hidden_word, i, letter, &flag, &guessed_letters, word_buffer);
				}
				else wrong_input(letter_array, letter, &flag);
			}
			printed_letters(letter_array, letter, &letter_count);
		}
		free(hidden_word);
		if(lives < 9 && lives > 0) lives++;
		if(lives > 0) score += 100;
	}
	free(prov);
}

void leaderboard()
{
	FILE *st;
	int i;
	system("clear");
	st = fopen("records.dat", "rb"); // открытие бинарного файла для чтения
	i = 1;
	fread(&t1, sizeof(t1), 1, st); // чтение из файла структуры t1
	while (!feof(st))
	{
		printf("\n %3d)%10s............................%4d",i, t1.name, t1.sc);
		fread(&t1, sizeof(t1), 1, st);
		i++;
	}
	printf("\n");
	fclose(st);
	getchar();
}
