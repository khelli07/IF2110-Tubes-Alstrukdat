#include <stdio.h>
#include <stdlib.h>
#include "mobita.h"
#include "../utilities/boolean.h"
#include "../point/location.h"
//#include "../ability/ability.h"
//#include "../linkedlist/linkedlist.h"
//#include "../staticlist/staticlist.h"
//#include "../dynamiclist/dynamiclist.h"
//#include "../adjmat/adjmat.h"
//#include "../map/map.h"

/* KONSTRUKTOR */
void CreateMobita(Mobita *m)
{
    //Creates base mobita
    BALANCE(*m) = 0;
    LOCATION(*m) = {1, 1}; //will be switched to hq coords
    ABILITY(*m) = 0;       //will be switched to default ability
    TODO(*m) = NULL;       //empty linked list
    INPROGRESS(*m) = NULL; //empty linked list
    StaticList s;
    CreateStaticList(&s);
    INVENTORY(*m) = s; //empty static list
    DynamicList d;
    CreateDynamicList(&d);
    BUILDINGLIST(*m) = d;
    Adjmat adj;
    CreateAdjMat(&adj);
    ADJMAT(*m) = adj;
    Map map;
    CreateMap(&map)
        MAP(*m) = map;
}
