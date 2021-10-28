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

/* OPERANDS */
void DisplayShop(GadgetList *g){
	int i=0;
	for(;i<5;i++){
		if(!isOwned(g,i))printf("%d. %s (%d yen)\n",i+1,NAME(*g,i),PRICE(*g,i));
		else printf("%d. - \n",i+1);
	}
}

void DisplayInventory(GadgetList *g){
	int i=0;
	for(;i<5;i++){
		if(isOwned(g,i))printf("%d. %s\n",i+1,NAME(*g,i));
		else printf("%d. - \n",i+1);
	}
}

boolean isOwned(GadgetList *g, int idx){
	return OWNED(*g,idx);
}

void UpdateItem(GadgetList *g, int idx){
	OWNED(*g,idx)^=1;
}
