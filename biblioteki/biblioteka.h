#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

//biblioteki uzywane w programie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

//makrodefinicje i stale uzywane w programie
#define czyscEkran() printf("\033[H\033[J")
#define WYPISZ 1
#define DODAJ 2
#define POBIERZ 3
#define ZMIEN 4
#define USUN 5

//struktury
typedef struct Plik{
    char nazwaPliku[17];        //16 znaków
    char rozszerzeniePliku[4];  //3 znaki
    char dataUtworzenia[11];    //10 znaków
    char usun;                  //0 - nie 1 - tak
    unsigned long rozmiar;

}Plik;

typedef struct Komunikat{
    long typKomunikatu;         //typ komunikatu
    int wiadomosc;              //rodzaj wiadomosci
    char dane[255];             //maksymalny rozmiar wysylanych danych
}Komunikat;


//funkcje dla klienta
int menu();
Plik* odbierzDane(int id);
char* wprowadzDane(int iloscZnakow);
void wyslijZapytanie(int id, int rodzajZapytania, char* dane);

//funkcje dla serwera
void zaladujDysk(char *nazwaPartycji);
void wyslijDane(int id, Plik *naglowekPliku);
Komunikat odbierzZapytanie(int id);


//funckje dodatkowe
int sprawdzZnaki(char *napis, int iloscZnakow);
#endif // BIBLIOTEKA_H
