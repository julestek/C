#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listes.h"

list * listCreate() {
    return NULL;
}

list * listAdd(list * l,int n){
    list * plist=(list *) malloc(sizeof(list));
    if (plist==NULL) return NULL;

    plist->value=n;
    plist->next=l;
    return plist;
}



void listDisplay(list * l){
    if (l!=NULL){
        printf("(%d)\t-> ", l->value);
        listDisplay(l->next);
    }
    else{
        printf("  NULL\n");}
}


void listInverseDisplay(list * l){
    if (l==NULL){printf("NULL ->  ");}
    else{
        listInverseDisplay(l->next);
        printf("(%d)\t-> ", l->value);
    }
}

int listSearch(list * plist, int n){
    if (plist!=NULL){
        if (plist->value == n){
            return 1;
        }
        else{
            return listSearch(plist->next, n);
        }
    }
    else{
        return 0;
    }
}


list * listMap(list* l, int (*f)(int)){
    if (!l) return NULL;  
    list * newList = listAdd(listMap(l->next, f),f(l->value));
    return newList;
}

list * listFilter(list* l , int (*p)(int)){
    if(l==NULL){return NULL;}
    if(p(l->value)){
        return listAdd(listFilter(l->next, p), l->value);
    }
    else{
        return listFilter(l->next, p);
    }
    
}

int listFold(list* l , int (*op)(int,int),int base){
    if(!l){return base;}
    else{
        return op(base, listFold(l->next, op, l->value));
    }
}


int opSum(int x, int y){
    return x + y;
}

int listSum(list* l ){
    return listFold(l, opSum, 0);
}

int opProd(int x, int y){
    return x*y;
}

int listProd(list* l ){
    return listFold(l, opProd, 1);
}

int opLen(int x, int y){
    int res = x;
    while (y>0){
        res+=1;
        y--;
    }
    return res;
}


int listLen(list* l ){
    return listFold(l, opLen, 1)/3 ;
}

// list * ajouteInverse(list * l1,list * l2){
//     if (l1){
//         list * suivant = l1->next;
//         l1->next = l2;
//         l2 = ajouteInverse(suivant, l1);
//     }
//     return l2;
// }

list* listInverse(list *l){
    if (l == NULL) return NULL;  
    list* newList = listInverse(l->next);
    list* inverse = listAdd(newList, l->value);
    return inverse;
}




void listFree(list * l){
    if(l){
        list * temp = l->next;
        free(l);
        listFree(temp);    
    }
}