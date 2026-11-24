#pragma once
#include "raylib.h"
#include "Constants.h"

class Paddle {
private:
    Rectangle rect;
    float speed;
    float originalWidth;
    float bonusTimer;
public:
    Paddle();
    void Reset();
    void ApplyPowerUp(PowerUpType type);
    void Update(float deltaTime);
    void Draw() const;
    Rectangle GetRect() const;
};