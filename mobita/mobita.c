#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mobita.h"
#include "../utilities/boolean.h"
#include "../mesin/charmachine.h"
#include "../point/location.h"
#include "../list_linked/linked_list_to_do.h"
#include "../list_linked/linked_list_in_progress.h"
#include "../list_biasa/gadgetlist.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
#include "../matriks/map.h"
#include "../tas/stack.h"

/* VARIABLES */

int globalTime;
/*int abilityHeavy;
int abilitySpeed;
int abilityReturn;
*/

/* KONSTRUKTOR */
void CreateMobita(Mobita *m)
{
    //Creates base mobita
    BALANCE(*m) = 0;
    //LOCATION(*m) = {1, 1}; //will be switched to hq coords
    CreateToDoList(&TODO(*m));       //empty linked list
    CreateInProgressList(&INPROGRESS(*m)); //empty linked list
    CreateGadgetList(&INVENTORY(*m));
    CreateDynamicList(&BUILDINGLIST(*m),30);
    //CreateAdjMat(&adj);
    //CreateMap(&map);
}

/* COMMANDS (SPEC SUBJECT TO CHANGE) */ 
void CommandMove(Mobita* m){
	//printf("Waktu: %d\n", SCORETIME(*m));
	//printf("Current Location: "); displayLoc(LOCATION(*m)); printf("\n");
	DynamicList accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	printf("Posisi yang dapat dicapai:\n");
	displayLocList(accesibleloc);
	printf("\n");

	int command = getInputCommand("Posisi yang dipilih?", NEFF(accesibleloc));
	if(command == 0){
		printf("Dibatalkan!\n");
		return;
	}
	
	LOCATION(*m) = LOC(accesibleloc, command - 1);
	int itemcounts[JENISITEMCOUNT];
	countStackByJenisItem(TAS(*m), itemcounts);
	if(itemcounts[HEAVY] > 0){
		globalTime += (1 + itemcounts[HEAVY]);
		m->speedBoostAbility = -1;
	} else if(m->speedBoostAbility > 0){
		if(m->speedBoostAbility % 2 == 1){
			globalTime += 1;
		}
		m->speedBoostAbility -= 1;
	} else{
		globalTime += 1;
	}

	printf("Mobita sekarang berada di titik ");
	displayLoc(LOCATION(*m));
	printf("\n");
	printf("Waktu: %d\n", SCORETIME(*m));
}

int getInputCommand(char msg[], int n){
	printf(msg);
	printf(" (ketik 0 jika ingin kembali)\n");
	printf("Enter COMMAND: ");
	int command;
	scanf("%d", &command);
	while(command < 0 || command > n){
		printf("Input Salah! Coba Lagi (ketik 0 jika ingin kembali)\n");
		printf("Enter Command: ");
		scanf("%d", &command);
	}
	return command;
}

void CommandPickup(Mobita* m){
	Location currentLoc = LOCATION(*m);
	int todolength = lengthToDo(TODO(*m));
	List todoPesanan = TODO(*m);
	List pesananInLocation;
	CreateToDoList(&pesananInLocation);
	for(int i = 0; i < todolength; i++){
		if(isLocEqual(currentLoc, LokasiPickUp(getPesananToDo(todoPesanan, i)))){
			insertFirstToDo(&pesananInLocation, getPesananToDo(todoPesanan, i));
		}
	}
	if(isToDoEmpty(pesananInLocation)){
		printf("Pesanan tidak ditemukan!\n");
	} else{
		// Mencari Pesanan yang masuk paling dulu
		int inloclength = lengthToDo(pesananInLocation);
		Pesanan firstPesanan = getPesananToDo(pesananInLocation, 0);
		for(int i=1; i<inloclength; i++){
			if(WaktuIn(getPesananToDo(pesananInLocation, i)) < WaktuIn(firstPesanan))
				firstPesanan = getPesananToDo(pesananInLocation, i);
		}
		// Menghapus Pesanan dari To Do (sudah dimasukkan ke In Progress dan Tas)
		int i, n;
		n = lengthToDo(todoPesanan);
		for(i=0; i<n; i++){
			if(isPesananEqual(firstPesanan, getPesananToDo(todoPesanan, i)))
				break;
		}
		insertFirstInProgress(&INPROGRESS(*m), firstPesanan);
		push(&TAS(*m), firstPesanan);
		Pesanan temp;
		deleteAtToDo(&TODO(*m), i, &temp);
		printf("Pesanan berupa %s Item berhasil diambil!\n", getJenisItemString(firstPesanan));
		printf("Tujuan Pesanan: %c\n", NAME(LokasiDropOff(firstPesanan)));
	}
}

void CommandBuy(Mobita* m){
	//if not in HQ, return
	printf("Uang anda sekarang: %d yen\n",BALANCE(*m));
	printf("Mobita HQ Shop:\n");
	DisplayShop(&INVENTORY(*m));
	printf("Gadget mana yang ingin dibeli? (ketik 0 untuk kembali)\n\n");
	printf("ENTER COMMAND: ");
	int cmd; scanf("%d",&cmd);
	switch(cmd){
		case 0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if(InventorySize(&INVENTORY(*m))==5){
				printf("Inventory anda penuh\n");
				return;
			}
			if(BALANCE(*m)>=GADGETPRICE(INVENTORY(*m),cmd-1)){
				UpdateItem(&INVENTORY(*m),cmd-1,1);
				BALANCE(*m)-=GADGETPRICE(INVENTORY(*m),cmd-1);
				printf("Transaksi berhasil. Uang anda sekarang adalah %d yen\n",BALANCE(*m));
			}else{
				printf("Uang anda tidak mencukupi\n");
			}
			break;
		default:
			printf("Command tidak valid\n");
	}
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

void CommandSave(Mobita *m){
	/* Get File Name*/
	char* in=malloc(50*sizeof(char));
	printf("Masukkan nama file: ");
	scanf("%s",&in);
	char* filename=malloc(50*sizeof(char));
	strcpy(filename,"Savefiles/");
	strcat(filename,in);
	strcat(filename,".mob");
	FILE* fp;
	fp=fopen(filename,"w");
	
	/* Normal Config File */
	// Map Size
	fprintf(fp,"%d %d\n",ROWS(MAP(*m)),COLS(MAP(*m)));
	// HQ Coords
	// TBD
	// Locations
	int n=NEFF(BUILDINGLIST(*m));
	fprintf(fp,"%d\n",n);
	int i;
	for(i=0;i<n;i++){
		Location temp=LOC(BUILDINGLIST(*m),i);
		fprintf(fp,"%c %d %d\n",NAME(temp),POINT(temp).x,POINT(temp).y);
	}
	// AdjMat
	int j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fprintf(fp,"%d ",ADJ(ADJMAT(*m),i,j));
		}
		fprintf(fp,"\n");
	}
	// Pesanan
	// TBD
	
	/* EXTRAS */
	// Time
	// TBD
	// Ability Status
	// TBD
	// Balance
	fprintf(fp,"%d\n",BALANCE(*m));
	// Location (Building Name, X, Y)
	Location temp=LOCATION(*m);
	fprintf(fp,"%c %d %d\n",NAME(temp),POINT(temp).x,POINT(temp).y);
	// To Do list
	// TBD
	// In Progress List
	// TBD
	// Inventory
	for(i=0;i<5;i++){
		fprintf(fp,"%d ",GADGETOWNED(INVENTORY(*m),i));
	}
	fprintf(fp,"\n");
	fclose(fp);
}

void CommandLoad(Mobita *m){
	/* Get File Name */
	char* in=malloc(50*sizeof(char));
	printf("Masukkan nama file: ");
	scanf("%s",&in);
	char* filename=malloc(50*sizeof(char));
	strcpy(filename,"Savefiles/");
	strcat(filename,in);
	strcat(filename,".mob");
	FILE* fp;
	if(access(filename,R_OK)==0){
    	fp=fopen(filename,"r");
	}else{
    	printf("Savefile doesn't exist\n");
    	return;
	}	
	/* Normal File */
	// CommandNewGame(m);
	
	/* Extras */
	// Time
	// TBD
	// Ability Status
	// TBD
	// Balance
	fscanf(fp,"%d",&BALANCE(*m));
	// Location (Building Name, X, Y)
	fscanf(fp,"%c %d %d",&NAME(LOCATION(*m)),&POINT(LOCATION(*m)).x,&POINT(LOCATION(*m)).y);
	// To Do list
	// TBD
	// In Progress List
	// TBD
	// Inventory
	int i;
	for(i=0;i<5;i++){
		fscanf(fp,"%d",&GADGETOWNED(INVENTORY(*m),i));
	}
	fclose(fp);
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

