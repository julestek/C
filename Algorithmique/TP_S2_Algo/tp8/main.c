#include <stdio.h>
#include <stdlib.h>
#include "record.h"

int main(int argc, char ** argv) {
    printf("=== Test 1 : Affichage d’une liste vide ===\n");
    list * ListVide = listCreate();
    listDisplay(ListVide);
    listDestroy(ListVide);

    printf("\n=== Test 2 : Effacement d’une liste vide ===\n");
    list *ListVide2 = listCreate();
    listFree(ListVide2);  
    listDestroy(ListVide2);

    printf("\n=== Test 3 : Ajout de 3 éléments puis affichage ===\n");
    list *testList = listCreate();
    addRecord(testList, 4, 10);
    addRecord(testList, 5, 9);
    addRecord(testList, 6, 8);
    listDisplay(testList);

    printf("\n=== Test 4 : Ajout + test avec veriTer ===\n");
    int result = veriTer(testList);
    printf("Résultat de veriTer : %d\n", result); 
    listDestroy(testList);

    printf("\n=== Test 5 : Exécution du programme de terminaison ===\n");
    list *listI = listCreate();
    list *listJ = listCreate();
    int resi = -1, resj = -1;
    int i = 12, j;

    while (i >= 0) {
        j = 1;
        while (j != i % 10) {
            j += 1;
            // test pour j
            if (listSize(listJ) < 20 && j != i % 10) {
                addRecord(listJ, j, i % 10);
            } else {
                printf("Termination for j\n");
                listDisplay(listJ);
                resj = veriTer(listJ);
                listFree(listJ);
                printf("Termination j: %d\n", resj);
            }
            if (resj == 0) {
                listDestroy(listI);
                listDestroy(listJ);
                return 0;
            }
            // fin test j
        }
        i -= 1;
        // test pour i
        if (listSize(listI) < 20 && i > 1) {
            addRecord(listI, i, 0);
        } else {
            printf("Termination for i\n");
            listDisplay(listI);
            resi = veriTer(listI);
            listFree(listI);
            printf("Termination i: %d\n", resi);
        }
        if (resi == 0) {
            listDestroy(listI);
            listDestroy(listJ);
            return 0;
        }
        // fin test i
    }

    listDestroy(listI);
    listDestroy(listJ);

    return 0;
}
