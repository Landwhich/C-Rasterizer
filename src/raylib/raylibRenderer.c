#include "raylibRenderer.h"

void raylibRasterizerRun(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib rasterizer test");

    Texture2D texture = LoadTextureFromImage(GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK));

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle src = {0, SCREEN_HEIGHT, SCREEN_WIDTH, -SCREEN_HEIGHT};
        Rectangle dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        Vector2 origin = {0, 0};

        DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();
}