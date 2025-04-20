#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code.h"

// determine si une case est interessante pour le deplacement ou pour la destruction
// c'est le moteur de jeu de l'adversaire machine
int interessante(Terrain terrain, int i, int j) {
   int tab[10] = {0};
   int result = 5;

   for(int k=1; k<10; k+=1+(k==4)) {
      tab[k] = 0;
      if (terrain[i+PAVE[k][0]][j+PAVE[k][1]] == 0) {
         for(int l=1; l<10; ++l) {
            int a = i+PAVE[k][0]+PAVE[l][0];
            int b = j+PAVE[k][1]+PAVE[l][1];
            if (a>0 && b>0 && a<L+1 && b<C+1) {
               if(terrain[a][b]==0)
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

    Terrain terrain;
    
    int position;
    int r;
    int fin = 0;
    int i, j;

    initialiser(terrain);

    placer(terrain, 1, 1, 2);
    placer(terrain, 2, 4, 5);
    
    while(!fin) {
        fin = bloque(terrain, 1);
        r = 0;
        while (!fin && r!=1) {
            afficher(stdout, terrain);
            printf("Deplacer joueur 1 ?\n");
            printf("7 8 9\n4 J 6\n1 2 3\n");
            scanf("%d", &position);
            if (position==5 || position==0)
               fin = 1;
            else r = deplacer(terrain, 1, position);
        }
        r = 0;
        while(!fin && r!=1) {
            afficher(stdout, terrain);
            printf("Detruire case ?\n");
            scanf("%d %d", &i, &j);
            int m = terrain[i][j];
            r = detruire(terrain, i, j);
            printf("case %d %d %d // %d\n", i, j, r, m);
        }

        if (!fin) {

            fin = bloque(terrain, 2);

            if (fin)
                printf("Joueur 2 a perdu\n");
            else {
                trouver(terrain, 2, &i, &j);
                int pos = interessante(terrain, i, j);
                printf("2 deplace %d %d %d -> %d %d\n", i, j, pos, i+PAVE[pos][0], j+PAVE[pos][1]);
                deplacer(terrain, 2, pos);
                trouver(terrain, 1, &i, &j);
                pos = interessante(terrain, i, j);
                // on n'a pas teste detruire, si la position est 5, en fait, le joueur 2 a gagne
                printf("2 detruit %d %d %d -> %d %d\n", i, j, pos, i+PAVE[pos][0], j+PAVE[pos][1]);
                detruire(terrain, i+PAVE[pos][0], j+PAVE[pos][1]);
            }
        } else printf("Joueur 1 a perdu\n");
    }

    return 0;
}

