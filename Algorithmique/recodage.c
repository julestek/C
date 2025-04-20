#include <stdio.h>
#include <stdlib.h>

#define N 5



int estPermutation(int tab[N]){
    int tab2[N] = { 0 };
    for(int i = 0; i<N; i++){
        if (tab2[tab[i]]==1){
            return 0;
        }
        else{
            tab2[tab[i]]++;
        }
    }
    return 1;

}




int recherche_naive(int tab[N], int x){
    for(int i = 0; i<N; i++){
        if (tab[i]=x)
            return x;
        else
            return -1;
    }
}



int recherche_dicho(int tab[N], int x, int deb, int fin){
    int pivot = (fin-deb)/2;
    if (deb > fin){
        return -1;
    }
    if (tab[pivot]==x){
        return x;}
    else if (tab[pivot]<x){
        recherche_dicho(tab, x, pivot, fin);
    }
    else{
        recherche_dicho(tab, x, deb, pivot);
    }
}



int recherche_2d(int mat[N][N], int x){
    int i = 0;
    int j = N-1;
    while(i<N && j>=0){
        if(mat[i][j]==x){
            return x;
        }
        else if(mat[i][j]>x){
            i++;
        }
        else{
            j--;
        }
    }
    return -1;
}








int main(void){
    int tab1[N]={0,2,3,1,4};
    printf("%d", estPermutation(tab1));
    return 0;
}