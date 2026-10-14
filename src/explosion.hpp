#pragma once

#include <raylib.h>
#include <vector>

class Explosion
{
public:
    void Update(float dt);
    void Draw() const;

private:
    void HandleInput(float dt);
    void SpawnExplosion(Vector2 origin);

    bool configExplosion_ = false;
    float particleCount_  = 60.0f;

    static constexpr float MIN_PARTICLE_COUNT         = 10.0f;
    static constexpr float MAX_PARTICLE_COUNT         = 300.0f;
    static constexpr float PARTICLE_COUNT_CHANGE_RATE = 400.0f;
};
