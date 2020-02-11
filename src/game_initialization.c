#include "basic_input.h"
#include "console.h"
#include "game.h"
#include "max.h"
#include <stdlib.h>

static void fillGameBoard(Game* game);
static void initRequiredPointCount(Game* game);
static Player chooseOpener();

void initGame(Game* game) {
    
    loadDimensions(&game->dimensions);

    fillGameBoard(game);
    initRequiredPointCount(game);
    
    game->currentPlayer = chooseOpener();
    game->winner = NO_PLAYER;

    clearConsole();
    
}

void fillGameBoard(Game* game) {

    for(unsigned p = 0; p < game->dimensions.y; ++p) {
        for(unsigned q = 0; q < game->dimensions.x; ++q) {
            game->gameBoard[p][q] = NO_PLAYER;
        }
    }

}

void initRequiredPointCount(Game* game) {
    
    if(game->dimensions.x == 3 && game->dimensions.y == 3) {
        game->requiredPointCount = 3;
        return;
    }
    
    const unsigned maxPossiblePointCount = max(game->dimensions.x, game->dimensions.y);
    game->requiredPointCount = loadBoundedInteger("ilosc znakow konieczna do wygranej", 3, maxPossiblePointCount);
    
}

Player chooseOpener() {
    return (rand() % 2 == 0) ? (PLAYER_O) : (PLAYER_X);
}