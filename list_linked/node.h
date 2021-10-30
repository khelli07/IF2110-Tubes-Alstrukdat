#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "../pesanan/pesanan.h"

typedef Pesanan ElType;
typedef struct node* Address;
typedef struct node {
    ElType info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElType val);


#endif