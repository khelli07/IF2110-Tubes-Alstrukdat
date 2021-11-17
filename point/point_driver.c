#include "location.h"
#include <stdio.h>

int main()
{
    Location l, l1;
    CreateLocation(&l, 10, 10, 'T');
    CreateLocation(&l1, 10, 10, 'T');
    l.color = R;

    displayColoredLoc(l);
    printf("\n");
    displayLoc(l);
    printf("\n");
    printf("%d", isLocEqual(l, l1));
    return 0;
}