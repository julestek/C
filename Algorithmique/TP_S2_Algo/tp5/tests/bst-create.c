#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(void) {
    struct bst * abr;
    abr = NULL;
    bstDisplay(abr);
    printf("\n");
    bstFree(abr);
	return 0;
}
