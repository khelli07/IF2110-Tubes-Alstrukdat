/* DEFINISI ADT LOCATION */
#ifndef LOCATION_H
#define LOCATION_H

#include "../utilities/boolean.h"
#include "point.h"

typedef struct
{
    Point titik;
    char namaBangunan;
} Location;

/* SELEKTOR */
#define TITIK(p) (p).titik
#define NAMA_BANGUNAN(p) (p).namaBangunan

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c);

/* I/O */
void displayLocation(Location loc);

#endif