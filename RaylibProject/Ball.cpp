#include "Ball.h"
#include <cmath>

Ball::Ball() {
    radius = 8.0f;
    Reset();
}

void Ball::Reset() {
    position = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    speed = { 300.0f, -400.0f };
    active = true;
}

void Ball::ApplyPowerUp(PowerUpType type) {
    if (type == POWERUP_SPEEDY) {
        speed.x *= 0.7f;
        speed.y *= 0.7f;
    }
}

void Ball::Update(float deltaTime) {
    position.x += speed.x * deltaTime;
    position.y += speed.y * deltaTime;

    if (position.x - radius < 0) { position.x = radius; speed.x = -speed.x; }
    if (position.x + radius > SCREEN_WIDTH) { position.x = SCREEN_WIDTH - radius; speed.x = -speed.x; }
    if (position.y - radius < 0) { position.y = radius; speed.y = -speed.y; }
    if (position.y - radius > SCREEN_HEIGHT) { active = false; }
}

void Ball::Draw() const {
    if (!active) return;
    DrawCircle((int)position.x, (int)position.y + 2, radius, DARKGRAY);
    DrawCircleV(position, radius, WHITE);
    DrawCircle((int)position.x - 2, (int)position.y - 2, radius / 3, LIGHTGRAY);
}

void Ball::CollideWithPaddle(Rectangle paddleRect) {
    if (CheckCollisionCircleRec(position, radius, paddleRect)) {
        position.y = paddleRect.y - radius;
        float paddleCenter = paddleRect.x + paddleRect.width / 2;
        float hitPosition = (position.x - paddleCenter) / (paddleRect.width / 2);
        if (hitPosition > 1.0f) hitPosition = 1.0f;
        if (hitPosition < -1.0f) hitPosition = -1.0f;
        speed.x = hitPosition * 400.0f;
        speed.y = -400.0f;
    }
}

bool Ball::CollideWithBlock(Rectangle blockRect) {
    if (!CheckCollisionCircleRec(position, radius, blockRect)) return false;

    float overlapLeft = (position.x + radius) - blockRect.x;
    float overlapRight = (blockRect.x + blockRect.width) - (position.x - radius);
    float overlapTop = (position.y + radius) - blockRect.y;
    float overlapBottom = (blockRect.y + blockRect.height) - (position.y - radius);

    float minOverlap = overlapLeft;
    if (overlapRight < minOverlap) minOverlap = overlapRight;
    if (overlapTop < minOverlap) minOverlap = overlapTop;
    if (overlapBottom < minOverlap) minOverlap = overlapBottom;

    if (minOverlap == overlapLeft) { speed.x = -std::abs(speed.x); position.x = blockRect.x - radius; }
    else if (minOverlap == overlapRight) { speed.x = std::abs(speed.x); position.x = blockRect.x + blockRect.width + radius; }
    else if (minOverlap == overlapTop) { speed.y = -std::abs(speed.y); position.y = blockRect.y - radius; }
    else if (minOverlap == overlapBottom) { speed.y = std::abs(speed.y); position.y = blockRect.y + blockRect.height + radius; }
    return true;
}

Vector2 Ball::GetPosition() const { return position; }
bool Ball::IsActive() const { return active; }
void Ball::SetPosition(Vector2 pos) { position = pos; }
void Ball::SetSpeed(Vector2 spd) { speed = spd; }