#include "raylib.h"

int main()
{
    InitWindow(960, 540, "CPP2409-P");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("My first raylib game!", 40, 40, 30, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}