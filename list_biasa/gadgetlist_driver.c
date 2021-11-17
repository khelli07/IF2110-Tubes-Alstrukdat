#include <stdio.h>
#include <stdlib.h>
#include "gadgetlist.h"
#include "../utilities/boolean.h"

int main(){
	GadgetList g;
	CreateGadgetList(&g);
	DisplayShop(&g);
	DisplayInventory(&g);
	UpdateItem(&g,1,1);
	UpdateItem(&g,4,2);
	DisplayShop(&g);
	DisplayInventory(&g);
}
