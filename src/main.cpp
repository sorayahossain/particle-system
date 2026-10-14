#include <raylib.h>

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TARGET_FPS    = 60;

static void Update(float dt)
{
    (void) dt;
}

static void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(10, 10);

    EndDrawing();
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Systems Demo");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        Update(GetFrameTime());
        Draw();
    }

    CloseWindow();
    return 0;
}
