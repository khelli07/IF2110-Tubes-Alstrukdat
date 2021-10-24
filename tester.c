#include <stdio.h>
#include "adt_mesin/locmachine.h"

int main()
{
    startReadLoc();
    while (!endReadLoc)
    {
        displayLocation(currentLoc);
        printf("\n");
        advReadLoc();
    }

    char c;
    printf("Press enter to exit\n");
    scanf("%c", &c);
    return 0;
}