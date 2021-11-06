/* File : stack.h */
/* Definisi ADT Stack dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef STACK_H
#define STACK_H

#include "../utilities/boolean.h"
#include "../pesanan/pesanan.h"

#define IDX_UNDEF -1
#define CAPACITY_TAS 100

typedef struct {
  Pesanan buffer[CAPACITY_TAS]; /* tabel penyimpan elemen */
  int idxTop;              /* alamat TOP: elemen puncak */
} Stack;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Stack, maka akses elemen : */
#define IDX_TOP(s) (s).idxTop
#define     TOP(s) (s).buffer[(s).idxTop]

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isEmpty(Stack s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isFull(Stack s);
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, Pesanan val);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, Pesanan *val);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

int sizeStack(Stack s);
/* Mengirim ukuran Stack s saat ini */

/* Menghitung rincian bawaan yang dibawa
 * I.S.: result sembarang, tas terdefinisi
 * F.S.: result berisi rincian jumlah barang dari tiap JenisItem */
void countStackByJenisItem(Stack tas, int result[JENISITEMCOUNT]);

#endif