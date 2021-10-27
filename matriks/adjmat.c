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
    /* ALGORITMA */
    CreateAdjMatrix(m, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ADJ(*m, i, j) = readInt();
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