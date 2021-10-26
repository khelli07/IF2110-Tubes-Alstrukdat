#ifndef MAP_H
#define MAP_H

#include "../utilities/boolean.h"
#include "../utilities/pcolor.h"
#include "../point/location.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define MAP_CAP 100

typedef Location ElType;
typedef struct
{
    ElType contents[MAP_CAP][MAP_CAP];
    int rowEff;
    int colEff;
} Map;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..MAP_CAP-1][0..MAP_CAP-1] */

/* *** Selektor *** */
#define ROWS(M) (M).rowEff
#define COLS(M) (M).colEff
#define MAP(M, i, j) (M).contents[(i)][(j)] //akses elemen

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Map *** */
void CreateMap(Map *m, int row, int col);

/* ********** KELOMPOK BACA/TULIS ********** */
void setBangunan(Map *m, Location loc);
void displayMap(Map m);

#endif