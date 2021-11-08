#ifndef CHAR_ENGINE_H
#define CHAR_ENGINE_H

#include "../utilities/boolean.h"
#include <stdio.h>

#define MARK '#'
/* Char Engine State */
extern char currentChar;
extern boolean eot;

extern FILE* file;

void start();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void adv();
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
          Jika  currentChar = MARK maka EOP akan menyala (true) */
void end();

void startReadFile(char *filename);
void advReadFile();
void endReadFile();

#endif
