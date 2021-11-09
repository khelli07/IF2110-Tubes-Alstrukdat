#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mobita.h"
#include "../utilities/boolean.h"
#include "../mesin/charmachine.h"
#include "../mesin/locmachine.h"
#include "../mesin/wordmachine.h"
#include "../point/location.h"
#include "../list_linked/linked_list_to_do.h"
#include "../list_linked/linked_list_in_progress.h"
#include "../list_biasa/gadgetlist.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
#include "../matriks/map.h"
#include "../tas/stack.h"
#include "../pesanan/pesanan.h"
#include "../pesanan/queuepesanan.h"
#include "../point/location.h"
#include "../point/point.h"
#include "../list_linked/node.h"

/* VARIABLES */

int globalTime=0;
// Tas capacity sudah ada di Mobita
QueuePesanan daftarPesanan;
int delivered=0;

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
    CreateStack(&TAS(*m)); // empty stack
    //CreateAdjMat(&adj);
    //CreateMap(&map);
    
    TASCAPACITY(*m)=3;
    (*m).speedBoostAbility=0;
    (*m).returnToSenderAbility=0;
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
	int i;
	for(i = 0; i < NEFF(accesibleloc); i++){
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
	Pesanan temp;
	i = 0;
	while(i < lengthInProgress(INPROGRESS(*m)) && isPesananExpired(getPesananInProgress(INPROGRESS(*m), i))){	// isPesananExpired return false jika bukan perishable
		pop(&TAS(*m), &temp);
		deleteFirstInProgress(&INPROGRESS(*m), &temp);
		i++;
	}

	if(!isEmpty(TAS(*m)))
		updateLocationColor(m, LokasiDropOff(TOP(TAS(*m))));	// Update warna lokasi drop off selanjutnya

	// Mengupdate warna lokasi yang aksesibel menjadi hijau
	dealocate(&accesibleloc);
	accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	for(i = 0; i < NEFF(accesibleloc); i++){
		if(COLOR(LOC(accesibleloc, i)) == HI)
			setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOC(accesibleloc, i), G);
	}

	// Mengupdate warna lokasi sebelumnya dan sekarang
	/*
	displayLoc(prevloc); printf("\n"); displayLoc(LOCATION(*m)); printf("\n");
	printf("%d\n", COLOR(prevloc));
	*/
	updateLocationColor(m, prevloc);
	updateLocationColor(m, LOCATION(*m));
	dealocate(&accesibleloc);
	printf("Mobita sekarang berada di titik "); displayLoc(LOCATION(*m)); printf("\n");
}

void updateLocationColor(Mobita* m, Location loc){
	if(isLocEqual(loc, LOCATION(*m))){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, O);
		return;
	}
	if(!isEmpty(TAS(*m)) && isLocEqual(loc, LokasiDropOff(TOP(TAS(*m))))){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, B);
		return;
	}
	if(!isToDoEmpty(TODO(*m)) && isLocationHasToDo(TODO(*m), loc)){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, R);
		return;
	}
	if(COLOR(loc) == G){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, G);
		return;
	}
	setLocationColor(&PETA(*m), &BUILDINGLIST(*m), loc, HI);
}


int getInputCommand(char msg[], int n){
	printf(msg);
	printf(" (ketik 0 jika ingin kembali)\n");
	printf("Enter Command: ");
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
			insertLastToDo(&pesananInLocation, getPesananToDo(todoPesanan, i));
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
		int i = indexOfPesananToDo(TODO(*m), firstPesanan);
		if(i == -1){
			printf("Error tak terduga terjadi\n");
			return;
		}
		insertFirstInProgress(&INPROGRESS(*m), firstPesanan);
		if(!isEmpty(TAS(*m))){
			Location prev = LokasiDropOff(TOP(TAS(*m)));
			push(&TAS(*m), firstPesanan);
			updateLocationColor(m, prev);
		} else{
			push(&TAS(*m), firstPesanan);
		}
		Pesanan temp;
		deleteAtToDo(&TODO(*m), i, &temp);
		updateLocationColor(m, LokasiDropOff(firstPesanan));

		printf("Pesanan berupa %s Item berhasil diambil!\n", getJenisItemString(firstPesanan));
		printf("Tujuan Pesanan: %c\n", NAME(LokasiDropOff(firstPesanan)));
	}
}

void CommandDropoff(Mobita* m){
	if(isEmpty(TAS(*m))){
		printf("Tidak ada pesanan yang dapat diantarkan (Tas kosong)\n");
		return;
	}
	if(!isLocEqual(LOCATION(*m), LokasiDropOff(TOP(TAS(*m))))){
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
	delivered++;
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

void CommandMap(Mobita* m){
	setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOCATION(*m), O);
	displayMap(PETA(*m));
	setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOCATION(*m), HI);
}

void CommandBuy(Mobita* m){
	//if not in HQ, return
	if(LOCATION(*m).buildingName!='8'){
		printf("Shop hanya dapat diakses di HQ!\n");
		return;
	}
	printf("Uang anda sekarang: %d yen\n",BALANCE(*m));
	printf("Mobita HQ Shop:\n");
	DisplayShop(&INVENTORY(*m));
	printf("Gadget mana yang ingin dibeli? (ketik 0 untuk kembali)\n\n");
	printf("Enter Command: ");
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
	printf("Enter Command: ");
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

void CommandHelp(){
	printf("Command List\n");
	printf("1. Move\n");
	printf("2. Pick Up\n");
	printf("3. Drop Off\n");
	printf("4. To Do List\n");
	printf("5. In Progress List\n");
	printf("6. Map\n");
	printf("7. Shop\n");
	printf("8. Inventory\n");
	printf("9. Balance\n");
	printf("10. Return\n");
	printf("11. Help\n");
	printf("12. Save\n");
	printf("13. Exit\n");
}

void CommandNewGame(Mobita* m){
    /* KAMUS LOKAL */
    int mrow, mcol, px, py, N;
    int timeIn, timeoutPerish;
    char pickUpCC, dropOffCC;

    JenisItem itemType;
    Location HQ, pickUpLoc, dropOffLoc;
    Pesanan currentPesanan;
    QueuePesanan qPesanan;
    DynamicList locList;
    AdjMatrix adjMat;
    Map map;

    /* ALGORITMA */
    char input[50] = "";
    printf("Masukkan nama file kamu: ");
    scanf("%s", &input);
    startReadFile(input);
    
    // BACA MAP
    mrow = readInt();
    mcol = readInt();
    CreateMap(&map, mrow, mcol);

    // BACA HEADQUARTER
    px = readInt();
    py = readInt();
    CreateLocation(&HQ, px, py, '8');
    LOCATION(*m)=HQ;
    setBuilding(&map, HQ);

    startReadLoc();
    CreateDynamicList(&locList, readLocCounter);
    insertLoc(&locList, HQ);
    while (!endReadLoc)
    {
        insertLoc(&locList, currentLoc);
        setBuilding(&map, currentLoc);
        advReadLoc();
    }

    // READ ADJ MATRIX
    N = countBuilding(locList);
    CreateAdjMatrix(&adjMat, N);
    readAdjMatrix(&adjMat, N);

    CreateQueue(&qPesanan);
    ignoreWhiteSpace();
    N = readInt();
    while (N != 0)
    {
    	timeoutPerish=0;
        ignoreWhiteSpace();
        timeIn = readInt();
        ignoreWhiteSpace();
        pickUpCC = currentChar;
        advReadFile();
        ignoreWhiteSpace();
        dropOffCC = currentChar;
        advReadFile();
        ignoreWhiteSpace();
        itemType = charToJenisItem(currentChar);
        advReadFile();

        pickUpLoc = getLoc(locList, pickUpCC);
        dropOffLoc = getLoc(locList, dropOffCC);
        if (itemType == PERISHABLE)
        {
            timeoutPerish = readInt();
            CreatePesananPerish(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn, timeoutPerish);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
        else
        {
            CreatePesanan(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
        //printf("%c %c %d %d\n",pickUpLoc.buildingName,dropOffLoc.buildingName,timeIn,timeoutPerish);
    }

    sortQueue(&qPesanan);
    endReadFile();
    printf("Read file done!\n");

    daftarPesanan = qPesanan;
	CreateToDoList(&TODO(*m));
	CreateInProgressList(&INPROGRESS(*m));
	CreateStack(&TAS(*m));
    BUILDINGLIST(*m) = locList;
    ADJMAT(*m) = adjMat;
    PETA(*m) = map;
	updateLocationColor(m, LOCATION(*m));
	DynamicList accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	for(int i = 0; i < NEFF(accesibleloc); i++){
		if(COLOR(LOC(accesibleloc, i)) == HI)
			setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOC(accesibleloc, i), G);
	}
}


void CommandSave(Mobita *m){
	/* Get File Name*/
	char in[50]="";
	printf("Masukkan nama file: ");
	scanf("%s",&in);
	char filename[50]="";
	strcpy(filename,"Savefiles/");
	strcat(filename,in);
	strcat(filename,".mob");
	FILE* fp;
	fp=fopen(filename,"w");
	
	/* Normal Config File */
	// Map Size
	fprintf(fp,"%d %d\n",ROWS(PETA(*m)),COLS(PETA(*m)));
	// HQ Coords
	int n=NEFF(BUILDINGLIST(*m));
	int i;
	for(i=0;i<n;i++){
		Location temp=LOC(BUILDINGLIST(*m),i);
		if(NAME(temp)!='8')continue;
		fprintf(fp,"%d %d\n",POINT(temp).x,POINT(temp).y);
	}
	// Locations
	n=NEFF(BUILDINGLIST(*m));
	fprintf(fp,"%d\n",n-1);
	for(i=0;i<n;i++){
		Location temp=LOC(BUILDINGLIST(*m),i);
		if(NAME(temp)=='8')continue;
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
	n=lengthQueue(daftarPesanan);
	fprintf(fp,"%d\n",n);
	if(n>0)for(i=daftarPesanan.idxHead;i<=daftarPesanan.idxTail;i++){
		int in=daftarPesanan.buffer[i].waktuIn;
		char start=daftarPesanan.buffer[i].pickUp.buildingName;
		char end=daftarPesanan.buffer[i].dropOff.buildingName;
		char type=getJenisItemChar(daftarPesanan.buffer[i]);
		int timer=daftarPesanan.buffer[i].timeoutInitial;
		fprintf(fp,"%d %c %c %c ",in,start,end,type);
		if(type=='P')fprintf(fp,"%d",timer);
		fprintf(fp,"\n");
	}
	/* EXTRAS */
	// Time
	fprintf(fp,"%d\n",globalTime);
	// Ability Status
	fprintf(fp,"%d %d\n",(*m).speedBoostAbility,(*m).returnToSenderAbility);
	// Balance
	fprintf(fp,"%d\n",BALANCE(*m));
	// Bag Capacity
	fprintf(fp,"%d\n",TASCAPACITY(*m));
	// Location (Building Name, X, Y)
	Location temp=LOCATION(*m);
	fprintf(fp,"%c %d %d\n",NAME(temp),POINT(temp).x,POINT(temp).y);
	// To Do list
	n=lengthToDo(TODO(*m));
	fprintf(fp,"%d\n",n);
	for(i=0;i<n;i++){
		int startx=getPesananToDo(TODO(*m),i).pickUp.point.x;
		int starty=getPesananToDo(TODO(*m),i).pickUp.point.y;
		char startc=getPesananToDo(TODO(*m),i).pickUp.buildingName;
		int endx=getPesananToDo(TODO(*m),i).dropOff.point.x;
		int endy=getPesananToDo(TODO(*m),i).dropOff.point.y;
		char endc=getPesananToDo(TODO(*m),i).dropOff.buildingName;
		int in=getPesananToDo(TODO(*m),i).waktuIn;
		int price=getPesananToDo(TODO(*m),i).price;
		int timernow=getPesananToDo(TODO(*m),i).timeout;
		int timerori=getPesananToDo(TODO(*m),i).timeoutInitial;
		char type=getJenisItemChar(getPesananToDo(TODO(*m),i));
		fprintf(fp,"%d %d %c %d %d %c %d %d %d %d %c\n",startx,starty,startc,endx,endy,endc,in,price,timernow,timerori,type);
	}
	// In Progress List
	n=lengthInProgress(INPROGRESS(*m));
	fprintf(fp,"%d\n",n);
	for(i=0;i<n;i++){
		int startx=getPesananInProgress(INPROGRESS(*m),i).pickUp.point.x;
		int starty=getPesananInProgress(INPROGRESS(*m),i).pickUp.point.y;
		char startc=getPesananInProgress(INPROGRESS(*m),i).pickUp.buildingName;
		int endx=getPesananInProgress(INPROGRESS(*m),i).dropOff.point.x;
		int endy=getPesananInProgress(INPROGRESS(*m),i).dropOff.point.y;
		char endc=getPesananInProgress(INPROGRESS(*m),i).dropOff.buildingName;
		int in=getPesananInProgress(INPROGRESS(*m),i).waktuIn;
		int price=getPesananInProgress(INPROGRESS(*m),i).price;
		int timernow=getPesananInProgress(INPROGRESS(*m),i).timeout;
		int timerori=getPesananInProgress(INPROGRESS(*m),i).timeoutInitial;
		char type=getJenisItemChar(getPesananInProgress(INPROGRESS(*m),i));
		fprintf(fp,"%d %d %c %d %d %c %d %d %d %d %c\n",startx,starty,startc,endx,endy,endc,in,price,timernow,timerori,type);
	}
	// Inventory
	for(i=0;i<5;i++){
		fprintf(fp,"%d ",GADGETOWNED(INVENTORY(*m),i));
	}
	fprintf(fp,"\n");
	fclose(fp);
}

int CommandLoad(Mobita *m){
	/* Get File Name*/
	char in[50]="";
	printf("Masukkan nama file: ");
	scanf("%s",&in);
	char filename[50]="";
	strcpy(filename,"Savefiles/");
	strcat(filename,in);
	strcat(filename,".mob");
	FILE* fp;	
	
	if(access(filename,R_OK)==0){
    	startReadFile(filename);
	}else{
    	printf("Savefile doesn't exist\n");
    	return 0;
	}
	/* Normal File */
	    /* KAMUS LOKAL */
    int mrow, mcol, px, py, N;
    int timeIn, timeoutPerish;
    char pickUpCC, dropOffCC;

    JenisItem itemType;
    Location HQ, pickUpLoc, dropOffLoc;
    Pesanan currentPesanan;
    QueuePesanan qPesanan;
    DynamicList locList;
    AdjMatrix adjMat;
    Map map;
    
    
    // BACA MAP
    mrow = readInt();
    mcol = readInt();
    CreateMap(&map, mrow, mcol);

    // BACA HEADQUARTER
    px = readInt();
    py = readInt();
    CreateLocation(&HQ, px, py, '8');
    LOCATION(*m)=HQ;
    setBuilding(&map, HQ);

    startReadLoc();
    CreateDynamicList(&locList, readLocCounter);
    insertLoc(&locList, HQ);
    while (!endReadLoc)
    {
        insertLoc(&locList, currentLoc);
        setBuilding(&map, currentLoc);
        advReadLoc();
    }

    // READ ADJ MATRIX
    N = countBuilding(locList);
    CreateAdjMatrix(&adjMat, N);
    readAdjMatrix(&adjMat, N);

    CreateQueue(&qPesanan);
    ignoreWhiteSpace();
    N = readInt();
    while (N != 0)
    {
        ignoreWhiteSpace();
        timeIn = readInt();
        ignoreWhiteSpace();
        pickUpCC = currentChar;
        advReadFile();
        ignoreWhiteSpace();
        dropOffCC = currentChar;
        advReadFile();
        ignoreWhiteSpace();
        itemType = charToJenisItem(currentChar);
        advReadFile();

        pickUpLoc = getLoc(locList, pickUpCC);
        dropOffLoc = getLoc(locList, dropOffCC);
        if (itemType == PERISHABLE)
        {
            timeoutPerish = readInt();
            CreatePesananPerish(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn, timeoutPerish);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
        else
        {
            CreatePesanan(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
    }

    sortQueue(&qPesanan);

    daftarPesanan = qPesanan;
    BUILDINGLIST(*m) = locList;
    ADJMAT(*m) = adjMat;
    PETA(*m) = map;
	
	fp=file;
	/* Extras */
	// Time
	fscanf(fp,"%d",&globalTime);
	// Ability Status
	fscanf(fp,"%d %d",&(*m).speedBoostAbility,&(*m).returnToSenderAbility);
	// Balance
	fscanf(fp,"%d",&BALANCE(*m));
	// Bag Capacity
	fscanf(fp,"%d",&TASCAPACITY(*m));
	// Location (Building Name, X, Y)
	char dump;
	fscanf(fp,"%c",&dump);
	fscanf(fp,"%c %d %d",&(NAME(LOCATION(*m))),&(POINT(LOCATION(*m)).x),&(POINT(LOCATION(*m)).y));
	// To Do list
	int i,n;
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++){
		int startx,starty,endx,endy,in,price,timernow,timerori;
		char startc,endc,type;
		fscanf(fp,"%d %d %c %d %d %c %d %d %d %d %c",&startx,&starty,&startc,&endx,&endy,&endc,&in,&price,&timernow,&timerori,&type);
		Pesanan item;
		item.pickUp.point.x=startx;
		item.pickUp.point.y=starty;
		item.pickUp.buildingName=startc;
		item.dropOff.point.x=endx;
		item.dropOff.point.y=endy;
		item.dropOff.buildingName=endc;
		item.waktuIn=in;
		item.price=price;
		item.timeout=timernow;
		item.timeoutInitial=timerori;
		item.jenisItem=charToJenisItem(type);
		insertLastToDo(&TODO(*m),item);
	}
	// In Progress List
	n=0;
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++){
		int startx,starty,endx,endy,in,price,timernow,timerori;
		char startc,endc,type;
		fscanf(fp,"%d %d %c %d %d %c %d %d %d %d %c",&startx,&starty,&startc,&endx,&endy,&endc,&in,&price,&timernow,&timerori,&type);
		Pesanan item;
		item.pickUp.point.x=startx;
		item.pickUp.point.y=starty;
		item.pickUp.buildingName=startc;
		item.dropOff.point.x=endx;
		item.dropOff.point.y=endy;
		item.dropOff.buildingName=endc;
		item.waktuIn=in;
		item.price=price;
		item.timeout=timernow;
		item.timeoutInitial=timerori;
		item.jenisItem=charToJenisItem(type);
		insertLastInProgress(&INPROGRESS(*m),item);
		push(&TAS(*m),item);
	}
	// Inventory
	for(i=0;i<5;i++){
		fscanf(fp,"%d",&GADGETOWNED(INVENTORY(*m),i));
	}
	fclose(fp);
	
	// COLORS!!!!
	
	// Green
	DynamicList accesibleloc = getAccLoc(ADJMAT(*m), BUILDINGLIST(*m), LOCATION(*m));
	displayLocList(accesibleloc);
	printf("\n");

	for(i = 0; i < NEFF(accesibleloc); i++){
		setLocationColor(&PETA(*m), &BUILDINGLIST(*m), LOC(accesibleloc, i), G);
	}
	
	// The Rest
	for(i=0;i<NEFF(BUILDINGLIST(*m));i++){
		updateLocationColor(m,LOC(BUILDINGLIST(*m),i));
	}
	
	// Blue da bi da
	setLocationColor(&PETA(*m), &BUILDINGLIST(*m), TOP(TAS(*m)).dropOff, B);
	return 1;
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
	printf("\nEnter Command: ");
	int in=0;
	scanf("%d",&in);
	while(in<1&&in>countBuilding(BUILDINGLIST(*m))){
		printf("Masukan tidak valid\n Enter Command: ");
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

