// #include <stdio.h>
#include <stdlib.h>

#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

#include "types/primitives/genericTypes.h"
#include "helpers/bitmapEncoder.h"
#include "helpers/rasterMath.h"


void CreateTestImage()
{
    const int width = 128;
    const int height = 128;
    rasterizer_float3** image = malloc(height * sizeof(rasterizer_float3*));
    for (int i = 0; i < height; i++){
        image[i] = malloc(width * sizeof(rasterizer_float3));
    }

    rasterizer_float2 a = {0.2f * (float)width, 0.2f * (float)height};
    rasterizer_float2 b = {0.7f * (float)width, 0.5f * (float)height};
    rasterizer_float2 c = {0.4f * (float)width, 0.8f * (float)height};

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            rasterizer_float2 pixel = {x, y};
            bool insideTriangle = pointInTriangle(a, b, c, pixel);
            if (insideTriangle){image[y][x] = (rasterizer_float3){1,1,0};}
            // if (pixel.x == a.x && pixel.y == a.y ||
            //     pixel.x == b.x && pixel.y == b.y ||
            //     pixel.x == c.x && pixel.y == c.y)
            // {image[x][y] = (float3){1,0,0};}
        }  
    }

    createBMP("img.bmp", width, height, image);

    for (int i = 0; i < height; i++){
        free(image[i]);
    }

    free(image);
    printf("image updated!!!");
}

int main(){
    CreateTestImage();
    return 0;
}