#include "explosion.hpp"

#include <raymath.h>
#include <algorithm>
#include <cmath>

void Explosion::Update(float dt)
{
    HandleInput(dt);

    const float groundY = static_cast<float>(GetScreenHeight());

    for (auto &particle : particles_) {
        particle.age        += dt;
        particle.velocity.y += GRAVITY * dt;
        particle.position.x += particle.velocity.x * dt;
        particle.position.y += particle.velocity.y * dt;

        if (particle.position.y >= groundY) {
            particle.position.y = groundY;
            particle.velocity.y = -particle.velocity.y;
        }
    }

    std::erase_if(particles_, [](const Particle &particle) {
        return particle.age >= particle.lifetime;
    });
}

void Explosion::Draw() const
{
    for (const auto &particle : particles_) {
        const float t = std::clamp(particle.age / particle.lifetime, 0.0f, 1.0f);
        DrawCircleV(particle.position, particle.radius, ComputeColor(t));
    }

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

void Explosion::SpawnExplosion(Vector2 origin)
{
    const int particleCount = static_cast<int>(particleCount_);

    for (int i = 0; i < particleCount; ++i) {
        const float angle = static_cast<float>(GetRandomValue(0, 359)) * DEG2RAD;
        const float speed  = static_cast<float>(GetRandomValue(static_cast<int>(SPEED_MIN), static_cast<int>(SPEED_MAX)));

        Particle particle;

        particle.position = origin;
        particle.velocity = {cosf(angle) * speed, sinf(angle) * speed};
        particle.radius   = static_cast<float>(GetRandomValue(20, 50)) / 10.0f;
        particle.age      = 0.0f;
        particle.lifetime = static_cast<float>(GetRandomValue(100, 250)) / 100.0f;

        particles_.push_back(particle);
    }
}

Color Explosion::ComputeColor(float t)
{
    Color color;

    if (t < STAGE_YELLOW) {
        color = ColorLerp(COLOR_HOT, COLOR_YELLOW, t / STAGE_YELLOW);
    } else if (t < STAGE_RED) {
        color = ColorLerp(COLOR_YELLOW, COLOR_RED, (t - STAGE_YELLOW) / (STAGE_RED - STAGE_YELLOW));
    } else if (t < STAGE_SMOKE) {
        color = ColorLerp(COLOR_RED, COLOR_SMOKE, (t - STAGE_RED) / (STAGE_SMOKE - STAGE_RED));
    } else {
        color = COLOR_SMOKE;
    }

    if (t > FADE_START) {
        const float fadeT = (t - FADE_START) / (1.0f - FADE_START);
        color = ColorAlpha(color, 1.0f - fadeT);
    }

    return color;
}
