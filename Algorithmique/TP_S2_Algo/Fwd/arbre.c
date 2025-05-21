#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"

arbre * feuille(char c){
  arbre *A = (arbre*)malloc(sizeof(arbre));
  if (A==NULL)
  {
    return NULL;
  }
  A->data = c ;
  A->gauche = NULL;
  A-> droite = NULL;
  return A;
}

arbre * noeud(char c, arbre * g, arbre * d){
  arbre *A = (arbre*)malloc(sizeof(arbre));
  if (A==NULL)
  {
    return NULL;
  }
  A->data = c ;
  A->gauche = g;
  A-> droite = d;
  return A ; 
}

int est_feuille(arbre * a) {
  if ((a->gauche == NULL)&&(a->droite == NULL))
  {
    return 1;
  }
  return 0;
}

void libere_arbre(arbre ** a){
  if ((*a)!=NULL) return ;
  {
  libere_arbre(&((*a)->gauche));
  libere_arbre(&((*a)->droite));
  free(*a);
  *a=NULL; 
  }
}

void infixe_inverse(FILE * f, arbre * a) {
  if (a!=NULL)
  {
    infixe_inverse(f,a->droite);
    fprintf (f, "%c\n", a->data);
    infixe_inverse(f,a->gauche);
  }
 
}

void imprime_blancs(FILE * f, int niveau, int est_droit) {
  for (int i=0 ; i< niveau; i++)
  {
    fprintf(f,"   ");
  }
  if (est_droit)
  {
    fprintf(f,"/-");
  }
  else
  {
    if (niveau!=0) {
      fprintf(f,"\\-");
    }
  }
  
}

void imprime_avec_blancs(FILE * f, arbre * a, int niveau, int est_droit) {
  if (est_feuille(a))
  {
    imprime_blancs (f, niveau ,est_droit);
    fprintf (f, "%c\n", a->data);
  }
  else
  {
    imprime_avec_blancs(f,a->droite, niveau+1, 1);
    imprime_blancs(f, niveau, est_droit);
    fprintf (f, "%c\n", a->data);
    imprime_avec_blancs(f,a->gauche, niveau+1, 0);
  }
}

void imprime_arbre(FILE * f, arbre * a){
  imprime_avec_blancs(f, a, 0, 0);
}


