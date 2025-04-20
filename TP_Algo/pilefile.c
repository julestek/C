#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Pile{
    int *contenu;
    int capacite;
    int taille;
} pile_t;



pile_t* InitPile(int n){
    pile_t* pile = malloc(sizeof(pile_t));
    pile->contenu = malloc(sizeof(int)*n);
    pile->capacite = n;
    pile->taille = 0;
    return pile;
}

pile_t* CreerPile(int n, int* tab){
    pile_t* pile = InitPile(n);
    pile->taille = n;
    for(int i=0; i<pile->taille; i++){
        pile->contenu[i] = tab[i];
    }
    return pile;
}

bool estVide(pile_t* p){
    return (p->taille==0);
}


int Depiler(pile_t* p){
    if (p->taille > 0){
        int k = p->contenu[p->taille - 1];
        p->taille--;
        return k;
    }
    else{
        return false;
    }
}

bool Empiler(pile_t* p, int x){
    if(p->taille<p->capacite){
        p->contenu[p->taille] = x;
        p->taille++;
        return true;
    }
    else{
        return false;
    }
}


bool estPalindrome(char tab[], int n){
    pile_t* pile = InitPile(n);
    int i;
    
    for(i = 0; i < n / 2; i++){
        Empiler(pile, tab[i]);
    }

    if (n % 2 != 0) {
        i++;
    }

    for(; i < n; i++){
        if(tab[i] != Depiler(pile)){
            free(pile->contenu);
            free(pile);
            return false;
        }
    }

    free(pile->contenu);
    free(pile);
    return true;
}


bool estBienParenthese(char tab[], int n){
    pile_t* p = InitPile(n);
    int i = 0;
    for(i = 0; i<n;i++){
        if(tab[i]=='('){
            Empiler(p, tab[i]);
        }
        else if(tab[i]==')' && !estVide(p)){
            if (estVide(p)){
                free(p->contenu);
                free(p);
                return false;}

            Depiler(p);
        }
    }
    
    bool resultat = estVide(p); 
    free(p->contenu);
    free(p);
    return resultat;

}




int main(void){
    char tab[6]={'k','a','a','a','a','k'};
    printf("%d", estPalindrome(tab, 6));
    return 0;
}