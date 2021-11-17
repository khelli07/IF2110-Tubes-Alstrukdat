#include "dynamiclist.h"

int main()
{
    Location A, B, C, tmp;
    CreateLocation(&A, 1, 2, 'A');
    CreateLocation(&B, 3, 4, 'B');
    CreateLocation(&C, 5, 6, 'C');

    DynamicList l;
    CreateDynamicList(&l, 3);
    insertLoc(&l, A);
    insertLoc(&l, B);
    deleteLoc(&l, &tmp);
    insertLoc(&l, C);
    displayLocList(l);

    printf("\n%d\n", getLocIndex(l, A));
    displayLoc(getLoc(l, 'C'));
    printf("\n%d\n", countBuilding(l));

    dealocate(&l);
    return 0;
}