#include "locmachine.h"
#include <stdio.h>

int readLocCounter = -1;
boolean endReadLoc;
Location currentLoc;

int charToInt(char cc)
{
    return cc - 48;
}

int readInt()
{
    ignoreWhiteSpace();
    int i = 0;
    int value = 0;
    while (currentChar >= 48 && currentChar <= 48 + 9 && i < NUM_CAP)
    {
        value = value * 10 + currentChar - 48;
        i++;
        advReadFile();
    }

    return value;
}

void ignoreWhiteSpace()
{
    while (currentChar == BLANK || currentChar == NEWLINE || currentChar == TAB)
    {
        advReadFile();
    }
}

void startReadLoc()
{
    ignoreWhiteSpace();
    readLocCounter = readInt();
    if (readLocCounter <= 0)
    {
        endReadLoc = true;
    }
    else
    {
        endReadLoc = false;
        ignoreWhiteSpace();
        copyCurrentLoc();
    }
}

void advReadLoc()
{
    if (readLocCounter <= 0)
    {
        endReadLoc = true;
    }
    else
    {
        ignoreWhiteSpace();
        copyCurrentLoc();
    }
}

void copyCurrentLoc()
{
    char cc = currentChar;
    advReadFile();
    int x = readInt();
    int y = readInt();

    CreateLocation(&currentLoc, x, y, cc);
    readLocCounter -= 1;
}