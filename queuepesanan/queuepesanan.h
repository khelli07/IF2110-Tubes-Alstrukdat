/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi statik */

#ifndef QUEUEPESANAN_H
#define QUEUEPESANAN_H

#include "queuepesanan.h"
#include "pesanan.h"

#define IDX_UNDEF -1
#define QUEUE_CAPACITY 100

/* Definisi elemen dan address */
typedef struct {
	Pesanan buffer[QUEUE_CAPACITY]; 
	int idxHead;
	int idxTail;
} Queue;


/* ********* AKSES (Selektor) ********* */
/* Jika q adalah Queue, maka akses elemen : */
#define IDX_HEADQUEUE(q) (q).idxHead
#define IDX_TAILQUEUE(q) (q).idxTail
#define     HEADQUEUE(q) (q).buffer[(q).idxHead]
#define     TAILQUEUE(q) (q).buffer[(q).idxTail]

/* *** Kreator *** */
void CreateQueue(Queue *q);
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */

/* ********* Prototype ********* */
boolean isQueueEmpty(Queue q);
/* Mengirim true jika q kosong: lihat definisi di atas */
boolean isQueueFull(Queue q);
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUE_CAPACITY-1 */
int lengthQueue(Queue q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, Pesanan val);
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAILQUEUE yang baru, IDX_TAILQUEUE "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAILQUEUE baru  */

void dequeue(Queue *q, Pesanan *val);
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEADQUEUE pd I.S., HEADQUEUE dan IDX_HEADQUEUE "mundur"; 
        q mungkin kosong */

/* *** Display Queue *** */
void displayQueue(Queue q);
/* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */


#endif
