#include "game.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    
    srand((unsigned)time(0));
    
    Game game;
    initGame(&game);
    
    run(&game);
    
}