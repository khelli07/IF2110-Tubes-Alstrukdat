/* DEFINISI ADT LOCATION */
#ifndef LOCATION_H
#define LOCATION_H

#include "../utilities/boolean.h"
#include "../utilities/pcolor.h"
#include "point.h"

enum locationColor{O, R, B, G, HI};
typedef enum locationColor Color;
typedef struct
{
    Point point;
    char buildingName;
    Color color;
} Location;

/* SELEKTOR */
#define POINT(p) (p).point
#define BUILD_NAME(p) (p).buildingName
#define COLOR(p) (p).color

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c);

/* SETTER */
void setLocationColor(Location *loc, Color c);

/* I/O */
void displayLoc(Location loc);
void displayColoredLoc(Location loc);

/* FUNGSI TAMBAHAN */
boolean isLocEqual(Location l1, Location l2);

#endif