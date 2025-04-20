#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue * queueCreate() {
	queue * q = malloc(sizeof(queue));
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
	return q;
}

int queueIsEmpty(queue * q) {
	return q->size == 0;
}

void queueAdd(queue * q, int v) {
	queue_element * maillon = malloc(sizeof(queue_element));
	
	maillon -> value = v;
	maillon -> next = q -> head;

	q -> size ++;
	if (q->tail == NULL){
		q->tail = maillon;
		q->head = maillon;
	}
	else{
		q->head->previous = maillon;
	}

	q->head = maillon;
	maillon->previous = NULL;

	
}

int queueGet(queue * q) {
	return q->tail->value;
}

void queueRemove(queue * q) {

    if (q->head == q->tail) { 
		free(q->tail);
        q->head = NULL;
        q->tail = NULL;
    } 
	else{
		queue_element * tmp = q->tail->previous;
		free(q->tail);
		tmp->next = NULL;
		q->tail = tmp;
    }

    q->size--;
}

void queueDestroy(queue * q) {
	if (q!=NULL){
		while(q->tail!=NULL){
			queueRemove(q);
		}	
	free(q);}
}

int queueSize(queue * q) {
	return q->size;
}

void queueDisplay(queue * q) {
	queue_element * temp = q->tail;
	if (!queueIsEmpty(q)){
		while(temp != NULL){
			printf("%d\n", temp->value);
			temp = temp->previous;
		}
	}
	else{
		return;
	}
}
