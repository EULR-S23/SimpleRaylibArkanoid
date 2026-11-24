#pragma once
#include "raylib.h"
#include "Constants.h"

class PowerUp {
private:
    Vector2 position;
    float radius;
    float speed;
    PowerUpType type;
    bool active;
public:
    PowerUp(Vector2 pos, PowerUpType t);
    void Update(float deltaTime);
    void Draw() const;
    Vector2 GetPosition() const;
    float GetRadius() const;
    PowerUpType GetType() const;
    bool IsActive() const;
    void Deactivate();
};