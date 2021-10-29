#include <stdio.h>
#include <stdlib.h>
#include "gadgetlist.h"
#include "../utilities/boolean.h"

/* KONSTRUKTOR */
void CreateGadgetList(GadgetList *g){
	char* name;
	name="Kain Pembungkus Waktu";
	NAME(*g,0)=name;
	PRICE(*g,0)=800;
	OWNED(*g,0)=0;
	
	name="Senter Pembesar";
	NAME(*g,1)=name;
	PRICE(*g,1)=1200;
	OWNED(*g,1)=0;
	
	name="Pintu Kemana Saja";
	NAME(*g,2)=name;
	PRICE(*g,2)=1500;
	OWNED(*g,2)=0;
	
	name="Mesin Waktu";
	NAME(*g,3)=name;
	PRICE(*g,3)=3000;
	OWNED(*g,3)=0;
	
	name="Senter Pengecil";
	NAME(*g,4)=name;
	PRICE(*g,4)=800;
	OWNED(*g,4)=0;
}

/* STATUS */
int InventorySize(GadgetList *g){
	int ret=0;
	int i=0;
	for(;i<5;i++)ret+=(OWNED(*g,i));
}

/* OPERANDS */
void DisplayShop(GadgetList *g){
	int i=0;
	for(;i<5;i++){
		printf("%d. %s (%d yen)\n",i+1,NAME(*g,i),PRICE(*g,i));
	}
}

void DisplayInventory(GadgetList *g){
	if(InventorySize(g)==0){
		printf("Inventory Kosong\n");
		return;
	}
	int i=0;
	int cnt=0;
	while(i<5){
		int j=0;
		for(;j<OWNED(*g,i);j++){
			printf("%d. %s\n",cnt+1,NAME(*g,i));
			cnt++;
		}
		i++;
	}
}

void UpdateItem(GadgetList *g, int idx, int change){
	OWNED(*g,idx)+=change;
}
