#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack * stackCreate() {
	return NULL;
}

int stackIsEmpty(stack * s) {
	return s == NULL;
}

stack * stackAdd(stack * s, int v) {
	stack * new = malloc(sizeof(stack));
	new->next = s;
	new->value = v;
	return new;
}


int stackTop(stack * s) {
	if (!stackIsEmpty(s)){
		return s->value;
	}
	return -1;
}

stack * stackRemove(stack * s) {
	if (!stackIsEmpty(s)){
		stack * new = s->next;
		free(s);
		s=new;
	}
	return s;
}

int stackSize(stack * s) {
	if(!stackIsEmpty(s)){
		return 1 + stackSize(s->next);
	}
	else{
		return 0;
	}
}

void stackDisplay(stack * s) {
	if (!stackIsEmpty(s)){
		printf("%d\n", s->value);
		stackDisplay(s->next);
	}
	else{
		return;
	}
}

void stackFree(stack * s) {
	if (s){
		stack * temp = s->next;
		free(s);
		stackFree(temp);
	}
}