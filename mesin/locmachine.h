/* DEFINISI MESIN BACA LOKASI */
#ifndef LOCMACHINE_H
#define LOCMACHINE_H

#include "../utilities/boolean.h"
#include "../point/location.h"
#include "../pesanan/pesanan.h"
#include "../pesanan/queuepesanan.h"
#include "charmachine.h"

#define BLANK ' '
#define NEWLINE '\n'
#define TAB '\t'
#define NUM_CAP 50

/* STATE MACHINE */
extern int readLocCounter;
extern boolean endReadLoc;
extern Location currentLoc;

/* MACHINE PROGRAM */
void ignoreWhiteSpace();
/* Mengabaikan BLANK, NEWLINE, dan TAB */
void startReadLoc();
/* Mulai readloc, inisialisasi readLocCounter dan endReadLoc */
void advReadLoc();
/* Baca lokasi selanjutnya, selesai jika counter <= 0 */
void copyCurrentLoc();
/* Menyalin lokasi ke currentLoc */

/* SUPPORTING FUNCTIONS */
int charToInt(char cc); // convert char to integer
int readInt();          // baca char >= 2 digit, langsung jadi integer

#endif