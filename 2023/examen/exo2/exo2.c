#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "code.h"
#include "teZZt.h"


// DEBUT DES FONCTIONS DE TESTS
BEGIN_TEST_GROUP(isola)

TEST(INITIALISER, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    REQUIRE( 0==strcmp(buffer, res));  
    liberer(&jeu);  
}

TEST(DETRUIRE1, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2   X            \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);
    int r = detruire(jeu, 2, 2);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res));    
    liberer(&jeu);
}

TEST(DETRUIRE2, "") {
    Jeu jeu;

    initialiser(&jeu, 6, 8);     

    int r = detruire(jeu, 2, 2);
    CHECK( 1 == r);

    r = detruire(jeu, 2, 2);
    REQUIRE( 0 == r);
    liberer(&jeu); 
}

TEST(DETRUIRE3, "") {
    Jeu jeu;

    initialiser(&jeu, 6, 8);
    int r = 1;

    r = detruire(jeu, 0, 0);
    REQUIRE( 0 == r);
    
    r = detruire(jeu, jeu.L+2, jeu.C+2);
    REQUIRE( 0 == r);

    r = detruire(jeu, -1, -1);
    REQUIRE( 0 == r);

    r = detruire(jeu, 30, 6);
    REQUIRE( 0 == r);

    liberer(&jeu);
}
TEST(TROUVER1, "") {
    Jeu jeu;
    int i,j;

    initialiser(&jeu, 6, 8);

    trouver(jeu, 1, &i, &j);
    
    REQUIRE( -1 == i);
    REQUIRE( -1 == j);    

    liberer(&jeu);
}


TEST(PLACER1, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3   1            \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);
    int r = placer(jeu, 1, 3, 2);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res)); 

    liberer(&jeu);   
}

TEST(TROUVER2, "") {
    Jeu jeu;
    int i = -1,j =-1;

    initialiser(&jeu, 6, 8);
    int r = placer(jeu, 1, 3, 2);

    trouver(jeu, 1, &i, &j);
    
    REQUIRE( 1 == r);
    REQUIRE( 3 == i);
    REQUIRE( 2 == j);    

    liberer(&jeu);
}

TEST(PLACER2, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5         1      \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);
    int r = placer(jeu, 1, 3, 2);

    // on change l'emplacement du joueur 1
    r = placer(jeu, 1, 5, 5);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res));   

    liberer(&jeu); 
}


TEST(PLACER3, "") {
    Jeu jeu;

    initialiser(&jeu, 6, 8);
    int r = placer(jeu, 1, 3, 2);

    REQUIRE( 1 == r);
    
    // Le meme joueur ne peut etre mis deux fois
    r = placer(jeu, 1, 3, 2);
    REQUIRE( 0 == r);

    // un autre joueur ne peut etre au meme endroit
    r = placer(jeu, 2, 3, 2);
    REQUIRE( 0 == r);

    // pas en dehors du terrain non plus
    r = placer(jeu, 1, 0, 0);
    REQUIRE( 0 == r);

    liberer(&jeu);
}

TEST(DEPLACER1, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1 1              \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);
    int r = placer(jeu, 1, 3, 2);
    r = deplacer(jeu, 1, 7);
    REQUIRE( 1 == r);
    r = deplacer(jeu, 1, 8);
    REQUIRE( 1 == r);
    r = deplacer(jeu, 1, 7);
    REQUIRE( 0 == r);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    
    REQUIRE( 0 == strcmp(buffer, res));    

    liberer(&jeu);
}

TEST(BLOQUER1, "") {
    Jeu jeu;
    
    initialiser(&jeu, 6, 8);
    
    placer  (jeu, 1, 1, 1);
    
    int r = bloque(jeu, 1);
    REQUIRE( 0 == r);

    liberer(&jeu);
}

TEST(BLOQUER2, "") {
    Jeu jeu;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1 1 X            \n"
                       " 2 X X            \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(&jeu, 6, 8);

    placer  (jeu, 1, 1, 1);

    detruire(jeu, 1, 2);
    detruire(jeu, 2, 1);
    detruire(jeu, 2, 2);
    
    int r = bloque(jeu, 1);
    REQUIRE( 1 == r);

    afficher(stdout, jeu);
    afficher(file, jeu);

    fclose(file);
    
    REQUIRE( 0 == strcmp(buffer, res));    

    liberer(&jeu);
}

TEST(CONNEXE1, "") {
    Jeu jeu;
    
    initialiser(&jeu, 6, 8);

    placer  (jeu, 1, 1, 1);
    placer  (jeu, 2, 5, 6);
    
    afficher(stdout, jeu);

    int r = 0; 

    r = connexe(jeu, 1, 2);

    REQUIRE( 1 == r);

    liberer(&jeu);
}

TEST(CONNEXE2, "") {
    Jeu jeu;
    
    initialiser(&jeu, 6, 8);

    placer  (jeu, 1, 1, 1);
    placer  (jeu, 2, 5, 6);

    detruire(jeu, 1, 7 );
    detruire(jeu, 2, 6 );
    detruire(jeu, 3, 5 );
    detruire(jeu, 4, 4 );
    detruire(jeu, 5, 3 );
    detruire(jeu, 6, 2 );


    afficher(stdout, jeu);

    int r = 0; 
    
    r = connexe(jeu, 1, 2);

    REQUIRE( 1 == r);

    liberer(&jeu);
}


TEST(CONNEXE3, "") {
    Jeu jeu;
    
    initialiser(&jeu, 6, 8);

    placer  (jeu, 1, 1, 1);
    placer  (jeu, 2, 5, 6);

    detruire(jeu, 1, 4 );
    detruire(jeu, 2, 4 );
    detruire(jeu, 3, 4 );
    detruire(jeu, 4, 4);
    detruire(jeu, 5, 4 );
    detruire(jeu, 6, 4 );

    afficher(stdout, jeu);

    int r = 0; 
    
    r = connexe(jeu, 1, 2);

    REQUIRE( 0 == r);

    liberer(&jeu);
}



END_TEST_GROUP(isola)


int main() {
    RUN_TEST_GROUP(isola); 
 
   return 0;
}

