#include <stdio.h>
#include <string.h>
#include "romains.h"


int chiffreRomainToDecimal(char chiffreRomain){
    char chiffres[] = {'M','D','C','L','X','V','I','\0'};
    int valeursDecimales[] = {1000,500,100,50,10,5,1};

    for (int i = 0; chiffres[i] != '\0'; i++){
        if (chiffres[i] == chiffreRomain){
            return valeursDecimales[i];
        }
    }

    return -1;
}

int AuxnombreRomainToDecimal(char* strRomain, int i) {
    if (strRomain[i] == '\0') return 0;

    int valeurActuelle = chiffreRomainToDecimal(strRomain[i]);
    if (valeurActuelle == -1) return -1;

    int valeurSuivante = chiffreRomainToDecimal(strRomain[i + 1]);
    if (valeurSuivante == -1 && strRomain[i + 1] != '\0') return -1;

    if (valeurSuivante > valeurActuelle) {
        int suite = AuxnombreRomainToDecimal(strRomain, i + 1);
        if (suite == -1) return -1;
        return -valeurActuelle + suite;
    } else {
        int suite = AuxnombreRomainToDecimal(strRomain, i + 1);
        if (suite == -1) return -1;
        return valeurActuelle + suite;
    }
}

int nombreRomainToDecimal(char* strRomain) {
    if (strRomain == NULL || strRomain[0] == '\0') return -1;

    int resultat = AuxnombreRomainToDecimal(strRomain, 0);
    return resultat;
}