#include <stdio.h>
#include "pesanan.h"
#include "../location/location.h"

int main(){
    int xpick, ypick, xdrop, ydrop;
    char cpick, cdrop;
    Location pick, drop;
    scanf("%d %d %d %d", &xpick, &ypick, &xdrop, &ydrop);
    scanf(" %c %c", &cpick, &cdrop);
    CreateLocation(&pick, xpick, ypick, cpick);
    CreateLocation(&drop, xdrop, ydrop, cdrop);

    int waktuIn;
    scanf(" %d", &waktuIn);

    char jenis;
    scanf(" %c", &jenis);
    JenisItem jenisItem = charToJenisItem(jenis);

    Pesanan p;
    if(jenisItem == PERISHABLE){
        int timeout;
        scanf(" %d", &timeout);
        CreatePesananPerish(&p, jenisItem, pick, drop, waktuIn, timeout);
    } else{
        CreatePesanan(&p, jenisItem, pick, drop, waktuIn);
    }
    
    displayPesanan(p);
}