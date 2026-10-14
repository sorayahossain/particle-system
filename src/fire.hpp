#pragma once

#include <raylib.h>
#include <vector>

class Fire
{
public:
    void Update(float dt);
    void Draw() const;

private:
    void HandleInput(float dt);
    void SpawnEmbers();

    bool burning_           = false;
    bool configFire_        = false;
    float spawnProbability_ = 0.15f;

    static constexpr float MIN_PROBABILITY         = 0.0f;
    static constexpr float MAX_PROBABILITY         = 10.0f;
    static constexpr float PROBABILITY_CHANGE_RATE = 0.3f;
};
