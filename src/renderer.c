#include "renderer.h"

void render(Object obj, const int screenWidth, const int screenHeight, rasterizer_float3** image, rotMatDeg rotation, rasterizer_float3 position) {

    const rasterizer_float2 screenSize = {screenWidth, screenHeight};

    // setbackground
    for(int y = 0; y < screenHeight; y++){for(int x = 0; x < screenWidth; x++){
        image[y][x] = (rasterizer_float3){0,0,0};
    }}

    // render Image
    for(size_t i = 0; i < obj.size; i+=3){
        rasterizer_float2 a = vertexToScreenSpace(obj.triangles[i + 0].position, rotation, screenSize, position);
        rasterizer_float2 b = vertexToScreenSpace(obj.triangles[i + 1].position, rotation, screenSize, position);
        rasterizer_float2 c = vertexToScreenSpace(obj.triangles[i + 2].position, rotation, screenSize, position);

        rasterizer_float3 color;
        if      (i % 6 == 0)    {color = (rasterizer_float3){200,0,0};}
        else if (i % 6 == 3)    {color = (rasterizer_float3){0,200,0};}

        float minX = fmin(fmin(a.x, b.x), c.x);
        float minY = fmin(fmin(a.y, b.y), c.y);
        float maxX = fmax(fmax(a.x, b.x), c.x);
        float maxY = fmax(fmax(a.y, b.y), c.y);

        int boundStartX = clamp((int)minX, 0, screenWidth - 1);
        int boundStartY = clamp((int)minY, 0, screenHeight - 1);
        int boundEndX = clamp((int)ceil(maxX), 0, screenWidth - 1);
        int boundEndY = clamp((int)ceil(maxY), 0, screenHeight - 1);

        for(int y = boundStartY; y < boundEndY; y++){
            for(int x = boundStartX; x < boundEndX; x++){
                rasterizer_float2 pixel = {x, y};
                if (pointInTriangle(a, b, c, pixel)) {image[y][x] = color;}
            }
        }
    }
}