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
        else if (strncmp(line, "f ", 2) == 0) {
            stats.faceCount++;
            size_t spaceCount = 0;
            for (const char* p = line; *p; p++) {if (*p == ' ') spaceCount++;}
            stats.maxFaceLineWidth = fmax(spaceCount, stats.maxFaceLineWidth);
        }
    }

    // printf("positions: %zu\nnormals: %zu\nuvs: %zu\nfaces: %zu\nmax face line width: %zu\n", 
    //     stats.positionCount, stats.normalCount, stats.uvCount, stats.faceCount, stats.maxFaceLineWidth);
    fclose(f);
    return stats;
}

rasterizer_float3 parseFloat3InLine(char line[], char* typeBuffer){
    rasterizer_float3 vector3 = {0};
    // 😉
    sscanf(line, "%s %f %f %f", typeBuffer, &vector3.x, &vector3.y, &vector3.z);
    // testing
    // printf("%f %f %f\n", vector3.x, vector3.y, vector3.z);
    
    return vector3;    
}

rasterizer_float2 parseFloat2InLine(char line[], char* typeBuffer){
    rasterizer_float2 vector2 = {0};
    sscanf(line, "%s %f %f", typeBuffer, &vector2.x, &vector2.y);
    // testing
    // printf("%f %f\n", vector2.x, vector2.y);
    
    return vector2;    
}

// returns a set of vertices for position, normal, and texture
void parseFaceToken(const char* token, int* vi, int* ti, int* ni){
    *vi = *ti = *ni = 0;

    int slashCount = 0;
    for (const char* p = token; *p; p++)
        if (*p == '/') slashCount++;

    if (slashCount == 0) {sscanf(token, "%d", vi);}
    else if (slashCount == 1) {sscanf(token, "%d/%d", vi, ti);}
    else {
        if (strstr(token, "//")) {sscanf(token, "%d//%d", vi, ni);}
        else {sscanf(token, "%d/%d/%d", vi, ti, ni);}
    }
}

void parseFaceLine(
    char* line, Object* obj, size_t* outCount,
    rasterizer_float3* positions, size_t numPositions,
    rasterizer_float3* normals,   size_t numNormals,
    rasterizer_float2* uvs,       size_t numUVs
    )
{
    // *outCount = 0;
    char* saveptr;
    char* tok = strtok_r(line + 2, " ", &saveptr);
    
    vertex faceVerts[32];
    size_t faceCount = 0;

    // loop returns a struct array of unordered vertices, for a whole .obj "face" line
    while (tok) {
        int vi, ti, ni;
        parseFaceToken(tok, &vi, &ti, &ni);

        vertex v;
        v.position = (vi > 0) ? positions[vi - 1] : (rasterizer_float3){0};
        v.normal   = (ni > 0) ? normals[ni - 1]   : (rasterizer_float3){0};
        v.uv       = (ti > 0) ? uvs[ti - 1]       : (rasterizer_float2){0};

        faceVerts[faceCount++] = v;
        tok = strtok_r(NULL, " ", &saveptr);
    }

    // array of unordered vertices => array of ordered vertices
    // Triangulate: output (n-2) triangles
    for (int i = 0; i < faceCount; i++) {
        if (i >= 3){
            // 3rd last index
            obj->triangles[*outCount] = obj->triangles[(*outCount)-3]; (*outCount)++;
            // 2nd last index after updating
            obj->triangles[*outCount] = obj->triangles[(*outCount)-2]; (*outCount)++;
        }
        obj->triangles[*outCount] = faceVerts[i]; (*outCount)++;
    }
}

Object loadModel(const char* filename){
    Object obj = {0};
    objectVertices allVertices = {0};
    size_t triangleCount = 0;

    objVertexCount objectSize = countObjElements(filename);

    obj.size = ((objectSize.maxFaceLineWidth - 3) * 3 + 3) * objectSize.faceCount;

    obj.triangles = malloc(sizeof(vertex) * obj.size);

    allVertices.positions = malloc(sizeof(rasterizer_float3) * objectSize.positionCount);
    allVertices.normals = malloc(sizeof(rasterizer_float3) * objectSize.normalCount);
    allVertices.uvs = malloc(sizeof(rasterizer_float2) * objectSize.uvCount);

    FILE* f = fopen(filename, "r");
    if (!f) return obj;

    char line[256];
    char buffer[8];
    int vertexIndices[] = {0, 0, 0};
    while(fgets(line, sizeof(line), f)){
        if (strncmp(line, "v ", 2) == 0){
            allVertices.positions[vertexIndices[0]++] = parseFloat3InLine(line, buffer);
        }
        else if (strncmp(line, "vn ", 3) == 0){
            allVertices.normals[vertexIndices[1]++] = parseFloat3InLine(line, buffer);
        }
        else if (strncmp(line, "vt ", 3) == 0){
            allVertices.uvs[vertexIndices[2]++] = parseFloat2InLine(line, buffer);
        }
        else if (strncmp(line, "f ", 2) == 0){
            parseFaceLine(
                line, &obj, &triangleCount,
                allVertices.positions, objectSize.positionCount,
                allVertices.normals,   objectSize.normalCount,
                allVertices.uvs,       objectSize.uvCount
            );
        }
    }

    free(allVertices.positions);
    free(allVertices.normals);
    free(allVertices.uvs);

    allVertices.positions = NULL;
    allVertices.normals = NULL;
    allVertices.uvs = NULL;

    return obj;
}