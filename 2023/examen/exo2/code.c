#include "code.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

const int PAVE[10][2] = { {0,0}, {+1, -1}, {+1, 0}, {+1, +1}, {0, -1}, {0, 0}, {0, +1}, {-1, -1}, {-1, 0}, {-1, +1}};

void initialiser(Jeu * jeu, int L, int C) {

}

void liberer(Jeu * jeu) {

}


int detruire(Jeu jeu, int i, int j) {
  
}  

void afficher(FILE * file, Jeu jeu) {

}


int  bloque(Jeu jeu, int numero) {

   return 2;
} 

void trouver(Jeu jeu, int numero, int *pi, int *pj) {
 
}


int  placer(Jeu jeu, int numero, int i, int j) {

   return 1;
}

int deplacer(Jeu jeu, int numero, int position) {
  

   return 0;
}


void parcours(Terrain terrain, int j1, int j2, int i, int j, int *r){
 
} 

int connexe(Jeu jeu, int j1, int j2) {
  

   return 0;
}
