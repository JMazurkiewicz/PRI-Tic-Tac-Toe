#pragma once

#include "vector2.h"

unsigned loadBoundedInteger(const char* name, unsigned minVal, unsigned maxVal);
void loadDimensions(Vector2* dimensions);

void removeExtraCharsFromStdin();