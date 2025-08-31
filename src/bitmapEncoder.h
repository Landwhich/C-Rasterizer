#pragma once

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "dataTypes.c"

void createBMP(const char *filename, const int width, const int height, float3** imgData);