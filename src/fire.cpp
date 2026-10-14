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

    for (auto &ember : embers_) {
        ember.age        += dt;
        ember.position.y -= ember.riseSpeed * dt;
        ember.position.x  = ember.baseX + sinf(ember.age * ember.wobbleSpeed + ember.wobblePhase) * ember.wobbleAmplitude;
    }

    std::erase_if(embers_, [](const Ember &ember) {
        return ember.age >= ember.lifetime;
    });
}

void Fire::Draw() const
{
    for (const auto &ember : embers_) {
        const float t = std::clamp(ember.age / ember.lifetime, 0.0f, 1.0f);
        DrawCircleV(ember.position, ember.radius, ComputeColor(t));
    }

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

void Fire::SpawnEmbers()
{
    for (int i = 0; i < MAX_SPAWN_ATTEMPTS_PER_FRAME; ++i) {
        const float roll = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;

        if (roll <= spawnProbability_) {
            const float spawnX = static_cast<float>(GetRandomValue(0, GetScreenWidth()));

            Ember ember;

            ember.position        = {spawnX, static_cast<float>(GetScreenHeight())};
            ember.baseX           = spawnX;
            ember.radius          = static_cast<float>(GetRandomValue(40, 140)) / 10.0f;
            ember.riseSpeed       = static_cast<float>(GetRandomValue(80, 220));
            ember.wobbleSpeed     = static_cast<float>(GetRandomValue(20, 60)) / 10.0f;
            ember.wobblePhase     = static_cast<float>(GetRandomValue(0, 628)) / 100.0f;
            ember.wobbleAmplitude = static_cast<float>(GetRandomValue(5, 20));
            ember.age             = 0.0f;
            ember.lifetime        = static_cast<float>(GetRandomValue(100, 220)) / 100.0f;

            embers_.push_back(ember);
        }
    }
}

Color Fire::ComputeColor(float t)
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
