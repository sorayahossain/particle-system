#include <raylib.h>

#include "explosion.hpp"
#include "fire.hpp"
#include "rain.hpp"

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TARGET_FPS    = 60;

static void Update(Rain &rain, Fire &fire, Explosion &explosion, float dt)
{
    rain.Update(dt);
    fire.Update(dt);
    explosion.Update(dt);
}

static void Draw(const Rain &rain, const Fire &fire, const Explosion &explosion)
{
    BeginDrawing();
    ClearBackground(BLACK);

    rain.Draw();
    fire.Draw();
    explosion.Draw();
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
    Explosion explosion;

    while (!WindowShouldClose())
    {
        Update(rain, fire, explosion, GetFrameTime());
        Draw(rain, fire, explosion);
    }

    CloseWindow();
    return 0;
}
