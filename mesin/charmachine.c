/* File: charmachine.c */
/* Implementasi Character Engine */

#include "charmachine.h"
#include <stdio.h>

char currentChar;
boolean eot;

static FILE *tape;
static int retval;

void start(char *filename)
{
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    tape = fopen(filename, "r");
    adv();
}

void adv()
{
    /* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(tape, "%c", &currentChar);
    // eot = (currentChar == MARK);
    // if (eot)
    // {
    //     fclose(tape);
    // }
}

void end()
{
    // close manual
    fclose(tape);
}