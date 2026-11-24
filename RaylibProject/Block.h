#pragma once
#include "raylib.h"

class Block {
private:
    Rectangle rect;
    int lives;
    Color color;
    bool active;
    void UpdateColor();
public:
    Block(float x, float y, float width, float height, int hp);
    void Hit();
    void Draw() const;
    Rectangle GetRect() const;
    bool IsActive() const;
};