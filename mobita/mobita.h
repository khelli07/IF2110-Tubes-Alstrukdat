// TEMPORARY SUMMARY OF MOBITA DS; SUBJECT TO CHANGE

#ifndef MOBITA_H
#define MOBITA_H

#include "../utilities/boolean.h"
#include "../point/location.h"
//#include "../linkedlist/linkedlist.h"
#include "../list_biasa/gadgetlist.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
//#include "../map/map.h"

//extras
#include "../pesanan/pesanan.h"

/*
extern int globalTime;
extern int abilityHeavy;
extern int abilitySpeed;
extern int abilityRet
*/

typedef struct{
	int balance;
    Location curLoc;
    //LinkedList toDoList;
    //LinkedList inProgressList;
    GadgetList inventory;
    DynamicList buildingList;
    AdjMatrix adjMatrix;
    //Map map;
} Mobita;

/* SELEKTOR */
#define BALANCE(m) (m).balance
#define LOCATION(m) (m).curLoc
//#define TODO(m) (m).toDoList
//#define INPROGRESS(m) (m).inProgressList
#define INVENTORY(m) (m).inventory
#define BUILDINGLIST(m) (m).buildingList
#define ADJMAT(m) (m).adjMatrix
//#define PETA(m) (m).map //MAP sudah ada di file lain ....

/* KONSTRUKTOR */
void CreateMobita(Mobita* m);

/* COMMANDS (SPEC SUBJECT TO CHANGE) */ 
void CommandMove(Mobita *m);
// moves mobita to loc (updates LOCATION(m))

void CommandPickUp(Mobita *m);
// moves P from toDoList to inProgressList

void CommandDropOff(Mobita *m);
// deletes P from inProgressList, adds balance

void CommandMap(Mobita* m);
// displays map

void CommandToDo(Mobita* m);
// displays to do list

void CommandInProgress(Mobita* m);
// displays in progress list (picked up items)

void CommandBuy(Mobita* m);
// buys gadget

void CommandInventory(Mobita* m);
// displays inventory, may use a gadget

void CommandSave(Mobita* m);
// saves to file.mob

void CommandLoad(Mobita* m);
// loads file.mob

/* INTERNAL COMMANDS */

/* GADGET USE */
boolean UseKainWaktu(Mobita *m);

boolean UseSenterPembesar(Mobita *m);

boolean UsePintuKemanaSaja(Mobita *m);

boolean UseMesinWaktu(Mobita *m);

boolean UseSenterPengecil(Mobita *m);
#endif
