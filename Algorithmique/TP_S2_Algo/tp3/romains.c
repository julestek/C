#include <stdio.h>
#include <string.h>
#include "romains.h"


int chiffreRomainToDecimal(char chiffreRomain){
	char chiffres[]={'M','D','C','L','X','V','I','f'};
	int valeursDecimales[]={1000,500,100,50,10,5,1};
	int decimal=0;
	for (int i = 0; chiffres[i]!='f';i++){
		if (chiffres[i]==chiffreRomain){
			decimal=valeursDecimales[i];
		}
	}
	return decimal;
}
int AuxnombreRomainToDecimal(char* strRomain, int i) {
    if (strRomain[i] == '\0') {
        return 0;
    }
    
    int valeurActuelle = chiffreRomainToDecimal(strRomain[i]);
    int valeurSuivante = chiffreRomainToDecimal(strRomain[i + 1]);

    if (valeurActuelle < valeurSuivante) {
        return -valeurActuelle + AuxnombreRomainToDecimal(strRomain, i + 1);
    } else {
        return valeurActuelle + AuxnombreRomainToDecimal(strRomain, i + 1);
    }
}

int nombreRomainToDecimal(char* strRomain) {
    if (strRomain == NULL || strRomain[0] == '\0') {
        return -1;
    }

    printf("Entrée dans nombreRomainToDecimal, chiffreRomain=%s\n", strRomain);
    int decimal = AuxnombreRomainToDecimal(strRomain, 0);
    printf("Sortie de nombreRomainToDecimal, chiffreRomain=%s, valeur retournée: %d\n", strRomain, decimal);
    
    return decimal;
}
