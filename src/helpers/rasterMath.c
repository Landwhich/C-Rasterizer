#include "rasterMath.h"

float dotProduct(rasterizer_float2 a, rasterizer_float2 b){return a.x * b.x + a.y * b.y;}

rasterizer_float2 makePerpendicular(rasterizer_float2 oldVec){
    rasterizer_float2 newVec = {oldVec.y, -oldVec.x};
    return newVec;
}

bool pointOnRightSideOfLine(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 p){
    rasterizer_float2 ap = {p.x - a.x, p.y - a.y};
    rasterizer_float2 ab = {b.x - a.x, b.y - a.y};
    rasterizer_float2 abPerp = makePerpendicular(ab);
    return dotProduct(ap, abPerp) >= 0;
}

bool pointInTriangle(rasterizer_float2 a, rasterizer_float2 b, rasterizer_float2 c, rasterizer_float2 p){
    bool AB = pointOnRightSideOfLine(a, b, p);
    bool BC = pointOnRightSideOfLine(b, c, p);
    bool CA = pointOnRightSideOfLine(c, a, p);
    return AB == BC && BC == CA;
}