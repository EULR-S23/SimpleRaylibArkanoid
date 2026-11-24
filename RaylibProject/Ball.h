#pragma once
#include "raylib.h"
#include "Constants.h"

class Ball {
private:
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
public:
    Ball();
    void Reset();
    void ApplyPowerUp(PowerUpType type);
    void Update(float deltaTime);
    void Draw() const;
    void CollideWithPaddle(Rectangle paddleRect);
    bool CollideWithBlock(Rectangle blockRect);

    Vector2 GetPosition() const;
    bool IsActive() const;
    void SetPosition(Vector2 pos);
    void SetSpeed(Vector2 spd);
};