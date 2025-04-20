#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"

arbre * feuille(char c){
  arbre * a = malloc(sizeof(arbre));
  a->gauche = NULL;
  a->droite = NULL;
  a->data = c;
  return a;
}

arbre * noeud(char c, arbre * g, arbre * d){
  arbre * a = malloc(sizeof(arbre));
  a->gauche = g;
  a->droite = d;
  a->data = c;
  return a;
}

int est_feuille(arbre * a) {
  return (a->gauche == NULL && a->droite == NULL);
}

void libere_arbre(arbre ** a){
  if ((*a)){
    libere_arbre(&(*a)->gauche);
    libere_arbre(&(*a)->droite);
    free(*a);
    *a = NULL;
  }
  return;
}

void infixe_inverse(FILE * f, arbre * a) {
  if (a){
    infixe_inverse(f, a->droite);
    fprintf(f, "%c\n", a->data);
    infixe_inverse(f, a->gauche);
  }
  return;
}

void imprime_blancs(FILE * f, int niveau, int est_droit) {
  for(int i = 0; i < niveau; i++){
    fprintf(f, "   ");
  }
  if(niveau!=0){
    if(est_droit == 1){
      fprintf(f, "/-");
    }
    else{
      fprintf(f, "\\-");
    }
  }
  else{
    return;
  }
}

void imprime_avec_blancs(FILE * f, arbre * a, int niveau, int est_droit) {
  if (a){
    imprime_avec_blancs(f, a->droite, niveau+1, 1);
    imprime_blancs(f, niveau, est_droit);
    fprintf(f, "%c\n", a->data);
    imprime_avec_blancs(f, a->gauche, niveau+1, 0);
  }
  else{
    return;
  }
}


void imprime_arbre(FILE * f, arbre * a){
  imprime_avec_blancs(f, a, 0, -1);
}


// int main(int argc, char ** argv) {

//   arbre * a=noeud('b',
//                 feuille('a'),
//                 noeud('d',
//                       feuille('c'),
//                       noeud('f', feuille('e'), feuille('g'))));;

//   imprime_arbre(stdout, a);
// }
