#ifndef GETBDD_H
#define GETBDD_H

#define MAX_LINE_LEN 2200
#define TOTAL_WORDS 2315  // Ajusté pour correspondre au fichier
#define MAX_WORD_LENGTH 6

void generateBDD(char* input_file, char* output_file);
void getWord(char* bddName, char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
int checkValidWord(char* word, char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
void checkLetters(char* word, char* guess, char* try);
void displayColorLetter(char* word, char* try);
void filterByIncludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* included, int count);
void filterByExcludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* excluded, int count);
void filterByLetterPosition(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char letter, int position);
void filterBySubstring(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* substring);
void displayFilteredWords(char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
#endif
