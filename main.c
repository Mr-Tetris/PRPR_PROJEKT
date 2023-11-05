
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v(FILE **subor, char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania, int *pocet_zaznamov) {
    *subor = fopen("dataloger.txt", "r");
    if (subor == NULL) {
        printf("Subor sa nepodarilo otvorit\n");
        return;
    }

    rewind(*subor);
    char riadok[256];
    int zaznam_cislo = 0;

    if (*pocet_zaznamov == 0) {
        while (fgets(riadok, sizeof(riadok), *subor)) {
            switch (zaznam_cislo % 7) {
                case 0:
                    printf("ID. mer. modulu: %s", riadok);
                    break;
                case 1:
                    printf("Pozícia modulu: %s", riadok);
                    break;
                case 2:
                    printf("Typ mer. veliciny: %s", riadok);
                    break;
                case 3:
                    printf("Hodnota: %s", riadok);
                    break;
                case 4:
                    printf("Cas merania: %s", riadok);
                    break;
                case 5:
                    printf("Datum merania: %s", riadok);
                    printf("\n");
                    break;
            }
            zaznam_cislo++;
        }
    } else {
        for (int i = 0; i < *pocet_zaznamov; i++) {
            printf("ID. mer. modulu: %s\n", (*id_modulu)[i]);
            printf("Pozícia modulu: %s", (*pozicia_modulu)[i]);
            printf("Typ mer. veliciny: %s\n", (*typ_mer_veliciny)[i]);
            printf("Hodnota: %.2lf\n", (*hodnota)[i]);
            printf("Cas merania: %04d\n", (*cas_merania)[i]);
            printf("Datum merania: %08d\n", (*datum_merania)[i]);
            printf("\n");

        }
    }
}

void n(FILE *subor, char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania, int *pocet_zaznamov) {
    if (subor == NULL) {
        printf("Chyba pri otvarani suboru.\n");
        return;
    }
    rewind(subor);
    char riadok[256];

    *pocet_zaznamov = 0;


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
    int zaznam = 0;
    int aktualny_zaznam = 0;
    while (aktualny_zaznam < *pocet_zaznamov) {
        fgets(riadok, sizeof(riadok), subor);
        if (riadok[0] == '\n') {
            continue;
        }

        switch (zaznam % 6) {
            case 0:
                id_modulu_temp[aktualny_zaznam] = strdup(riadok);
                id_modulu_temp[aktualny_zaznam][strlen(id_modulu_temp[aktualny_zaznam]) - 1] = '\0';
                break;
            case 1:
                pozicia_modulu_temp[aktualny_zaznam] = strdup(riadok);
                break;
            case 2:
                typ_mer_veliciny_temp[aktualny_zaznam] = strdup(riadok);
                typ_mer_veliciny_temp[aktualny_zaznam][strlen(typ_mer_veliciny_temp[aktualny_zaznam]) - 1] = '\0';
                break;
            case 3:
                hodnota_temp[aktualny_zaznam] = atof(riadok);
                break;
            case 4:
                cas_merania_temp[aktualny_zaznam] = atoi(riadok);
                break;
            case 5:
                datum_merania_temp[aktualny_zaznam] = atoi(riadok);
                aktualny_zaznam++;
                break;
        }
        zaznam++;
    }
    *id_modulu = id_modulu_temp;
    *pozicia_modulu = pozicia_modulu_temp;
    *typ_mer_veliciny = typ_mer_veliciny_temp;
    *hodnota = hodnota_temp;
    *cas_merania = cas_merania_temp;
    *datum_merania = datum_merania_temp;
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

    int nekorektnyZaznam = 0;

    for (int i = 0; i < pocet_zaznamov; i++) {
        int nasielSa = 0;
        for (int j = 0; j <= Cpocet_zaznamov; j++) {
            int datum_ciachovania = datum_merania_temp[j];
            if (strcmp(id_modulu[i], id_moduluC_temp[j]) == 0) {
                nasielSa = 1;
                int rozdiel_mesiacov = (datum_merania[i] / 10000 - datum_ciachovania / 10000) * 12 +
                                       (datum_merania[i] / 100 % 100 - datum_ciachovania / 100 % 100);
                if (rozdiel_mesiacov >= Y) {
                    rozdiel_mesiacov = rozdiel_mesiacov - Y;
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

    for (int i = 0; i < Cpocet_zaznamov; i++) {
        free(id_moduluC_temp[i]);
    }
    free(id_moduluC_temp);
    free(datum_merania_temp);

}


void s(char **id_modulu, char **typ_mer_veliciny, double *hodnota, int *cas_merania, int *datum_merania, int pocet_zaznamov, char **pozicia_modulu) {
    int index[256];
    int pocitadloS = 0;
    printf("Zadaj ID. mer. modulu a typ meracej veliciny: ");
    char id_moduluS[256];
    char typ_mer_velicinyS[256];
    scanf("%s %s", id_moduluS, typ_mer_velicinyS);
    FILE *Ssubor = fopen("vystup_S.txt", "w");
    if (Ssubor == NULL) {
        printf("Nepodarilo sa otvorit subor pre zapis.\n");
        return;
    }
    for (int i = 0; i < pocet_zaznamov; i++) {
        if (strcmp(id_modulu[i], id_moduluS) == 0 && strcmp(typ_mer_veliciny[i], typ_mer_velicinyS) == 0) {
            index[pocitadloS] = i;
            pocitadloS++;
        }
    }
    long long int datumovePole[256];
    for (int i = 0; i < pocitadloS; i++) {
        long int datum = datum_merania[index[i]];
        long int cas = cas_merania[index[i]];

        long int rok = datum / 10000;    // Získajte rok z datumu
        long int mesiac_den = datum % 10000;
        long int mesiac = mesiac_den / 100;  // Získajte mesiac z datumu
        long int den = mesiac_den % 100;     // Získajte deň z datumu

        long int hodiny = cas / 100;    // Získajte hodiny z času
        long int minuty = cas % 100;    // Získajte minúty z času

        // Uložte dátum a čas vo formáte "RRRRMMDDHHMM"
        printf("%ld\n", (rok * 100000000 + mesiac * 1000000 + den * 10000 + hodiny * 100 + minuty));
        datumovePole[i] = rok * 100000000 + mesiac * 1000000 + den * 10000 + hodiny * 100 + minuty;
    }
    for (int i = 0; i < pocitadloS - 1; i++) {
        for (int j = 0; j < pocitadloS - i - 1; j++) {
            if (datumovePole[j] > datumovePole[j + 1]) {
                long long int tempDatum = datumovePole[j];
                int tempIndex = index[j];
                datumovePole[j] = datumovePole[j + 1];
                datumovePole[j + 1] = tempDatum;
                tempIndex = index[j];
                index[j] = index[j + 1];
                index[j + 1] = tempIndex;
            }
        }
    }
    for (int i = 0; i < pocitadloS; i++) {
        int current_index = index[i];

        // Rozdelenie reťazca pozicia_modulu[index] na prvú a druhú časť
        char *pozicia = pozicia_modulu[current_index];
        char *prva_cast = strtok(pozicia, "+");
        char *druha_cast = strtok(NULL, "+");

        // Konverzia reťazcov na čísla
        double prva_hodnota = atof(prva_cast);
        double druha_hodnota = atof(druha_cast);

        // Formátovanie a výpis do súboru
        fprintf(Ssubor, "%lld     %.5f     +%.4f     +%.4f\n",
                datumovePole[i], hodnota[current_index], (prva_hodnota / 10000), (druha_hodnota / 10000));
    }
    fclose(Ssubor);
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

        printf("%-15s %-10d %-10.2lf %-10.2lf\n", typ, pocetnost, minimum, maximum);
    }
}

void z(int *pocet_zaznamov, char ***id_modulu, char ***pozicia_modulu, char ***typ_mer_veliciny, double **hodnota, int **cas_merania, int **datum_merania) {
    printf("Zadajte ID. mer. modulu: ");
    char id_moduluZ[256];
    scanf("%s", id_moduluZ);
    int docasnyPocet = *pocet_zaznamov;
    int poleIndexov[docasnyPocet];
    int pocetIndexov = 0;
    for (int i = 0; i < docasnyPocet; i++){
        if (strcmp(id_moduluZ, (*id_modulu)[i]) != 0){
            poleIndexov[pocetIndexov]= i;
            pocetIndexov++;
        }

    }
    char **id_modulu_temp = (char **)malloc(pocetIndexov * sizeof(char *));
    char **pozicia_modulu_temp = (char **)malloc(pocetIndexov * sizeof(char *));
    char **typ_mer_veliciny_temp = (char **)malloc(pocetIndexov * sizeof(char *));
    double *hodnota_temp = (double *)malloc(pocetIndexov * sizeof(double));
    int *cas_merania_temp = (int *)malloc(pocetIndexov * sizeof(int));
    int *datum_merania_temp = (int *)malloc(pocetIndexov * sizeof(int));
    int pocitadloIndexov = 0;
    for (int i = 0; i < *pocet_zaznamov; i++) {
        if (poleIndexov[pocitadloIndexov] == i){
            id_modulu_temp[pocitadloIndexov] = strdup((*id_modulu)[i]);
            pozicia_modulu_temp[pocitadloIndexov] = strdup((*pozicia_modulu)[i]);
            typ_mer_veliciny_temp[pocitadloIndexov] = strdup((*typ_mer_veliciny)[i]);
            hodnota_temp[pocitadloIndexov] = (*hodnota)[i];
            cas_merania_temp[pocitadloIndexov] = (*cas_merania)[i];
            datum_merania_temp[pocitadloIndexov] = (*datum_merania)[i];
            pocitadloIndexov++;
        }
        free((*id_modulu)[i]);
        free((*pozicia_modulu)[i]);
        free((*typ_mer_veliciny)[i]);
    }
    free(*id_modulu);
    free(*pozicia_modulu);
    free(*typ_mer_veliciny);
    free(*hodnota);
    free(*cas_merania);
    free(*datum_merania);
    *id_modulu = id_modulu_temp;
    *pozicia_modulu = pozicia_modulu_temp;
    *typ_mer_veliciny = typ_mer_veliciny_temp;
    *hodnota = hodnota_temp;
    *cas_merania = cas_merania_temp;
    *datum_merania = datum_merania_temp;
    printf("Počet zmazaných záznamov: %d\n", *pocet_zaznamov-pocetIndexov);
    *pocet_zaznamov = pocetIndexov;


}



void k(FILE **subor, char **id_modulu, char **pozicia_modulu, char **typ_mer_veliciny, double *hodnota, int *cas_merania, int *datum_merania, int pocet_zaznamov) {
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
    fclose(*subor);
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
    FILE *subor;
    while (1) {
        printf("Zadaj prikaz: ");
        scanf(" %c", &prikaz);

        if (prikaz == 'v') {
            v(&subor, &id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania, &pocet_zaznamov);
        } else if (prikaz == 'n') {
            n(subor, &id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania, &pocet_zaznamov);
        } else if (prikaz == 'c') {
            c(id_modulu, datum_merania, pocet_zaznamov);
        } else if (prikaz == 's') {
            s(id_modulu, typ_mer_veliciny, hodnota, cas_merania, datum_merania, pocet_zaznamov, pozicia_modulu);
        } else if (prikaz == 'h') {
            h(typ_mer_veliciny, hodnota, pocet_zaznamov);
        } else if (prikaz == 'z') {
            z(&pocet_zaznamov, &id_modulu, &pozicia_modulu, &typ_mer_veliciny, &hodnota, &cas_merania, &datum_merania);
        } else if (prikaz == 'k') {
            k(&subor, id_modulu, pozicia_modulu, typ_mer_veliciny, hodnota, cas_merania, datum_merania, pocet_zaznamov);
        } else {
            printf("Neplatný príkaz\n");
            break;
        }
    }
    return 0;
}
