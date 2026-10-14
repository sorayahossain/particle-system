#pragma once

#include <raylib.h>
#include <vector>

class Rain
{
public:
    void Update(float dt);
    void Draw() const;

private:
    struct Drop
    {
        Vector2 position;
        float   speed;
        float   thickness;
        float   length;
    };

    void HandleInput(float dt);
    void SpawnDrops();

    bool raining_           = false;
    bool configRain_        = false;
    float spawnProbability_ = 0.15f;
    std::vector<Drop> drops_;

    static constexpr float GRAVITY                  = 900.0f;
    static constexpr float MIN_PROBABILITY          = 0.0f;
    static constexpr float MAX_PROBABILITY          = 1.0f;
    static constexpr float PROBABILITY_CHANGE_RATE  = 0.3f;
    static constexpr int   SPAWN_ATTEMPTS_PER_FRAME = 6;
    static constexpr Color RAIN_COLOR = {137, 176, 225, 200};
};
