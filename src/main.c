#include "game.h"

#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));
    
    struct Game game;
    initGame(&game);
    
    run(&game);
}
