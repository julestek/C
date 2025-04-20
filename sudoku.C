#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9
int remplissage = 0;
int HORIZ = 2;
int VERT = 1;

void initialiser(int grille[N][N]){
    for(int i=0; i<N;++i){
        for(int j=0; j<N; ++j){
            grille[i][j]=0;
        }
    }
}

void afficher(int grille[N][N]){
    for(int i=0; i<N;++i){
        if(i%3==0){
            printf("_______________________________\n");
        }
        for(int j=0; j<N; ++j){
            if (j%3 == 0){
                printf("|");
                
            }
            printf(" %d ",grille[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("_______________________________\n");
}


int generer(int grille[N][N]){
    int i, j;
    int k = 0;
    srand(time(NULL));
    for(j=0;j<9; ++j){

        for(i=0; i<9; ++i){
            if(rand()%5 == 0){
                grille[j][i]=0;
                ++k;
            }
            else{grille[j][i] = (i + j*3 +j /3) %9 +1 ;}
        }   
    }
    return k;
}

void saisir(int grille[N][N]){
    int i;
    int j;
    int v;
    printf("Saisissez une valeur à insérer :");
    scanf("%d", &v);
    printf("Veuillez saisir les coordonnées où vous voulez placer votre valeur :");
    scanf("%d%d", &i, &j);
    if((grille[i][j]==0) && (0<v) && (v<10) && (0<=i) && (i<9) && (0<=j) && (j<9)){
        grille[i][j]=v;
        ++remplissage;
    }
    else{
        printf("Erreur, la case est déjà occupée");
    }
}

int verifierLigneColonne(int grille[N][N], int numero, int sens){
    int tab[9]={0};
    if(sens == 0){
        for(int i=0; i<N; i++){
            if(tab[grille[numero][i] - 1] == 0 && grille[numero][i] != 0) 
                ++tab[grille[numero][i] - 1];
            else{
                return 0;
            }
        }
    }
    else{
        for(int i=0; i<N; i++){
            if(tab[grille[i][numero] - 1] == 0 && grille[i][numero] != 0) 
                ++tab[grille[i][numero] - 1];
            else{
                return 0;
            }
        }

    }
    return 1;
}


int verifierRegion(int grille[N][N], int k, int l){
    int tab[9]={0};
    for(int i=k*3;i<=3*k+2;i++){
        for(int j=l*3;j<=3*l+2;j++){
            if(tab[grille[i][j] - 1] == 0 && grille[i][j] != 0) 
                ++tab[grille[i][j] - 1];
            else{
                return 0;
            }
        }
    }
    return 1;
}


int verifierGrille(int grille[N][N]){
    for(int i=0; i<9; i++){
        if (verifierLigneColonne(grille, i, 0)== 0 || verifierLigneColonne(grille, i, 1) == 0 || verifierRegion(grille, i%3, i/3)){
            return 0;
        }
    }
    return 1;
}



int main(){
    int grille[N][N];
    initialiser(grille);
    generer(grille);
    printf("%s", "SUDOKU\n");
    while (verifierGrille(grille)!=1){
        afficher(grille);
        saisir(grille);
    }
    
    return 0;
}