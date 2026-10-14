#include "fire.hpp"

#include <raymath.h>
#include <algorithm>
#include <cmath>

void Fire::Update(float dt)
{
    HandleInput(dt);

    if (burning_) {
        SpawnEmbers();
    }
}

void Fire::Draw() const
{
    if (configFire_) {
        DrawText(TextFormat("FIRE DENSITY: %02.0f", spawnProbability_ * 100.0f), 10, 50, 20, RAYWHITE);
    }
}

void Fire::HandleInput(float dt)
{
    const bool shiftDown = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    if (IsKeyPressed(KEY_F)) {
        if (shiftDown) {
            configFire_ = !configFire_;
        } else {
            burning_ = !burning_;
        }
    }

    if (configFire_) {
        if (IsKeyDown(KEY_EQUAL) || IsKeyDown(KEY_KP_ADD)) {
            spawnProbability_ += PROBABILITY_CHANGE_RATE * dt;
        }

        if (IsKeyDown(KEY_MINUS) || IsKeyDown(KEY_KP_SUBTRACT)) {
            spawnProbability_ -= PROBABILITY_CHANGE_RATE * dt;
        }

        spawnProbability_ = std::clamp(spawnProbability_, MIN_PROBABILITY, MAX_PROBABILITY);
    }
}

void Fire::SpawnEmbers() {}
