#pragma once

#include <stdio.h>

#include "types/primitives/genericTypes.h"
#include "types/objectTypes.h"
// #include "types/transformTypes.h"
#include "helpers/rasterMath.h"

void render(Object obj, const int screenWidth, const int screenHeight, rasterizer_float3** image, rotMatDeg rotation);