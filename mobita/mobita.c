#include <stdio.h>
#include <stdlib.h>
#include "mobita.h"
#include "../utilities/boolean.h"
#include "../mesin/charmachine.h"
#include "../point/location.h"
//#include "../ability/ability.h"
//#include "../linkedlist/linkedlist.h"
#include "../gadgetlist/gadgetlist.h"
//#include "../dynamiclist/dynamiclist.h"
//#include "../adjmat/adjmat.h"
//#include "../map/map.h"

/* KONSTRUKTOR */
void CreateMobita(Mobita *m)
{
    //Creates base mobita
    BALANCE(*m) = 0;
    //LOCATION(*m) = {1, 1}; //will be switched to hq coords
    //ABILITY(*m) = 0;       //will be switched to default ability
    //TODO(*m) = NULL;       //empty linked list
    //INPROGRESS(*m) = NULL; //empty linked list
    CreateGadgetList(&INVENTORY(*m));
    //DynamicList d;
    //CreateDynamicList(&d);
    //BUILDINGLIST(*m) = d;
    //Adjmat adj;
    //CreateAdjMat(&adj);
    //ADJMAT(*m) = adj;
    //Map map;
    //CreateMap(&map);
    //MAP(*m) = map;
}

/* COMMANDS (SPEC SUBJECT TO CHANGE) */ 

void CommandBuy(Mobita* m){
	
}

void CommandInventory(Mobita* m){
	DisplayInventory(&INVENTORY(*m));
	printf("Gadget mana yang ingin digunakan? (ketik 0 untuk kembali)\n\n");
	printf("ENTER COMMAND: ");
	int cmd; scanf("%d",&cmd); //TEMPORARY SCANF
	//Guards Empty Bag
	if(cmd>=1&&cmd<=5&&GADGETOWNED(INVENTORY(*m),cmd-1)==0)cmd=6;
	switch(cmd){
		case 0:
			return;
		case 1:
			if(UseKainWaktu(m))UpdateItem(&INVENTORY(*m),cmd-1,-1);
			break;
		case 2:
			if(UseSenterPembesar(m))UpdateItem(&INVENTORY(*m),cmd-1,-1);
			break;
		case 3:
			if(UsePintuKemanaSaja(m))UpdateItem(&INVENTORY(*m),cmd-1,-1);
			break;
		case 4:
			if(UseMesinWaktu(m))UpdateItem(&INVENTORY(*m),cmd-1,-1);
			break;
		case 5:
			if(UseSenterPembesar(m))UpdateItem(&INVENTORY(*m),cmd-1,-1);
			break;
		default:
			printf("Command tidak valid\n");
	}
	
}

/* INTERNAL COMMANDS */
boolean UseKainWaktu(Mobita *m){
	return 1;
}

boolean UseSenterPembesar(Mobita *m){
	return 1;
}

boolean UsePintuKemanaSaja(Mobita *m){
	return 1;
}

boolean UseMesinWaktu(Mobita *m){
	return 1;
}

boolean UseSenterPengecil(Mobita *m){
	return 1;
}

