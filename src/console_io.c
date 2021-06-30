#include "console_io.h"

#include "game.h"

#include <stdio.h>
#include <stdlib.h>

void printTryAgain() {
    printf("Invalid input! Try again: ");
}

void newLine() {
    putchar('\n');
}

int scanBoundedInt(const char* msg, int minVal, int maxVal) {
    printf("Enter %s (min: %d, max: %d): ", msg, minVal, maxVal);
    
    int val;
    while(scanf("%d", &val) == 0 || val < minVal || maxVal < val) {
        printTryAgain();
        clearStdin();
    }

    return val;
}

void clearStdin() {
    while(getchar() != '\n');
}

void clearConsole() {
#ifdef _WIN32
    (void) system("cls");
#else
    (void) system("clear");
#endif
}
