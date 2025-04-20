#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tas{
    int capacite;
    int* tab;
    int taille;
} tas_t;


tas_t* initTas(int n){
    tas_t* B = NULL;
    B = malloc(sizeof(tas_t));
    B->tab = malloc(sizeof(int)*(n+1));
    B->capacite = n;
    B->taille = 0;
    return B;
}

void Echange(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int ajoutTas(tas_t *tas, int valeur) {
    if (tas->taille >= tas->capacite) {
        printf("Le tas est plein, impossible d'ajouter l'élément.\n");
        return -1;
    }

    tas->tab[tas->taille] = valeur;
    tas->taille++;

    int i = tas->taille - 1; 
    while (i > 0) {
        int parent = (i - 1) / 2; 
        if (tas->tab[i] > tas->tab[parent]) {
            Echange(&tas->tab[i], &tas->tab[parent]); 
            i = parent; }
        else{
            break;
        }
    }
    return valeur;
}

void EntasserMax(tas_t* B, int i) {
    int max = i;
    int gauche = 2 * i + 1;  // L'enfant gauche est à 2*i + 1
    int droite = 2 * i + 2;  // L'enfant droit est à 2*i + 2

    // Comparer avec l'enfant gauche
    if (gauche < B->taille && B->tab[gauche] > B->tab[max]) {
        max = gauche;
    }

    // Comparer avec l'enfant droit
    if (droite < B->taille && B->tab[droite] > B->tab[max]) {
        max = droite;
    }

    // Si le maximum a changé, échanger et récursivement entasser
    if (max != i) {
        Echange(&B->tab[i], &B->tab[max]);
        EntasserMax(B, max);
    }
}

void entasser_bas(tas_t* B, int i){
    int candidat = i;
    int j = 2*i + 1;
    if (j<B->taille){
        if (B->tab[j] > B->tab[i]){
            candidat = j;
        }
        if (j+1<B->taille && B->tab[j+1]>B->tab[candidat]){
            candidat = j + 1;
        }
        if (candidat != i){
            Echange(&B->tab[i], &B->tab[candidat]);
            entasser_bas(B, candidat);
        }
    }
}

int extraireTas(tas_t* B){
    if (B->taille == 0) {
        printf("Le tas est vide, impossible de supprimer d'élément.\n");
        return -1;
    }
    int max = B->tab[0];
    B->tab[0]=B->tab[B->taille-1];
    B->taille--;
    entasser_bas(B, 0);


    return max;
}

tas_t* CreerTas(int tab[], int n) {
    tas_t* A = initTas(n);
    // Copier les éléments dans le tas
    for (int i = 0; i < n; i++) {
        A->tab[i] = tab[i];
    }
    A->taille = n;

    // Entasser de bas en haut
    for (int i = n / 2; i >= 0; i--) {
        EntasserMax(A, i);
    }
    return A;
}

void TrierTab_par_Tas(int tab[], int n){
    tas_t* B = CreerTas(tab, n);
    printf("\n");
    for (int i = n; i > 0; i--) { 
        Echange(&B->tab[0], &B->tab[i]);
        B->taille--;
        EntasserMax(B, 0);  
    }
}




void afficheTas(tas_t* B){
    for(int i=0; i<B->taille;i++){
        printf("%d ", B->tab[i]);
    }
}

void afficheTab(int tab[], int n){
    for(int i = 0; i<n; i++){
        printf("%d ", tab[i]);
    }
}


int main(void){
    int tab[5]={0, -12, -8, 3, 5};
    tas_t* C = CreerTas(tab, 5);
    afficheTas(C);
    TrierTab_par_Tas(tab, 5);
    afficheTab(tab, 5);
    return 0;
}