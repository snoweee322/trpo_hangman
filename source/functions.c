#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool victory_check(int guessed_letters, char *word_buffer, char *hidden_word)
{
	if (guessed_letters == 0) // условие победы
	{
		return true;
	}
	return false;
}

bool defeat_check(int wrong_letters, char *word_buffer, char *hidden_word)
{
	if (wrong_letters == 9) // условие поражения
	{
		return true;
	}
	return false;
}

bool wrong_letter_check(int flag, int *wrong_letters)
{
	if (flag == 1) // неотгаданная неправильно буква
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
