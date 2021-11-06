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

int globalTime=0;
// Tas capacity sudah ada di Mobita
List daftarPesanan;

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
	DynamicList accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	printf("Posisi yang dapat dicapai:\n");
	displayLocList(accesibleloc);
	printf("\n");

	int command = getInputCommand("Posisi yang dipilih?", NEFF(accesibleloc));
	if(command == 0){
		printf("Dibatalkan!\n");
		return;
	}

	// Mengganti warna accessible location sebelumnya dari hijau ke hitam (tidak mengupdate jika ada pickup/dropoff di sana)
	for(int i = 0; i < NEFF(accesibleloc); i++){
		if(COLOR(LOC(accesibleloc, i)) == G )
			setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOC(accesibleloc, i), HI);
	}

	// Menyimpan lokasi sebelumnya dan mengupdate lokasi sekarang
	Location prevloc = LOCATION(*m);
	LOCATION(*m) = LOC(accesibleloc, command - 1);

	// Menambahkan waktu berdasarkan jenis item
	int timeincrement = 0;
	int itemcounts[JENISITEMCOUNT];
	countStackByJenisItem(TAS(*m), itemcounts);
	if(itemcounts[HEAVY] > 0){
		timeincrement = 1 + itemcounts[HEAVY];
		m->speedBoostAbility = -1;
	} else if(m->speedBoostAbility > 0){
		if(m->speedBoostAbility % 2 == 1){
			timeincrement = 1;
		}
		m->speedBoostAbility -= 1;
	} else{
		timeincrement = 1;
	}
	globalTime += timeincrement;

	// Mengurangi waktu perishable di InProgress, menghapus yang terdepan di InProgress dan teratas di tas jika expired
	reduceTimeoutPerishInProgress(&INPROGRESS(*m), timeincrement);
	int i = 0;
	Pesanan temp;
	while(isPesananExpired(getPesananInProgress(INPROGRESS(*m), i))){	// isPesananExpired return false jika bukan perishable
		pop(&TAS(*m), &temp);
		deleteFirstInProgress(&INPROGRESS(*m), &temp);
		i++;
	}
	updateTodoFromQueue(m);

	// Mengupdate warna sekarang lokasi yang aksesibel menjadi hijau
	accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	for(int i = 0; i < NEFF(accesibleloc); i++){
		if(COLOR(LOC(accesibleloc, i)) == HI)
			setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOC(accesibleloc, i), G);
	}

	// Mengupdate warna lokasi sebelumnya dan sekarang
	updateLocationColor(m, prevloc);
	updateLocationColor(m, LOCATION(*m));

	printf("Mobita sekarang berada di titik "); displayLoc(LOCATION(*m)); printf("\n");
	printf("Waktu: %d\n", globalTime);
}

void updateLocationColor(Mobita* m, Location loc){
	if(isLocEqual(loc, LOCATION(*m))){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, O);
		return;
	}
	if(isLocEqual(loc, LokasiDropOff(TOP(TAS(*m))))){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, B);
		return;
	}
	if(isLocationHasToDo(TODO(*m), loc)){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, R);
	}
	if(COLOR(loc) == G){
		return;
	}
	setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, HI);
}

void updateTodoFromQueue(Mobita* m){
	if(isQueueEmpty(QUEUEPESANAN(*m)))
		return;
	while(WaktuIn(HEADQUEUE(QUEUEPESANAN(*m))) <= globalTime){
		Pesanan pesanan;
		dequeue(&QUEUEPESANAN(*m), &pesanan);
		insertLastToDo(&TODO(*m), pesanan);
	}
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
	if(lengthInProgress(INPROGRESS(*m)) >= TASCAPACITY(*m)){
		printf("Tas sudah penuh! Antarkan dulu pesanan di tas\n");
		return;
	}
	Location currentLoc = LOCATION(*m);
	int todolength = lengthToDo(TODO(*m));
	List todoPesanan = TODO(*m);
	List pesananInLocation;
	CreateToDoList(&pesananInLocation);
	int i=0;
	for(i = 0; i < todolength; i++){
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
		for(i=1; i<inloclength; i++){
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

void CommandDropoff(Mobita* m){
	if(isEmpty(TAS(*m))){
		printf("Tidak ada pesanan yang dapat diantarkan (Tas kosong)\n");
		return;
	}
	if(!IsLocEqual(LOCATION(*m), LokasiDropoff(TOP(TAS(*m))))){
		printf("Pesanan teratas tidak diantarkan ke sini!\n");
		return;
	}

	Pesanan toppesanan;
	deleteFirstInProgress(&INPROGRESS(*m), &toppesanan);
	pop(&TAS(*m), &toppesanan);
	BALANCE(*m) += Price(toppesanan);
	if(!isEmpty(TAS(*m)))
		updateLocationColor(m, LokasiDropOff(TOP(TAS(*m))));	// Update warna lokasi drop off selanjutnya

	switch (JenisItem(toppesanan)){
	case PERISHABLE:
		TASCAPACITY(*m) += 1;
		break;
	case VIP:
		m->returnToSenderAbility = true;
		break;
	}

	printf("Pesanan %s Item berhasil diantarkan\n", getJenisItemString(toppesanan));
	printf("Uang yang didapatkan: %d Yen\n", Price(toppesanan));
}

void CommandToDo(Mobita* m) {
	List l;
	l = TODO(*m);
	displayToDoList(l);
}

void CommandInProgress(Mobita *m) {
	List l;
	l = INPROGRESS(*m);
	displayInProgressList(l);
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
	fprintf(fp,"%d %d\n",ROWS(PETA(*m)),COLS(PETA(*m)));
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

void CommandBalance(Mobita* m){
	printf("Uang anda sekarang adalah: %d\n",BALANCE(*m));
}

/* INTERNAL COMMANDS */
boolean UseKainWaktu(Mobita *m){
	if(!isEmpty(TAS(*m))&&TOP(TAS(*m)).jenisItem==PERISHABLE)TOP(TAS(*m)).timeout=TOP(TAS(*m)).timeoutInitial;
	printf("Kain Waktu berhasil digunakan!\n");
	printf("Karena senang deadline delivery diperpanjang, anda melempar kain tersebut dan melupakannya di pinggir jalan\n");
	return 1;
}

boolean UseSenterPembesar(Mobita *m){
	TASCAPACITY(*m) *= 2;
	if(TASCAPACITY(*m) > 100) TASCAPACITY(*m) = 100;
	printf("Senter Pembesar berhasil digunakan! Kapasitas tas sekarang adalah %d\n", TASCAPACITY(*m));
	printf("Sayangnya, senter tersebut kehabisan baterai, dan anda memutuskan untuk membuangnya\n");
	return 1;
}

boolean UsePintuKemanaSaja(Mobita *m){
	printf("Pilih destinasi Pintu Kemana Saja: ");
	displayLocList(BUILDINGLIST(*m));
	pritnf("\nENTER COMMAND: ");
	int in=0;
	scanf("%d",&in);
	while(in<1&&in>countBuilding(BUILDINGLIST(*m))){
		printf("Masukan tidak valid\n ENTER COMMAND: ");
		scanf("%d",&in);
	}
	LOCATION(*m)=LOC(BUILDINGLIST(*m),in-1);
	printf("Anda membuka pintu kemana saja, dan mencapai lokasi ");
	displayLoc(LOCATION(*m));
	printf("\n");
	printf("Namun, sesampainya disana pintu anda dicuri Suneo\n");
	return 1;
}

boolean UseMesinWaktu(Mobita *m){
	globalTime-=50;
	if(globalTime<0)globalTime=0;
	printf("Mesin Waktu berhasil digunakan! Waktu sekarang adalah %d\n",globalTime);
	printf("Doraemon kemudian datang dan menggunakan mesin waktu anda untuk kembali ke masa depan\n");
	return 1;
}

boolean UseSenterPengecil(Mobita *m){
	if(!isEmpty(TAS(*m))&&TOP(TAS(*m)).jenisItem==HEAVY)TOP(TAS(*m)).jenisItem=NORMAL;
	printf("Senter pengecil berhasil digunakan!\n");
	printf("Senter tersebut juga ikut mengecil sampai tidak dapat digunakan lagi\n");
	return 1;
}

