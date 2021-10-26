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
/* I.S. m sembarang */
/* F.S. terbentuk map: matriks dengan row x col */

/* ********** SETTER ********** */
void setBuilding(Map *m, Location loc);
/* I.S. m terdefinisi */
/* F.S. lokasi pada titik ke x, y akan diletakkan pada matriks
        ke-x, y pada map. Jika sudah ada bangunan, akan dioverwrite */

/* ********** KELOMPOK BACA/TULIS ********** */
void displayMap(Map m);
/* I.S. m terdefinisi */
/* F.S. menampilkan map */

#endif