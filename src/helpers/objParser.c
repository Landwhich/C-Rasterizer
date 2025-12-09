#include "objParser.h"

objVertexCount countObjElements(const char* filename) {
    objVertexCount stats = {0};
    FILE* f = fopen(filename, "r");
    if (!f) return stats;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "v ", 2) == 0) stats.positionCount++;
        else if (strncmp(line, "vn ", 3) == 0) stats.normalCount++;
        else if (strncmp(line, "vt ", 3) == 0) stats.uvCount++;
        else if (strncmp(line, "f ", 2) == 0) stats.faceCount++;
    }

    printf("positions: %zu\nnormals: %zu\nuvs: %zu\nfaces: %zu\n", stats.positionCount, stats.normalCount, stats.uvCount, stats.faceCount);
    fclose(f);
    return stats;
}

rasterizer_float3 parseFloat3InLine(char line[]){
    char* buffer;
    rasterizer_float3 vector = {0};
    // 😉
    sscanf(line, "%s %f %f %f", buffer, &vector.x, &vector.y, &vector.z);
    // testing
    printf("%f %f %f\n", vector.x, vector.y, vector.z);
    
    return vector;    
}

rasterizer_float2 parseFloat2InLine(char line[]){
    char* buffer;
    rasterizer_float2 vector = {0};
    sscanf(line, "%s %f %f", buffer, &vector.x, &vector.y);
    // testing
    printf("%f %f\n", vector.x, vector.y);
    
    return vector;    
}

void parseFaceLine(char* line, int v[4], int vt[4], int vn[4]) {
    char* token = strtok(line, " ");

    token = strtok(NULL, " ");

    int i = 0;
    while (token != NULL && i < 4) {
        // only for 1/2/3 formats
        sscanf(token, "%d/%d/%d", &v[i], &vt[i], &vn[i]);
        i++;
        token = strtok(NULL, " ");
    }
}


Object loadModel(const char* filename){
    Object obj = {0};

    objVertexCount objectSize = countObjElements(filename);

    obj.positions = malloc(sizeof(rasterizer_float3) * objectSize.positionCount);
    obj.normals = malloc(sizeof(rasterizer_float3) * objectSize.normalCount);
    obj.uvs = malloc(sizeof(rasterizer_float2) * objectSize.uvCount);

    FILE* f = fopen(filename, "r");
    if (!f) return obj;

    char line[256];
    while(fgets(line, sizeof(line), f)){
        if (strncmp(line, "v ", 2) == 0){
            for (int i = 0; i < objectSize.positionCount; i++){
                obj.positions[i] = parseFloat3InLine(line);
                fgets(line, sizeof(line), f);
            }
        }
        if (strncmp(line, "vn ", 3) == 0){
            for (int i = 0; i < objectSize.normalCount; i++){
                obj.normals[i] = parseFloat3InLine(line);
                fgets(line, sizeof(line), f);
            }
        }
        if (strncmp(line, "vt ", 3) == 0){
            for (int i = 0; i < objectSize.uvCount; i++){
                obj.uvs[i] = parseFloat2InLine(line);
                fgets(line, sizeof(line), f);
            }
        }
    }

    return obj;
}