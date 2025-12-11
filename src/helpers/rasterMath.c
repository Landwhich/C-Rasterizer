#include "rasterMath.h"

// STD MATH HELPERS
int clamp(int x, int lower, int upper){
    return fmin(upper, fmax(x, lower));
}

// LINEAR FUNCTIONS FOR TRIANGLE RASTER MATH
float dotProduct(rasterizer_float2 a, rasterizer_float2 b){return a.x * b.x + a.y * b.y;}

rasterizer_float2 makePerpendicular(rasterizer_float2 oldVec){
    rasterizer_float2 newVec = {oldVec.y, -oldVec.x};
    return newVec;
}

_Bool pointOnRightSideOfLine(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 p){
    rasterizer_float2 ap = {p.x - a.x, p.y - a.y};
    rasterizer_float2 ab = {b.x - a.x, b.y - a.y};
    rasterizer_float2 abPerp = makePerpendicular(ab);
    return dotProduct(ap, abPerp) >= 0;
}

_Bool pointInTriangle(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 c, rasterizer_float2 p){
    _Bool AB = pointOnRightSideOfLine(a, b, p);
    _Bool BC = pointOnRightSideOfLine(b, c, p);
    _Bool CA = pointOnRightSideOfLine(c, a, p);
    return AB && BC && CA;
}

// VECTOR TRANSFORMS
rasterizer_float2 vertexToScreenSpace(rasterizer_float3 v, rotMatDeg rotations, rasterizer_float2 numPixels){

    rasterizer_float3 vertex = transformVector(rotations, v);

    float pixelsPerWorldUnit = numPixels.y / SCREEN_HEIGHT_WORLD;

    rasterizer_float2 pixelOffset = {
        vertex.x * pixelsPerWorldUnit,
        vertex.y * pixelsPerWorldUnit
    };

    return (rasterizer_float2){pixelOffset.x + numPixels.x / 2.0, pixelOffset.y + numPixels.y / 2.0};
}
// rotation
rotationMatrix getTransformMatrix(rotMatDeg rmd){
    rotationMatrix rotMatrix = {
        .ihat = cosf(rmd.yaw), 0, sinf(rmd.yaw),
        .jhat = 0, 1, 0,
        .khat = -sinf(rmd.yaw), 0, cosf(rmd.yaw),
    };
    return rotMatrix;
}
rasterizer_float3 transformVector(rotMatDeg rmd, rasterizer_float3 v){
    rotationMatrix rotMatrix = getTransformMatrix(rmd);
    rasterizer_float3 vector = {
        .x = v.x * rotMatrix.ihat.x + v.y * rotMatrix.jhat.x + v.z * rotMatrix.khat.x,
        .y = v.x * rotMatrix.ihat.y + v.y * rotMatrix.jhat.y + v.z * rotMatrix.khat.y,
        .z = v.x * rotMatrix.ihat.z + v.y * rotMatrix.jhat.z + v.z * rotMatrix.khat.z
    };
    return vector;
}