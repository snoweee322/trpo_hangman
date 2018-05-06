#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void game();
void leaderboard();

void hangman(int n) //виселица
{
        switch (n)
    {
        case 9: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_ / \\  |@|  "); break;
        case 8: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_ /    |@|  "); break;
        case 7: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|\\  |@|\n_|_      |@|  "); break;
        case 6: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |  /|   |@|\n_|_      |@|  "); break;
        case 5: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |   |   |@|\n_|_      |@|  "); break;
        case 4: printf("  ____   |@|\n |   |   |@|\n |   o   |@|\n |       |@|\n_|_      |@|  "); break;
        case 3: printf("  ____   |@|\n |       |@|\n |       |@|\n |       |@|\n_|_      |@|  "); break;
        case 2: printf("         |@|\n |       |@|\n |       |@|\n |       |@|\n_|_      |@|  "); break;
        case 1: printf("         |@|\n         |@|\n         |@|\n         |@|\n___      |@|  "); break;
        case 0: printf("         |@|\n         |@|\n         |@|\n         |@|\n         |@|  "); break;
    }
}

int main()
{
    srand(time(NULL));
	char c;
	while (1) // switch-меню
	{
	    system("cls");
    	puts(" 1. Start game");
    	puts(" 2. Leaderboard");
    	puts(" 3. Exit");
    	c = getchar();
    	switch(c)
    	{
            case '1': {
			            system("cls");
			            puts(" 1. Normal mode");
			            puts(" 2. Survival mode");
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
	int word_size = strlen(word_buffer); // кол-во символов в слове
	char *hidden_word = (char*)malloc(word_size); // дин.массив с отгаданными буквами
	for (i = 0; i < word_size; i++) // заполнение массива прочерками (неизветные буквы)
    {
        hidden_word[i] = '_';
        hidden_word[i+1] = '\0';
    }
    int guessed_letters = word_size; // кол-во неотгаданных букв (счётчик)
    int wrong_letters = 0; // неправильно отгаданные буквы (до 9)
    char letter_array[50] = {NULL}; // массив, куда будут вводиться отгадываемые буквы
    int letter_count = 0;
    int flag = 0;
    while (guessed_letters >= 0 && wrong_letters <= 9)
    {
        if (flag == 1) // неотгаданная буква
        {
            wrong_letters++;
        }
        flag = 1;
        system("cls");
        printf("A WORD: >> %s <<\n", word_buffer); // ОТЛАДКА
        printf("GUESSED LETTERS: >> %d <<\n", guessed_letters); // ОТЛАДКА
        printf("WRONG LETTERS: >> %d <<\n", wrong_letters); // ОТЛАДКА
        hangman(wrong_letters);
        if (guessed_letters == 0) // условие победы
        {
            printf("%s", word_buffer);
            printf("\nYou won!\nPrint any key to countinue.\n\n");
            free(hidden_word);
            scanf(" %c");
            return; // выход в меню
        }
        if (wrong_letters == 9) // условие поражения
        {
            printf("%s", word_buffer);
            printf("\nYou lost!\nPrint any key to countinue.\n\n");
            free(hidden_word);
            scanf(" %c");
            return; // выход в меню
        }
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
                if (!(strchr(hidden_word + i, letter))) // если буква не отгадана
                {
                    flag = 0;
                    guessed_letters--;
                    hidden_word[i] = word_buffer[i];
                }
            } else if (strchr(letter_array, letter) || letter <= 96 || letter >= 123) // повторный ввод или неправильный ввод (a = 97 z = 122 по ascii)
            {
                flag = 0;
            }
        }
        if (!(strchr(letter_array, letter) || letter <= 96 || letter >= 123)) // запись ПРАВИЛЬНО введённых букв
        {
            letter_array[letter_count++] = letter;
        }
    }
    free(hidden_word);
    return;
}

void survival()
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
	int word_size = strlen(word_buffer); // кол-во символов в слове
	char *hidden_word = (char*)malloc(word_size); // дин.массив с отгаданными буквами
	for (i = 0; i < word_size; i++) // заполнение массива прочерками (неизветные буквы)
    {
        hidden_word[i] = '_';
        hidden_word[i+1] = '\0';
    }
    int guessed_letters = word_size; // кол-во неотгаданных букв (счётчик)
    int wrong_letters = 0; // неправильно отгаданные буквы (до 9)
    char letter_array[50] = {NULL}; // массив, куда будут вводиться отгадываемые буквы
    int letter_count = 0;
    int flag = 0;
    while (guessed_letters >= 0 && wrong_letters <= 9)
    {
        if (flag == 1) // неотгаданная буква
        {
            wrong_letters++;
        }
        flag = 1;
        system("cls");
        printf("A WORD: >> %s <<\n", word_buffer); // ОТЛАДКА
        printf("GUESSED LETTERS: >> %d <<\n", guessed_letters); // ОТЛАДКА
        printf("WRONG LETTERS: >> %d <<\n", wrong_letters); // ОТЛАДКА
        hangman(wrong_letters);
        if (guessed_letters == 0) // условие победы
        {
            printf("%s", word_buffer);
            printf("\nYou won!\nPrint any key to countinue.\n\n");
            free(hidden_word);
            scanf(" %c");
            return; // выход в меню
        }
        if (wrong_letters == 9) // условие поражения
        {
            printf("%s", word_buffer);
            printf("\nYou lost!\nPrint any key to countinue.\n\n");
            free(hidden_word);
            scanf(" %c");
            return; // выход в меню
        }
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
                if (!(strchr(hidden_word + i, letter))) // если буква не отгадана
                {
                    flag = 0;
                    guessed_letters--;
                    hidden_word[i] = word_buffer[i];
                }
            } else if (strchr(letter_array, letter) || letter <= 96 || letter >= 123) // повторный ввод или неправильный ввод (a = 97 z = 122 по ascii)
            {
                flag = 0;
            }
        }
        if (!(strchr(letter_array, letter) || letter <= 96 || letter >= 123)) // запись ПРАВИЛЬНО введённых букв
        {
            letter_array[letter_count++] = letter;
        }
    }
    free(hidden_word);
    return;
}

void leaderboard()
{
}
