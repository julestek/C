#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

int main() {
    // test de PILE VIDE
    stack * s = stackCreate();
    if (stackIsEmpty(s)) {
        printf("ok = %d\n", 0); 
    }
    else {
        printf("pas ok =%d\n", 1);
        stackFree(s);
    }
    


    //Test de add et top
    stack * s2 = stackCreate();
    s2 = stackAdd(s2, 23);
    s2= stackAdd(s2, 42);
    s2= stackAdd(s2, 57);
    if (stackTop(s2)==57) {
        printf("ok= %d\n", 0);
    }
    else {
        printf("pas ok= %d\n", stackTop(s2));
    }
    s2= stackRemove(s2);
    printf("après remove on a en top :%d\n", stackTop(s2));
    printf("la taille est : %d \n", stackSize(s2));

    stackDisplay(s2);
    stackFree(s2);

    queue * q = queueCreate();
    if(queueIsEmpty(q)){
        printf("%s", "c'est bon\n");
    }
    else{
        printf("%s", "c'est pas bon\n");
    }
    queueDisplay(q);

    queueAdd(q, 2);
    queueAdd(q, 10);
    queueAdd(q, -3);
    queueAdd(q, -2);
    queueDisplay(q);
    printf("%s", "-1 élément\n");
    queueRemove(q);
    queueDisplay(q);
    printf("%s", "-1 élément\n");
    queueRemove(q);
    queueDisplay(q);
    printf("%s", "-1 élément\n");
    queueDestroy(q);






    return 0;
}
