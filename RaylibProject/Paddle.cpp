#include "Paddle.h"

Paddle::Paddle() {
    originalWidth = 120.0f;
    rect = { (float)SCREEN_WIDTH / 2 - originalWidth / 2, (float)SCREEN_HEIGHT - 40, originalWidth, 20.0f };
    speed = 600.0f;
    bonusTimer = 0.0f;
}

void Paddle::Reset() {
    rect.width = originalWidth;
    rect.x = (float)SCREEN_WIDTH / 2 - originalWidth / 2;
    bonusTimer = 0.0f;
}

void Paddle::ApplyPowerUp(PowerUpType type) {
    if (type == POWERUP_WIDEN) {
        rect.width = originalWidth * 1.5f;
        bonusTimer = 8.0f;
    }
}

void Paddle::Update(float deltaTime) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) rect.x -= speed * deltaTime;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) rect.x += speed * deltaTime;

    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.width > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - rect.width;

    if (bonusTimer > 0.0f) {
        bonusTimer -= deltaTime;
        if (bonusTimer <= 0.0f) rect.width = originalWidth;
    }
}

void Paddle::Draw() const {
    Color paddleColor = (rect.width > originalWidth) ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRounded(rect, 0.4f, 8, paddleColor);
    DrawRectangleRec({ rect.x + 4, rect.y + 2, rect.width - 8, 3 }, WHITE);
    if (bonusTimer > 0.0f && (int)(bonusTimer * 4) % 2 == 0) {
        DrawRectangleLinesEx(rect, 2, YELLOW);
    }
}

Rectangle Paddle::GetRect() const { return rect; }