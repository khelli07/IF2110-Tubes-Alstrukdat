#include <stdio.h>
#include "../mesin/locmachine.h"
#include "../mesin/charmachine.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
#include "../matriks/map.h"

// kalo mau test -> ubah main_test ke main(), pastikan tidak ada main() lain
int main_test()
{
    /* KAMUS LOKAL */
    int mrow, mcol;
    int px, py, N;
    Location HQ;
    DynamicList locList;
    AdjMatrix adjMat;
    Map map;

    /* ALGORITMA */
    start();

    // BACA MAP
    mrow = readInt();
    mcol = readInt();
    CreateMap(&map, mrow, mcol);

    // BACA HEADQUARTER
    px = readInt();
    py = readInt();
    CreateLocation(&HQ, px, py, '8');
    setBuilding(&map, HQ);

    startReadLoc();
    CreateDynamicList(&locList, readLocCounter);
    insertLoc(&locList, HQ);
    while (!endReadLoc)
    {
        // displayLoc(currentLoc);
        insertLoc(&locList, currentLoc);
        setBuilding(&map, currentLoc);
        advReadLoc();
    }

    // DISPLAY SEMUA BANGUNAN
    printf("\nBanyaknya bangunan: %d\n", countBuilding(locList));
    displayLocList(locList);
    printf("\n");

    // DISPLAY INITIAL MAP
    printf("\n=== MAP AWAL MOBITA ===\n");
    displayMap(map);
    printf("\n=== INPUT ADJ MATRIX ===\n");

    // READ ADJ MATRIX
    N = countBuilding(locList);
    CreateAdjMatrix(&adjMat, N);
    readAdjMatrix(&adjMat, N);

    printf("\n=== ADJ MATRIKS YANG DIMASUKKAN ===\n");
    displayAdjMatrix(adjMat);

    printf("\n=== DISPLAY ACCESSIBLE LOC DARI HQ ===\n");
    Location locHQ;
    CreateLocation(&locHQ, 1, 1, '8');
    displayAccLoc(adjMat, locList, locHQ);

    printf("\n=====\n");
    setLocationColor(&map, &locList, locHQ, R);
    displayMap(map);

    dealocate(&locList);
    return 0;
}