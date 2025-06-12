#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//wird nicht direkt aufgerufen, daher nicht erreichbar
void win() {
    system("/bin/sh"); //wenn der ROP exploit klappt, wird eine shell aufgerufen
}

//dummy functions, einfach für mehr gadgets
void dummy1(int a, int b) {
    printf("dum1: %d %d\n", a, b);
}

void dummy2(int x) {
    printf("dum2: %d\n", x);
}

//funktion mit buffer overflow vulnerability
void critFunc() {
    char buffer[64];
    printf("Input: ");
    gets(buffer);  //buffer overflow, gets unsicher
}

int main() {
    setbuf(stdout, NULL);
    critFunc();
    return 0;
}

