#include "biblioteki/biblioteka.h"

int main(int argc, char** argv){
    //zmienne dla programu
    char* nazwaDysku = argv[1];

    //odbieranie kolejki komunikatow
    int idKomunikatu = msgget(1995, 0777);
    if(idKomunikatu == -1){
        perror("Otwieranie komunikatu");
        exit(1);
    }

    //tworzenie kolejki FIFO
    mkfifo("_fifo_", 0777);
    int idKolejki = open("_fifo_", O_WRONLY);

    //funkcje inicjalizacujne
    zaladujDysk(nazwaDysku);




    while(1){
        Komunikat dane;
        dane = odbierzZapytanie(idKomunikatu);
        int i = dane.wiadomosc;
        char bufor[255];
        strcpy(bufor, dane.dane);

        switch(i){
            case WYPISZ:
                puts("Wypisz wszystkie dane");
                Plik* naglowek = malloc(sizeof(Plik));

                strcpy(naglowek->nazwaPliku, "motyle");
                strcpy(naglowek->rozszerzeniePliku, "png");
                strcpy(naglowek->dataUtworzenia, "06/06/2016");
                naglowek->rozmiar = 2000;
                naglowek->usun = 0;
                wyslijDane(idKolejki, naglowek);

                strcpy(naglowek->nazwaPliku, "analiza");
                strcpy(naglowek->rozszerzeniePliku, "txt");
                strcpy(naglowek->dataUtworzenia, "06/08/2016");
                naglowek->rozmiar = 3000;
                naglowek->usun = 1;
                wyslijDane(idKolejki, naglowek);

                strcpy(naglowek->nazwaPliku, "pliczek");
                strcpy(naglowek->rozszerzeniePliku, "txt");
                strcpy(naglowek->dataUtworzenia, "01/01/2015");
                naglowek->rozmiar = 100;
                naglowek->usun = 0;
                wyslijDane(idKolejki, naglowek);

                //-----------------komunikat wysylany zawsze na koncu----------------------
                strcpy(naglowek->nazwaPliku, "NULL");     //ostatni plik zawsze bedzie mial pola o wartosci "NULL"
                strcpy(naglowek->dataUtworzenia, "NULL");
                strcpy(naglowek->rozszerzeniePliku, "NULL");
                wyslijDane(idKolejki, naglowek);
                free(naglowek);
            break;
            case DODAJ:
                puts("Dodaj dane");
                puts(bufor);
            break;
            case POBIERZ:
                puts("Pobierz dane");
            break;
            case ZMIEN:

                puts("Zmień nazwę");
            break;
            case USUN:
                puts("Usuń dane");
            break;
            default:
                puts("Koniec programu");
                return 0;
        }
    }
}
