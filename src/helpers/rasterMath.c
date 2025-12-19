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
rasterizer_float2 vertexToScreenSpace(rasterizer_float3 v, rotMatDeg rotationsDeg, rasterizer_float2 numPixels, rasterizer_float3 p){

    rotationMatrix rotations = getTransformMatrix(rotationsDeg);
    rasterizer_float3 vertex = transformVectorRotate(rotations, v);
    vertex = transformVectorPosition(p, vertex);

    float pixelsPerWorldUnit = numPixels.y / SCREEN_HEIGHT_WORLD / vertex.z;

    rasterizer_float2 pixelOffset = {
        vertex.x * pixelsPerWorldUnit,
        vertex.y * pixelsPerWorldUnit
    };

    return (rasterizer_float2){pixelOffset.x + numPixels.x / 2.0, pixelOffset.y + numPixels.y / 2.0};
}
// rotation
rotationMatrix getTransformMatrix(rotMatDeg rmd){
    rotationMatrix rotMatrix_yaw = {
        .ihat = cosf(rmd.yaw), 0, sinf(rmd.yaw),
        .jhat = 0, 1, 0,
        .khat = -sinf(rmd.yaw), 0, cosf(rmd.yaw),
    };
    rotationMatrix rotMatrix_pitch = {
        .ihat = 1, 0 ,0,
        .jhat = 0, cosf(rmd.pitch), -sinf(rmd.pitch),
        .khat = 0, sinf(rmd.pitch), cosf(rmd.pitch),
    };
    rotationMatrix rotMatrix_roll = {
        .ihat = cosf(rmd.roll), sinf(rmd.roll), 0,
        .jhat = -sinf(rmd.roll), cosf(rmd.roll), 0,
        .khat = 0, 0, 1,
    };
    rotationMatrix rotMatrix_yawPitch = {
        .ihat = transformVectorRotate(rotMatrix_yaw, rotMatrix_pitch.ihat),
        .jhat = transformVectorRotate(rotMatrix_yaw, rotMatrix_pitch.jhat),
        .khat = transformVectorRotate(rotMatrix_yaw, rotMatrix_pitch.khat),
    };
    rotationMatrix rotMatrix = {
        .ihat = transformVectorRotate(rotMatrix_yawPitch, rotMatrix_roll.ihat),
        .jhat = transformVectorRotate(rotMatrix_yawPitch, rotMatrix_roll.jhat),
        .khat = transformVectorRotate(rotMatrix_yawPitch, rotMatrix_roll.khat),
    };
    return rotMatrix;
}
rasterizer_float3 transformVectorRotate(rotationMatrix rotMatrix, rasterizer_float3 v){
    rasterizer_float3 vector = {
        .x = v.x * rotMatrix.ihat.x + v.y * rotMatrix.jhat.x + v.z * rotMatrix.khat.x,
        .y = v.x * rotMatrix.ihat.y + v.y * rotMatrix.jhat.y + v.z * rotMatrix.khat.y,
        .z = v.x * rotMatrix.ihat.z + v.y * rotMatrix.jhat.z + v.z * rotMatrix.khat.z
    };
    return vector;
}

rasterizer_float3 transformVectorPosition(rasterizer_float3 p, rasterizer_float3 v){
    return (rasterizer_float3){
        v.x + p.x,
        v.y + p.y,
        v.z + p.z
    };
}