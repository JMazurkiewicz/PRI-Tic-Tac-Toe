#include "basic_input.h"
#include "game.h"
#include <stdio.h>

unsigned loadInteger(const char* name, unsigned minVal, unsigned maxVal) {

    printf("Podaj %s (min: %u, max: %u): ", name, minVal, maxVal);
    unsigned integer;

    while(scanf("%ul", &integer) == 0 || integer > maxVal || integer < minVal) {

        printf("Nieprawidlowa wartosc! Sprobuj ponownie: ");
        removeExtraCharsFromStdin();

    }

    return integer;

}

void loadDimensions(Vector2* dimensions) {
    dimensions->x = loadInteger("szerokosc planszy", 3, GREATEST_DIMENSION);
    dimensions->y = loadInteger("wysokosc planszy", 3, GREATEST_DIMENSION);
}

void removeExtraCharsFromStdin() {
    while(getchar() != '\n');
}