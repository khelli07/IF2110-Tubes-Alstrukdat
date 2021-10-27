#include "dynamiclist.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
void CreateDynamicList(DynamicList *l, int capacity)
{
    BUFFER(*l) = (ElType *)malloc((capacity + 2) * sizeof(ElType));
    if (BUFFER(*l) != NULL)
    {
        NEFF(*l) = 0;
        CAPACITY(*l) = capacity + 1;
    }
}

void dealocate(DynamicList *l)
{
    if (BUFFER(*l) != NULL)
    {
        free(BUFFER(*l));
        CAPACITY(*l) = 0;
        NEFF(*l) = 0;
    }
}

/* I/O LIST LOCATION */
void displayLocList(DynamicList l)
{
    for (int i = 0; i < NEFF(l); i++)
    {
        if (i != NEFF(l) - 1)
        {
            printf("%d. ", i + 1);
            displayLoc(LOC(l, i));
            printf("\n");
        }
        else
        {
            printf("%d. ", i + 1);
            displayLoc(LOC(l, i));
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
void insertLoc(DynamicList *l, ElType loc)
{
    LOC(*l, NEFF(*l)) = loc;
    NEFF(*l) += 1;
}

void deleteLoc(DynamicList *l, ElType *val)
{
    *val = LOC(*l, NEFF(*l) - 1);
    NEFF(*l) -= 1;
}

/* ********** GETTER ********** */
int getLocIndex(DynamicList l, Location loc)
{
    int i = 0;
    boolean found = false;
    while (i < NEFF(l) && !found)
    {
        if (isLocEqual(LOC(l, i), loc))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }

    if (found)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

DynamicList getAccLoc(AdjMatrix m, DynamicList l, Location lstart)
{
    int idx;
    DynamicList ltemp;

    CreateDynamicList(&ltemp, CAPACITY(l));
    idx = getLocIndex(l, lstart);
    for (int j = 0; j < SIZE(m); j++)
    {
        if (ADJ(m, idx, j) == 1)
        {
            insertLoc(&ltemp, LOC(l, j));
        }
    }

    return ltemp;
}

void displayAccLoc(AdjMatrix m, DynamicList l, Location lstart)
{
    DynamicList ltemp = getAccLoc(m, l, lstart);
    displayLocList(ltemp);
    dealocate(&ltemp);
}

boolean isAccLoc(AdjMatrix m, DynamicList l, Location lstart, Location ldest)
{
    DynamicList ltemp = getAccLoc(m, l, lstart);
    int i = 0;
    boolean found = false;
    while (i < NEFF(ltemp))
    {
        if (isLocEqual(ldest, LOC(ltemp, i)))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    dealocate(&ltemp);
    return found;
}

/* ********** FUNGSI TAMBAHAN *********** */
boolean isEmpty(DynamicList l)
{
    return (NEFF(l) == 0);
}

boolean isFull(DynamicList l)
{
    return (NEFF(l) == CAPACITY(l) - 1);
}

int countBuilding(DynamicList l)
{
    return NEFF(l);
}
