#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../types/objectTypes.h"
#include "../types/primitives/genericTypes.h"

typedef struct{
    rasterizer_float3* positions;
    rasterizer_float3* normals;
    rasterizer_float2* uvs;
    rasterizer_float2* faces;
} objectVertices;

typedef struct{
    size_t positionCount; 
    size_t normalCount; 
    size_t uvCount; 
    size_t faceCount; 
    size_t maxFaceLineWidth;
} objVertexCount;

objVertexCount countObjElements(const char* filename);

Object loadModel(const char* filename);

rasterizer_float3 parseFloat3InLine(char line[], char* typeBuffer);
rasterizer_float2 parseFloat2InLine(char line[], char* typeBuffer);
void parseFaceToken(const char* token, int* vi, int* ti, int* ni);
void parseFaceLine(
    char* line, Object* obj, size_t* outCount,
    rasterizer_float3* positions, size_t numPositions,
    rasterizer_float3* normals,   size_t numNormals,
    rasterizer_float2* uvs,       size_t numUVs
);



