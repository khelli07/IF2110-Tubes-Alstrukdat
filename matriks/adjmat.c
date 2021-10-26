/* IMPORTS */
#include <stdio.h>
#include "adjmat.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk AdjMatrix *** */
void CreateAdjMatrix(AdjMatrix *m, int N)
{
    SIZE(*m) = N;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readAdjMatrix(AdjMatrix *m, int N)
{
    /* KAMUS LOKAL */
    int val;

    /* ALGORITMA */
    CreateAdjMatrix(m, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &val);
            ADJ(*m, i, j) = val;
        }
    }
}

void displayAdjMatrix(AdjMatrix m)
{
    for (int i = 0; i < SIZE(m); i++)
    {
        for (int j = 0; j < SIZE(m); j++)
        {
            printf((j == SIZE(m) - 1) ? "%d" : "%d ", ADJ(m, i, j));
        }
        printf((i == SIZE(m) - 1) ? "" : "\n");
    }
}

/* FUNGSI TAMBAHAN */
boolean isSymmetric(AdjMatrix m)
{
    boolean flag = true;
    // DIJAMIN SQUARE
    for (int i = 0; i < SIZE(m); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (ADJ(m, i, j) != ADJ(m, j, i))
            {
                flag = false;
            }
        }
    }

    return flag;
}

void transpose(AdjMatrix *m)
{
    AdjMatrix mt;
    // DIJAMIN SQUARE
    CreateAdjMatrix(&mt, SIZE(*m));
    for (int i = 0; i < SIZE(*m); i++)
    {
        for (int j = 0; j < SIZE(*m); j++)
        {
            ADJ(mt, i, j) = ADJ(*m, j, i);
        }
    }

    *m = mt;
}
