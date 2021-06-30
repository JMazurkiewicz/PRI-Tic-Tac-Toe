#include "game.h"

#include "console_io.h"

#include <stdio.h>

static char toUpper(char symbol);
static bool isInputOk(const struct Game* game, int column, int row);
static bool isColumnOk(const struct Game* game, int column);
static bool isRowOk(const struct Game* game, int row);
static bool isPlaceFree(const struct Game* game, int column, int row);
static void markBoardField(struct Game* game, int column, int row);

void askForInput(struct Game* game) {
    printf("Enter column letter and row number (eg \"A1\"): ");
    
    char column, row;
    while(scanf(" %c %c", &column, &row) == 0 || !isInputOk(game, toUpper(column), row)) {
        printTryAgain();
        clearStdin();
    }
    
    markBoardField(game, toUpper(column), row);
}

char toUpper(char symbol) {
    if('a' <= symbol && symbol <= 'z') {
        return symbol - 32;
    } else {
        return symbol;
    }
}

bool isInputOk(const struct Game* game, int column, int row) {
    return isColumnOk(game, column) && isRowOk(game, row) && isPlaceFree(game, column, row);
}

bool isColumnOk(const struct Game* game, int column) {
    const int columnValue = column;
    return ('A' <= columnValue) && (columnValue <= 'A' + game->dimensions.x - 1);
}

bool isRowOk(const struct Game* game, int row) {
    return ('1' <= row) && (row <= '1' + game->dimensions.y - 1);
}

bool isPlaceFree(const struct Game* game, int column, int row) {
    return game->board[row - '1'][column - 'A'] == NO_PLAYER;
}

void markBoardField(struct Game* game, int column, int row) {
    game->board[row - '1'][column - 'A'] = game->currentPlayer;
}
