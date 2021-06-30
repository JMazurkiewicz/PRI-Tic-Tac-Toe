#include "game.h"

#include "console_io.h"

static void switchPlayers(struct Game* game);

void run(struct Game* game) {
    do {
        clearConsole();
        displayGameBoard(game);
        displayTurnInfo(game);
        
        askForInput(game);
        
        switchPlayers(game);
    } while(!isEndOfGame(game));
    
    displayWinnerInfo(game);
}

void switchPlayers(struct Game* game) {
    if(game->currentPlayer == O_PLAYER) {
        game->currentPlayer = X_PLAYER;
    } else {
        game->currentPlayer = O_PLAYER;
    }
}
