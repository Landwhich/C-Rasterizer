#include <stdlib.h>

#include "raylib/raylibRenderer.h"

#include "types/primitives/genericTypes.h"
#include "helpers/bitmapEncoder.h"
#include "helpers/rasterMath.h"
#include "helpers/objParser.h"

void CreateTestImage(){

    const int height = 2560;
    const int width = 2560;

    rasterizer_float3** image = malloc(height * sizeof(rasterizer_float3*));
    for (int i = 0; i < height; i++){
        image[i] = malloc(width * sizeof(rasterizer_float3));
    }

    rasterizer_float2 a = {0.2f * (float)width, 0.2f * (float)height};
    rasterizer_float2 b = {0.7f * (float)width, 0.5f * (float)height};
    rasterizer_float2 c = {0.4f * (float)width, 0.8f * (float)height};

    float minX = fmin(fmin(a.x, b.x), c.x);
    float minY = fmin(fmin(a.y, b.y), c.y);
    float maxX = fmax(fmax(a.x, b.x), c.x);
    float maxY = fmax(fmax(a.y, b.y), c.y);

    int boundStartX = clamp((int)minX, 0, width);
    int boundStartY = clamp((int)minY, 0, height);
    int boundEndX = clamp((int)ceil(maxX), 0, width);
    int boundEndY = clamp((int)ceil(maxY), 0, height);

    // setbackground
    for(int y = 0; y < height; y++){for(int x = 0; x < width; x++){
        image[y][x] = (rasterizer_float3){0,0,1};
    }}

    for(int y = boundStartY; y < boundEndY; y++){
        for(int x = boundStartX; x < boundEndX; x++){
            rasterizer_float2 pixel = {x, y};

            _Bool insideTriangle = pointInTriangle(a, b, c, pixel);

            if (insideTriangle){image[y][x] = (rasterizer_float3){1,1,0};}
            else {image[y][x] = (rasterizer_float3){1,0,0};}
        }
    }

    createBMP("img.bmp", width, height, image);

    for (int i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);

    // printf("image updated!!!\n");
}

int main(){
    // CreateTestImage();
    Object cube = loadModel("assets/models/cube.obj");
    // objVertexCount count = countObjElements("assets/models/cube.obj");
    // printf("Cube Vertex Stats:\nVertices: %zu\nNormals: %zu\nUVs: %zu", count.positionCount, count.normalCount, count.uvCount);

    // raylibRasterizerRun();

    char test[] = "2/3/4 3/2/3 4/5/6";
    char* newTest = strtok(test, " /");
    int arr[9];
    sscanf(newTest, "%i %i %i", &arr[0], &arr[1], &arr[2]);

    for (int i = 0; i < 3; i++){printf("%i\n", arr[i]);}

    char line[] = "f 1/1/1 5/2/1 7/3/1 3/4/1";

    int v[4], vt[4], vn[4];
    parseFaceLine(line, v, vt, vn);

    for (int i = 0; i < 4; i++) {
        printf("Vertex %d → v=%d vt=%d vn=%d\n", i, v[i], vt[i], vn[i]);
    }


    return 0;
}