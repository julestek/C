#include <stdio.h>
#include <stdlib.h>



typedef struct Maillon{
    int val;
    struct Maillon* successeur;
    struct Maillon* predecesseur;
} maillon_t;

typedef struct Liste{
    maillon_t* debut;
    maillon_t* fin;
}















int main(void){
    return 0;
}