#include <stdio.h>
#include <stdlib.h>
#include "gadgetlist.h"
#include "../utilities/boolean.h"

/* KONSTRUKTOR */
void CreateGadgetList(GadgetList *g){
	char* name;
	name="Kain Pembungkus Waktu";
	GADGETNAME(*g,0)=name;
	GADGETPRICE(*g,0)=800;
	GADGETOWNED(*g,0)=0;
	
	name="Senter Pembesar";
	GADGETNAME(*g,1)=name;
	GADGETPRICE(*g,1)=1200;
	GADGETOWNED(*g,1)=0;
	
	name="Pintu Kemana Saja";
	GADGETNAME(*g,2)=name;
	GADGETPRICE(*g,2)=1500;
	GADGETOWNED(*g,2)=0;
	
	name="Mesin Waktu";
	GADGETNAME(*g,3)=name;
	GADGETPRICE(*g,3)=3000;
	GADGETOWNED(*g,3)=0;
	
	name="Senter Pengecil";
	GADGETNAME(*g,4)=name;
	GADGETPRICE(*g,4)=800;
	GADGETOWNED(*g,4)=0;
}

/* STATUS */
int InventorySize(GadgetList *g){
	int ret=0;
	int i=0;
	for(;i<5;i++)ret+=(GADGETOWNED(*g,i));
	return ret;
}

/* OPERANDS */
void DisplayShop(GadgetList *g){
	int i=0;
	for(;i<5;i++){
		printf("%d. %s (%d yen)\n",i+1,GADGETNAME(*g,i),GADGETPRICE(*g,i));
	}
}

int DisplayInventory(GadgetList *g){
	if(InventorySize(g)==0){
		printf("Inventory Kosong\n");
		return 0;
	}
	int i=0;
	int cnt=0;
	while(i<5){
		if(GADGETOWNED(*g,i))printf("%d. %s (x%d)\n",i+1,GADGETNAME(*g,i),GADGETOWNED(*g,i));
		else printf("%d. -\n",i+1);
		i++;
	}
	return 1;
}

void UpdateItem(GadgetList *g, int idx, int change){
	GADGETOWNED(*g,idx)+=change;
}
