#pragma once

#include <stdlib.h>
#include "primitives/genericTypes.h"

typedef struct{
    rasterizer_float3 position;
    rasterizer_float3 normal;
    rasterizer_float2 uv;
} vertex;

typedef struct{
    size_t size;
    vertex* triangles;
} Object;