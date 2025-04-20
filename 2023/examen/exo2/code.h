#ifndef CODE_EXO1
#define CODE_EXO1

#include<stdio.h>

typedef int ** Terrain;

// Jeu
// champ terrain -> dynamique
// champs L et C
typedef struct Jeu {

} Jeu;




extern const int PAVE[10][2];

// fonctions pour le terrain seulement
void initialiser(Jeu* jeu, int l, int c);
void liberer(Jeu* jeu);
void afficher(FILE *, Jeu);
int  detruire(Jeu, int, int);


// fonctions pour le joueur
void trouver(Jeu, int, int*, int*);
int  placer(Jeu, int, int, int);
int  deplacer(Jeu, int, int);
int  bloque(Jeu, int);
int  connexe(Jeu, int, int);

#endif