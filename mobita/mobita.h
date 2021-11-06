// TEMPORARY SUMMARY OF MOBITA DS; SUBJECT TO CHANGE

#ifndef MOBITA_H
#define MOBITA_H

#include "../utilities/boolean.h"
#include "../point/location.h"
#include "../list_linked/linked_list_to_do.h"
#include "../list_linked/linked_list_in_progress.h"
#include "../list_biasa/gadgetlist.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
#include "../matriks/map.h"
#include "../tas/stack.h"

//extras
#include "../pesanan/pesanan.h"


extern int globalTime;
extern int bagCapacity;
extern List daftarPesanan;

typedef struct{
	int balance;
    int scoreTime;
    int tasCapacity;
    Location curLoc;
    List toDoList;
    List inProgressList;
    QueuePesanan notYetQueue;
    Stack tas;
    GadgetList inventory;
    DynamicList buildingList;
    AdjMatrix adjMatrix;
    Map map;

    // Daftar Ability
    int speedBoostAbility;  // Siswa waktu speed boost, -1 atau 0 jika tidak ada, waktu global dievaluasi bertambah jika ganjil
    boolean returnToSenderAbility;
} Mobita;

/* SELEKTOR */
#define BALANCE(m) (m).balance
#define SCORETIME(m) (m).scoreTime
#define TASCAPACITY(m) (m).tasCapacity
#define LOCATION(m) (m).curLoc
#define TODO(m) (m).toDoList
#define INPROGRESS(m) (m).inProgressList
#define QUEUEPESANAN(m) (m).notYetQueue
#define TAS(m) (m).tas
#define INVENTORY(m) (m).inventory
#define BUILDINGLIST(m) (m).buildingList
#define ADJMAT(m) (m).adjMatrix
#define PETA(m) (m).map //MAP sudah ada di file lain ....

/* KONSTRUKTOR */
void CreateMobita(Mobita* m);

/* Command move, menampilkan lokasi aksesibel terlebih dahulu
 * I.S.: Mobita m terdefinisi
 * F.S.: Tertampilkan accesible location, dan lokasi m berpindah ke tujuan, atau dibatalkan */
void CommandMove(Mobita* m);

/* Mendapatkan input command, dengan menampilkan pesan msg dulu. Return masukan yang valid 0-n */
int getInputCommand(char msg[], int n);

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

void CommandBalance(Mobita* m);
// displays balance

/* INTERNAL COMMANDS */

/* GADGET USE */
boolean UseKainWaktu(Mobita *m);

boolean UseSenterPembesar(Mobita *m);

boolean UsePintuKemanaSaja(Mobita *m);

boolean UseMesinWaktu(Mobita *m);

boolean UseSenterPengecil(Mobita *m);
#endif
