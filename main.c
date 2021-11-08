#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utilities/boolean.h"
#include "utilities/pcolor.h"
#include "mesin/charmachine.h"
#include "mesin/wordmachine.h"
#include "mesin/locmachine.h"
#include "point/location.h"
#include "list_linked/linked_list_to_do.h"
#include "list_linked/linked_list_in_progress.h"
#include "list_biasa/gadgetlist.h"
#include "list_biasa/dynamiclist.h"
#include "matriks/adjmat.h"
#include "matriks/map.h"
#include "tas/stack.h"
#include "pesanan/pesanan.h"
#include "pesanan/queuepesanan.h"
#include "point/location.h"
#include "point/point.h"
#include "mobita/mobita.h"
#include "list_linked/node.h"

int getCmd(int range){
	printf("\nEnter Command: ");
	int ret;
	scanf("%d",ret);
	if(ret>range||ret<1){
		printf("Command tidak valid\n");
		return getCmd(range);
	}
	return ret;
}

void printCmd(){
	printf("Waktu sekarang adalah %d\n",globalTime);
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

void UpdatePesanan(Mobita *m){
	int cnt=0;
	while(!isQueueEmpty(daftarPesanan)&&HEADQUEUE(daftarPesanan).waktuIn<=globalTime){
		Pesanan k;
		dequeue(&daftarPesanan,&k);
		insertFirstToDo(&TODO(*m),k);
		cnt++;
	}
	if(cnt>0)printf("Anda mendapatkan %d pesanan baru!\n",cnt);
}

int main(){
	Mobita m;
	CreateMobita(&m);
	printf("Selamat datang di permainan Mobilita!\n");
	printf("1. New Game\n");
	printf("2. Load Game\n");
	printf("3. Exit\n");
	int cmd=getCmd(3);
	switch(cmd){
		case 1:
			CommandNewGame(&m);
			break;
		case 2:
			CommandLoad(&m);
			break;
		case 3:
			return 0;
		}
	while(cmd!=13){
		UpdatePesanan(&m);
		printCmd();
		cmd=getCmd(13);
		switch(cmd){
			case 1:
				CommandMove(&m);
				break;
			case 2:
				CommandPickup(&m);
				break;
			case 3:
				CommandDropoff(&m);
				break;
			case 4:
				CommandToDo(&m);
				break;
			case 5:
				CommandInProgress(&m);
				break;
			case 6:
				//CommandMap(&m);
				break;
			case 7:
				CommandBuy(&m);
				break;
			case 8:
				CommandInventory(&m);
				break;
			case 9:
				CommandBalance(&m);
				break;
			case 10:
				//CommandReturn(&m);
				break;
			case 11:
				CommandHelp();
				break;
			case 12:
				CommandSave(&m);
				break;
			default:
				break;
			}
	}
	printf("Thank You For Playing\n");
	return 0;
}
