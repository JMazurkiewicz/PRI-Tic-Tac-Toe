#include "game.h"

#include "console_io.h"
#include "max.h"

#include <stdlib.h>

static void scanDimensions(struct Vector2* dimensions);
static void fillBoard(struct Game* game);
static void initRequiredPointCount(struct Game* game);
static enum Player chooseFirstPlayer();

void initGame(struct Game* game) {
    scanDimensions(&game->dimensions);

    fillBoard(game);
    initRequiredPointCount(game);

    game->currentPlayer = chooseFirstPlayer();
    game->winner = NO_PLAYER;
}

void scanDimensions(struct Vector2* dimensions) {
    dimensions->x = scanBoundedInt("board width", SMALLEST_DIMENSION, GREATEST_DIMENSION);
    dimensions->y = scanBoundedInt("board height", SMALLEST_DIMENSION, GREATEST_DIMENSION);
}

void fillBoard(struct Game* game) {
    for(int row = 0; row < game->dimensions.y; ++row) {
        for(int column = 0; column < game->dimensions.x; ++column) {
            game->board[row][column] = NO_PLAYER;
        }
    }
}

void initRequiredPointCount(struct Game* game) {
    if(game->dimensions.x == 3 && game->dimensions.y == 3) {
        game->requiredPoints = 3;
    } else {
        const int maxPossiblePointCount = max(game->dimensions.x, game->dimensions.y);
        const char* const msg = "amount of points required to win";

        game->requiredPoints = scanBoundedInt(msg, SMALLEST_DIMENSION, maxPossiblePointCount);
    }
}

enum Player chooseFirstPlayer() {
    return (rand() % 2 == 0) ? (O_PLAYER) : (X_PLAYER);
}
