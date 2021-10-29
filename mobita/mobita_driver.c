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

int main(){
	Mobita m;
	CreateMobita(&m);
	UpdateItem(&INVENTORY(m),2,5);
	CommandInventory(&m);
	BALANCE(m)=2002;
	CommandBuy(&m);
	CommandInventory(&m);
}
