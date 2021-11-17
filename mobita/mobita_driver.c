#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mobita.h"
#include "../utilities/boolean.h"
#include "../mesin/charmachine.h"
#include "../mesin/configmachine.h"
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

int main(){
	globalTime = 0;
	Mobita m;
	CreateMobita(&m);
	UpdateItem(&INVENTORY(m),2,5);
	CommandInventory(&m);
	BALANCE(m)=2002;
	CommandBuy(&m);
	CommandInventory(&m);
}
