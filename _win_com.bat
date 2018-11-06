@echo off
gcc basic_input.c console.c custom_math.c end_of_game.c game.c game_display.c game_initialization.c game_input.c main.c -std=c11 -pedantic -Wall -o _tic_tac_toe
pause