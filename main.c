#include <stdio.h>
#include "boolean.h"
#include "to_do_list/linked_list_to_do.h"
#include "in_progress_list/linked_list_in_progress.h"

int main() {
    // KAMUS 
    List l1, l2;
    Pesanan p1, p2;
    Location x1, x2;

    // ALGORITMA
    CreateLocation(&x1, 5, 6 ,'D');
    CreateLocation(&x2, 7, 8 ,'G');

    CreatePesanan(&p1, NORMAL, x1, x2, 2);
    CreatePesanan(&p2, HEAVY, x1, x2, 5);
    
    printf("Apakah pesanan sama? %d\n", isPesananEqual(p1, p2));

    CreateToDoList(&l1);
    insertFirstToDo(&l1, p1);
    insertLastToDo(&l1, p2);
    displayToDoList(l1);

    CreateInProgressList(&l2);
    insertFirstInProgress(&l2, p2);
    insertLastInProgress(&l2, p1);

    printf("\n");
    displayInProgressList(l2);

    return 0;
}