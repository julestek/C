#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

list * listCreate() {
	return NULL; 
}

hashtable * hashtableCreate(int n) {
	hashtable * h = malloc(sizeof(hashtable));
	h->n = n;
	h->tab = malloc(sizeof(list*)*n);
	for(int i = 0; i<n; i++){
		h->tab[i]=listCreate();
	}
	return h;
}

int hash(char * key, int n) {
	int s = 0;
	for(int i = 0; key[i]!='\0'; i++){
		s = s + key[i];
	}
	return (s % n);
}

void listDisplay(list * l) {
	list * temp = l;
	while(temp!=NULL){
		printf("(clé : %s, valeur : %s) -> ", temp->key, temp->value);
		temp = temp->next;
	}
	printf("NULL\n");
}

void hashtableDisplay(hashtable * h) {
	if (h != NULL){
		for(int i = 0; i<h->n; i++){
			printf("\t [%d] -> ", i);
			listDisplay(h->tab[i]);
		}
	}
	else{
		printf("Table de hash vide\n");
	}
	printf("\n");
}

list * listAdd(list * l, char * newK, char * newV) {
	list * temp = malloc(sizeof(list));
	temp->key = strdup(newK);
	temp->value = strdup(newV);
	temp->next = l;
	return temp;
}

char * listSearch(list * l, char * k) {
	list * temp = l;
    while (temp != NULL) {
        if (temp->key != NULL && strcmp(temp->key, k) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}


char * hashtableSearch(hashtable * h, char * key) {
	int i = hash(key, h->n);
    return listSearch(h->tab[i], key);

}

void hashtableAdd(hashtable * h, char * key, char * value) {
	char * test = hashtableSearch(h, key);
	if (test != NULL){
		return;
	}
	else{
		int i = hash(key, h->n);
   		h->tab[i] = listAdd(h->tab[i], key, value);
	}
}

void listFree(list * l) {
    while (l != NULL) {
        list * temp = l;
        l = l->next;
        free(temp->key);     
        free(temp->value);   
        free(temp);          
    }
}

void hashtableFree(hashtable * h) {
	if (h == NULL) return;
	for(int i = 0; i< h->n; i++){
		listFree(h->tab[i]);
	}
	free(h->tab);
	free(h);
}

hashtable * hashtableRehash(hashtable * h, int newN) {
	hashtable * hnew = hashtableCreate(newN);
	for(int i = 0; i<h->n; i++){
		list * l = h->tab[i];
		while(l!=NULL){
			hashtableAdd(hnew, l->key, l->value);
			l=l->next;
		}
	}
	hashtableFree(h);
	return hnew;
}