#include <stdio.h>
#include "location.h"

/* KONSTRUKTOR */
void CreateLocation(Location *loc, int x, int y, char c)
{
    Point p;
    CreatePoint(&p, x, y);
    POINT(*loc) = p;
    BUILD_NAME(*loc) = c;
    COLOR(*loc) = HI; // DEFAULT = HITAM
}

/* SETTER */
void setLocationColor(Location *loc, Color cc)
{
    COLOR(*loc) = cc;
}

/* I/O */
void displayLoc(Location loc)
{
    Point p = POINT(loc);
    printf("%c (%d, %d)", BUILD_NAME(loc), ABSIS(p), ORDINAT(p));
}

void displayColoredLoc(Location loc)
{
    char name = BUILD_NAME(loc);
    switch (COLOR(loc))
    {
    case O:
        print_yellow(name);
        break;
    case R:
        print_red(name);
        break;
    case G:
        print_green(name);
        break;
    case B:
        print_blue(name);
        break;
    default:
        printf("%c", name);
        break;
    }
}

boolean isLocEqual(Location l1, Location l2)
{
    Point p1 = POINT(l1);
    Point p2 = POINT(l2);

    return ((p1.x == p2.x) && (p1.y == p2.y) && (BUILD_NAME(l1) == BUILD_NAME(l2)) && (COLOR(l1) == COLOR(l2)));
}