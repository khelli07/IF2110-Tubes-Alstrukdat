#include <stdio.h>
#include "../pesanan/pesanan.h"
#include "../point/location.h"
#include "queuepesanan.h"

int main(){
    Pesanan p1, p2, p3;
    Location a, b;
    QueuePesanan q;

    CreateLocation(&a, 10, 20, 'A');
    CreateLocation(&b, 5, 7, 'B');
    CreatePesanan(&p1, NORMAL, a, b, 10);
    CreatePesananPerish(&p2, PERISHABLE, b, a, 5, 200);
    CreatePesanan(&p3, HEAVY, a, b, 7);
    
    CreateQueue(&q);
    enqueue(&q, p1);
    enqueue(&q, p2);
    enqueue(&q, p3);
    displayQueue(q);

    sortQueue(&q);
    displayQueue(q);

    return 0;
}