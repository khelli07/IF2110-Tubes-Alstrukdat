#ifndef ADJMAT_H
#define ADJMAT_H

#include "../utilities/boolean.h"
#include "../mesin/locmachine.h"

#define ADJ_CAP 100

typedef struct
{
    int contents[ADJ_CAP][ADJ_CAP];
    int adjSize;
} AdjMatrix;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Selektor *** */
#define SIZE(M) (M).adjSize
#define ADJ(M, i, j) (M).contents[(i)][(j)]

/* *** Konstruktor membentuk AdjMatrix *** */
void CreateAdjMatrix(AdjMatrix *m, int N);

/* ********** KELOMPOK BACA/TULIS ********** */
void readAdjMatrix(AdjMatrix *m, int N);
/* Proses: Melakukan CreateAdjMatrix(m, N) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika N = 3, maka contoh cara membaca isi matriks :
0 1 1
1 0 0
1 0 0 
*/

void displayAdjMatrix(AdjMatrix m);
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */

#endif