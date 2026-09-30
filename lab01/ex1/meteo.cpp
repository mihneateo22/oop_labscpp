#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= Structuri de date ================= 

// Structura de date care retine informatiile citite de la senzor
struct Reading {
    char date[11]; // data calendaristica, in format yyyy-mm-dd
    double tmax;   // temperatura maxima inregistrata in acea zi
    double tmin;   // temperatura minima inregistrata in acea zi
    double rain;   // cantitatea de precipitatii din  acea zi
};

// Structura de date care retine toate masuratorile de la o statie meteo
struct Station {
    char city[8];       // numele statiei
    Reading *readings;  // tablou cu masuratorile inregistrate la statie
    int count;          // numarul curent de masuratori din tablou
    int capacity;       // capacitatea totala (spatiu alocat) a tabloului
};

// ============ Crearea, copierea si distrugerea unei statii ============

Station createStation(char *city, int capacity) {
    Station s;
    s.readings = (Reading *)malloc(capacity * sizeof(Reading));
    s.count = 0;
    s.capacity = capacity;
    strcpy(s.city, city);
    return s;
}

Station copyStation(Station *other) {
    Station copy = createStation(other->city, other->capacity);
    int i;
    for (i = 0; i < other->count; i++) copy.readings[i] = other->readings[i];
    copy.count = other->count;
    return copy;
}

void destroyStation(Station *station) {
    free(station->readings);
}

void addReading(Station *station, Reading reading) {
    station->readings[station->count] = reading;
    station->count++;
}

char *describe(Reading *r) {
    char text[64];
    sprintf(text, "%s: %.1f / %.1f C, %.1f mm", r->date, r->tmax, r->tmin, r->rain);
    return text;
}

// ================= Citirea din fisierul de intrare ================= 
// In fisierul de intrare inregistrările meteo sunt separate 
// de o linie (antet) de forma "statie nume_statie, numar_inregistrari"

// Returneaza 0 la sfarsitul fisierului, 1 altfel 
int readHeader(FILE *file, char *name, int *count) {
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) return 0;
    sscanf(line, "statie %63[^,], %d", name, count);
    return 1;
}

// Citeste urmatoarele count randuri si adauga in statie masuratorile valide
void readReadings(FILE *file, Station *station, int count) {
    char line[256];
    Reading r;
    int i;
    for (i = 0; i < count; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        sscanf(line, "%10s %lf %lf %lf", r.date, &r.tmax, &r.tmin, &r.rain);
        addReading(station, r);
    }
}

// ================= Calcule =================

int hottestDay(Station *s) {
    double best = 0;
    int bestIndex = -1;
    int i;
    for (i = 0; i < s->count; i++) {
        if (s->readings[i].tmax > best) {
            best = s->readings[i].tmax;
            bestIndex = i;
        }
    }
    return bestIndex;
}

double totalRain(Station *s) {
    int total = 0;
    int i;
    for (i = 0; i < s->count; i++) total += s->readings[i].rain;
    return total;
}

Reading *findByDate(Station *s, char *date) {
    int i;
    for (i = 0; i < s->count; i++)
        if (s->readings[i].date == date) return &s->readings[i];
    return NULL;
}

void sortByMax(Station *s) {
    int i, j, best;
    Reading aux;
    for (i = 0; i < s->count - 1; i++) {
        best = i;
        for (j = i + 1; j < s->count; j++)
            if (s->readings[j].tmax > s->readings[best].tmax) best = j;
        aux = s->readings[i];
        s->readings[i] = s->readings[best];
        s->readings[best] = aux;
    }
}

// ================= Scrierea fisierului de output =================
// NU modificati aceste functii!!! 
// Sigur nu contin erori. 
// Doar scriu rezultatele in formatul asteptat al fisierului de output

// Scrie in fisierul de output statisticile despre fiecare statie
void writeStationReport(FILE *out, Station *station, Station *sorted, int invalid) {
    int i, hot;
    fprintf(out, "statie=%s\n", station->city);
    fprintf(out, "zile=%d\n", station->count);
    fprintf(out, "zile invalide=%d\n", invalid);
    fprintf(out, "date=");
    for (i = 0; i < station->count; i++)
        fprintf(out, "%s%s", i > 0 ? "," : "", station->readings[i].date);
    fprintf(out, "\n");
    hot = hottestDay(station);
    fprintf(out, "cea_mai_calda=%s max=%.1f\n", station->readings[hot].date, station->readings[hot].tmax);
    fprintf(out, "ploaie=%.1f\n", totalRain(station));
    fprintf(out, "top3=");
    for (i = 0; i < sorted->count && i < 3; i++)
        fprintf(out, "%s%s", i > 0 ? "," : "", sorted->readings[i].date);
    fprintf(out, "\n");
}

// Scrie informatii despre ziua cautata
void writeSearchReport(FILE *out, char *date, Reading *day) {
    if (day == NULL) {
        fprintf(out, "cautare %s negasit\n\n", date);
        return;
    }
    fprintf(out, "cautare %s max=%.1f\n", date, day->tmax);
    fprintf(out, "descriere %s\n\n", describe(day));
}

// Raporteaza statiile care nu contin date valide
void writeEmptyReport(FILE *out, Station *station, int invalid) {
    fprintf(out, "statie=%s\n", station->city);
    fprintf(out, "fara date\n");
    fprintf(out, "zile invalide=%d\n\n", invalid);
}

// ================= sfarsitul sectiunii ce nu trebuie modificata ================= 

int main(void) {
    char searchedDate[] = "2026-10-02";
    char name[64];
    int count;
    Station station, sorted;
    FILE *in = fopen("01.in", "r");
    FILE *out = fopen("01.out", "w");

    while (!feof(in)) {
        readHeader(in, name, &count);
        station = createStation(name, count);
        readReadings(in, &station, count);

        if (station.count == 0) {
            writeEmptyReport(out, &station, count);
            continue;
        }

        // creeaza o copie a statie pentru a sorta datele statiei
        sorted = station;  
        sortByMax(&sorted);
        writeStationReport(out, &station, &sorted, count - station.count);
        writeSearchReport(out, searchedDate, findByDate(&station, searchedDate));

        destroyStation(&sorted);
        destroyStation(&station);
    }

    fclose(in);
    fclose(out);
    return 0;
}