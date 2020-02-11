cmake_minimum_required(VERSION 3.10)
project(Tic-Tac-Toe-PRI C)

add_executable(${PROJECT_NAME} src/basic_input.c
                               src/console.c
                               src/max.c
                               src/end_of_game.c
                               src/game_display.c
                               src/game_initialization.c
                               src/game_input.c
                               src/game.c
                               src/main.c)

include_directories(include)