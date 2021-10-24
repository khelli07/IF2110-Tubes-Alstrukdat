/* DEFINISI MESIN BACA LOKASI */
#ifndef LOCMACHINE_H
#define LOCMACHINE_H

#include "../utilities/boolean.h"
#include "../adt_point/location.h"
#include "charmachine.h"

#define BLANK ' '
#define NEWLINE '\n'
#define NUM_CAP 50

/* STATE MACHINE */
extern int readLocCounter;
extern boolean endReadLoc;
extern Location currentLoc;

/* COMMAND */
void ignoreBlank();

void startReadLoc();

void advReadLoc();

void copyCurrentLoc();

#endif