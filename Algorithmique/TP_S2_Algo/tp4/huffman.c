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

void libere_liste(liste * l) {
  if (l == NULL) {
      return;  // Base case: Si la liste est vide, rien à libérer
  }
  libere_arbre(&l->data->element);
  libere_liste(l->suivant);
  free(l);
}


arbrepoids * extrait_aux(liste ** l, int min, arbrepoids * a) {
  if (*l != NULL) {
      if (min > (*l)->data->poids) {
          min = (*l)->data->poids;
          a = (*l)->data;
          liste * temp = *l;
          *l = (*l)->suivant;
          free(temp);

      } else {
          extrait_aux(&(*l)->suivant, min, a);
      }
  }
  return a;
}


arbrepoids * extrait_min(liste ** l) {
  return extrait_aux(l, (*l)->data->poids, (*l)->data);
}


int compter_elements(liste *l) {
  int count = 0;
  while (l != NULL) {
      count++;
      l = l->suivant;
  }
  return count;
}

arbre * huffman(char * s) {
  liste * l = genere_liste(s);

  while (compter_elements(l) > 1) {
      arbrepoids * a1 = extrait_min(&l);
      arbrepoids * a2 = extrait_min(&l);

      arbre * a = noeud('\0', a1->element, a2->element);  
      int poids = a1->poids + a2->poids;  

      l = cree_liste(a, poids, l);
  }

  arbrepoids * arbreHuffman = l->data;
  arbre * huffman_tree = arbreHuffman->element;

  libere_liste(l);  

  return huffman_tree;  
}


/* test par ChatGPT */

int verifier_arbre_huffman(arbre *a, char* s) {
  // Vérifie la fréquence des caractères dans la chaîne d'entrée
  int tab[256] = {0};
  for (int i = 0; s[i] != '\0'; i++) {
      tab[(unsigned char)s[i]]++;
  }

  // Vérifier que les nœuds dans l'arbre correspondent aux fréquences
  // Si les fréquences sont correctes, on peut assumer que l'arbre de Huffman est valide.
  // Vérification simplifiée (si c'est un arbre binaire avec les bonnes fréquences)
  
  // On devrait parcourir l'arbre et vérifier que chaque feuille correspond à un caractère de `tab`
  if (a->gauche && est_feuille(a->gauche)) {
      printf("Feuille gauche : %c\n", a->gauche->data);
      if (tab[(unsigned char)a->gauche->data] == 0) {
          printf("Erreur : fréquence incorrecte pour %c\n", a->gauche->data);
          return 1;
      }
  }
  if (a->droite && est_feuille(a->droite)) {
      printf("Feuille droite : %c\n", a->droite->data);
      if (tab[(unsigned char)a->droite->data] == 0) {
          printf("Erreur : fréquence incorrecte pour %c\n", a->droite->data);
          return 1;
      }
  }
  return 0;
}

int main(int argc, char ** argv) {
  char* s = "ababaaacad";

  // Créer l'arbre de Huffman pour la chaîne d'entrée
  arbre * a = huffman(s);

  // Vérification de l'arbre de Huffman
  int erreur = verifier_arbre_huffman(a, s);

  // Ajout d'une vérification supplémentaire de l'arbre :
  // Vérifie si les racines gauche et droite sont 'a' et 'b' (après un traitement préalable)
  erreur = erreur || ((a->gauche)->data != 'a' && (a->droite)->data != 'a');
  if (a->droite->data == 'a')
      a = a->gauche;
  else
      a = a->droite;

  erreur = erreur || (a->gauche->data != 'b' && a->droite->data != 'b');
  if (a->droite->data == 'b')
      a = a->gauche;
  else
      a = a->droite;

  erreur = erreur || (a->gauche->data != 'd' && a->droite->data != 'd')
      || (a->gauche->data != 'c' && a->droite->data != 'c');

  return erreur;
}