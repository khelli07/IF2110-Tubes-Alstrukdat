#include <stdio.h>
#include "location.h"
#include "point.h"

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c)
{
    Point p;
    CreatePoint(&p, x, y);
    TITIK(*loc) = p;
    NAMA_BANGUNAN(*loc) = c;
}

/* I/O */
void displayLocation(Location loc)
{
    Point p = TITIK(loc);
    printf("%c (%d, %d)", NAMA_BANGUNAN(loc), ABSIS(p), ORDINAT(p));
}