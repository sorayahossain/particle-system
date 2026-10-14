#pragma once

#include <raylib.h>
#include <vector>

class Fire
{
public:
    void Update(float dt);
    void Draw() const;

private:
    struct Ember
    {
        Vector2 position;
        float baseX;
        float radius;
        float riseSpeed;
        float wobbleSpeed;
        float wobblePhase;
        float wobbleAmplitude;
        float age;
        float lifetime;
    };

    void HandleInput(float dt);
    void SpawnEmbers();
    static Color ComputeColor(float t);

    bool burning_           = false;
    bool configFire_        = false;
    float spawnProbability_ = 0.15f;
    std::vector<Ember> embers_;

    static constexpr float MIN_PROBABILITY              = 0.0f;
    static constexpr float MAX_PROBABILITY              = 10.0f;
    static constexpr float PROBABILITY_CHANGE_RATE      = 0.3f;
    static constexpr int   MAX_SPAWN_ATTEMPTS_PER_FRAME = 100;

    static constexpr float STAGE_YELLOW = 0.25f;
    static constexpr float STAGE_RED    = 0.55f;
    static constexpr float STAGE_SMOKE  = 0.80f;
    static constexpr float FADE_START   = 0.60f;

    static constexpr Color COLOR_HOT    = {255, 255, 255, 255};
    static constexpr Color COLOR_YELLOW = {255, 196, 61, 255};
    static constexpr Color COLOR_RED    = {193, 39, 30, 255};
    static constexpr Color COLOR_SMOKE  = {80, 80, 80, 255};
};
