#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(int argc, char ** argv) {
	printf("test\n");
	list * l = listCreate();
	printf("test\n");

	l = listAdd(l, "01", "voiture");
	printf("test\n");

	listDisplay(l);
	printf("test\n");

	printf("%s\n", listSearch(l, "01"));
	printf("test\n");

	printf("Voici la valeur de hash de Alice pour n = 10 : %d\n", hash("Alice", 10));
	printf("Voici la valeur de hash de Bob pour n = 10 : %d\n", hash("Bob", 10));
	printf("Voici la valeur de hash de Charles pour n = 10 : %d\n", hash("Charles", 10));
	printf("Voici la valeur de hash de David pour n = 10 : %d\n", hash("David", 10));

	hashtable * h = hashtableCreate(10);
	printf("Hashtable vide :\n");
	hashtableDisplay(h);
	printf("Hashtable sans collision :\n");
	hashtableAdd(h, "Alice", "Dupont");
	hashtableAdd(h, "Bob", "Dupond");
	hashtableAdd(h, "Charles", "Dupon");
	hashtableDisplay(h);
	printf("Hashtable avec collision :\n");
	hashtableAdd(h, "David", "Duppont");
	hashtableDisplay(h);
	printf("Rehash à 5 :\n");
	h = hashtableRehash(h, 5);
	hashtableDisplay(h);
	printf("Rehash à 20 :\n");
	h = hashtableRehash(h, 20);
	hashtableDisplay(h);
	listFree(l);
	hashtableFree(h);

	return 0;
}
