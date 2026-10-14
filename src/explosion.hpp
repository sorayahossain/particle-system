#pragma once

#include <raylib.h>
#include <vector>

class Explosion
{
public:
    void Update(float dt);
    void Draw() const;

private:
    struct Particle
    {
        Vector2 position;
        Vector2 velocity;
        float radius;
        float age;
        float lifetime;
    };

    void HandleInput(float dt);
    void SpawnExplosion(Vector2 origin);
    static Color ComputeColor(float t);

    bool configExplosion_ = false;
    float particleCount_  = 60.0f;
    std::vector<Particle> particles_;

    static constexpr float MIN_PARTICLE_COUNT         = 10.0f;
    static constexpr float MAX_PARTICLE_COUNT         = 300.0f;
    static constexpr float PARTICLE_COUNT_CHANGE_RATE = 400.0f;

    static constexpr float GRAVITY   = 900.0f;
    static constexpr float SPEED_MIN = 300.0f;
    static constexpr float SPEED_MAX = 600.0f;

    static constexpr float STAGE_YELLOW = 0.25f;
    static constexpr float STAGE_RED    = 0.55f;
    static constexpr float STAGE_SMOKE  = 0.80f;
    static constexpr float FADE_START   = 0.60f;

    static constexpr Color COLOR_HOT    = {255, 255, 255, 255};
    static constexpr Color COLOR_YELLOW = {255, 196, 61, 255};
    static constexpr Color COLOR_RED    = {193, 39, 30, 255};
    static constexpr Color COLOR_SMOKE  = {80, 80, 80, 255};
};
