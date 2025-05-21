#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "huffman.h"

arbrepoids * cree_arbrepoids(arbre * a, int poids) {
  arbrepoids * ap =  malloc(sizeof(struct arbrepoids));
  if (ap != NULL) {
    ap->element = a;
    ap->poids = poids;
  }
  return ap;
}

liste * cree_liste(arbre * a, int poids, liste *suivant) {
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
  int freqs[256] = {0};
  
  for (int i = 0; s[i] != '\0'; i++) 
  {
    unsigned char c = s[i];
    freqs[c]++;
  }
  liste * l = NULL;
  for (int i = 0; i < 256; i++) {
    if (freqs[i] > 0) {
        arbre *a = feuille((char)i);
        l=cree_liste(a , freqs[i], l);
    }
  }
  return l;
}

arbrepoids * extrait_min(liste ** l) {
  if (l == NULL || *l == NULL) return NULL;
  liste *curr=*l, *prev=NULL ;
  liste *min_prev=NULL, *min_node=*l ;
  while (curr != NULL)
  {
    if ( curr->data->poids < min_node->data->poids)
    {
      min_prev = prev ; 
      min_node = curr ; 
    }
    prev=curr;
    curr = curr->suivant; 
  }
  if (min_prev==NULL)
  {
    *l = min_node ->suivant;
  }
  else
  {
    min_prev->suivant = min_node->suivant;
  }
  arbrepoids *res = min_node->data;
  free(min_node);
  return res;
}

arbre * huffman(char * s) {
  liste *l= genere_liste(s);
  while (l!= NULL && l->suivant!=NULL)
  {
    arbrepoids * ap1 = extrait_min(&l);
    arbrepoids * ap2 = extrait_min(&l);
    arbre *fusion = noeud('*', ap1->element, ap2->element);
    int poids_total = ap1->poids + ap2->poids ; 
    l= cree_liste (fusion, poids_total, l);
    free(ap1);
    free(ap2);
  }
  arbre *result = NULL ; 
  if (l != NULL)
  {
    result = l->data->element ; 
    free (l->data);
    free (l);
  }
  return result;
}
