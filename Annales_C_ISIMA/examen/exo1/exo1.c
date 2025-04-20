#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "code.h"
#include "teZZt.h"


// DEBUT DES FONCTIONS DE TESTS
BEGIN_TEST_GROUP(isola)

TEST(INITIALISER, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    REQUIRE( 0==strcmp(buffer, res));    
}

TEST(DETRUIRE1, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2   X            \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);
    int r = detruire(terrain, 2, 2);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res));    
}


TEST(DETRUIRE2, "") {
    Terrain terrain;

    initialiser(terrain);
    
    int r = detruire(terrain, 2, 2);
    CHECK( 1 == r);

    r = detruire(terrain, 2, 2);
    REQUIRE( 0 == r);

}

TEST(DETRUIRE3, "") {
    Terrain terrain;

    initialiser(terrain);
    int r = 1;

    r = detruire(terrain, 0, 0);
    REQUIRE( 0 == r);
    
    r = detruire(terrain, L+2, C+2);
    REQUIRE( 0 == r);

    r = detruire(terrain, -1, -1);
    REQUIRE( 0 == r);

    r = detruire(terrain, 30, 6);
    REQUIRE( 0 == r);
}

TEST(TROUVER1, "") {
    Terrain terrain;
    int i,j;

    initialiser(terrain);

    trouver(terrain, 1, &i, &j);
    
    REQUIRE( -1 == i);
    REQUIRE( -1 == j);    
}


TEST(PLACER1, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3   1            \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);
    int r = placer(terrain, 1, 3, 2);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res));    
}

TEST(TROUVER2, "") {
    Terrain terrain;
    int i = -1,j =-1;

    initialiser(terrain);
    int r = placer(terrain, 1, 3, 2);

    trouver(terrain, 1, &i, &j);
    
    REQUIRE( 1 == r);
    REQUIRE( 3 == i);
    REQUIRE( 2 == j);    
}

TEST(PLACER2, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1                \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5         1      \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);
    int r = placer(terrain, 1, 3, 2);

    // on change l'emplacement du joueur 1
    r = placer(terrain, 1, 5, 5);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    
    REQUIRE( 1 == r);
    REQUIRE( 0 == strcmp(buffer, res));    
}


TEST(PLACER3, "") {
    Terrain terrain;

    initialiser(terrain);
    int r = placer(terrain, 1, 3, 2);

    REQUIRE( 1 == r);
    
    // Le meme joueur ne peut etre mis deux fois
    r = placer(terrain, 1, 3, 2);
    REQUIRE( 0 == r);

    // un autre joueur ne peut etre au meme endroit
    r = placer(terrain, 2, 3, 2);
    REQUIRE( 0 == r);

    // pas en dehors du terrain non plus
    r = placer(terrain, 1, 0, 0);
    REQUIRE( 0 == r);
}

TEST(DEPLACER1, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1 1              \n"
                       " 2                \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);
    int r = placer(terrain, 1, 3, 2);
    r = deplacer(terrain, 1, 7);
    REQUIRE( 1 == r);
    r = deplacer(terrain, 1, 8);
    REQUIRE( 1 == r);
    r = deplacer(terrain, 1, 7);
    REQUIRE( 0 == r);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    
    REQUIRE( 0 == strcmp(buffer, res));    
}

TEST(BLOQUER1, "") {
    Terrain terrain;
    
    initialiser(terrain);
    
    placer  (terrain, 1, 1, 1);
    
    int r = bloque(terrain, 1);
    REQUIRE( 0 == r);
}

TEST(BLOQUER2, "") {
    Terrain terrain;
    
    const char * res = "   1 2 3 4 5 6 7 8\n"
                       " 1 1 X            \n"
                       " 2 X X            \n"
                       " 3                \n"
                       " 4                \n"
                       " 5                \n"
                       " 6                \n";

    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
    
    initialiser(terrain);

    placer  (terrain, 1, 1, 1);

    detruire(terrain, 1, 2);
    detruire(terrain, 2, 1);
    detruire(terrain, 2, 2);
    
    int r = bloque(terrain, 1);
    REQUIRE( 1 == r);

    afficher(stdout, terrain);
    afficher(file, terrain);

    fclose(file);
    
    REQUIRE( 0 == strcmp(buffer, res));    
}
/*
TEST(CONNEXE1, "") {
    Terrain terrain;
    
    initialiser(terrain);

    placer  (terrain, 1, 1, 1);
    placer  (terrain, 2, 5,6);
    
    afficher(stdout, terrain);

    int r = 0; 

    r = connexe(terrain, 1, 2);

    REQUIRE( 1 == r);
}

TEST(CONNEXE2, "") {
    Terrain terrain;
    
    initialiser(terrain);

    placer  (terrain, 1, 1, 1);
    placer  (terrain, 2, 5, 6);

    detruire(terrain, 1, 7 );
    detruire(terrain, 2, 6 );
    detruire(terrain, 3, 5 );
    detruire(terrain, 4, 4 );
    detruire(terrain, 5, 3 );
    detruire(terrain, 6, 2 );


    afficher(stdout, terrain);

    int r = 0; 
    
    r = connexe(terrain, 1, 2);

    REQUIRE( 1 == r);
}


TEST(CONNEXE3, "") {
    Terrain terrain;
    
    initialiser(terrain);

    placer  (terrain, 1, 1, 1);
    placer  (terrain, 2, 5, 6);

    detruire(terrain, 1, 4 );
    detruire(terrain, 2, 4 );
    detruire(terrain, 3, 4 );
    detruire(terrain, 4, 4);
    detruire(terrain, 5, 4 );
    detruire(terrain, 6, 4 );

    afficher(stdout, terrain);

    int r = 0; 
    
    r = connexe(terrain, 1, 2);

    REQUIRE( 0 == r);
}

*/

END_TEST_GROUP(isola)


int main() {
    RUN_TEST_GROUP(isola); 
 
   return 0;
}

