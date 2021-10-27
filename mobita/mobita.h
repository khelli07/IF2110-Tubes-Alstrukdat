// TEMPORARY SUMMARY OF MOBITA DS; SUBJECT TO CHANGe

#ifndef MOBITA_H
#define MOBITA_H

#include "../utilities/boolean.h"
#include "../point/location.h"
//#include "../ability/ability.h"
//#include "../linkedlist/linkedlist.h"
//#include "../staticlist/staticlist.h"
//#include "../dynamiclist/dynamiclist.h"
//#include "../adjmat/adjmat.h"
//#include "../map/map.h"

//extras
#include "../pesanan/pesanan.h"

typedef struct{
	int balance;
    Location curLoc;
    Ability curAbility;
    LinkedList toDoList;
    LinkedList inProgressList;
    StaticList inventory;
    DynamicList buildingList;
    Adjmat adjMatrix;
    Map map;
} Mobita;

/* SELEKTOR */
#define BALANCE(m) (m).balance
#define LOCATION(m) (m).curLoc
#define ABILITY(m) (m).curAbility
#define TODO(m) (m).toDoList
#define INPROGRESS(m) (m).inProgressList
#define INVENTORY(m) (m).inventory
#define BUILDINGLIST(m) (m).buildingList
#define ADJMAT(m) (m).adjMatrix
#define MAP(m) (m).map

/* KONSTRUKTOR */
void CreateMobita(Mobita* m);

/* COMMANDS (SPEC SUBJECT TO CHANGE) */ 
void CommandMove(Mobita *m, Location loc);
// moves mobita to loc (updates LOCATION(m))

void CommandPickUp(Mobita *m, Pesanan P);
// moves P from toDoList to inProgressList

void CommandDropOff(Mobita *m, Pesanan P);
// deletes P from inProgressList, adds balance

void CommandMap(Mobita m);
// displays map

void CommandToDo(Mobita m);
// displays to do list

void CommandInProgress(Mobita m);
// displays in progress list (picked up items)

void CommandBuy(Mobita* m);
// buys gadget, parameters still unclear

void CommandInventory(Mobita m);
// displays inventory

#endif
