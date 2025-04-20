#ifndef CODE_EXO1
#define CODE_EXO1

#include<stdio.h>

// constantes si necessaires pour la taille du terrain
#define L 6
#define C 8

typedef int Terrain [L+2][C+2];

extern const int PAVE[10][2];

// fonctions pour le terrain seulement
void initialiser(Terrain);
void afficher(FILE *, Terrain);
int  detruire(Terrain, int, int);


// fonctions pour le joueur
void trouver(Terrain, int, int*, int*);
int  placer(Terrain, int, int, int);
int  deplacer(Terrain, int, int);
int  bloque(Terrain, int);
int connexe(Terrain, int, int);

#endif
