#include "basic_input.h"
#include "game.h"
#include <stdio.h>

unsigned loadBoundedInteger(const char* name, unsigned minVal, unsigned maxVal) {

    printf("Podaj %s (min: %u, max: %u): ", name, minVal, maxVal);
    unsigned integer;

    while(scanf("%ul", &integer) == 0 || integer > maxVal || integer < minVal) {

        printf("Nieprawidlowa wartosc! Sprobuj ponownie: ");
        removeExtraCharsFromStdin();

    }

    return integer;

}

void loadDimensions(Vector2* dimensions) {
    dimensions->x = loadBoundedInteger("szerokosc planszy", LOWEST_DIMENSION, GREATEST_DIMENSION);
    dimensions->y = loadBoundedInteger("wysokosc planszy", LOWEST_DIMENSION, GREATEST_DIMENSION);
}

void removeExtraCharsFromStdin() {
    while(getchar() != '\n');
}