#include "rain.hpp"

#include <raymath.h>
#include <algorithm>

void Rain::Update(float dt)
{
    HandleInput(dt);

    if (raining_) {
        SpawnDrops();
    }

    for (auto &drop : drops_) {
        drop.speed      += GRAVITY * dt;
        drop.position.y += drop.speed * dt;
    }

    const float screenHeight = static_cast<float>(GetScreenHeight());
    std::erase_if(drops_, [screenHeight](const Drop &drop) {
        return drop.position.y - drop.length > screenHeight;
    });
}

void Rain::Draw() const
{
    for (const auto &drop : drops_) {
        const Vector2 start = drop.position;
        const Vector2 end = {drop.position.x, drop.position.y - drop.length};
        DrawLineEx(start, end, drop.thickness, RAIN_COLOR);
    }

    if (configRain_) {
        DrawText(TextFormat("RAIN DENSITY: %02.0f", spawnProbability_ * 100.0f), 10, 30, 20, RAYWHITE);
    }
}

void Rain::HandleInput(float dt)
{
    const bool shiftDown = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    if (IsKeyPressed(KEY_R)) {
        if (shiftDown) {
            configRain_ = !configRain_;
        } else {
            raining_ = !raining_;
        }
    }

    if (configRain_) {
        if (IsKeyDown(KEY_EQUAL) || IsKeyDown(KEY_KP_ADD)) {
            spawnProbability_ += PROBABILITY_CHANGE_RATE * dt;
        }

        if (IsKeyDown(KEY_MINUS) || IsKeyDown(KEY_KP_SUBTRACT)) {
            spawnProbability_ -=  PROBABILITY_CHANGE_RATE * dt;
        }

        spawnProbability_ = std::clamp(spawnProbability_, MIN_PROBABILITY, MAX_PROBABILITY);
    }
}

void Rain::SpawnDrops()
{
    for (int i = 0; i < SPAWN_ATTEMPTS_PER_FRAME; ++i) {
        const float roll = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;

        if (roll <= spawnProbability_) {
            Drop drop;

            drop.position  = {static_cast<float>(GetRandomValue(0, GetScreenWidth())), 0.0f};
            drop.speed     = static_cast<float>(GetRandomValue(400, 700));
            drop.thickness = static_cast<float>(GetRandomValue(10, 25)) / 10.0f;
            drop.length    = static_cast<float>(GetRandomValue(10, 25));

            drops_.push_back(drop);
        }
    }
}
