#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v(char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania, int *pocet_zaznamov) {
    FILE *subor = fopen("dataloger.txt", "r");
    if (subor == NULL) {
        printf("Subor sa nepodarilo otvorit\n");
        return;
    }

    char riadok[256];
    int zaznam_cislo = 0;

    if (*pocet_zaznamov == 0) {
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
        printf("Pisem zo suboru\n");
        for (int i = 0; i < *pocet_zaznamov; i++) {
            printf("ID. mer. modulu: %s", (*id_modulu)[i]);
            printf("Pozícia modulu: %s", (*pozicia_modulu)[i]);
            printf("Typ mer. veliciny: %s", (*typ_mer_veliciny)[i]);
            printf("Hodnota: %.2lf\n", (*hodnota)[i]);
            printf("Cas merania: %04d\n", (*cas_merania)[i]);
            printf("Datum merania: %08d\n", (*datum_merania)[i]);
            printf("\n");
        }
    }
    fclose(subor);
}

void n(char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania, int *pocet_zaznamov) {
    FILE *subor = fopen("dataloger.txt", "r");
    if (subor == NULL) {
        printf("Chyba pri otvarani suboru.\n");
        return;
    }

    char riadok[256];

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            (*pocet_zaznamov)++;
        }
    }

    rewind(subor);

    char **id_modulu_temp = (char **)malloc((*pocet_zaznamov) * sizeof(char *));
    char **pozicia_modulu_temp = (char **)malloc((*pocet_zaznamov) * sizeof(char *));
    char **typ_mer_veliciny_temp = (char **)malloc((*pocet_zaznamov) * sizeof(char *));
    double *hodnota_temp = (double *)malloc((*pocet_zaznamov) * sizeof(double));
    int *cas_merania_temp = (int *)malloc((*pocet_zaznamov) * sizeof(int));
    int *datum_merania_temp = (int *)malloc((*pocet_zaznamov) * sizeof(int));
    int aktualny_zaznam = 0;

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            continue;
        }

        switch (aktualny_zaznam % 6) {
            case 0:
                id_modulu_temp[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 1:
                pozicia_modulu_temp[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 2:
                typ_mer_veliciny_temp[aktualny_zaznam / 6] = strdup(riadok);
                break;
            case 3:
                hodnota_temp[aktualny_zaznam / 6] = atof(riadok);
                break;
            case 4:
                cas_merania_temp[aktualny_zaznam / 6] = atoi(riadok);
                break;
            case 5:
                datum_merania_temp[aktualny_zaznam / 6] = atoi(riadok);
                break;
        }

        aktualny_zaznam++;
    }
    *id_modulu = id_modulu_temp;
    *pozicia_modulu = pozicia_modulu_temp;
    *typ_mer_veliciny = typ_mer_veliciny_temp;
    *hodnota = hodnota_temp;
    *cas_merania = cas_merania_temp;
    *datum_merania = datum_merania_temp;

    fclose(subor);
}

void c(char **id_modulu, int *datum_merania, int pocet_zaznamov) {
    int Y;
    printf("Zadaj počet mesiacov: \n");
    scanf("%d", &Y);

    FILE *subor = fopen("ciachovanie.txt", "r");

    char riadok[256];
    int Cpocet_zaznamov = 0;

    if (!subor) {
        printf("Chyba pri otváraní súboru.\n");
        return;
    }

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            Cpocet_zaznamov++;
        }
    }
    rewind(subor);

    char **id_moduluC_temp = (char **)malloc(Cpocet_zaznamov * sizeof(char *));
    int *datum_merania_temp = (int *)malloc(Cpocet_zaznamov * sizeof(int));
    int aktualny_zaznam = 0;

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (riadok[0] == '\n') {
            continue;
        }

        switch (aktualny_zaznam % 2) {
            case 0:
                id_moduluC_temp[aktualny_zaznam / 2] = strdup(riadok);
                break;
            case 1:
                datum_merania_temp[aktualny_zaznam / 2] = atoi(riadok);
                break;
        }

        aktualny_zaznam++;
    }

    int nekorektnyZaznam = 0; // Pre kontrolu, či záznamy nie sú korektné

    for (int i = 0; i <= pocet_zaznamov; i++) {
        int nasielSa = 0; // Pre kontrolu, či sa našiel záznam v poli id_modulu
        for (int j = 0; j <= Cpocet_zaznamov; j++) {
            int datum_ciachovania = datum_merania_temp[j];
            if (strcmp(id_modulu[i], id_moduluC_temp[j]) == 0) {
                nasielSa = 1;
                int rozdiel_mesiacov = (datum_merania[i] / 10000 - datum_ciachovania / 10000) * 12 +
                                       (datum_merania[i] / 100 % 100 - datum_ciachovania / 100 % 100);
                if (rozdiel_mesiacov > Y) {
                    printf("ID. mer. modulu [%s] má %d mesiacov od ciachovania.\n", id_modulu[i], rozdiel_mesiacov);
                }
            }
        }

        if (nasielSa == 0) {
            printf("ID. mer. modulu [%s] nie je ciachovany.\n", id_modulu[i]);
            nekorektnyZaznam = 1;
        }
    }

    if (nekorektnyZaznam == 0) {
        printf("Data su korektne.\n");
    }

    // Uvoľnenie temp premenných a dynamicky alokovanej pamäte
    for (int i = 0; i < Cpocet_zaznamov; i++) {
        free(id_moduluC_temp[i]);
    }
    free(id_moduluC_temp);
    free(datum_merania_temp);

    fclose(subor);
}


void s() {
    // Doimplementujte tuto funkciu
}

void h() {
    // Doimplementujte tuto funkciu
}

void z() {
    // Doimplementujte tuto funkciu
}

void k() {
    // Doimplementujte tuto funkciu
}

int main() {
    char prikaz;
    char **id_modulu = NULL;
    char **pozicia_modulu = NULL;
    char **typ_mer_veliciny = NULL;
    double *hodnota = NULL;
    int *cas_merania = NULL;
    int *datum_merania = NULL;
    int pocet_zaznamov = 0;

    while (1) {
        printf("Zadaj prikaz: ");
        scanf(" %c", &prikaz);

        if (prikaz == 'v') {
            v(&id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania, &pocet_zaznamov);
        } else if (prikaz == 'n') {
            n(&id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania, &pocet_zaznamov);
        } else if (prikaz == 'c') {
            c(id_modulu, datum_merania, pocet_zaznamov);
        } else if (prikaz == 's') {
            s();
        } else if (prikaz == 'h') {
            h();
        } else if (prikaz == 'z') {
            z();
        } else if (prikaz == 'k') {
            k();
        } else {
            printf("Neplatný príkaz\n");
            break;
        }
    }

    // Uvoľnenie dynamicky alokovanej pamäte na konci programu
    for (int i = 0; i < pocet_zaznamov; i++) {
        free(id_modulu[i]);
        free(pozicia_modulu[i]);
        free(typ_mer_veliciny[i]);
    }
    free(id_modulu);
    free(pozicia_modulu);
    free(typ_mer_veliciny);
    free(hodnota);
    free(cas_merania);
    free(datum_merania);

    return 0;
}
