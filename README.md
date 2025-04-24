# wordle_solver_Fenitra_Josue

# Installation :
 
Dans un repertoire cloner le repo. On suppose que vous souhaiter le cloner dans Documents.

```bash
cd ~/Documents
git clone https://github.com/njaraT/wordle_solver_Fenitra_Josue.git
```
# Compilation :

```bash
cd ~/Documents/wordle_solver_Fenitra_Josue
mkdir bin
gcc -o bin/main -I include/ src/getBDD.c src/main.c
```
# Utilisation :

```bash
cd ~/Documents/wordle_solver_Fenitra_Josue
bin/main
```

Suivre les instructions du jeu, taper un mot de 5 lettres puis taper sur la touche entree. Si la lettre est verte alors elle est bien placee si elle est orange alors la lettre est dans le mot mais mal positionnee sinon la lettre n'est pas dans le mot. Vous avez 6 essaies.

Tapez "filtre" avant le 6ᵉ essai si vous n'avez aucune idée du mot à chercher. Cela permet de tricher, de relancer le jeu à zéro et de rechercher le mot en utilisant des filtres. Ensuite, choisissez l'option que vous voulez :

Choix 1 : Indiquez les lettres en vert (correctes) ou en orange (mal placées) que vous avez trouvées pendant vos 5 essais précédents pour afficher toutes les possibilités.

Choix 2 : Excluez les lettres qui ne changent pas de couleur (lettres absentes) des mots suggérés.

Choix 3 : Spécifiez les lettres en vert pour trouver les mots avec la lettre à cette position exacte. Exemple : i2 pour "taint" (le i est en 2ᵉ position).

Choix 4 : Entrez une suite de lettres que vous pensez correctes pour affiner votre recherche. Exemple : int pour afficher taint, intro, minty...

Choix 5 : Réinitialisez les filtres si vous pensez avoir fait une erreur dans votre recherche.

Choix 6 : Fermez les filtres et recommencez le jeu au 1ᵉʳ essai avec le même mot à trouver.
