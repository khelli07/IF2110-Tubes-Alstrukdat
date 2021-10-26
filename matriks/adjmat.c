/* IMPORTS */
#include <stdio.h>
#include "adjmat.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
void CreateMatrix(int nRow, int nCol, Matrix *m)
{
    ROWS(*m) = nRow;
    COLS(*m) = nCol;
}

/* *** Selektor "DUNIA Matrix" *** */
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
boolean isIdxValid(int i, int j)
{
    return (((i >= 0) && (i < ROW_CAP)) && ((j >= 0) && (j < COL_CAP)));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
/* Mengirimkan Index baris terbesar m */
Index getLastIdxRow(Matrix m)
{
    return (ROWS(m) - 1);
}

/* Mengirimkan Index kolom terbesar m */
Index getLastIdxCol(Matrix m)
{
    return (COLS(m) - 1);
}

/* Mengirimkan true jika i, j adalah Index efektif bagi m */
boolean isIdxEff(Matrix m, Index i, Index j)
{
    return (((i >= 0) && (i < ROWS(m))) && ((j >= 0) & (j < COLS(m))));
}

/* Mengirimkan elemen m(i,i) */
ElType getElmtDiagonal(Matrix m, Index i)
{
    return ELMT(m, i, i);
}

/* ********** Assignment  Matrix ********** */
/* Melakukan assignment MRes = MIn */
void copyMatrix(Matrix mIn, Matrix *mRes)
{
    CreateMatrix(ROWS(mIn), COLS(mIn), mRes);
    for (int i = 0; i < ROWS(mIn); i++)
    {
        for (int j = 0; j < COLS(mIn); j++)
        {
            ELMT(*mRes, i, j) = ELMT(mIn, i, j);
        }
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void readMatrix(Matrix *m, int nRow, int nCol)
{
    /* KAMUS LOKAL */
    int val;

    /* ALGORITMA */
    CreateMatrix(nRow, nCol, m);
    for (int i = 0; i < nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            scanf("%d", &val);
            ELMT(*m, i, j) = val;
        }
    }
}

/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
void displayMatrix(Matrix m)
{
    for (int i = 0; i < ROWS(m); i++)
    {
        for (int j = 0; j < COLS(m); j++)
        {
            printf((j == COLS(m) - 1) ? "%d" : "%d ", ELMT(m, i, j));
        }
        printf((i == ROWS(m) - 1) ? "" : "\n");
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrix addMatrix(Matrix m1, Matrix m2)
{
    /* KAMUS LOKAL */
    Matrix m3;

    /* ALGORITMA */
    CreateMatrix(ROWS(m1), COLS(m1), &m3);
    for (int i = 0; i < ROWS(m1); i++)
    {
        for (int j = 0; j < COLS(m1); j++)
        {
            ELMT(m3, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
    }

    return m3;
}

/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
Matrix subtractMatrix(Matrix m1, Matrix m2)
{
    /* KAMUS LOKAL */
    Matrix m3;

    /* ALGORITMA */
    CreateMatrix(ROWS(m1), COLS(m1), &m3);
    for (int i = 0; i < ROWS(m1); i++)
    {
        for (int j = 0; j < COLS(m1); j++)
        {
            ELMT(m3, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
    }

    return m3;
}

/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
Matrix multiplyMatrix(Matrix m1, Matrix m2)
{
    /* KAMUS LOKAL */
    Matrix m3;

    /* ALGORITMA */
    CreateMatrix(ROWS(m1), COLS(m2), &m3);
    for (int i = 0; i < ROWS(m3); i++)
    {
        for (int j = 0; j < COLS(m3); j++)
        {
            ELMT(m3, i, j) = 0;
            for (int k = 0; k < COLS(m1); k++)
            {
                ELMT(m3, i, j) += ELMT(m1, i, k) * ELMT(m2, k, j);
            }
        }
    }

    return m3;
}

/* Mengirim hasil perkalian setiap elemen m dengan x */
Matrix multiplyConst(Matrix m, ElType x)
{
    /* KAMUS LOKAL */
    Matrix m3;

    /* ALGORITMA */
    CreateMatrix(ROWS(m), COLS(m), &m3);
    for (int i = 0; i < ROWS(m); i++)
    {
        for (int j = 0; j < COLS(m); j++)
        {
            ELMT(m3, i, j) = ELMT(m, i, j) * x;
        }
    }

    return m3;
}

/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
void pMultiplyConst(Matrix *m, ElType k)
{
    for (int i = 0; i < ROWS(*m); i++)
    {
        for (int j = 0; j < COLS(*m); j++)
        {
            ELMT(*m, i, j) = ELMT(*m, i, j) * k;
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isEqual(Matrix m1, Matrix m2)
{
    /* KAMUS LOKAL */
    boolean flag = true;

    /* ALGORITMA */
    if (isSizeEqual(m1, m2))
    {
        for (int i = 0; i < ROWS(m1); i++)
        {
            for (int j = 0; j < COLS(m1); j++)
            {
                if (ELMT(m1, i, j) != ELMT(m2, i, j))
                {
                    flag = false;
                }
            }
        }
    }
    else
    {
        flag = false;
    }

    return flag;
}

/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isNotEqual(Matrix m1, Matrix m2)
{
    return (!isEqual(m1, m2));
}

/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
boolean isSizeEqual(Matrix m1, Matrix m2)
{
    return ((ROWS(m1) == ROWS(m2)) && (COLS(m1) == COLS(m2)));
}

/* ********** Operasi lain ********** */
/* Mengirimkan banyaknya elemen m */
int count(Matrix m)
{
    return (ROWS(m) * COLS(m));
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSquare(Matrix m)
{
    return (ROWS(m) == COLS(m));
}

/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
boolean isSymmetric(Matrix m)
{
    /* KAMUS LOKAL */
    boolean flag = true;

    /* ALGORITMA */
    if (isSquare(m))
    {
        for (int i = 0; i < ROWS(m); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (ELMT(m, i, j) != ELMT(m, j, i))
                {
                    flag = false;
                }
            }
        }
    }
    else
    {
        flag = false;
    }

    return flag;
}

/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
boolean isIdentity(Matrix m)
{
    /* KAMUS LOKAL */
    boolean flag = true;

    /* ALGORITMA */
    if (isSquare(m))
    {
        for (int i = 0; i < ROWS(m); i++)
        {
            for (int j = 0; j < COLS(m); j++)
            {
                if ((i == j) && (ELMT(m, i, j) != 1))
                {
                    flag = false;
                }
                else if ((i != j) && ELMT(m, i, j) != 0)
                {
                    flag = false;
                }
            }
        }
    }
    else
    {
        flag = false;
    }

    return flag;
}

/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
boolean isSparse(Matrix m)
{
    /* KAMUS LOKAL */
    int ctr = 0;
    float percentage;

    /* ALGORITMA */
    for (int i = 0; i < ROWS(m); i++)
    {
        for (int j = 0; j < COLS(m); j++)
        {
            if (ELMT(m, i, j) != 0)
            {
                ctr += 1;
            }
        }
    }
    percentage = (float)ctr / count(m);

    return (percentage <= 0.05);
}

/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
Matrix inverse1(Matrix m)
{
    return multiplyConst(m, -1);
}

/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void pInverse1(Matrix *m)
{
    pMultiplyConst(m, -1);
}

/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
float determinant(Matrix m)
{
    /* KAMUS LOKAL */
    int length = ROWS(m);
    float mtemp[ROW_CAP][COL_CAP];
    float det = 1;

    /* ALGORITMA */
    //COPY ARRAY TO FLOAT
    for (int i = 0; i < length; i++)
    {

        for (int j = 0; j < length; j++)
        {
            mtemp[i][j] = ELMT(m, i, j);
        }
    }

    // MENGGUNAKAN METODE SEGITIGA BAWAH
    for (int k = 1; k < length; k++)
    {
        for (int i = k; i < length; i++)
        {
            float p = mtemp[i][k - 1];
            float q = mtemp[k - 1][k - 1];

            // supaya tidak ada div by 0
            if (q != 0)
            {
                for (int j = 0; j < length; j++)
                {
                    mtemp[i][j] = mtemp[i][j] - (p / q) * mtemp[k - 1][j];
                }
            }
        }
    }

    // HITUNG DETERMINAN
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (i == j)
            {
                det *= mtemp[i][j];
            }
        }
    }

    if (det == 0)
        det = 0;

    return det;
}

/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void transpose(Matrix *m)
{
    /* KAMUS LOKAL */
    Matrix mt;

    /* ALGORITMA */
    if (isSquare(*m))
    {
        CreateMatrix(ROWS(*m), COLS(*m), &mt);
        for (int i = 0; i < ROWS(*m); i++)
        {
            for (int j = 0; j < COLS(*m); j++)
            {
                ELMT(mt, i, j) = ELMT(*m, j, i);
            }
        }

        *m = mt;
    }
}
