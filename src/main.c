// #include <stdio.h>
#include <stdlib.h>
#include "bitmapEncoder.h"
// #include "dataTypes.c"


void CreateTestImage()
{
    const int width = 512;
    const int height = 512;
    float3** image = malloc(height * sizeof(float3*));
    for (int i = 0; i < height; i++){
        image[i] = malloc(width * sizeof(float3));
    }

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            float r = (float)x / (width -1);
            float g = (float)y / (height -1); //normalize to [0,1]? / (width - 1)
            image[y][x] = (float3){ r, g, 0.0f};
            // printf("%f \n",image[y][x].y);
        }
        
    }

    createBMP("../img.bmp", width, height, image);

    for (int i = 0; i < height; i++){
        free(image[i]);
    }

    free(image);
    printf("image updated!!!");
}

//     // Convert float3 to uint8_t array (row-major RGB)
//     uint8_t *rgbData = malloc(width * height * 3);
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             int index = (y * width + x) * 3;
//             rgbData[index + 0] = (uint8_t)(image[y][x].x * 255.0f); // Red
//             rgbData[index + 1] = (uint8_t)(image[y][x].y * 255.0f); // Green
//             rgbData[index + 2] = (uint8_t)(image[y][x].z * 255.0f); // Blue
//         }
//     }

    // Now write BMP file with proper RGB byte data
//     createBMP("img.txt", width, height, rgbData);

//     // Free float3 image

//     free(rgbData);

// 

int main(){

    CreateTestImage();

    return 0;
}