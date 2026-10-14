#include <raylib.h>

#include "rain.hpp"

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TARGET_FPS    = 60;

static void Update(Rain &rain, float dt)
{
    rain.Update(dt);
}

static void Draw(const Rain &rain)
{
    BeginDrawing();
    ClearBackground(BLACK);

    rain.Draw();
    DrawFPS(10, 10);

    EndDrawing();
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Systems Demo");
    SetTargetFPS(TARGET_FPS);

    Rain rain;

    while (!WindowShouldClose())
    {
        Update(rain, GetFrameTime());
        Draw(rain);
    }

    CloseWindow();
    return 0;
}
