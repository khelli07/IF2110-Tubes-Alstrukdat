/* IMPORTS */
#include <stdio.h>
#include "map.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Map *** */
void CreateMap(Map *m, int row, int col)
{
    ROWS(*m) = row;
    COLS(*m) = col;

    Location locBound;
    Location locEmpty;
    CreateLocation(&locBound, 0, 0, '*');
    CreateLocation(&locEmpty, 0, 0, ' ');

    int rowBound = row + 2;
    int colBound = col + 2;

    for (int i = 0; i < rowBound; i++)
    {
        for (int j = 0; j < colBound; j++)
        {
            if (i == 0 || i == rowBound - 1)
            {
                MAP(*m, i, j) = locBound;
            }
            else if (j == 0 || j == colBound - 1)
            {
                MAP(*m, i, j) = locBound;
            }
            else
            {
                MAP(*m, i, j) = locEmpty;
            }
        }
    }
}

/* ********** SETTER ********** */
void setBuilding(Map *m, Location loc)
{
    int row = loc.point.x;
    int col = loc.point.y;
    MAP(*m, row, col) = loc;
}

void setLocationColor(Map *m, DynamicList *locList, Location loc, Color cc)
{
    int i = getLocIndex(*locList, loc);
    printf("Ketemu: %d\n", i);
    // Ubah yang ada di daftar list bangunan
    LOC(*locList, i).color = cc;
    // Ubah yang ada di map
    Point p = POINT(LOC(*locList, i));
    int row = p.x;
    int col = p.y;
    MAP(*m, row, col).color = cc;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void displayMap(Map m)
{
    for (int i = 0; i < ROWS(m) + 2; i++)
    {
        for (int j = 0; j < COLS(m) + 2; j++)
        {
            displayColoredLoc(MAP(m, i, j));
        }
        printf("\n");
    }
}