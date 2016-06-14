#include "biblioteka.h"

//zmienne globalne
Komunikat komunikat;

int menu(){
    puts("Wybierz odpowiednią opcję\n");
    puts("1) Wypisz dane zawarte na plikopartycji");
    puts("2) Dodaj dane do plikopartycji");
    puts("3) Pobierz dane do katalogu z programem");
    puts("4) Zmień nazwę pliku na plikopartycji");
    puts("5) Usuń dane z plikopartycji\n");
    puts("0) Zakończ program\n");
    printf("Twój wybór: ");
    int wybor;
    scanf("%d", &wybor);
    return wybor;
}

void wyslijZapytanie(int id, int rodzajZapytania, char *dane){
    Komunikat komunikat;

    if(dane != NULL)
        strcpy(komunikat.dane, dane);
    komunikat.typKomunikatu = 1;                                //typ komunikatu ustawiony na 1 - zakladamy ze normalny komunikat
    komunikat.wiadomosc = rodzajZapytania;

    if(msgsnd(id, &komunikat, sizeof(komunikat), 0) == -1){
        perror("Wysyłanie komunikatu");
        exit(1);
    }
}

Komunikat odbierzZapytanie(int id){
    if(msgrcv(id, &komunikat, sizeof(komunikat), 1, 0) >= 0){}  //tak musi byc bo inaczej nie dziala
    return komunikat;
}


void zaladujDysk(char* nazwaPartycji){                          //funkcja nic nie robi podczas, gdy plik istnieje
    FILE* plik;
    plik = fopen(nazwaPartycji, "rb+");
    if(plik == NULL){
        plik = fopen(nazwaPartycji, "wb+");
        if(plik == NULL){
            perror("Tworzenie pliku");
            exit(1);
        }else{
            int i;
            for(i=0; i<50*10000; i++){                          //50*10000 = 500000*100bajtów = 50000000bajtów = 50MB
                fwrite("\0", 1, 100, plik);
            }
        }
    }
    fclose(plik);
}

void wyslijDane(int id, Plik *naglowek){
    write(id, naglowek, sizeof(Plik));
}

Plik* odbierzDane(int id){
    Plik* naglowek = malloc(sizeof(Plik));
    if(read(id, naglowek, sizeof(Plik)) == -1){
        perror("Błąd");
        exit(1);
    }
    return naglowek;
}

//tutaj ostatnio zakonczylem
char* wprowadzDane(int iloscZnakow){
    char *bufor = malloc(sizeof(char)*30);
    while(1){
        scanf("%s", bufor);
        if (sprawdzZnaki(bufor, iloscZnakow)) break;
        printf("Zbyt duża ilość znaków!\nPowtórz: ");
    }
    return bufor;
}

int sprawdzZnaki(char *napis, int iloscZnakow){
    if(strlen(napis) <= iloscZnakow) return 1;
    return 0;
}
