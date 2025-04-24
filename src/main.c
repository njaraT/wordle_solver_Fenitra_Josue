#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getBDD.h"
#include <time.h>
#include <ctype.h>
#include <unistd.h>

char listeMots[TOTAL_WORDS][MAX_WORD_LENGTH];
char guess[MAX_WORD_LENGTH];
int num_try = 0, is_victory = 0, randomIndex;
char restart = ' ';

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
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

int main() {
    printf("Chargement du fichier de mots...\n");
    if (access("../ressource/bdd_wordle_clean.txt", F_OK) == -1) {
        printf("Erreur: Le fichier de mots est introuvable.\n");
        printf("Veuillez placer bdd_wordle_clean.txt dans le dossier ressource/\n");
        return 1;
    }
    getWord("../ressource/bdd_wordle_clean.txt", listeMots);
    
    while (restart != 'q') {
        num_try = 0;
        is_victory = 0;
        randomIndex = rand() % TOTAL_WORDS;
        
        while (num_try < 6) {
            printf("Essai numéro: %d\n", num_try + 1);
            printf("Entrez un mot de 5 lettres (ou 'filtre' pour filtrer):\n");
            
            scanf("%19s", guess);
            toLowerCase(guess);
            
            if (strcmp(guess, "filtre") == 0) {
                applyFilters(listeMots);
                continue;
            }
            
            if (strlen(guess) != 5) {
                printf("Le mot doit faire exactement 5 lettres\n");
                continue;
            }
            
            if (!checkValidWord(guess, listeMots)) {
                printf("Entrez un mot valide de 5 lettres:\n");
                continue;
            }
            
            char try[] = "xxxxx";
            checkLetters(listeMots[randomIndex], guess, try);
            printf("--------------------------\n");
            displayColorLetter(guess, try);
            printf("--------------------------\n");
            
            if (!strcmp(try, "vvvvv")) {
                is_victory = 1;
                printf("Vous avez gagné\n");
                break;
            }
            
            num_try++;
        }
        
        if (is_victory) {
            switch(num_try) {
                case 1: printf("Fantastique, vous avez réussi en %d essai\n", num_try); break;
                case 2: printf("Très bien, vous avez réussi en %d essais\n", num_try); break;
                case 3: printf("Bien joué, vous avez réussi en %d essais\n", num_try); break;
                case 4: printf("Pas mal, vous avez réussi en %d essais\n", num_try); break;
                case 5: printf("Bien, vous avez réussi en %d essais\n", num_try); break;
                case 6: printf("Ouf, vous avez réussi en %d essais\n", num_try); break;
            }
        } else {
            printf("Dommage, vous auriez dû deviner %s\n", listeMots[randomIndex]);
        }
        
        printf("Voulez-vous recommencer? Appuyez sur une touche pour continuer ou 'q' pour quitter\n");
        scanf(" %c", &restart);
    }
    
    return 0;
}
