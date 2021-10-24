#include <stdio.h>
#include "adt_mesin/locmachine.c"
#include "adt_point/location.h"

int main()
{
    startReadLoc();
    while (!endReadLoc)
    {
        displayLocation(currentLoc);
        printf("\n");
        advReadLoc();
    }
    return 0;
}