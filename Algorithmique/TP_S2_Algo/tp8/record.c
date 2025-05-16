#include <stdlib.h>
#include <stdio.h>
#include "record.h"

list * listCreate() {
    list * l = malloc(sizeof(list));
    l->length = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

int listSize(list * l) {
    if (l!=NULL){
        return l->length;
    }
    else{
        return 0;
    }
}

void addRecord(list * l, int variant, int limit) {
    if (l == NULL) return;

    record * new = malloc(sizeof(record));

    new->variant = variant;
    new->limit = limit;
    new->next = NULL;

    if (l->head == NULL) {
        l->head = new;
        l->tail = new;
    } else {
        l->tail->next = new;
        l->tail = new;
    }

    l->length++;
}

void listDisplay(list * l) {
    if (l==NULL||l->head==NULL){
        printf("Liste vide\n"); 
        return;}
    record * actuel = l->head;
    int index=0;
    while(actuel != NULL){
        printf("index = %d, variant = %d, limit = %d\n", index, actuel->variant, actuel->limit);
        actuel = actuel -> next;
        index++;
    }
}

void listFree(list *l) {
    if (l == NULL) return;

    record * r = l->head;
    while (r != NULL) {
        record * temp = r;
        r = r->next;
        free(temp);
    }

    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
}

void listDestroy(list *l) {
    if (l == NULL) return;

    listFree(l);
    free(l);
}

int veriTer(list * l){

    if (l == NULL || l->head == NULL || l->head->next == NULL) {
        return 0;
    }

    record * r = l->head;
    int precDiff = abs(r->variant - r->limit);
    while (r->next != NULL){
        int actuDiff = abs(r->next->variant - r->next->limit);
        if(actuDiff>=precDiff){
            return 0;
        }
        precDiff = actuDiff;
        r = r->next;
    }
    return 1;
}


