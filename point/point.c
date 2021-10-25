#include<stdio.h>
#include<stdlib.h>
#include "point.h"

/* SELEKTOR */
// ABSIS(P) -> P.x (integer)
// ORDINAT(P) -> P.y (integer)

/* KONSTRUKTOR */
void CreatePoint(Point *p, int x, int y){
    ABSIS(*p) = x;
    ORDINAT(*p) = y;
}
