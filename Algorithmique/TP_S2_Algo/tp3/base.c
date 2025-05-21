#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"

static int base=2;


//  IMPORTANT :  les nombres en binaires sont par exemple modélisés de la façon suivante :
//  Le nombre binaire 1101101
//  NULL <- 1 <- 1 <- 0 <- 1 <- 1 <- 0 <- 1 
//  C'est à dire que la tête de la liste est le bit de poids faible et la queue le bit de poids fort.

// 
void setBase(int b)
{
    base=b;
}

void printBaseB(list * l){
    char symboles[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k'};
    if(l){
        printBaseB(l->next);
        printf("%c", symboles[l->value]);
    }
}



int baseToDec(list* l){
    if (l == NULL){
        return 0;
    } 
    return l->value + base * baseToDec(l->next); 
}




int baseToDec2(list* l){
    int res = 0;
    int puissance = 1;

    while (l != NULL) {
        res += l->value * puissance;
        puissance *= base;
        l = l->next;
    }

    return res;
}

list* decToBase(int n ){
    if (n == 0) {
        return NULL;
    }
    
    list* l = listAdd(decToBase(n / base), n % base);
    return l;
}
