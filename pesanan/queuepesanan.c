#include <stdio.h>
#include "../utilities/boolean.h"
#include "queuepesanan.h"

/* *** Kreator *** */
void CreateQueue(QueuePesanan *q)
{
    IDX_HEADQUEUE(*q) = -1;
    IDX_TAILQUEUE(*q) = -1;
}

boolean isQueueEmpty(QueuePesanan q)
{
    if (IDX_HEADQUEUE(q) == -1 && IDX_TAILQUEUE(q) == -1)
        return true;
    return false;
}

boolean isQueueFull(QueuePesanan q)
{
    if (IDX_HEADQUEUE(q) == 0 && IDX_TAILQUEUE(q) == QUEUE_CAPACITY - 1)
        return true;
    return false;
}

int lengthQueue(QueuePesanan q)
{
    if (isQueueEmpty(q))
        return 0;
    else
        return (IDX_TAILQUEUE(q) - IDX_HEADQUEUE(q) + 1);
}

void enqueue(QueuePesanan *q, Pesanan val)
{
    if (isQueueEmpty(*q))
    {
        IDX_HEADQUEUE(*q) = 0;
        IDX_TAILQUEUE(*q) = 0;
        TAILQUEUE(*q) = val;
        return;
    }
    if (IDX_TAILQUEUE(*q) == QUEUE_CAPACITY - 1)
    {
        int i;
        for (i = IDX_HEADQUEUE(*q); i <= IDX_TAILQUEUE(*q); i++)
        {
            (*q).buffer[i - IDX_HEADQUEUE(*q)] = (*q).buffer[i];
        }
        IDX_TAILQUEUE(*q) -= IDX_HEADQUEUE(*q);
        IDX_HEADQUEUE(*q) = 0;
    }
    IDX_TAILQUEUE(*q)
    ++;
    TAILQUEUE(*q) = val;
}

void dequeue(QueuePesanan *q, Pesanan *val)
{
    *val = HEADQUEUE(*q);
    IDX_HEADQUEUE(*q)
    ++;
    if (IDX_HEADQUEUE(*q) > IDX_TAILQUEUE(*q))
    {
        IDX_HEADQUEUE(*q) = -1;
        IDX_TAILQUEUE(*q) = -1;
    }
}

void displayQueue(QueuePesanan q)
{
    int i = 1;
    while (!isQueueEmpty(q))
    {
        Pesanan p;
        dequeue(&q, &p);
        printf("%d. ", i);
        displayPesanan(p);
        i++;
    }
}

void sortQueue(QueuePesanan *q)
{
    int i, j, n;
    Pesanan temp;

    n = lengthQueue(*q);
    Pesanan arr[QUEUE_CAPACITY];
    for (i = 0; i < n; i++)
    {
        dequeue(q, &temp);
        arr[i] = temp;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j > 0; j--)
        {
            if (WaktuIn(arr[j]) < WaktuIn(arr[j - 1]))
            {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
            else
            {
                break;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        enqueue(q, arr[i]);
    }
}