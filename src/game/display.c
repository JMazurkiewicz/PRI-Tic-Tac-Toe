#include "game.h"

#include "console_io.h"

#include <stdio.h>

#define VERTICAL_PIPE ((char)'|')
#define CROSS_PIPE ((char)'+')
#define HORIZONTAL_PIPE ((char)'-')

static void displayColumnIndices(int boardWidth);
static void displayHorizontalBar(int boardWidth);
static void displaySingleRow(const enum Player* board, int row, int boardWidth);

void displayTurnInfo(const struct Game* game) {
    printf("Current player: %c\n", game->currentPlayer);
}

void displayGameBoard(const struct Game* game) {
    const int boardWidth = game->dimensions.x;
    displayColumnIndices(boardWidth);
    newLine();
    
    displaySingleRow(game->board[0], 0, boardWidth);
    for(int row = 1; row < game->dimensions.y; ++row) {
        displayHorizontalBar(boardWidth);
        displaySingleRow(game->board[row], row, boardWidth);        
    }

    newLine();
}

void displayWinnerInfo(struct Game* game) {
    clearConsole();
    displayGameBoard(game);
    
    if(game->winner != NO_PLAYER) {
        printf("Player %c won!\n", game->winner);
    } else {
        puts("Tie!");
    }
}

void displayColumnIndices(int boardWidth) {
    printf("  ");
    const char lastSymbol = (char)('A' + boardWidth);
    
    for(char columnSymbol = 'A'; columnSymbol < lastSymbol; ++columnSymbol) {
        printf(" %c", columnSymbol);
    }
    
    newLine();
}

void displayHorizontalBar(int boardWidth) {
    printf("   %c", HORIZONTAL_PIPE);
    --boardWidth;

    for(int i = 0; i < boardWidth; ++i) {
        putchar(CROSS_PIPE);
        putchar(HORIZONTAL_PIPE);
    }
    
    newLine();
}

void displaySingleRow(const enum Player* board, int row, int boardWidth) {
    const char rowSymbol = (char)('1' + row);
    printf("%c  ", rowSymbol);
    
    putchar(board[0]);
    for(int i = 1; i < boardWidth; ++i) {
        putchar(VERTICAL_PIPE);
        putchar(board[i]);
    }
    
    newLine();
}
