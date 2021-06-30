#include "game.h"

#include <stddef.h>

static bool isTie(const struct Game* game);
static enum Player getWinner(const struct Game* game);

static enum Player checkAllColumns(const struct Game* game);
static enum Player checkColumn(const struct Game* game, int column);

static enum Player checkAllRows(const struct Game* game);
static enum Player checkRow(const struct Game* game, int row);

enum Slant {
    LEFT, RIGHT
};

static enum Player checkAllUpperSlants(const struct Game* game);
static enum Player checkAllLowerSlants(const struct Game* game);
static enum Player checkSlant(const struct Game* game, struct Vector2 start, enum Slant slant);

bool isEndOfGame(struct Game* game) {
    const enum Player winner = getWinner(game);
    
    if(winner != NO_PLAYER) {
        game->winner = winner;
        return true;
    } else {
        return isTie(game);
    }
}

bool isTie(const struct Game* game) {
    for(int row = 0; row < game->dimensions.y; ++row) {
        for(int column = 0; column < game->dimensions.x; ++column) {
            if(game->board[row][column] == NO_PLAYER) {
                return false;
            }
        }
    }
    
    return true;
}

enum Player getWinner(const struct Game* game) {
    typedef enum Player (*Check)(const struct Game* game);
    static const Check checks[4] = {
        checkAllColumns, checkAllRows,
        checkAllUpperSlants, checkAllLowerSlants
    };

    for(int i = 0; i < 4; ++i) {
        const enum Player winner = checks[i](game);
        if(winner != NO_PLAYER) {
            return winner;
        }
    }

    return NO_PLAYER;
}

enum Player checkAllColumns(const struct Game* game) {
    if(game->requiredPoints > game->dimensions.y) {
        return NO_PLAYER;
    }
    
    for(int column = 0; column < game->dimensions.x; ++column) {
        const enum Player possibleWinner = checkColumn(game, column);
        
        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkColumn(const struct Game* game, int column) {
    enum Player possibleWinner = game->board[0][column];
    int points = 1;
    
    for(int row = 1; row < game->dimensions.y; ++row) {
        if(game->board[row][column] == possibleWinner) {
            ++points;
        } else {
            possibleWinner = game->board[row][column];
            points = 1;
        }
        
        if(points == game->requiredPoints && possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkAllRows(const struct Game* game) {
    if(game->requiredPoints > game->dimensions.x) {
        return NO_PLAYER;
    }
    
    for(int row = 0; row < game->dimensions.y; ++row) {
        const enum Player possibleWinner = checkRow(game, row);

        if(possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkRow(const struct Game* game, int row) {
    enum Player possibleWinner = game->board[row][0];
    int points = 1;
    
    for(int column = 1; column < game->dimensions.x; ++column) {
        if(game->board[row][column] == possibleWinner) {
            ++points;
        } else {
            possibleWinner = game->board[row][column];
            points = 1;
        }
        
        if(points == game->requiredPoints && possibleWinner != NO_PLAYER) {
            return possibleWinner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkAllUpperSlants(const struct Game* game) {
    const int upperSlantCount = game->dimensions.x - game->requiredPoints + 1;
    struct Vector2 start = {0, 0};
    
    for(int i = 0; i < upperSlantCount; ++i, ++start.x) {
        enum Player winner = checkSlant(game, start, LEFT);
        if(winner != NO_PLAYER) {
            return winner;
        }
        
        const struct Vector2 rightSlantStart = {game->dimensions.x - start.x - 1, start.y};
        winner = checkSlant(game, rightSlantStart, RIGHT);
        if(winner != NO_PLAYER) {
            return winner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkAllLowerSlants(const struct Game* game) {
    const int lowerSlantCount = game->dimensions.y - game->requiredPoints;
    struct Vector2 start = {0, 1};
    
    for(int i = 0; i < lowerSlantCount; ++i, ++start.y) {
        enum Player winner = checkSlant(game, start, LEFT);
        if(winner != NO_PLAYER) {
            return winner;
        }
        
        const struct Vector2 rightSlantStart = {game->dimensions.x - 1, start.y};
        winner = checkSlant(game, rightSlantStart, RIGHT);
        if(winner != NO_PLAYER) {
            return winner;
        }
    }
    
    return NO_PLAYER;
}

enum Player checkSlant(const struct Game* game, struct Vector2 start, enum Slant slant) {
    enum Player winner = game->board[start.y][start.x];
    int points = 0;
    
    for(; start.x < game->dimensions.x && start.y < game->dimensions.y;
          ++start.y, (slant == RIGHT ? --start.x : ++start.x)) {
        
        if(game->board[start.y][start.x] == winner) {
            ++points;
        } else {
            winner = game->board[start.y][start.x];
            points = 1;
        }
        
        if(points == game->requiredPoints && winner != NO_PLAYER) {
            return winner;
        }
    }
    
    return NO_PLAYER;
}
