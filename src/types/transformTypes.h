#pragma once

#include "primitives/genericTypes.h"

typedef struct{
    float roll;
    float pitch; 
    float yaw;
} rotMatDeg;

typedef struct{
    rasterizer_float3 ihat;
    rasterizer_float3 jhat;
    rasterizer_float3 khat;
}rotationMatrix;
