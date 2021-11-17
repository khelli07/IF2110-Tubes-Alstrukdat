#include <stdio.h>
#include "wordmachine.h"

int main() {
    int i;
    startWord();
    while (!endWord) {
        for (i = 0; i < currentWord.length; i ++) {
            printf("%c", currentWord.contents[i]);
        }
        printf("\n");
        advWord();
    }
    return 0;
}