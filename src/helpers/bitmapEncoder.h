#pragma once

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../types/primitives/genericTypes.h"

void createBMP(const char *filename, const int width, const int height, rasterizer_float3** imgData);