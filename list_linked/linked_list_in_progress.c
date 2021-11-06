/* File : linked_list_in_progress.c */
/* Implementasi header linked list untuk command IN_PROGRESS */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list_in_progress.h"

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateInProgressList(List *l)
{
    // KAMUS LOKAL

    // ALGORITMA
    FIRST(*l) = NULL;

    /* I.S. sembarang             */
    /* F.S. Terbentuk list kosong */
}

/****************** TEST LIST KOSONG ******************/
boolean isInProgressEmpty(List l)
{
    // KAMUS LOKAL

    // ALGORITMA
    return FIRST(l) == NULL;

    /* Mengirim true jika list kosong */
}

/****************** GETTER SETTER ******************/
Pesanan getPesananInProgress(List l, int idx)
{
    // KAMUS LOKAL
    int ctr;
    Address p;

    // ALGORITMA
    ctr = 0;
    p = FIRST(l);
    while (ctr < idx)
    {
        ctr++;
        p = NEXT(p);
    }
    return INFO(p);

    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengembalikan nilai elemen l pada indeks idx */
}

void setPesananInProgress(List *l, int idx, Pesanan val)
{
    // KAMUS LOKAL
    int ctr;
    Address p;

    // ALGORITMA
    ctr = 0;
    p = FIRST(*l);
    while (ctr < idx)
    {
        ctr++;
        p = NEXT(p);
    }
    INFO(p) = val;

    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
}

int indexOfPesananInProgress(List l, Pesanan val)
{
    // KAMUS LOKAL
    int idx;
    Address p;
    boolean found;

    // ALGORITMA
    p = FIRST(l);
    found = false;
    idx = 0;
    while (p != NULL && !found)
    {
        if (isPesananEqual(INFO(p), val))
        {
            found = true;
        }
        else
        {
            idx++;
            p = NEXT(p);
        }
    }
    if (found)
    {
        return idx;
    }
    else
    {
        return -1;
    }

    /* I.S. l, val terdefinisi */
    /* F.S. Mencari apakah ada elemen list l yang bernilai val */
    /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
    /* Mengembalikan -1 jika tidak ditemukan */
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstInProgress(List *l, Pesanan val)
{
    // KAMUS LOKAL
    Address p;

    // ALGORITMA
    p = newNode(val);
    if (p != NULL)
    {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
    /* Jika alokasi gagal: I.S.= F.S. */
}

void insertLastInProgress(List *l, Pesanan val)
{
    // KAMUS LOKAL
    Address p, last;

    // ALGORITMA
    if (isInProgressEmpty(*l))
    {
        insertFirstInProgress(l, val);
    }
    else
    {
        p = newNode(val);
        if (p != NULL)
        {
            last = FIRST(*l);
            while (NEXT(last) != NULL)
            {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }

    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
}

void insertAtInProgress(List *l, Pesanan val, int idx)
{
    // KAMUS LOKAL
    int ctr;
    Address p, loc;

    // ALGORITMA
    if (idx == 0)
    {
        insertFirstInProgress(l, val);
    }
    else
    {
        p = newNode(val);
        if (p != NULL)
        {
            ctr = 0;
            loc = FIRST(*l);
            while (ctr < idx - 1)
            {
                ctr++;
                loc = NEXT(loc);
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
        }
    }

    /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
    /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstInProgress(List *l, Pesanan *val)
{
    // KAMUS LOKAL
    Address p;

    // ALGORITMA
    p = FIRST(*l);
    *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);

    /* I.S. List l tidak kosong  */
    /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
    /*      dan alamat elemen pertama di-dealokasi */
}

void deleteLastInProgress(List *l, Pesanan *val)
{
    // KAMUS LOKAL
    Address p, loc;

    // ALGORITMA
    p = FIRST(*l);
    loc = NULL;
    while (NEXT(p) != NULL)
    {
        loc = p;
        p = NEXT(p);
    }
    if (loc == NULL)
    {
        FIRST(*l) = NULL;
    }
    else
    {
        NEXT(loc) = NULL;
    }
    *val = INFO(p);
    free(p);

    /* I.S. list tidak kosong */
    /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
    /*      dan alamat elemen terakhir di-dealokasi */
}

void deleteAtInProgress(List *l, int idx, Pesanan *val)
{
    // KAMUS LOKAL
    int ctr;
    Address p, loc;

    // ALGORITMA
    if (idx == 0)
    {
        deleteFirstInProgress(l, val);
    }
    else
    {
        ctr = 0;
        loc = FIRST(*l);
        while (ctr < idx - 1)
        {
            ctr++;
            loc = NEXT(loc);
        }
        p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        free(p);
    }

    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayInProgressList(List l)
{
    // KAMUS LOKAL
    int ctr;
    Address p;

    // ALGORITMA
    if (isInProgressEmpty(l))
    {
        printf("Tidak ada pesanan yang sedang diantarkan!\n");
    }
    else
    {
        printf("Pesanan yang sedang diantarkan:\n");
        ctr = 1;
        p = FIRST(l);
        if (JenisItem(INFO(p)) == NORMAL)
        {
            printf("%d. Normal Item ", ctr);
        }
        else if (JenisItem(INFO(p)) == HEAVY)
        {
            printf("%d. Heavy Item ", ctr);
        }
        else if (JenisItem(INFO(p)) == PERISHABLE)
        {
            printf("%d. Perishable Item ", ctr);
        }
        else if (JenisItem(INFO(p)) == VIP)
        {
            printf("%d. VIP Item", ctr);
        }
        printf("(Tujuan: %c)\n", NAME(LokasiDropOff(INFO(p))));
        while (NEXT(p) != NULL)
        {
            p = NEXT(p);
            ctr++;
            if (JenisItem(INFO(p)) == NORMAL)
            {
                printf("%d. Normal Item ", ctr);
            }
            else if (JenisItem(INFO(p)) == HEAVY)
            {
                printf("%d. Heavy Item ", ctr);
            }
            else if (JenisItem(INFO(p)) == PERISHABLE)
            {
                printf("%d. Perishable Item ", ctr);
            }
            else if (JenisItem(INFO(p)) == VIP)
            {
                printf("%d. VIP Item", ctr);
            }
            printf("(Tujuan: %c)\n", NAME(LokasiDropOff(INFO(p))));
        }
    }

    /* I.S. List mungkin kosong */
    /* F.S. Jika list tidak kosong, list dicetak dengan format seperti: */
    /* Pesanan pada To Do List:
        1. G -> F (Normal Item)
        2. D -> H (Normal Item)
    */
    /* Jika list kosong dituliskan keterangan bahwa To Do List kosong */
}

int lengthInProgress(List l)
{
    // KAMUS LOKAL
    int ctr;
    Address p;

    // ALGORITMA
    ctr = 0;
    p = FIRST(l);
    while (p != NULL)
    {
        ctr++;
        p = NEXT(p);
    }
    return ctr;
}
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/****************** PROSES TERHADAP LIST ******************/
List concatInProgress(List l1, List l2)
{
    // KAMUS LOKAL
    Address p;
    List l3;

    // ALGORITMA
    CreateInProgressList(&l3);
    p = FIRST(l1);
    while (p != NULL)
    {
        insertLastInProgress(&l3, INFO(p));
        p = NEXT(p);
    }
    p = FIRST(l2);
    while (p != NULL)
    {
        insertLastInProgress(&l3, INFO(p));
        p = NEXT(p);
    }
    return l3;

    /* I.S. l1 dan l2 sembarang */
    /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
    /* Konkatenasi dua buah list : l1 dan l2    */
    /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
    /* Tidak ada alokasi/dealokasi pada prosedur ini */
}

void reduceTimeoutPerishInProgress(List* l, int amount){
    Address last;

    // ALGORITMA
    if (isInProgressEmpty(*l))
    {
        return;
    }
    else
    {
        last = FIRST(*l);
        while (last != NULL)
        {
            TimeoutPerish(INFO(last)) -= amount;
            last = NEXT(last);
        }
        
    }
}