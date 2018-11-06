#include "console.h"
#include "game.h"
#include <stdio.h>

const char VERTICAL_PIPE = '\xB3';
const char CROSS_PIPE = '\xC5';
const char HORIZONTAL_PIPE = '\xC4';

void displayUpperIndexes(unsigned boardWidth);
void displayBoard(const Game* game);
void displayHorizontalBar(unsigned boardWidth);
void displaySingleRow(const Player* board, unsigned rowIndex, unsigned boardWidth);
void newLine();

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