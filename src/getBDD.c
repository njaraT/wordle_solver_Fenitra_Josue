#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"getBDD.h"

// Variables globales
char listeMots[TOTAL_WORDS][MAX_WORD_LENGTH];
char guess[MAX_WORD_LENGTH];
int num_try = 0, is_victory = 0, randomIndex;
char restart = ' ';

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void displayColorLetter(char* word, char* try) {
    for(int i = 0; i < MAX_WORD_LENGTH-1; i++) {
        if(try[i] == 'v') {
            printf("\e[0;32m");
            printf("%c ", word[i]);
        }
        else if(try[i] == 'o') {
            printf("\e[0;33m");
            printf("%c ", word[i]);
        }
        else {
            printf("\e[0m");
            printf("%c ", word[i]);
        }
    }
    printf("\e[0m\n");
}

void getWord(char* bddName, char words[TOTAL_WORDS][MAX_WORD_LENGTH]) {
    FILE* bdd_file = fopen(bddName, "r");
    if(bdd_file == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", bddName);
        exit(1);
    }
    
    char word[MAX_WORD_LENGTH];
    int numWord = 0;
    
    while(fgets(word, MAX_WORD_LENGTH, bdd_file) != NULL && numWord < TOTAL_WORDS) {
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        if(strlen(word) == MAX_WORD_LENGTH-1) {
            strcpy(words[numWord], word);
            numWord++;
        }
    }
    fclose(bdd_file);
}

int checkValidWord(char* word, char words[TOTAL_WORDS][MAX_WORD_LENGTH]) {
    for(int i = 0; i < TOTAL_WORDS; i++) {
        if(!strcmp(word, words[i])) {
            return 1;
        }
    }
    return 0;
}

void checkLetters(char* word, char* guess, char* try) {
    int wordCount[26] = {0}; 
    int guessCount[26] = {0};

    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        wordCount[word[i] - 'a']++;
        guessCount[guess[i] - 'a']++;
    }
    
    for(int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        if(word[i] == guess[i]) {
            try[i] = 'v';
            wordCount[word[i] - 'a']--; 
            guessCount[guess[i] - 'a']--; 
        }
    }
    
    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        if (try[i] != 'v') { 
            if (wordCount[guess[i] - 'a'] > 0) { 
                try[i] = 'o';
                wordCount[guess[i] - 'a']--;
            }
        }
    }
}

void filterByIncludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* included, int count) {
    for (int i = 0; i < TOTAL_WORDS; i++) {
        if (words[i][0] == '\0') continue;
        
        int match = 1;
        for (int j = 0; j < count; j++) {
            if (strchr(words[i], included[j]) == NULL) {
                match = 0;
                break;
            }
        }
        
        if (!match) {
            words[i][0] = '\0';
        }
    }
}

void filterByExcludedLetters(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* excluded, int count) {
    for (int i = 0; i < TOTAL_WORDS; i++) {
        if (words[i][0] == '\0') continue;
        
        for (int j = 0; j < count; j++) {
            if (strchr(words[i], excluded[j]) != NULL) {
                words[i][0] = '\0';
                break;
            }
        }
    }
}

void filterByLetterPosition(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char letter, int position) {
    if (position < 0 || position >= MAX_WORD_LENGTH-1) return;
    
    for (int i = 0; i < TOTAL_WORDS; i++) {
        if (words[i][0] == '\0') continue;
        
        if (words[i][position] != letter) {
            words[i][0] = '\0';
        }
    }
}

void filterBySubstring(char words[TOTAL_WORDS][MAX_WORD_LENGTH], char* substring) {
    for (int i = 0; i < TOTAL_WORDS; i++) {
        if (words[i][0] == '\0') continue;
        
        if (strstr(words[i], substring) == NULL) {
            words[i][0] = '\0';
        }
    }
}

void displayFilteredWords(char words[TOTAL_WORDS][MAX_WORD_LENGTH]) {
    int count = 0;
    printf("\nMots filtrés restants:\n");
    for (int i = 0; i < TOTAL_WORDS; i++) {
        if (words[i][0] != '\0') {
            printf("%-8s", words[i]);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    printf("\n\nTotal: %d mots possibles\n", count);
}

void applyFilters(char originalWords[TOTAL_WORDS][MAX_WORD_LENGTH]) {
    char input[100];
    char workingCopy[TOTAL_WORDS][MAX_WORD_LENGTH];
    
    for (int i = 0; i < TOTAL_WORDS; i++) {
        strcpy(workingCopy[i], originalWords[i]);
    }
    
    while (1) {
        system("clear || cls");
        displayFilteredWords(workingCopy);
        
        printf("\nOptions de filtre:\n");
        printf("1. Inclure des lettres (doivent être présentes)\n");
        printf("2. Exclure des lettres (ne doivent pas être présentes)\n");
        printf("3. Lettre à une position spécifique\n");
        printf("4. Sous-chaîne dans le mot\n");
        printf("5. Réinitialiser les filtres\n");
        printf("6. Quitter les filtres\n");
        printf("Choix: ");
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                printf("Entrez les lettres à inclure (sans espaces): ");
                scanf("%99s", input);
                toLowerCase(input);
                filterByIncludedLetters(workingCopy, input, strlen(input));
                break;
            }
            case 2: {
                printf("Entrez les lettres à exclure (sans espaces): ");
                scanf("%99s", input);
                toLowerCase(input);
                filterByExcludedLetters(workingCopy, input, strlen(input));
                break;
            }
            case 3: {
                printf("Entrez la lettre et la position (ex: a1): ");
                scanf("%99s", input);
                toLowerCase(input);
                if (strlen(input) >= 2 && isalpha(input[0]) && isdigit(input[1])) {
                    filterByLetterPosition(workingCopy, input[0], input[1] - '0');
                }
                break;
            }
            case 4: {
                printf("Entrez la sous-chaîne à rechercher: ");
                scanf("%99s", input);
                toLowerCase(input);
                filterBySubstring(workingCopy, input);
                break;
            }
            case 5: {
                for (int i = 0; i < TOTAL_WORDS; i++) {
                    strcpy(workingCopy[i], originalWords[i]);
                }
                break;
            }
            case 6: 
                return;
            default: 
                printf("Choix invalide.\n");
        }
    }
}
