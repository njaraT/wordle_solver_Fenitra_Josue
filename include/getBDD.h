#ifndef GETBDD_H
#define GETBDD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE_LEN 2200
#define TOTAL_WORDS 2315
#define MAX_WORD_LENGTH 6

// Structures de données
extern char listeMots[TOTAL_WORDS][MAX_WORD_LENGTH];
extern char guess[MAX_WORD_LENGTH];
extern int num_try, is_victory, randomIndex;
extern char restart;

// Prototypes des fonctions
void toLowerCase(char* str);
void displayColorLetter(char* word, char* try);
int checkValidWord(char* word, char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
void checkLetters(char* word, char* guess, char* try);
void filterByIncludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* included, int count);
void filterByExcludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* excluded, int count);
void filterByLetterPosition(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char letter, int position);
void filterBySubstring(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* substring);
void displayFilteredWords(char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
void getWord(char* bddName, char words[TOTAL_WORDS][MAX_WORD_LENGTH]);
void applyFilters(char originalWords[TOTAL_WORDS][MAX_WORD_LENGTH]);

#endif
