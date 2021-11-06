/* File : stack.c */
/* Implementasi header stack */
#include "stack.h"

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s)
{
    IDX_TOP(*s) = -1;

    /* I.S. sembarang; */
    /* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
    /* - Index top bernilai -1 */
    /* Proses : Melakukan alokasi, membuat sebuah s kosong */
}

/* ************ Prototype ************ */
boolean isEmpty(Stack s)
{
    return IDX_TOP(s) == -1;

    /* Mengirim true jika s kosong: lihat definisi di atas */
}

boolean isFull(Stack s)
{
    return IDX_TOP(s) == CAPACITY_TAS - 1;

    /* Mengirim true jika tabel penampung nilai s stack penuh */
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, Pesanan val)
{
    IDX_TOP(*s)
    ++;
    TOP(*s) = val;

    /* Menambahkan val sebagai elemen Stack s */
    /* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
    /* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */
}

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, Pesanan *val)
{
    *val = TOP(*s);
    IDX_TOP(*s)
    --;

    /* Menghapus val dari Stack s */
    /* I.S. s tidak mungkin kosong */
    /* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */
}

int sizeStack(Stack s)
{
    return IDX_TOP(s) + 1;

    /* Mengirim ukuran Stack s saat ini */
}

void countStackByJenisItem(Stack tas, int result[JENISITEMCOUNT])
{
    for (int i = 0; i < JENISITEMCOUNT; i++)
        result[i] = 0;
    while (!isEmpty(tas))
    {
        Pesanan val;
        pop(&tas, &val);
        result[JenisItem(val)] += 1;
    }
}