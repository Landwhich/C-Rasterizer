#pragma once

typedef struct{
    float x;
    float y;
    float z;
} rasterizer_float3;

typedef struct{
    float x;
    float y;
} rasterizer_float2;

typedef struct{
    rasterizer_float3 position;
    rasterizer_float3 normal;
    rasterizer_float2 texture;
} vertex;

