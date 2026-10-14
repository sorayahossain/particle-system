#include <raylib.h>

#include "fire.hpp"
#include "rain.hpp"

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TARGET_FPS    = 60;

static void Update(Rain &rain, Fire &fire, float dt)
{
    rain.Update(dt);
    fire.Update(dt);
}

static void Draw(const Rain &rain, const Fire &fire)
{
    BeginDrawing();
    ClearBackground(BLACK);

    rain.Draw();
    fire.Draw();
    DrawFPS(10, 10);

    EndDrawing();
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Systems Demo");
    SetTargetFPS(TARGET_FPS);

    Rain rain;
    Fire fire;

    while (!WindowShouldClose())
    {
        Update(rain, fire, GetFrameTime());
        Draw(rain, fire);
    }

    CloseWindow();
    return 0;
}
