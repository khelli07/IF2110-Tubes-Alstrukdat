#ifndef GADGETLIST_H
#define GADGETLIST_H

#include "../utilities/boolean.h"

typedef struct{
	char* name;
	int price;
	boolean owned; //0 if buyable, 1 if owned
}GadgetList[5];

/* SELEKTOR */
#define NAME(g,i) ((g)[i]).name
#define PRICE(g,i) ((g)[i]).price
#define OWNED(g,i) ((g)[i]).owned

/* KONSTRUKTOR */
void CreateGadgetList(GadgetList *g);

/* OPERANDS */
void DisplayShop(GadgetList *g);

void DisplayInventory(GadgetList *g);

boolean isOwned(GadgetList *g, int idx);

void UpdateItem(GadgetList *g, int idx);

#endif
