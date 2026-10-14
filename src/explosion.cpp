#include "explosion.hpp"

#include <raymath.h>
#include <algorithm>
#include <cmath>

void Explosion::Update(float dt)
{
    HandleInput(dt);
}

void Explosion::Draw() const
{
    if (configExplosion_) {
        DrawText(TextFormat("EXPLOSION PARTICLES: %d", static_cast<int>(particleCount_)), 10, 70, 20, RAYWHITE);
    }
}

void Explosion::HandleInput(float dt)
{
    const bool shiftDown = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    if (IsKeyPressed(KEY_E) && shiftDown) {
        configExplosion_ = !configExplosion_;
    }

    if (configExplosion_) {
        if (IsKeyDown(KEY_EQUAL) || IsKeyDown(KEY_KP_ADD)) {
            particleCount_ += static_cast<int>(PARTICLE_COUNT_CHANGE_RATE * dt);
        }

        if (IsKeyDown(KEY_MINUS) || IsKeyDown(KEY_KP_SUBTRACT)) {
            particleCount_ -= static_cast<int>(PARTICLE_COUNT_CHANGE_RATE * dt);
        }

        particleCount_ = std::clamp(particleCount_, MIN_PARTICLE_COUNT, MAX_PARTICLE_COUNT);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        SpawnExplosion(GetMousePosition());
    }
}

void Explosion::SpawnExplosion(Vector2 origin) {}

Color Explosion::ComputeColor(float t) {}
