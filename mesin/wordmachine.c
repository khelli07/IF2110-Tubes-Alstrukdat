#include <stdio.h>
#include "wordmachine.h"
#include <stdlib.h>

/* Word Engine State */
boolean endWord;
Word currentWord;

void ignoreBlank()
{
    while (currentChar == BLANK || currentChar == TAB)
    {
        adv();
    }
}

void startWord()
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    start();
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        copyWord();
    }
    /* I.S. : currentChar sembarang 
    F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
}

void advWord()
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        copyWord();
    }

    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi 
    F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
    Proses : Akuisisi kata menggunakan procedure copyWord */
}

void copyWord()
{
    /* KAMUS LOKAL */
    int i;
    /* ALGORITMA */
    i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK))
    {
        if (i < CAPACITY_WORD)
        {
            currentWord.contents[i] = currentChar;
        }
        adv();
        i++;
    }
    if (i > CAPACITY_WORD)
    {
        currentWord.length = CAPACITY_WORD;
    }
    else
    {
        currentWord.length = i;
    }

    /* Mengakuisisi kata, menyimpan dalam currentWord
    I.S. : currentChar adalah karakter pertama dari kata
    F.S. : currentWord berisi kata yang sudah diakuisisi; 
          currentChar = BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
}
