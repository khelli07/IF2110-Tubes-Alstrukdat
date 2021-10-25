#ifndef LOCATION_H
#define LOCATION_H

#include "../point/point.h"

typedef struct{
    Point point;
    char name;
} Location;

/* SELEKTOR */
#define POINT(p) (p).point
#define NAME(p) (p).name

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c);

/* DISPLAY */
void DisplayLocation(Location loc);

#endif
