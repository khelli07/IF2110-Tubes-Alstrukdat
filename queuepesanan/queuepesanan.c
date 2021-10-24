#include <stdio.h>
#include "../boolean.h"
#include "queuepesanan.h"


/* *** Kreator *** */
void CreateQueue(Queue *q){
    IDX_HEADQUEUE(*q) = IDX_UNDEF;
    IDX_TAILQUEUE(*q) = IDX_UNDEF;
}


boolean isQueueEmpty(Queue q){
    if(IDX_HEADQUEUE(q) == IDX_UNDEF && IDX_TAILQUEUE(q) == IDX_UNDEF) return true;
    return false;
}

boolean isQueueFull(Queue q){
    if(IDX_HEADQUEUE(q) == 0 && IDX_TAILQUEUE(q) == QUEUE_CAPACITY-1) return true;
    return false;
}

int lengthQueue(Queue q){
    if(isQueueEmpty(q)) return 0;
    else return (IDX_TAILQUEUE(q) - IDX_HEADQUEUE(q) + 1);
}


void enqueue(Queue *q, Pesanan val){
    if(isQueueEmpty(*q)){
        IDX_HEADQUEUE(*q) = 0;
        IDX_TAILQUEUE(*q) = 0;
        TAILQUEUE(*q) = val;
        return;
    }
    if(IDX_TAILQUEUE(*q) == QUEUE_CAPACITY-1){
        int i;
        for(i = IDX_HEADQUEUE(*q); i <= IDX_TAILQUEUE(*q); i++){
            (*q).buffer[i-IDX_HEADQUEUE(*q)] = (*q).buffer[i];
        }
        IDX_TAILQUEUE(*q) -= IDX_HEADQUEUE(*q);
        IDX_HEADQUEUE(*q) = 0;
    }
    IDX_TAILQUEUE(*q)++;
    TAILQUEUE(*q) = val;
}

void dequeue(Queue *q, Pesanan *val){
    *val = HEADQUEUE(*q);
    IDX_HEADQUEUE(*q)++;
    if(IDX_HEADQUEUE(*q) > IDX_TAILQUEUE(*q)){
        IDX_HEADQUEUE(*q) = IDX_UNDEF;
        IDX_TAILQUEUE(*q) = IDX_UNDEF;
    }
}


void displayQueue(Queue q){
    while(!isQueueEmpty(q)){
        Pesanan p;
        dequeue(&q, &p);
        printf("%d ", WaktuIn(p));
        switch (JenisItem(p))
        {
        case NORMAL:
            printf("Normal 200 Yen");
            break;
        case HEAVY:
            printf("Heavy 400 Yen");
            break;
        case PERISHABLE:
            printf("Perishable 400 Yen Timeout: %d", TimeoutPerish(p));
            break;
        case VIP:
            printf("VIP 600 Yen");
            break;
        }
        printf("\n");
    }
}