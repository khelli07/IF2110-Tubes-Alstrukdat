#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "../utilities/boolean.h"
#include "../point/location.h"
#include "../matriks/adjmat.h"

/* Definisi elemen dan koleksi objek */
typedef int IdxType;
typedef struct
{
    Location *buffer; /* memori tempat penyimpan elemen (container) */
    int nEff;         /* >=0, banyaknya elemen efektif */
    int capacity;     /* ukuran elemen */
} DynamicList;

/* ********** SELEKTOR ********** */
#define NEFF(l) (l).nEff
#define BUFFER(l) (l).buffer
#define LOC(l, i) (l).buffer[i] // akses elemen
#define LIST_CAP(l) (l).capacity

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateDynamicList(DynamicList *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity + 2, 1 untuk HQ, 1 untuk menghindari bug */

void dealocate(DynamicList *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* OUTPUT LIST LOCATION */
void displayLocList(DynamicList l);
/* I.S. l terdefinisi */
/* F.S. menampilkan lokasi yang ada di dalam list, misal
1. A (1, 2)
2. B (7, 5), dst */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLoc(DynamicList *l, Location loc);
/* Menambahkan loc sebagai elemen terakhir list */

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLoc(DynamicList *l, Location *loc);
/* Menghapus elemen terakhir list */

/* ********** GETTER ********** */
int getLocIndex(DynamicList l, Location loc);
/* Mengembalikan indeks loc di list l */
Location getLoc(DynamicList l, char cc);
/* Mengembalikan lokasi bernama cc, cc dijamin ada dalam list */
DynamicList getAccLoc(AdjMatrix m, DynamicList l, Location lstart);
/* Mengembalikan lokasi yang aksesibel dari lstart*/
void displayAccLoc(AdjMatrix m, DynamicList l, Location lstart);
/* I.S. m dan l terdefinisi */
/* F.S. Output lokasi yang aksesibel dari lstart */
boolean isAccLoc(AdjMatrix m, DynamicList l, Location lstart, Location ldest);
/* Mengembalikan nilai benar jika ldest bisa diakses dari lstart */

/* ********** FUNGSI TAMBAHAN *********** */
int countBuilding(DynamicList l);
/* Mengembalikan jumlah banyaknya bangunan yang terdefinisi */

#endif
