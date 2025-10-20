#include "rasterMath.h"

float dotProduct(float2 a, float2 b){return a.x * b.x + a.y * b.y;}

float2 makePerpendicular(float2 oldVec){
    float2 newVec = {oldVec.y, -oldVec.x};
    return newVec;
}

bool pointOnRightSideOfLine(float2 a, float2 b, float2 p){
    float2 ap = {p.x - a.x, p.y - a.y};
    float2 ab = {b.x - a.x, b.y - a.y};
    float2 abPerp = makePerpendicular(ab);
    return dotProduct(ap, abPerp) >= 0;
}

bool pointInTriangle(float2 a, float2 b, float2 c, float2 p){
    bool AB = pointOnRightSideOfLine(a, b, p);
    bool BC = pointOnRightSideOfLine(b, c, p);
    bool CA = pointOnRightSideOfLine(c, a, p);
    return AB == BC && BC == CA;
}