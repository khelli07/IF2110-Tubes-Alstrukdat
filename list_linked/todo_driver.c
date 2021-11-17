#include <stdio.h>
#include "linked_list_to_do.h"
#include "../utilities/boolean.h"
#include "../pesanan/pesanan.h"
#include "../point/location.h"
#include "../point/point.h"

int main() {
    Pesanan p1, p2, p3, p4, p5;
    Location l1, l2, l3, l4, l5;
    List L;

    CreateToDoList(&L);
    CreateLocation(&l1, 3, 5, 'F');
    CreateLocation(&l2, 4, 11, 'J');
    CreateLocation(&l3, 10, 13, 'G');
    CreateLocation(&l4, 11, 15, 'H');
    CreateLocation(&l5, 11, 14, 'I');
    CreatePesanan(&p1, HEAVY, l1, l2, 6);
    CreatePesanan(&p2, NORMAL, l2, l3, 7);
    CreatePesanan(&p3, NORMAL, l3, l4, 7);
    CreatePesanan(&p4, NORMAL, l4, l5, 7);

    printf("Apakah to do list kosong? %d\n", isToDoEmpty(L));

    insertLastToDo(&L, p1);
    insertLastToDo(&L, p2);
    insertFirstToDo(&L, p3);
    insertFirstToDo(&L, p4);
    deleteFirstToDo(&L, &p5);
    deleteLastInToDo(&L, &p5);

    printf("Banyaknya to do list: %d\n", lengthToDo(L));

    displayToDoList(L);
    return 0;
}