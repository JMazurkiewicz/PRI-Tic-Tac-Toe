#include "console.h"
#include "game.h"
#include <stdio.h>

static const char VERTICAL_PIPE = '\xB3';
static const char CROSS_PIPE = '\xC5';
static const char HORIZONTAL_PIPE = '\xC4';

static void displayUpperIndexes(unsigned boardWidth);
static void displayBoard(const Game* game);
static void displayHorizontalBar(unsigned boardWidth);
static void displaySingleRow(const Player* board, unsigned rowIndex, unsigned boardWidth);
static void newLine();

void displayTurnInfo(const Game* game) {
    printf("Kolej gracza %c\n", game->currentPlayer);
}

void displayGameBoard(const Game* game) {
    
    displayUpperIndexes(game->dimensions.x);
    newLine();
    
    displayBoard(game);
    newLine();
    
}

void displayUpperIndexes(unsigned boardWidth) {
    
    printf("   ");
    
    for(char c = 'A'; boardWidth--; ++c) {
        printf("%c ", c);
    }
    
    newLine();
    
}

void displayBoard(const Game* game) {
    
    const unsigned boardWidth = game->dimensions.x;
    
    displaySingleRow(game->gameBoard[0], 0, boardWidth);
    
    for(unsigned i = 1; i < game->dimensions.y; ++i) {
        
        displayHorizontalBar(boardWidth);
        displaySingleRow(game->gameBoard[i], i, boardWidth);
        
    }
    
}

void displayHorizontalBar(unsigned boardWidth) {
    
    printf("   %c", HORIZONTAL_PIPE);
    
    while(--boardWidth) {
        putchar(CROSS_PIPE);
        putchar(HORIZONTAL_PIPE);
    }
    
    newLine();
    
}

void displaySingleRow(const Player* board, unsigned rowIndex, unsigned boardWidth) {
    
    printf("%c  ", '1'+rowIndex);
    
    putchar(*board++);
    
    while(--boardWidth) {
        putchar(VERTICAL_PIPE);
        putchar(*board++);
    }
    
    newLine();
    
}

void newLine() {
    putchar('\n');
}