#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

bool victory_check(int guessed_letters, char *word_buffer, char *hidden_word);
bool defeat_check(int wrong_letters, char *word_buffer, char *hidden_word);
bool wrong_letter_check(int flag, int *wrong_letters);
bool printed_letters(char *letter_array, char letter, int *letter_count);
bool letter_guessed(char *hidden_word, int i, char letter, int *flag, int *guessed_letters, char *word_buffer);
bool wrong_input(char *letter_array, char letter, int *flag);

#endif
