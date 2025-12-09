#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../types/primitives/genericTypes.h"

enum VECTOR_TYPE{
    position    = 0,
    normal      = 1,
    uv          = 2,
    face        = 3,
};

typedef struct{
    rasterizer_float3* positions;
    rasterizer_float3* normals;
    rasterizer_float2* uvs;
    rasterizer_float2* faces;
} Object;

typedef struct{
    size_t positionCount; 
    size_t normalCount; 
    size_t uvCount; 
    size_t faceCount; 
} objVertexCount;

objVertexCount countObjElements(const char* filename);

Object loadModel(const char* filename);

rasterizer_float3 parseFloat3InLine(char line[]);
rasterizer_float2 parseFloat2InLine(char line[]);
void parseFaceLine(char* line, int v[4], int vt[4], int vn[4]);



