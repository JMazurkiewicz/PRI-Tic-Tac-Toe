#include "console.h"
#include <stdlib.h>

void clearConsole() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}