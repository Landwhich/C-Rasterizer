#pragma once
#include <stdbool.h>
#include "../types/primitives/genericTypes.h"

float dotProduct(rasterizer_float2 a, rasterizer_float2 b);

rasterizer_float2 makePerpendicular(rasterizer_float2 oldVec);

bool pointOnRightSideOfLine(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 p);

bool pointInTriangle(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 c, rasterizer_float2 p);

