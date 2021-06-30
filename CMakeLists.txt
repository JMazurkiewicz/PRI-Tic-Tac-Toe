cmake_minimum_required(VERSION 3.10)
project(Tic-Tac-Toe C)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(SOURCES
    src/game/checks.c
    src/game/display.c
    src/game/init.c
    src/game/input.c
    src/game/run.c

    src/console_io.c
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
