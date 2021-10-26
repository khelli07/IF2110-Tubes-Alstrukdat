#include "locmachine.h"
#include "../point/location.h"
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
    ignoreBlank();
    int i = 0;
    int value = 0;
    while (currentChar >= 48 && currentChar <= 48 + 9 && i < NUM_CAP)
    {
        value = value * 10 + currentChar - 48;
        i++;
        adv();
    }

    return value;
}

void ignoreBlank()
{
    while (currentChar == BLANK || currentChar == NEWLINE)
    {
        adv();
    }
}

void startReadLoc()
{
    // start();
    ignoreBlank();
    readLocCounter = readInt();
    if (readLocCounter <= 0)
    {
        endReadLoc = true;
    }
    else
    {
        endReadLoc = false;
        ignoreBlank();
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
        ignoreBlank();
        copyCurrentLoc();
    }
}

void copyCurrentLoc()
{
    char cc = currentChar;
    adv();
    int x = readInt();
    int y = readInt();

    CreateLocation(&currentLoc, x, y, cc);
    readLocCounter -= 1;
}