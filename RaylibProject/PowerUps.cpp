#include "PowerUps.h"

PowerUp::PowerUp(Vector2 pos, PowerUpType t) {
    position = pos;
    radius = 15.0f;
    speed = 200.0f;
    type = t;
    active = true;
}

void PowerUp::Update(float deltaTime) {
    position.y += speed * deltaTime;
    if (position.y > SCREEN_HEIGHT + radius) active = false;
}

void PowerUp::Draw() const {
    if (!active) return;

    Color color = BLUE;
    const char* label = "?";
    if (type == POWERUP_WIDEN) { color = BLUE; label = "W"; }
    else if (type == POWERUP_SPEEDY) { color = GREEN; label = "S"; }
    else if (type == POWERUP_MULTIBALL) { color = PURPLE; label = "M"; }

    DrawCircleV(position, radius, color);
    DrawCircleLines((int)position.x, (int)position.y, radius, WHITE);
    DrawText(label, (int)position.x - 4, (int)position.y - 6, 14, WHITE);
}

Vector2 PowerUp::GetPosition() const { return position; }
float PowerUp::GetRadius() const { return radius; }
PowerUpType PowerUp::GetType() const { return type; }
bool PowerUp::IsActive() const { return active; }
void PowerUp::Deactivate() { active = false; }