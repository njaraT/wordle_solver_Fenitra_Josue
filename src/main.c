#include "getBDD.h"

int main() {
    srand(time(NULL));
    
    printf("Chargement du fichier de mots...\n");
    if (access("ressource/bdd_wordle_clean.txt", F_OK) == -1) {
        printf("Erreur: Le fichier de mots est introuvable.\n");
        printf("Veuillez placer bdd_wordle_clean.txt dans le dossier ressource/\n");
        return 1;
    }
    getWord("ressource/bdd_wordle_clean.txt", listeMots);
    
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
