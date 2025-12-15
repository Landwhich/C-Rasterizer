#pragma once

#include <math.h>
// #include <stdio.h>

#include "../types/primitives/genericTypes.h"
#include "../types/transformTypes.h"
#include "../constants.h"

// STD MATH HELPERS
int clamp(int x, int lower, int upper);

// LINEAR FUNCTIONS FOR TRIANGLE RASTER MATH
float dotProduct(rasterizer_float2 a, rasterizer_float2 b);
rasterizer_float2 makePerpendicular(rasterizer_float2 oldVec);

_Bool pointOnRightSideOfLine(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 p);
_Bool pointInTriangle(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 c, rasterizer_float2 p);

// VECTOR TRANSFORMS
rasterizer_float2 vertexToScreenSpace(rasterizer_float3 vertex, rotMatDeg rotations, rasterizer_float2 numPixels);
//Rotation 
rotationMatrix getTransformMatrix(rotMatDeg rmd);
inline rasterizer_float3 transformVector(rotationMatrix rmd, rasterizer_float3 v);

