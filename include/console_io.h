#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "vector2.h"

void printTryAgain();
void newLine();

int scanBoundedInt(const char* msg, int minVal, int maxVal);

void clearStdin();
void clearConsole();

#endif
