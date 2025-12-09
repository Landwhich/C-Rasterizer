#pragma once

// #include <stdbool.h>
#include <math.h>

#include "../types/primitives/genericTypes.h"

int clamp(int x, int lower, int upper);

float dotProduct(rasterizer_float2 a, rasterizer_float2 b);

rasterizer_float2 makePerpendicular(rasterizer_float2 oldVec);

_Bool pointOnRightSideOfLine(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 p);

_Bool pointInTriangle(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 c, rasterizer_float2 p);

