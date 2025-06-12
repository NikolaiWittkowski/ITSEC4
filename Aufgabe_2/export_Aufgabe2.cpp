#include <iostream>
#include <cstring>
#include <string>

int main() {
    char local_78[16];       // Kennwort-Puffer
    char local_68[32];       // Benutzername-Puffer
    char local_48[44];       // Entschlüsselter Flag-Puffer
    int local_1c = 0;        // Authentifizierungsvariable 

    std::cout << "Benutzername: ";       // Benutzername Input
    std::cin >> local_68;                // Eingabe OHNE Längenprüfung !!! 

    std::cout << "Kennwort: ";           // Kennwort abfragen
    std::cin >> local_78;                // Eingabe OHNE Längenprüfung !!! 

    //ACHTUNG: Durch die fehlende Längenprüfung wird ein BufferOverflow ermöglicht!!!

    if (strcmp(local_68, "ITS") == 0) {                          // Benutzername vergleichen
        if (strcmp(local_78, "String_Lesen_Ist_Nicht Die Loesung") == 0) {  // Passwort vergleichen
            local_1c = 1; // Wenn beides stimmt, dann wird die Authentifizierungsvariable auf 1 (true gesetzt)
        }
    }
    /*
    HINWEIS: Interessante Stelle, da hier nur geprüft wird, ob die Authentifizierungsvariable < 1 ist!

    Kurze Zwischenanmerkung (wird später genauer erläutert):
    Da die lokalen Variablen auf dem Stack hintereinander liegen (local_78 → local_68 → local_48 → local_1c),    
    und keine Längenprüfung für die Eingabe stattfindet, ist es möglich durch einen
    Buffer-Overflow die int variable zu überschreiben, unabhängig von der korrekten Eingabe der Login-Daten.

    Bei einem Overflow werden die eingegebenen Zeichen als rohe Bytes in den Speicher geschrieben.
    Bedeutet, das Zeichen wie 'A' werden intern zu ihrem ASCII-Wert --> 0x41 umgewandelt.
    //auch bei Zahlen: 1 wird als 0x31 interpretiert. Heißt bei 2 Zahlen sind es auch = 2 Bytes
    Je nach CPU Architektur (z.B. Little Endian) Byte für Byte in den int-Variable geschrieben

    Dadurch kann man die Passwortprüfung komplett umgehen!
    */
    if (local_1c < 1) {
        std::cout << "Falscher Benutzername oder Kennwort!\n";  // Fehlermeldung
    } else {
        //41 Zeichen, ul = unsigned long
        str_decrypt<41ul>(local_48);              // Flag entschlüsseln
        std::cout << local_48 << std::endl;       // Flag ausgeben (vereinfacht)
    }
    return 0;
}


/*

// # Decompiled Code aus Aufgabe1 exportiert aus Ghidra

undefined8 main(void)

{
  int iVar1;
  char *__s;
  char local_78 [16];
  char local_68 [32];
  array local_48 [44];
  int local_1c;
  
  local_1c = 0;
  std::operator<<((ostream *)std::cout,"Benutzername: ");
  std::operator>>((istream *)std::cin,local_68);
  std::operator<<((ostream *)std::cout,"Kennwort: ");
  std::operator>>((istream *)std::cin,local_78);
  iVar1 = strcmp(local_68,"ITS");
  if (iVar1 == 0) {
    iVar1 = strcmp(local_78,"String_Lesen_Ist_Nicht Die Loesung");
    if (iVar1 == 0) {
      local_1c = 1;
    }
  }
  if (local_1c < 1) {
    std::operator<<((ostream *)std::cout,"Falscher Benutzername oder Kennwort!\n");
  }
  else {
    str_decrypt<41ul>(local_48);
    __s = (char *)std::__cxx11::string::c_str();
                    //try { // try from 00401459 to 0040145d has its CatchHandler @ 0040148c 
    puts(__s);
    std::__cxx11::string::~string((string *)local_48);
  }
  return 0;
}

*/