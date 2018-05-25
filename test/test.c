#define CTEST_MAIN

#include <stdbool.h>
#include <ctest.h>
#include "functions.h"
#include <string.h>

CTEST(END_CONDITION, WIN_T) // условие победы
{
	int guessed_letters = 0;
	char word_buffer[25];
	strcpy(word_buffer, "nothing");
	char hidden_word[25];
	strcpy(hidden_word, "123213");
	bool result = victory_check(guessed_letters, word_buffer, hidden_word);
	ASSERT_TRUE(result);
}

CTEST(END_CONDITION, WIN_F) // условие победы (ложь)
{
	int guessed_letters = 3;
	char word_buffer[25];
	strcpy(word_buffer, "nothing");                 
	char hidden_word[25];
	strcpy(hidden_word, "123213");
	bool result = victory_check(guessed_letters, word_buffer, hidden_word);
	ASSERT_FALSE(result);
}

CTEST(END_CONDITION, DEFEAT_T) // условие поражения
{
	int wrong_letters = 9;
	char word_buffer[25];
	strcpy(word_buffer, "nothing");
	char hidden_word[25];
	strcpy(hidden_word, "123213");
	bool result = defeat_check(wrong_letters, word_buffer, hidden_word);
	ASSERT_TRUE(result);
}

CTEST(END_CONDITION, DEFEAT_F) // условие поражения (ложь)
{
	int wrong_letters = 5;
	char word_buffer[25];
	strcpy(word_buffer, "nothing");
	char hidden_word[25];
	strcpy(hidden_word, "123213");
	bool result = defeat_check(wrong_letters, word_buffer, hidden_word);
	ASSERT_FALSE(result);
}

CTEST(INPUT_CHECK, WRONG_LETTER_T) // увеличение счётчика при вводе неправильной буквы (нет в слове)
{
	int flag = 1;
	int wrong_letters = 1;
	bool result = wrong_letter_check(flag, &wrong_letters);
	ASSERT_TRUE(result);
}

CTEST(INPUT_CHECK, WRONG_LETTER_F) // увеличение счётчика при вводе правильной буквы (есть в слове)
{
	int flag = 0;
	int wrong_letters = 1;
	bool result = wrong_letter_check(flag, &wrong_letters);
	ASSERT_FALSE(result);
}
	
CTEST(INPUT_CHECK, PRINT_T) // ввод корректной буквы
{
	char letter_array[50] = {0};
	char letter = 'e';
	int letter_count = 0;
	bool result = printed_letters(letter_array, letter, &letter_count);
	ASSERT_TRUE(result);
}

CTEST(INPUT_CHECK, PRINT_F) // ввод некорректного символа
{
	char letter_array[50] = {0};
	char letter = '3';
	int letter_count = 0;
	bool result = printed_letters(letter_array, letter, &letter_count);
	ASSERT_FALSE(result);
}

CTEST(INPUT_CHECK, GUESSED_T) // буква угадана
{
	char word_buffer[25];
	strcpy(word_buffer, "nothing");
	int guessed_letters = 0;
	int flag;
	char letter = 'n';
	int i = 0;
	char hidden_word[25];
	strcpy(hidden_word, "_________");
	bool result = letter_guessed(hidden_word, i, letter, &flag, &guessed_letters, word_buffer);
	ASSERT_TRUE(result);
}

CTEST(INPUT_CHECK, GUESSED_F) // буква угадана (ложь)
{
	char word_buffer[25];
	strcpy(word_buffer, "nothing");
	int guessed_letters = 0;
	int flag;
	char letter = 'a';
	int i = 0;
	char hidden_word[25];
	strcpy(hidden_word, "_________");
	bool result = letter_guessed(hidden_word, i, letter, &flag, &guessed_letters, word_buffer);
	ASSERT_TRUE(result);
}

CTEST(INPUT_CHECK, WRONG_INPUT) // повторный ввод или неправильный ввод
{
	char letter_array[50] = {0};
	char letter = 'Q';
	int flag = 1;
	bool result = wrong_input(letter_array, letter, &flag);
	ASSERT_TRUE(result);
}
	
int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}
