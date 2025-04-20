#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include <stddef.h>
#include <assert.h>
#include "huffman.h"

arbrepoids * cree_arbrepoids(arbre * a, int poids) {
  arbrepoids * ap =  malloc(sizeof(struct arbrepoids));
  if (ap != NULL) {
    ap->element = a;
    ap->poids = poids;
  }
  return ap;
}

liste * cree_liste(arbre * a, int poids, liste * suivant) {
  liste * res = malloc(sizeof(struct liste));

  if (res != NULL) {
    arbrepoids * ap = cree_arbrepoids(a, poids);
    if (ap != NULL) {
      res->data = ap;
    }
    res->suivant = suivant;
  }

  return res;
}

liste * genere_liste(char * s) {
  int tab[256];
  int i = 0;
  
  while(s[i]!='\0'){
    tab[(unsigned char)s[i]]++;
    i++;
  }

  liste * l = NULL;
  for(int i=0; s[i]!='\0'; i++){
    if (tab[i]>0){
      arbre * a = feuille(s[i]);
      l = cree_liste(a, tab[i], l);
    }
  }

  return l;
}

arbrepoids * extrait_aux(liste ** l, int min, arbrepoids * a){
  if (*l!=NULL){
    if (min > (*l)->data->poids){
      min = (*l)->data->poids;
      a = (*l)->data;
      (*l)->data = (*l)->suivant->data;
      extrait_aux(&(*l), min, a);
    }
    else{
      extrait_aux(&(*l)->suivant, min, a);
    }
  }
  return a;
}

arbrepoids * extrait_min(liste ** l) {
  return extrait_aux(l, (*l)->data->poids, (*l)->data);
}

arbre * huffman(char * s) {
  liste * l = genere_liste(s);
  arbrepoids * a = cree_arbrepoids()
}

// Fonction pour compter les éléments d'une liste
int compter_elements(liste *l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->suivant;
    }
    return count;
}


