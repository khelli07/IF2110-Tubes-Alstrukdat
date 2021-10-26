#include "dynamiclist.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
void CreateDynamicList(DynamicList *l, int capacity)
{
    BUFFER(*l) = (ElType *)malloc(capacity * sizeof(ElType));
    if (BUFFER(*l) != NULL)
    {
        NEFF(*l) = 0;
        CAPACITY(*l) = capacity;
    }
}

/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
void dealocate(DynamicList *l)
{
    if (BUFFER(*l) != NULL)
    {
        ElType *p = BUFFER(*l);
        CAPACITY(*l) = 0;
        NEFF(*l) = 0;
        free(p);
    }
}

/* OUTPUT LIST LOCATION */
void displayLocList(DynamicList l)
{
    for (int i = 0; i < NEFF(l); i++)
    {
        if (i != NEFF(l) - 1)
        {
            printf("%d. ", i + 1);
            displayLoc(LOC(l, i));
            printf("\n");
        }
        else
        {
            printf("%d. ", i + 1);
            displayLoc(LOC(l, i));
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
/* Proses: Menambahkan location sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
void insertLoc(DynamicList *l, ElType loc)
{
    LOC(*l, NEFF(*l)) = loc;
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
void deleteLoc(DynamicList *l, ElType *val)
{
    *val = LOC(*l, NEFF(*l) - 1);
    NEFF(*l) -= 1;
}

/* FUNGSI TAMBAHAN */
/* Mengembalikan jumlah banyaknya bangunan yang terdefinisi */
int countBangunan(DynamicList l)
{
    return NEFF(l);
}

/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
boolean isEmpty(DynamicList l)
{
    return (NEFF(l) == 0);
}

/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
boolean isFull(DynamicList l)
{
    return (NEFF(l) == CAPACITY(l));
}