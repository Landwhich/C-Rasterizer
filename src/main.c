// #include <stdio.h>
#include <stdlib.h>
#include "types/primitives/genericTypes.c"
#include "helpers/bitmapEncoder.c"
#include "helpers/rasterMath.c"

void CreateTestImage()
{
    const int width = 512;
    const int height = 512;
    float3** image = malloc(height * sizeof(float3*));
    for (int i = 0; i < height; i++){
        image[i] = malloc(width * sizeof(float3));
    }

    float2 a = {0.2f * (float)width, 0.2f * (float)height};
    float2 b = {0.7f * (float)width, 0.5f * (float)height};
    float2 c = {0.4f * (float)width, 0.8f * (float)height};

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            float2 pixel = {x, y};
            bool insideTriangle = pointInTriangle(a, b, c, pixel);
            if (insideTriangle){image[y][x] = (float3){1,1,1};}
        }  
    }
    // image[(int)a.y][(int)a.x] = (float3){1,0,0};
    // image[(int)b.y][(int)b.x] = (float3){1,0,0};
    // image[(int)c.y][(int)c.x] = (float3){1,0,0};

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