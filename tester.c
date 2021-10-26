#include <stdio.h>
#include "mesin/locmachine.h"
#include "list/dynamiclist.h"
#include "matriks/map.h"

int main()
{
    /* KAMUS LOKAL */
    DynamicList locList;
    Map m;

    /* ALGORITMA */
    CreateMap(&m, 10, 15);

    startReadLoc();
    CreateDynamicList(&locList, readLocCounter);
    while (!endReadLoc)
    {
        displayLoc(currentLoc);
        insertLoc(&locList, currentLoc);
        setBangunan(&m, currentLoc);
        printf("\n");
        advReadLoc();
    }

    printf("\nBanyaknya bangunan: %d\n", countBangunan(locList));
    displayLocList(locList);

    printf("\n");
    displayMap(m);

    dealocate(&locList);

    printf("%d", NEFF(locList));
    printf(" %d\n", CAPACITY(locList));
    displayMap(m);
    return 0;
}