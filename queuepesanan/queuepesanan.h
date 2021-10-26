/* Definisi ADT QueuePesanan dengan representasi array secara eksplisit dan alokasi statik */

#ifndef QUEUEPESANAN_H
#define QUEUEPESANAN_H

#include "queuepesanan.h"
#include "../pesanan/pesanan.h"

#define IDX_UNDEF -1
#define QUEUE_CAPACITY 100

/* Definisi elemen dan address */
typedef struct {
	Pesanan buffer[QUEUE_CAPACITY]; 
	int idxHead;
	int idxTail;
} QueuePesanan;


/* ********* AKSES (Selektor) ********* */
/* Jika q adalah QueuePesanan, maka akses elemen : */
#define IDX_HEADQUEUE(q) (q).idxHead
#define IDX_TAILQUEUE(q) (q).idxTail
#define     HEADQUEUE(q) (q).buffer[(q).idxHead]
#define     TAILQUEUE(q) (q).buffer[(q).idxTail]

/* *** Kreator *** */
void CreateQueue(QueuePesanan *q);
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */

/* ********* Prototype ********* */
boolean isQueueEmpty(QueuePesanan q);
/* Mengirim true jika q kosong: lihat definisi di atas */
boolean isQueueFull(QueuePesanan q);
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUE_CAPACITY-1 */
int lengthQueue(QueuePesanan q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */

/* *** Primitif Add/Delete *** */
void enqueue(QueuePesanan *q, Pesanan val);
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAILQUEUE yang baru, IDX_TAILQUEUE "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAILQUEUE baru  */

void dequeue(QueuePesanan *q, Pesanan *val);
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEADQUEUE pd I.S., HEADQUEUE dan IDX_HEADQUEUE "mundur"; 
        q mungkin kosong */

// Menampilkan QueuePesanan Pesanan, memanggil displayPesanan() dalam implementasinya
void displayQueue(QueuePesanan q);


// Mengurutkan QueuePesanan Pesanan, dengan waktuIn terendah berada pada urutan prioritas
void sortQueue(QueuePesanan* q);

#endif
