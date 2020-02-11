#include "console.h"
#include "game.h"
#include "player.h"
#include <stdio.h>

void run(Game* game) {
    
    do {
        
        displayGameBoard(game);
        displayTurnInfo(game);
        
        askForInput(game);
        
        switchPlayers(game);
        clearConsole();
        
    } while(!isThisEndOfGame(game));
    
    announceWinner(game);
    
}

void switchPlayers(Game* game) {
    
    if(game->currentPlayer == PLAYER_O) {
        game->currentPlayer = PLAYER_X;
    } else {
        game->currentPlayer = PLAYER_O;
    }
    
}

void announceWinner(Game* game) {
    
    clearConsole();
    displayGameBoard(game);
    
    if(game->winner != NO_PLAYER) {
        printf("Zwyciezyl gracz %c!\n", game->winner);
    } else {
        puts("Remis!");
    }
    
}
