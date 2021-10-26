#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "../utilities/boolean.h"
#include "../point/location.h"

/* Definisi elemen dan koleksi objek */
typedef Location ElType; /* type elemen list */
typedef int IdxType;
typedef struct
{
    ElType *buffer; /* memori tempat penyimpan elemen (container) */
    int nEff;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ukuran elemen */
} DynamicList;

/* ********** SELEKTOR ********** */
#define NEFF(l) (l).nEff
#define BUFFER(l) (l).buffer
#define LOC(l, i) (l).buffer[i] // akses elemen
#define CAPACITY(l) (l).capacity

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateDynamicList(DynamicList *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void dealocate(DynamicList *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* OUTPUT LIST LOCATION */
void displayLocList(DynamicList l);

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLoc(DynamicList *l, ElType val);
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. loc adalah elemen terakhir l yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLoc(DynamicList *l, ElType *val);
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. loc adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */

/* FUNGSI TAMBAHAN */
int countBangunan(DynamicList l);
/* Mengembalikan jumlah banyaknya bangunan yang terdefinisi */
boolean isEmpty(DynamicList l);
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
boolean isFull(DynamicList l);
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

#endif
