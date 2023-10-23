#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256

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
    printf("Zadaj počet mesiacov: ");
    scanf("%d", &Y);

    FILE *subor = fopen("ciachovanie.txt", "r");

    if (!subor) {
        printf("Chyba pri otváraní súboru.\n");
        return;
    }

    char riadok[256];
    int Cpocet_zaznamov = 0;

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

        id_moduluC_temp[aktualny_zaznam] = strdup(riadok);
        fscanf(subor, "%d", &datum_merania_temp[aktualny_zaznam]);
        aktualny_zaznam++;
    }

    // Vypíšeme relevantní záznamy
    for (int i = 0; i < pocet_zaznamov; i++) {
        if (id_modulu[i]) {
            int najdene = 0;
            for (int j = 0; j < Cpocet_zaznamov; j++) {
                if (strcmp(id_modulu[i], id_moduluC_temp[j]) == 0) {
                    int datum_ciachovania = datum_merania_temp[j];
                    int rozdiel_mesiacov = ((datum_merania[i] / 10000 - datum_ciachovania / 10000) * 12 +
                                            (datum_merania[i] / 100 % 100 - datum_ciachovania / 100 % 100));
                    if (rozdiel_mesiacov > Y) {
                        printf("ID. mer. modulu [%s] má %d mesiacov od ciachovania.\n", id_modulu[i], rozdiel_mesiacov);
                    }
                    najdene = 1;
                    break;
                }
            }
            if (!najdene) {
                printf("ID. mer. modulu [%s] nie je ciachovaný.\n", id_modulu[i]);
            }
        }
    }

    // Uvolnění temp proměnných a dynamicky alokované paměti
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

void h(char **typy_meranych_velicin, double *hodnoty, int pocet_zaznamov) {
    if (typy_meranych_velicin == NULL || hodnoty == NULL || pocet_zaznamov == 0) {
        printf("Polia nie sú vytvorené.\n");
        return;
    }


    printf("%-15s %-10s %-10s %-10s\n", "Typ mer. vel.", "Početnosť", "Minimum", "Maximum");


    int pocet_unikatnych_typou = 0;
    char unikatne_typy[100][15];

    for (int i = 0; i < pocet_zaznamov; i++) {
        int nalezeno = 0;
        for (int j = 0; j < pocet_unikatnych_typou; j++) {
            if (strcmp(typy_meranych_velicin[i], unikatne_typy[j]) == 0) {
                nalezeno = 1;
                break;
            }
        }
        if (!nalezeno) {
            strcpy(unikatne_typy[pocet_unikatnych_typou], typy_meranych_velicin[i]);
            pocet_unikatnych_typou++;
        }
    }

    // Vytvořte tabulku pro každý jedinečný typ
    for (int i = 0; i < pocet_unikatnych_typou; i++) {
        char typ[15];
        strcpy(typ, unikatne_typy[i]);

        int pocetnost = 0;
        double minimum = -1.0;
        double maximum = -1.0;

        for (int j = 0; j < pocet_zaznamov; j++) {
            if (strcmp(typy_meranych_velicin[j], typ) == 0) {
                pocetnost++;
                if (minimum == -1.0 || hodnoty[j] < minimum) {
                    minimum = hodnoty[j];
                }
                if (maximum == -1.0 || hodnoty[j] > maximum) {
                    maximum = hodnoty[j];
                }
            }
        }

        // Vytisknout radek tabulky pro aktualni typ
        printf("%-15s %-10d %-10.2lf %-10.2lf\n", typ, pocetnost, minimum, maximum);
    }
}

void z(char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania, int *pocet_zaznamov) {
    // Implementace funkce pro smazání záznamů podle ID
    if (*id_modulu == NULL || *pozicia_modulu == NULL || *typ_mer_veliciny == NULL || *hodnota == NULL || *cas_merania == NULL || *datum_merania == NULL || *pocet_zaznamov == 0) {
        printf("Polia nie sú vytvorené.\n");
        return;
    }

    char id_splatit[MAX_LINE_LENGTH];
    printf("Napíšte ID, které chcete vymazat:\n");
    scanf("%s", id_splatit);

    int pocet_vymazanych = 0;

    for (int i = 0; i < *pocet_zaznamov; i++) {
        if (*id_modulu[i] && strcmp(*id_modulu[i], id_splatit) == 0) {
            free(*id_modulu[i]);
            free(*pozicia_modulu[i]);
            free(*typ_mer_veliciny[i]);
            pocet_vymazanych++;
            // Nastavíme ukazatele na NULL, aby bylo jasné, že tyto záznamy byly smazány
            *id_modulu[i] = NULL;
            *pozicia_modulu[i] = NULL;
            *typ_mer_veliciny[i] = NULL;
        }
    }

    // Vytvoření nových pole bez smazaných záznamů
    char **nove_id_modulu = (char **)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(char *));
    char **nove_pozicia_modulu = (char **)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(char *));
    char **nove_typ_mer_veliciny = (char **)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(char *));
    double *nove_hodnota = (double *)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(double));
    int *nove_cas_merania = (int *)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(int));
    int *nove_datum_merania = (int *)malloc((*pocet_zaznamov - pocet_vymazanych) * sizeof(int));

    int aktualny_index = 0;

    for (int i = 0; i < *pocet_zaznamov; i++) {
        if (*id_modulu[i] != NULL) {
            nove_id_modulu[aktualny_index] = *id_modulu[i];
            nove_pozicia_modulu[aktualny_index] = *pozicia_modulu[i];
            nove_typ_mer_veliciny[aktualny_index] = *typ_mer_veliciny[i];
            nove_hodnota[aktualny_index] = (*hodnota)[i];
            nove_cas_merania[aktualny_index] = (*cas_merania)[i];
            nove_datum_merania[aktualny_index] = (*datum_merania)[i];
            aktualny_index++;
        }
    }

    // Uvolnění původních polí
    free(*id_modulu);
    free(*pozicia_modulu);
    free(*typ_mer_veliciny);
    free(*hodnota);
    free(*cas_merania);
    free(*datum_merania);

    // Nastavení nových polí jako aktuálních polí
    *id_modulu = nove_id_modulu;
    *pozicia_modulu = nove_pozicia_modulu;
    *typ_mer_veliciny = nove_typ_mer_veliciny;
    *hodnota = nove_hodnota;
    *cas_merania = nove_cas_merania;
    *datum_merania = nove_datum_merania;
    *pocet_zaznamov -= pocet_vymazanych;

    printf("Vymazalo sa: %d záznamov!\n", pocet_vymazanych);
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
            h(typ_mer_veliciny, hodnota, pocet_zaznamov);
        } else if (prikaz == 'z') {
            z(&id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania, &pocet_zaznamov);
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
