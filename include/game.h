#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "vector2.h"

#include <stdbool.h>

#define SMALLEST_DIMENSION (3)
#define GREATEST_DIMENSION (9)

struct Game {
    struct Vector2 dimensions;
    int requiredPoints;

    enum Player board[GREATEST_DIMENSION][GREATEST_DIMENSION];
    
    enum Player currentPlayer;
    enum Player winner;
};

void initGame(struct Game* game);

void run(struct Game* game);

void displayTurnInfo(const struct Game* game);
void displayGameBoard(const struct Game* game);
void displayWinnerInfo(struct Game* game);

void askForInput(struct Game* game);
bool isEndOfGame(struct Game* game);

#endif
