#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include <time.h>
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)


// Partie donnée aux étudiants
list * listCreate() {
	return NULL;
}

list * listAdd(list * l, int v) {
	list * new = (list *)malloc(1*sizeof(list));
	if (new==NULL) {
		return NULL;
	}
	new->value = v;
	new->next = l;
	return new;
}

int listSize(list * l) {
	int n = 0;
	while (l!=NULL) {
		n = n+1;
		l = l->next;
	}
	return n;
}

void listDisplay(list * l) {
	printf("(");
	while (l) {
		printf("%d", l->value);
		if (l->next) {
			printf(", ");
		}
		l = l->next;
	}
	printf(")\n");
}

list * listRemove(list * l) {
	list * head;
	if (l==NULL) {
		return NULL;
	}
	else {
		head = l->next;
		free(l);
		return head;
	}
}

void listFree(list * l) {
	while (l) {
		l = listRemove(l);
	}
}

list* listInverse(list* l){
    list* l_copy = listCreate();
    while (l){
        l_copy = listAdd(l_copy,l->value);
        l = l->next;
    }
    return l_copy;
}

list* listCopy(list* l){
    list* temp = listInverse(l);
    list* result = listInverse(temp);
    listFree(temp);
    return result;
}

// Exo 1 : quicksort sans mémoire extra
list** listPivot(list* l, int pivot) {
    list* gauche = NULL;
    list* droite = NULL;
    list** pg = &gauche;  
    list** pd = &droite;

    int i = 0;

    while (l != NULL) {
        list* next = l->next; 
        if (l->value == pivot && i==0) {
            free(l); 
            i = 1;
        } else if (l->value > pivot) {
            *pd = l;
            pd = &l->next;
        } else {
            *pg = l;
            pg = &l->next;
        }
        l = next;
    }

    
    *pg = NULL;
    *pd = NULL;

    list** duo = malloc(2 * sizeof(list*));
    if (duo == NULL) return NULL;

    duo[0] = gauche;
    duo[1] = droite;
    return duo;
}


list* reassemble(list* gauche, list* droite, int pivot){
    
   list* l = listAdd(droite, pivot);
   if (gauche==NULL) {return l;}
   list* temp = gauche;
   while(temp->next!=NULL){
        temp = temp -> next;
   }
   temp->next = l;
   return gauche;

}

list* quickSort_rec(list* l){
    
    if(l!=NULL){
        int pivot = l->value;
        list** duo = listPivot(l, pivot);
        list* gauche = duo[0];
        list* droite = duo[1];

        gauche = quickSort_rec(gauche);
        droite = quickSort_rec(droite);

        return reassemble(gauche, droite, pivot);
    }

    return l;
}


list* quickSort(list* l){
    list* copy = listCopy(l);
    copy = quickSort_rec(copy);
    return copy;
}

// Exo 2 : choix du pivot aleatoire
int getRandomElement(list* l){
    if (l==NULL){return -1;}
    int N = listSize(l);
    int elt_rand = rand()%N;
    list* temp = l;
    while(elt_rand!=0 && temp!=NULL){
        elt_rand--;
        temp=temp->next;
    }

    return temp->value;
}

int getRandomPivot(list* l){
    if (l==NULL){return -1;}
    int a = getRandomElement(l);
    int b = getRandomElement(l);
    int c = getRandomElement(l);
    int mediane = a + b + c - min(a, min(b, c)) - max(a, max(b, c));
    return mediane;
}

list* quickSort_rec_alea(list* l){
    if(l!=NULL){
        int pivot = getRandomPivot(l);
        list** duo = listPivot(l, pivot);
        list* gauche = duo[0];
        list* droite = duo[1];

        gauche = quickSort_rec_alea(gauche);
        droite = quickSort_rec_alea(droite);

        return reassemble(gauche, droite, pivot);
    }

    return l;
}

list* quickSort_alea(list* l){
    list* copy = listCopy(l);
    copy = quickSort_rec_alea(copy);
    return copy;
}
 