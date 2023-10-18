#include "stdio.h"
#include <stdlib.h>
#include "string.h"

char **id_modulu = NULL;
char **pozicia_modulu = NULL;
char **typ_mer_veliciny = NULL;
double *hodnota = NULL;
int *cas_merania = NULL;
int *datum_merania = NULL;
int pocet_zaznamov = 0;


void v(){
    FILE *subor = fopen("dataloger.txt", "r");
    if (subor == NULL){
        printf("Subor sa nepodarilo otvorit\n");
        return;
    }
    char riadok[256];
    int zaznam_cislo = 0;
    if (pocet_zaznamov == 0){
        while (fgets(riadok, sizeof(riadok), subor)) {
            char *newline = strchr(riadok, '\n');
            if (newline) {
                *newline = '\0';
            }

            switch (zaznam_cislo % 6) {
                case 0:
                    printf("ID. mer. modulu: %s\n", riadok);
                    break;
                case 1:
                    printf("Pozícia modulu: %s\n", riadok);
                    break;
                case 2:
                    printf("Typ mer. veliciny: %s\n", riadok);
                    break;
                case 3:
                    printf("Hodnota: %s\n", riadok);
                    break;
                case 4:
                    printf("Cas merania: %s\n", riadok);
                    break;
                case 5:
                    printf("Datum merania: %s\n", riadok);
                    printf("\n"); // Prázdny riadok medzi záznammi
                    break;
            }

            zaznam_cislo++;
        }
    } else {
        printf("pisem zo suboru\n");
        for (int i = 0; i < pocet_zaznamov; i++) {
            printf("ID. mer. modulu: %s", id_modulu[i]);
            printf("Pozicia modulu: %s", pozicia_modulu[i]);
            printf("Typ mer. veliciny: %s", typ_mer_veliciny[i]);
            printf("Hodnota: %.2lf\n", hodnota[i]);
            printf("Cas merania: %04d\n", cas_merania[i]);
            printf("Datum merania: %08d\n", datum_merania[i]);
            printf("\n");
        }
    }
    fclose(subor);
}


void n(){
    FILE *subor = fopen("dataloger.txt", "r");
    if (!subor) {
        printf("Chyba pri otvarani suboru.\n");
        return;
    }

    // Získajte počet záznamov v súbore
    char riadok[256];

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            pocet_zaznamov++;
        }
    }

    rewind(subor);

    // Dynamicky vytvorte polia pre jednotlivé položky
    id_modulu = (char **)malloc(pocet_zaznamov * sizeof(char *));
    pozicia_modulu = (char **)malloc(pocet_zaznamov * sizeof(char *));
    typ_mer_veliciny = (char **)malloc(pocet_zaznamov * sizeof(char *));
    hodnota = (double *)malloc(pocet_zaznamov * sizeof(double));
    cas_merania = (int *)malloc(pocet_zaznamov * sizeof(int));
    datum_merania = (int *)malloc(pocet_zaznamov * sizeof(int));
    int aktualny_zaznam = 0;

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            continue;
        }

        switch (aktualny_zaznam % 6) {
            case 0:
                id_modulu[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 1:
                pozicia_modulu[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 2:
                typ_mer_veliciny[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 3:
                hodnota[aktualny_zaznam / 6] = atof(riadok);
                break;
            case 4:
                cas_merania[aktualny_zaznam / 6] = atoi(riadok);
                break;
            case 5:
                datum_merania[aktualny_zaznam / 6] = atoi(riadok);
                break;
        }

        aktualny_zaznam++;
    }
}

void c(){

}

void s(){

}
void h(){

}

void z(){

}

void k(){

}

int main(){
    char prikaz;
    while (1) {
        printf("Zadaj prikaz: ");
        scanf(" %c", &prikaz);

        if (prikaz == 'v') {
            v();
        } else if (prikaz == 'n') {
            n();
        } else if (prikaz == 'n') {
            n();
        } else if (prikaz == 'c') {
            c();
        } else if (prikaz == 's') {
            s();
        } else if (prikaz == 'h') {
            h();
        } else if (prikaz == 'z') {
            z();
        } else if (prikaz == 'k') {
            k();
        } else {
            printf("neplatny prikaz");
            break;
        }
    }
}