#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code.h"

// determine si une case est interessante pour le deplacement ou pour la destruction
// c'est le moteur de jeu de l'adversaire machine
int interessante(Jeu jeu, int i, int j) {
   int tab[10] = {0};
   int result = 5;

   for(int k=1; k<10; k+=1+(k==4)) {
      tab[k] = 0;
      if (jeu.terrain[i+PAVE[k][0]][j+PAVE[k][1]] == 0) {
         for(int l=1; l<10; ++l) {
            int a = i+PAVE[k][0]+PAVE[l][0];
            int b = j+PAVE[k][1]+PAVE[l][1];
            if (a>0 && b>0 && a<jeu.L+1 && b<jeu.C+1) {
               if(jeu.terrain[a][b]==0)
               ++tab[k];
            }
         }
         if (tab[k]>=tab[result])
            result = k;
      }
   }
   return result;           
}

// DEBUT DES FONCTIONS DE TESTS

int main(int argc, char** argv) {

    Jeu jeu;
    
    int position;
    int r;
    int fin = 0;
    int i, j;

    initialiser(&jeu, 6, 8);

    placer(jeu, 1, 1, 2);
    placer(jeu, 2, 4, 5);
    
    while(!fin) {
        fin = bloque(jeu, 1);
        r = 0;
        while (!fin && r!=1) {
            afficher(stdout, jeu);
            printf("Deplacer joueur 1 ?\n");
            printf("7 8 9\n4 J 6\n1 2 3\n");
            scanf("%d", &position);
            if (position==5 || position==0)
               fin = 1;
            else r = deplacer(jeu, 1, position);
        }
        r = 0;
        while(!fin && r!=1) {
            afficher(stdout, jeu);
            printf("Detruire case ?\n");
            scanf("%d %d", &i, &j);
            int m = jeu.terrain[i][j];
            r = detruire(jeu, i, j);
            printf("case %d %d %d // %d\n", i, j, r, m);
        }

        if (!fin) {

            fin = bloque(jeu, 2);

            if (fin)
                printf("Joueur 2 a perdu\n");
            else {
                trouver(jeu, 2, &i, &j);
                int pos = interessante(jeu, i, j);
                printf("2 deplace %d %d %d -> %d %d\n", i, j, pos, i+PAVE[pos][0], j+PAVE[pos][1]);
                deplacer(jeu, 2, pos);
                trouver(jeu, 1, &i, &j);
                pos = interessante(jeu, i, j);
                // on n'a pas teste detruire, si la position est 5, en fait, le joueur 2 a gagne
                printf("2 detruit %d %d %d -> %d %d\n", i, j, pos, i+PAVE[pos][0], j+PAVE[pos][1]);
                detruire(jeu, i+PAVE[pos][0], j+PAVE[pos][1]);
            }
        } else printf("Joueur 1 a perdu\n");
    }


    liberer(&jeu);
    return 0;
}

