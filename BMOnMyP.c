#include "BMOnMyP.h"

#pragma pack(push, 1) // this magical thing tells the compiler🫷 no padding 🚫
typedef struct{
    uint16_t bfType;            // magic word 'BM' to indicate .bmp
    uint32_t bfSize;            // file size in bytes
    uint16_t bfReserved1;       // Reserved (must be 0)
    uint16_t bfReserved2;       // Reserved (must be 0)
    uint32_t bfOffBits;         // Offset to pixel array 
} BMPFileHeader; //14 bytes
#pragma pack(pop)

typedef struct{
    uint32_t biSize;            // Size of this header (40 bytes)
    int32_t biWidth;            // Image width in pixels
    int32_t biHeight;           // Image height in pixels
    uint16_t biPlanes;          // Number of color planes (must be 1)
    uint16_t biBitCount;        // Bits per pixel (24 for RGB)
    uint32_t biCompression;     // Compression method (0 for none)
    uint32_t biSizeImage;       // Image size in bytes
    int32_t biXPelsPerMeter;    // X resolution in pixels per meter
    int32_t biYPelsPerMeter;    // Y resolution in pixels per meter
    uint32_t biClrUsed;         // Number of colors used
    uint32_t biClrImportant;    // Number of important colors
} BMPInfoHeader; //typically 40 bytes

// Header byte size represented
// 42 4D | 00 00 00 00 | 00 00 | 00 00 | 00 00 00 00 | 00 00
// 00 00 | 00 00 00 00 | 00 00 00 00 | 00 00 | 00 00 | 00 00 
// 00 00 | 00 00 00 00 | 00 00 00 00 | 00 00 00 00 | 00 00
// 00 00 | 00 00 00 00 |

// int ParseToBGRPixel(float3 pixel){
//     pixel.x = 
// }

void createBMP(const char* filename, const int width, const int height, float3** imgData){
    FILE *file = fopen(filename, "wb");
    if (!file) return;

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    // Initialize file header
    fileHeader.bfType = 0x4D42; // 'BM'
    fileHeader.bfSize = 54 + width * height * 3; // File size
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = 54; // Offset to pixel array

    // Initialize image header
    infoHeader.biSize = 40;
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = width * height * 3;
    infoHeader.biXPelsPerMeter = 0;
    infoHeader.biYPelsPerMeter = 0;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    // Write file header
    fwrite(&fileHeader, sizeof(fileHeader), 1, file);

    // Write image header
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);

    uint8_t pixel[3] = {0xAA, 0xAA, 0xAA};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fwrite(pixel, 3, 1, file);
        }
    }


    fclose(file);
}
