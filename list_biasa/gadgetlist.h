#ifndef GADGETLIST_H
#define GADGETLIST_H

#include "../utilities/boolean.h"

typedef struct{
	char* name;
	int price;
	int owned; //num of gadgets i owned
}GadgetList[5];

/* SELEKTOR */
#define GADGETNAME(g,i) ((g)[i]).name
#define GADGETPRICE(g,i) ((g)[i]).price
#define GADGETOWNED(g,i) ((g)[i]).owned

/* KONSTRUKTOR */
void CreateGadgetList(GadgetList *g);

/* STATUS */
int InventorySize(GadgetList *g);

/* OPERANDS */
void DisplayShop(GadgetList *g);

int DisplayInventory(GadgetList *g);

void UpdateItem(GadgetList *g, int idx, int change); //change= +1 or -1

#endif
