#include "biblioteki/biblioteka.h"

int main(){
    //zmienne dla programu

    //tworzenie kolejki komunikatów
    int idKomunikatu = msgget(1995, IPC_CREAT|0777);
    if(idKomunikatu == -1){
        perror("Tworzenie kolejki komunikatów");
        exit(1);
    }

    //tworzenie kolejki FIFO
    printf("Uruchom serwer!\n");
    mkfifo("_fifo_", 0777);
    int idKolejki = open("_fifo_", O_RDONLY);

    while(1){
        czyscEkran();
        switch(menu()){
            case WYPISZ:
                czyscEkran();
                printf("Dane znajdujące się na partycji\n\n");
                wyslijZapytanie(idKomunikatu, WYPISZ, NULL);
                Plik* dane = malloc(sizeof(Plik));      //alokacja pamięci

                while(1){
                    dane = odbierzDane(idKolejki);
                    if(!(strcmp(dane->nazwaPliku, "NULL") && strcmp(dane->dataUtworzenia, "NULL") && strcmp(dane->rozszerzeniePliku, "NULL"))) break;   //warunek zakonczenia pobierania danych od serwera
                    if(dane->usun != 0) continue;   //pomijanie wyswietlania usunietych plikow
                    printf("%s.%s | %ld bajtów | %s\n", dane->nazwaPliku, dane->rozszerzeniePliku, dane->rozmiar, dane->dataUtworzenia);
                }

                free(dane);                             //zwalnianie pamieci
                printf("\n\nWciśnij dowolny klawisz, aby kontynuować");
                getchar(); getchar();
            break;

            case DODAJ:
                czyscEkran();
                printf("Nazwa pliku[max 16 znaków]: ");
                char *nazwaPliku = wprowadzDane(16);
                wyslijZapytanie(idKomunikatu, DODAJ, nazwaPliku);

            break;

            case POBIERZ:
                wyslijZapytanie(idKomunikatu, POBIERZ, NULL);
            break;

            case ZMIEN:
                wyslijZapytanie(idKomunikatu, ZMIEN, NULL);
            break;

            case USUN:
                wyslijZapytanie(idKomunikatu, USUN, NULL);
            break;

            default:
                wyslijZapytanie(idKomunikatu, 0, NULL);
                if(msgctl(idKomunikatu, IPC_RMID, NULL) == -1){
                    perror("Usuwanie kolejki komunikatów");
                    exit(1);
                }

                unlink("_fifo_");
                return 0;
        }

    }
}
