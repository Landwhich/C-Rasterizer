#include "ppmEncoder.h"

#pragma pack(push, 1) // this magical bit tells the compiler no padding 
typedef struct{
    uint16_t bfType;            // magic word 'P3' to indicate .ppm
    uint32_t bfSize;            // file size in bytes
    uint16_t colorIntensity;    // typically 255
} PPMFileHeader; //8 bytes (so small)
#pragma pack(pop)

void createPPM(const char* filename, const int width, const int height, rasterizer_float3** imgData){
    FILE *file = fopen(filename, "wb");
    if (!file) return;

    PPMFileHeader fileHeader;

    fileHeader.bfType = 0x3350; // 'P3' format specifier
    fileHeader.bfSize = 54 + width * height * 3; // File size
    fileHeader.colorIntensity = 255;

    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    uint8_t pixel[3] = {0x00, 0x00, 0x00};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fputc((uint8_t)(fminf(fmaxf(imgData[y][x].x * 255.0f, 0.0f), 255.0f)),file); // R
            fputc((uint8_t)(fminf(fmaxf(imgData[y][x].y * 255.0f, 0.0f), 255.0f)),file); // G
            fputc((uint8_t)(fminf(fmaxf(imgData[y][x].z * 255.0f, 0.0f), 255.0f)),file); // B
        }
    }
    fclose(file);
}
