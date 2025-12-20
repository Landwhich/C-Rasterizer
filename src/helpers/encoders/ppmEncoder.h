// portable pix map (.ppm)
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "../../types/primitives/genericTypes.h"

void createPPM(const char* filename, const int width, const int height, rasterizer_float3** imgData);