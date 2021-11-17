#include <stdio.h>
#include "stack.h"
#include "../utilities/boolean.h"
#include "../pesanan/pesanan.h"
#include "../point/location.h"
#include "../point/point.h"

int main() {
    Pesanan p1, p2, p3;
    Stack s;
    Location l1, l2;

    CreateStack(&s);
    CreateLocation(&l1, 10, 8, 'N');
    CreateLocation(&l2, 5, 2, 'B');
    CreatePesanan(&p1, VIP, l1, l2, 5);
    CreatePesanan(&p2, NORMAL, l2, l1, 8);

    printf("Apakah stack kosong?%d\n", isEmpty(s));
    printf("Apakah stack full?%d\n", isFull(s));

    push(&s, p1);
    push(&s, p2);
    pop(&s, &p3);

    printf("Ukuran stack saat ini: %d\n", sizeStack(s));
    return 0;
}