#include<stdio.h>
#include<stdlib.h>
#include "location.h"
#include "../point/point.h"

/* SELEKTOR */
// POINT(L) -> L.point (POINT)
// NAME(L) -> L.name (char)

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c){
	Point p; CreatePoint(&p,x,y);
	POINT(*loc)=p;
	NAME(*loc)=c;
}

/* DISPLAY */
void DisplayLocation(Location loc){
	//prints {name (x,y)} without newline
	printf("%c (%d,%d)",NAME(loc),ABSIS(POINT(loc)),ORDINAT(POINT(loc)));
}
