#include <stdlib.h>
#include <stdio.h>
#include "codage.h"

encodage * cree_encodage(binaire data, encodage * suivant) {
  encodage * res = malloc(sizeof(struct listeBinaire));
  if (res != NULL) {
    res->data = data;
    res->suivant = suivant;
  }
  
  return res;
}

void imprime_encodage(FILE * f, encodage * e) {
  encodage * reste = e;
  while(reste != NULL) {
    fprintf(f, "%i", reste->data);
    reste = reste->suivant;
  }
  fprintf(f, "\n");
}


void libere_encodage(encodage ** e) {
  if (*e != NULL) {
    libere_encodage(&(*e)->suivant);
    free(*e);
    *e = NULL;
  }
}

int code_char_rec(arbre *a, char c, encodage **e) {
  if (a == NULL) return 0;

  if (est_feuille(a)) 
  {
    if (a->data == c) return 1;
    return 0;
  }
  if (code_char_rec(a->gauche, c, e)) 
  {
    *e = cree_encodage(0, *e);
    return 1;
  }
  if (code_char_rec(a->droite, c, e))
  {
    *e = cree_encodage(1, *e);
    return 1;
  }

  return 0;
}

int code_char(arbre *a, char c, encodage **e) 
{
  *e = NULL;
  return code_char_rec(a, c, e);
}

encodage * concat(encodage *a, encodage *b) {
  if (a == NULL) return b;
  encodage *p = a;
  while (p->suivant != NULL) p = p->suivant;
  p->suivant = b;
  return a;
}

encodage *code_texte(arbre *a, char *s) {
  encodage *result = NULL;

  for (int i = 0; s[i] != '\0'; i++) {
    encodage *code_c = NULL;
    if (!code_char(a, s[i], &code_c))
    {
      libere_encodage(&result);
      return NULL;  
    }
    result = concat(result, code_c);
  }

  return result;
}

encodage *decode_suivant(FILE *f, arbre *a, encodage *e) {
  arbre *courant = a;
  encodage *p = e;

  while (courant && !est_feuille(courant) && p != NULL) {
    if (p->data == 0) {
      courant = courant->gauche;
    } else if (p->data == 1) {
      courant = courant->droite;
    } else {
      return NULL;  
    }
    p = p->suivant;
  }

  if (courant && est_feuille(courant)) {
    fputc(courant->data, f);
    return p;
  }

  return NULL; 
}


void decode(FILE *f, arbre *a, encodage *e) {
  while (e != NULL) {
    e = decode_suivant(f, a, e);
  }
}