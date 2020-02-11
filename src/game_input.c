#include "basic_input.h"
#include <ctype.h>
#include "game.h"
#include <stdio.h>

static bool validateInput(const Game* game, char column, char row);
static bool validateColumn(const Game* game, char column);
static bool validateRow(const Game* game, char row);
static bool isPlaceFree(const Game* game, char column, char row);
static void setFieldOnBoardToCurrentPlayer(Game* game, char column, char row);

void askForInput(Game* game) {
    
    printf("Podaj litere kolumny i numer rzedu (np. \"A1\"): ");
    char column, row;
    
    while(scanf(" %c %c", &column, &row) == 0 || !validateInput(game, toupper(column), row)) {
        printf("Nieprawidlowe wartosci, sprobuj jeszcze raz: ");
        removeExtraCharsFromStdin();
    }
    
    setFieldOnBoardToCurrentPlayer(game, toupper(column), row);
    
}

bool validateInput(const Game* game, char column, char row) {
    return
        validateColumn(game, column) &&
        validateRow(game, row) &&
        isPlaceFree(game, column, row);
}

bool validateColumn(const Game* game, char column) {
    return (column >= 'A') && (column <= game->dimensions.x-1 + 'A');
}

bool validateRow(const Game* game, char row) {
    return (row >= '1') && (row <= game->dimensions.y-1 + '1');
}

bool isPlaceFree(const Game* game, char column, char row) {
    return game->gameBoard[row-'1'][column-'A'] == NO_PLAYER;
}

void setFieldOnBoardToCurrentPlayer(Game* game, char column, char row) {
    game->gameBoard[row-'1'][column-'A'] = game->currentPlayer;
}