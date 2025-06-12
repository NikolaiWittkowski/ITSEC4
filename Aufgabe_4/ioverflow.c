#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// berechne ein pseudo hash value basierend auf dem passwort
unsigned int rechneHash(const char *password) {
    unsigned int hash = 0;

    //automatisch int overflow provozieren, demozwecke
    if (strcmp(password, "IntegerOverflow") == 0) {
        //2^32 + 42 = ergibt durch overflow: 42
        unsigned long long grossWert = 4294967338ULL; //ULL unsigned long long

        //expliziter cast auf signed int. Nur die unteren 32 bit bleiben
        hash += (unsigned int)grossWert; // hier entsteht der overflow bewusst 

        printf("\nInteger Overflow demonstration.\n");
        printf("addition von 4294967338 (2^32 + 42) zu unsigned int Hash.\n");
        printf("durch overflow wird nur der untere 32 bit teil verwendet:\n");
        printf("(unsigned int)(4294967338) = %u\n\n", hash);
        
        return hash;
    }
    
    //summiere ASCII werte der pw-zeichen
    int len = strlen(password);
    for (int i = 0; i < len; i++) {
        hash += (unsigned int)password[i];
    }

    return hash;
}

// auth funktion - vergleicht berechneten hash mit dem festgesetzten wert (42)
int auth(const char *password) {
    // berechne den hash des input pw
    unsigned int hash = rechneHash(password);

    // vergleiche mit dem erwarteten Hash-Wert
    // zum testzweck: korrektes pw ergibt einen hash von 42
    if (hash == 42) {
        printf("auth erfolgreich. Sup\nHash: %u\n", hash);
        return 1;
    } else {
        printf("auth fail. Hash: %u\n", hash);
        return 0;
    }
}

int main() {
    char password[256]; // buffer für passwordinput

    printf("HINWEIS: der Hash des Passworts muss 42 ergeben\n");
    printf("Für Demozwecke: gib 'IntegerOverflow' ein, um automatisch einen Overflow zu testen\n");
    printf("Passwort eingeben: ");

    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("error beim input.\n");
        return 1;
    }

    // remove (\n) aus der eingabe
    password[strcspn(password, "\n")] = '\0';

    // auth versuchen
    auth(password);

    return 0;
}

