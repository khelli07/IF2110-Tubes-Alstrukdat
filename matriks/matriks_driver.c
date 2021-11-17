#include "map.h"

int main()
{
    Map m;
    CreateMap(&m, 10, 10);

    Location HQ;
    CreateLocation(&HQ, 5, 5, '8');

    setBuilding(&m, HQ);
    displayMap(m);
    return 0;
}