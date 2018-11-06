#include "game.h"
#include "player.h"
#include <stdbool.h>
#include "vector2.h"

bool isThisTie(const Game* game);
Player whoWon(const Game* game);

Player checkColumns(const Game* game);
Player checkSingleColumn(const Game* game, unsigned columnIndex);

Player checkRows(const Game* game);
Player checkSingleRow(const Game* game, unsigned rowIndex);

Player checkSlants(const Game* game);
Player checkHorizontalSlants(const Game* game);
Player checkVerticalSlants(const Game* game);

Player checkSingleSlant(const Game* game, Vector2 start, bool isReversed);

bool isThisEndOfGame(Game* game) {
    
    const Player winner = whoWon(game);
    
    if(winner != NO_PLAYER) {
        game->winner = winner;
        return true;
    }
    
    return isThisTie(game);
 
}

Player whoWon(const Game* game) {
    
    const char possibleWinners[3] = {
        checkColumns(game),
        checkRows(game),
        checkSlants(game)
    };
    
    for(unsigned i = 0; i < 3; ++i) {
        if(possibleWinners[i] != NO_PLAYER) {
            return possibleWinners[i];
        }
    }
    
    return NO_PLAYER;
    
}

Player checkColumns(const Game* game) {
    
    if(game->requiredPointCount > game->dimensions.y) {
        return NO_PLAYER;
    }
    
    for(unsigned i = 0; i < game->dimensions.x; ++i) {
        
        const Player possibleWinner = checkSingleColumn(game, i);
        
        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
        
    }
    
    return NO_PLAYER;
    
}

Player checkSingleColumn(const Game* game, unsigned columnIndex) {
    
    Player possibleWinner = game->gameBoard[0][columnIndex];
    unsigned pointCounter = 1;
    
    for(unsigned i = 1; i < game->dimensions.y; ++i) {
        
        if(game->gameBoard[i][columnIndex] == possibleWinner) {
            ++pointCounter;
        } else {
            possibleWinner = game->gameBoard[i][columnIndex];
            pointCounter = 1;
        }
        
        if(pointCounter == game->requiredPointCount && possibleWinner != NO_PLAYER) {
            break;
        }
        
    }
    
    return (pointCounter == game->requiredPointCount) ? possibleWinner : NO_PLAYER;
    
}

Player checkRows(const Game* game) {
    
    if(game->requiredPointCount > game->dimensions.x) {
        return NO_PLAYER;
    }
    
    for(unsigned i = 0; i < game->dimensions.y; ++i) {
        
        const Player possibleWinner = checkSingleRow(game, i);

        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
        
    }
    
    return NO_PLAYER;
    
}

Player checkSingleRow(const Game* game, unsigned rowIndex) {
    
    Player possibleWinner = game->gameBoard[rowIndex][0];
    unsigned pointCounter = 1;
    
    for(unsigned i = 1; i < game->dimensions.x; ++i) {
        
        if(game->gameBoard[rowIndex][i] == possibleWinner) {
            ++pointCounter;
        } else {
            possibleWinner = game->gameBoard[rowIndex][i];
            pointCounter = 1;
        }
        
        if(pointCounter == game->requiredPointCount && possibleWinner != NO_PLAYER) {
            break;
        }
        
    }
    
    return (pointCounter == game->requiredPointCount) ? possibleWinner : NO_PLAYER;
    
}

Player checkSlants(const Game* game) {
    
    const Player horizontal = checkHorizontalSlants(game);    
    if(horizontal != NO_PLAYER) {
        return horizontal;
    }
    
    const Player vertical = checkVerticalSlants(game);    
    if(vertical != NO_PLAYER) {
        return vertical;
    }
    
    return NO_PLAYER;
    
}

Player checkHorizontalSlants(const Game* game) {
    
    Vector2 position = {0, 0};
    
    const unsigned possibleHorizontalSlants = game->dimensions.x - game->requiredPointCount + 1;
    
    for(unsigned i = 0; i < possibleHorizontalSlants; ++i, ++position.x) {
        
        const Player possibleWinner = checkSingleSlant(game, position, false);
        
        const Vector2 reversedSlantPosition = {game->dimensions.x-position.x-1, position.y};
        const Player possibleReversedWinner = checkSingleSlant(game, reversedSlantPosition, true);

        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
        if(possibleReversedWinner != NO_PLAYER) {
            return possibleReversedWinner;
        }
        
    }
    
    return NO_PLAYER;
    
}

Player checkVerticalSlants(const Game* game) {
    
    Vector2 position = {0, 1};
    
    const unsigned possibleVerticalSlants = game->dimensions.y - game->requiredPointCount;
    
    for(unsigned i = 0; i < possibleVerticalSlants; ++i, ++position.y) {
        
        const Player possibleWinner = checkSingleSlant(game, position, false);
        
        const Vector2 reversedSlantPosition = {game->dimensions.x-1, position.y};
        const Player possibleReversedWinner = checkSingleSlant(game, reversedSlantPosition, true);
        
        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
        if(possibleReversedWinner != NO_PLAYER) {
            return possibleReversedWinner;
        }
        
    }
    
    return NO_PLAYER;
    
}

#include <stdio.h>

Player checkSingleSlant(const Game* game, Vector2 start, bool isReversed) {

    Player possibleWinner = game->gameBoard[start.y][start.x];
    unsigned pointCounter = 0;
    
    for(; start.x < game->dimensions.x && start.y < game->dimensions.y;
          ++start.y, (isReversed ? --start.x : ++start.x)) {
        
        printf("POS: %d/%d, POINTS: %d\n", start.x, start.y, pointCounter);
        
        if(game->gameBoard[start.y][start.x] == possibleWinner) {
            ++pointCounter;
        } else {
            possibleWinner = game->gameBoard[start.y][start.x];
            pointCounter = 1;
        }
        
        if(pointCounter == game->requiredPointCount && possibleWinner != NO_PLAYER) {
            break;
        }
        
    }
    
    printf("STOPPOS: %d/%d, POINTS: %d\n", start.x, start.y, pointCounter);
    printf("RESULT: %c\n\n", possibleWinner);
    
    return (pointCounter == game->requiredPointCount) ? possibleWinner : NO_PLAYER;
    
}

bool isThisTie(const Game* game) {
    
    for(unsigned p = 0; p < game->dimensions.y; ++p) {
        for(unsigned q = 0; q < game->dimensions.x; ++q) {

            if(game->gameBoard[p][q] == NO_PLAYER) {
                return false;
            }

        }
    }
    
    return true;
    
}