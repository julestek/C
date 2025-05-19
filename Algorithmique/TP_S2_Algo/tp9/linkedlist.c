#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"


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
list** listPivot(list* l, int pivot){
    list* gauche = listCreate();
    list* droite = listCreate();
    list** pg = &gauche;
    list** pd = &droite;
    int i=0;
    
    while (l!=NULL){
        list* suiv = l->next;
        if (l->value > pivot){
            *pd = l;
            pd = &l->next;
        }
        else{
            if (i==0){
                free(l);
                i++;
            }
            else{
                *pg = l;
                pg = &l->next;
            }
            l = suiv;
        }

        *pg = NULL;
        *pd = NULL;

    }


    list ** duo = (list **) malloc(2*sizeof(list *));
    if (duo){
        duo[0] = gauche;
        duo[1] = droite;
    } else{
        return NULL;
    }
    return duo;
}

list* reassemble(list* gauche, list* droite, int pivot){
    
   list* l = listAdd(droite, pivot);
   
   list* temp = gauche;
   while(temp->next!=NULL){
        temp = temp -> next;
   }
   temp = l;
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

        reassemble(gauche, droite, pivot);
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
    
    return 0;
}

int getRandomPivot(list* l){
    // A COMPLETER
    return 0;
}

list* quickSort_rec_alea(list* l){
    // A COMPLETER
    return NULL;
}

list* quickSort_alea(list* l){
    // A COMPLETER
    return NULL;
}
 