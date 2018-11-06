#pragma once

#include "player.h"
#include <stdbool.h>
#include "vector2.h"

#define GREATEST_DIMENSION 9

typedef struct Game {
    
    Vector2 dimensions;
    unsigned requiredPointCount;

    Player gameBoard[GREATEST_DIMENSION][GREATEST_DIMENSION];
    
    Player currentPlayer;
    Player winner;
    
} Game;

void initGame(Game* game);

void run(Game* game);

void displayTurnInfo(const Game* game);
void displayGameBoard(const Game* game);

void askForInput(Game* game);
void switchPlayers(Game* game);

bool isThisEndOfGame(Game* game);

void announceWinner(Game* game);