#include "rain.hpp"

#include <raymath.h>
#include <algorithm>

void Rain::Update(float dt)
{
    HandleInput(dt);
}

void Rain::Draw() const
{
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

void Rain::SpawnDrops() {}
