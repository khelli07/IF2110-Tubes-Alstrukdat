/* DEFINISI MESIN BACA LOKASI */
#ifndef LOCMACHINE_H
#define LOCMACHINE_H

#include "../utilities/boolean.h"
#include "../point/location.h"
#include "charmachine.h"

#define BLANK ' '
#define NEWLINE '\n'
#define NUM_CAP 50

/* STATE MACHINE */
extern int readLocCounter;
extern boolean endReadLoc;
extern Location currentLoc;

/* MACHINE PROGRAM */
void ignoreBlank();

void startReadLoc();

void advReadLoc();

void copyCurrentLoc();

/* SUPPORTING FUNCTIONS */
int charToInt(char cc);
int readInt();

#endif