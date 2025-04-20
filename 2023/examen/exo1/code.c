#include "code.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

const int PAVE[10][2] = { {0,0}, {+1, -1}, {+1, 0}, {+1, +1}, {0, -1}, {0, 0}, {0, +1}, {-1, -1}, {-1, 0}, {-1, +1}};

void initialiser(Terrain terrain) {
   for(int i = 0; i<L+2;i++){
      for (int j = 0; j<C+2;j++){
         if(i==0 || j == 0 || i==L+1 || j==C+1){
            terrain[i][j]=-1;
         }
         else{
         terrain[i][j]=0;}
      }
   }
}

int detruire(Terrain terrain, int i, int j) {
   if (i<=0 || i>=L+2 || j<=0 || j>=C+2 || terrain[i][j]!=0){
      return 0;
   }
   else{
      terrain[i][j]=-1;
      return 1;
   }
} 

void afficher(FILE * file, Terrain terrain) {
   fprintf(file, "   1 2 3 4 5 6 7 8\n");
   for (int i = 1; i<L+1; i++){
      fprintf(file, "%2d", i);
      for(int j = 1; j<C+1; j++){
         if(terrain[i][j]==-1){
            fprintf(file, " X");
         }
         else if(terrain[i][j]==0){
            fprintf(file, "  ");
         }
         else{
            fprintf(file, " %d", terrain[i][j]);
         }
      }
      fprintf(file, "\n");
   }
}

int  bloque(Terrain terrain, int numero) {
   /*
La fonction bloque() permet de savoir si le joueur donné en paramètre est bloqué ou PAS. 
C'est à dire si le joueur est complètement entouré par des cases détruites ou le/les autres joueurs.
L'utilisation de PAVE n'est pas obligatoire mais peut aider.*/
   int i, j;
   trouver(terrain, numero, &i, &j);
   if (i == -1 || j == -1) {
     return 1; // Joueur non trouvé, considéré comme bloqué
   }
   for(int k = 1; k<=9 && k!=5 ;k++){
      int ni = i + PAVE[k][0];
      int nj = j + PAVE[k][1];
      if(ni>0 && nj > 0 && ni < L-1 && nj <C-1 && terrain[ni][nj]==0){
         return 0;
      }
   }
   return 1;

}

void trouver(Terrain terrain, int numero, int *pi, int *pj) {
   for(int i = 0; i<L+1; i++){
      for(int j = 0; j<C+1; j++){
         if (terrain[i][j]==numero){
            *pi = i;
            *pj = j;
            return;
         }
      }
   }
   *pi = -1;
   *pj = -1;
}

int  placer(Terrain terrain, int numero, int i, int j) {
   /* La fonction placer() permet de placer le joueur donné par son numéro sur le terrain à la position 
i et j. Le terrain est mis à jour.
Le joueur ne peut etre posé que sur une case vide dont les indices sont valides.
Si le joueur a déjà été placé, la position est mise à jour (sinon on fait rien).*/
   int pi;
   int pj;
   if (i<=0 || i>=L+1 || j<=0 || j>=C+1 || terrain[i][j]!=0){
      return 0;
   }
   trouver(terrain, numero, &pi, &pj);
   if(pi!=-1 && pj!=-1){
      terrain[pi][pj]=0;
   }
   terrain[i][j]=numero;
   return 1;   
}

int deplacer(Terrain terrain, int numero, int position) {
   /*La fonction deplacer() permet de déplacer le joueur donné en parametre sur le terrain donne en parametre
dans la direction donnée par le dernier parametre.
On se sert du pavé numérique pour donner la direction => par exemple, 7 déplace d'une case vers le haut à gauche.
5 et 0 ne devraient pas être utilisées.*/
   int i, j;
   trouver(terrain, numero, &i, &j);
   if(j==-1 || i==-1){
      return 0;
   }
   int ni = i + PAVE[position][0];
   int nj = j + PAVE[position][1];
   if(ni<=0 || ni>=L-1 || nj<=0 || nj>=C-1 || terrain[ni][nj] != 0){
      return 0;
   }
   terrain[i][j] = 0;
   terrain[ni][nj]= numero;
   return 1;
   }

int connexe(Terrain terrain, int j1, int j2) {
   /*La fonction connexe() permet de savoir s'il existe un chemin entre les joueurs dont le numéro est donné en paramètre.
*/
   int i_1, j_1;
   int i_2,j_2;
   trouver(terrain, j1, &i_1, &j_1);
   trouver(terrain, j2, &i_2, &j_2);
   if(i_1 == -1 || i_2 == -1 || j_1 == -1 || j_2 == -1){
      return 0;
   }
   
   return 0;
}