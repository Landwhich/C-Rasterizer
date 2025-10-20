#pragma once
#include <stdbool.h>
#include "../types/primitives/genericTypes.c"

float dotProduct(float2 a, float2 b);

float2 makePerpendicular(float2 oldVec);

bool pointOnRightSideOfLine(float2 a, float2 b, float2 p);

bool pointInTriangle(float2 a, float2 b, float2 c, float2 p);

