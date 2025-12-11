#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "raylib/raylibRenderer.h"

#include "types/primitives/genericTypes.h"
#include "types/transformTypes.h"
#include "helpers/bitmapEncoder.h"
#include "helpers/rasterMath.h"
#include "helpers/objParser.h"
#include "renderer.h"
#include "constants.h"

void CreateTestImage(const char* filename, rotMatDeg rotation, Object obj){
    rasterizer_float3** image = malloc(SCREEN_HEIGHT * sizeof(rasterizer_float3*));
    for (int i = 0; i < SCREEN_HEIGHT; i++){
        image[i] = malloc(SCREEN_WIDTH * sizeof(rasterizer_float3));
    }

    render(obj, SCREEN_WIDTH, SCREEN_HEIGHT, image, rotation);

    createBMP(filename, SCREEN_WIDTH, SCREEN_HEIGHT, image);

    // DEALOCATE ALL MEMORY ALLOCATED
    for (int i = 0; i < SCREEN_HEIGHT; i++){
        free(image[i]);
        image[i] = NULL;
    }
    free(image);
    image = NULL;
    printf("image updated");
}

int main(){

    // Object cube = loadModel("assets/models/cube.obj");
    Object monkey = loadModel("assets/models/monkey.obj");

    clock_t begin = clock();
    char filename[25]; 
    rotMatDeg rotation = {
        .roll = 0,
        .pitch = 0,
        .yaw = 0,
    };
    for (int i = 0; i < 96; i++){
        sprintf(filename, "zanim/output-%03d.bmp", i);
        CreateTestImage(filename, rotation, monkey);
        rotation.yaw += M_PI/48;
        printf("Generating: %s\n", filename);
    }

    // CreateTestImage("img.bmp", rotation, monkey);

    clock_t end = clock();
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total TimeSpent: %f", timeSpent);

    free(monkey.triangles);
    monkey.triangles = NULL;

    // raylibRasterizerRun();

    return 0;
}