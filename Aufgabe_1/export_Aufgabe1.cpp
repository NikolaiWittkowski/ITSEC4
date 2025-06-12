/*
=============================
Binary: Aufgabe 1 Rekonstruktion
==============================

Hinweis: Der Code stellt nur eine funktionele Annähehrung dar, 
keine 1:1 Rekonstruktion der Originalimplementierung


+ PseudoCode und Decompiled Code aus Ghidra, wurden unten in den Kommentaren ergänzt

*/



#include <iostream>
#include <string>

// Verschlüsseltes Byte-Array 
// Kumulative additive Verschlüsselung
//    cipher[i] = plain[i] - sum;
//    sum += cipher[i]
// => wurde bereits direkt verschlüsselt!
unsigned char encrypted_flag[] = {
    0x68, 0xe7, 0x14, 0x05, 0xeb, 0xf0, 0x25, 0xed, 0xf7, 0x19,
    0xd3, 0x17, 0xf4, 0x05, 0x0d, 0xf8, 0xe0, 0x1c, 0x0b, 0xff,
    0xda, 0x43, 0xe2, 0xe2, 0x17, 0x29, 0xd5, 0x22, 0x0a, 0xd8,
    0xe5, 0xfb, 0x13, 0x35, 0xf1, 0xd3, 0x28, 0xe1, 0x23, 0xcc,
    0xcf
}; // 41 Zeichen


using namespace std;

// Annahme: str_decrypt füllt einen String mit entschlüsselten Daten (die Flag)
void str_decrypt(char *b){

  //Keine negativen Werte, da nur der Wertebereich: {0, 255} relevant ist
  //deswegen auch kein mod nötig, wird automatisch gemacht => 255 + 1 = 0, 255 + 45 = 300 --> 44
  unsigned char sum = 0;

  // Entschlüsselung (Rückführung der kumulativen Verschlüsselung)
  //   sum += cipher[i];
  //   plain[i] = sum;
  for(int i = 0; i < sizeof(encrypted_flag); i++){
    sum += encrypted_flag[i];
    b[i] = (char)sum;
  }

  //Terminierung (Ende des "Strings" setzen)
  b[41] = '\0';
}

int main(int argc, char *argv[]) {
    char* decrypted_string;
    char buffer[44];                // Buffer zur Übergabe an str_decrypt (Flag)
    int input_value;

    // argv[1] wird als String übergeben --> mit atoi in int konvertiert
    input_value = atoi(argv[1]);

    // es wird 0x45 (dezimal 69) addiert
    input_value = input_value + 69;

    // Prüfung, ob der modifizierte Wert = 1337 (0x539) ist
    if (input_value == 1337) {
        // Die verschlüsselte Nachricht (Flag) wird entschlüsselt
        str_decrypt(buffer);

        // umwandlung des entschlüsselten Arrays in einen String (char Array) zur Ausgabe
        decrypted_string = buffer;

        // gibt den entschlüsselten String (die Flag) aus
        puts(decrypted_string);

        // Speicherbereinigung für string-Objekte (in Ghidra relevant, hier symbolisch)
        // => std::__cxx11::string::~string((string *)local_48);
        // In reinem C wäre   unnötig, außer man verwendet malloc
    } else {
        // Wenn die Bedingung nicht erfüllt ist --> Fehlerausgabe auf stderr
        fprintf(stderr, "No !\n");
    }

    return 0;
}


/*
//# Pseudo-Code
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char buffer[100];
    char *decrypted_string;
    int input_value;

    input_value = atoi(argv[1]);            // Eingabe als Zahl interpretieren
    input_value = input_value + 69;         // Konstante Addition vgl. Assembly
    if (input_value == 1337) {              // Vergleich mit Zielwert
        str_decrypt(buffer);                // verschlüsseltes Array wird entschlüsselt
        decrypted_string = buffer;
        puts(decrypted_string);             // Ausgabe der Flag
    } else {
        fprintf(stderr, "No !\n");          // Fehlermeldung bei falscher Eingabe
    }

    return 0;
}


*/






/* 
// # Decompiled Code aus Aufgabe1 exportiert aus Ghidra
undefined8 main(undefined8 param_1,long param_2)

{
  char *__s;
  array local_48 [44];
  int local_1c;
  
  local_1c = atoi(*(char **)(param_2 + 8));
  local_1c = local_1c + 0x45;
  if (local_1c == 0x539) {
    str_decrypt<41ul>(local_48);
    __s = (char *)std::__cxx11::string::c_str();
                    // try { // try from 00401317 to 0040131b has its CatchHandler @ 00401354 
    puts(__s);
    std::__cxx11::string::~string((string *)local_48);
  }
  else {
    FUN_00401120("No !\n",1,5,stderr);
  }
  return 0;
}

*/