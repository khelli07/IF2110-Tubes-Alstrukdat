/* DEFINISI ADT POINT */
#ifndef POINT_H
#define POINT_H

#include "../utilities/boolean.h"

typedef struct 
{
    int x;
    int y;
} Point;

/* SELEKTOR */
#define ABSIS(p) (p).x
#define ORDINAT(p) (p).y

/* KONSTRUKTOR */
void CreatePoint(Point *p, int x, int y);

#endif