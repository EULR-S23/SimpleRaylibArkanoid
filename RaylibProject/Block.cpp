#include "Block.h"

Block::Block(float x, float y, float width, float height, int hp) {
    rect = { x, y, width, height };
    lives = hp;
    active = true;
    UpdateColor();
}

void Block::UpdateColor() {
    if (lives >= 3) color = RED;
    else if (lives == 2) color = ORANGE;
    else color = YELLOW;
}

void Block::Hit() {
    lives--;
    if (lives <= 0) active = false;
    else UpdateColor();
}

void Block::Draw() const {
    if (!active) return;
    DrawRectangleRec(rect, color);
    DrawRectangleRec({ rect.x + 2, rect.y + 2, rect.width - 4, 4 }, { 255, 255, 255, 100 });
    DrawRectangleLinesEx(rect, 2, DARKGRAY);
    //if (lives >= 3) DrawText("3", (int)rect.x + (int)rect.width / 2 - 4, (int)rect.y + (int)rect.height / 2 - 6, 12, WHITE);
}

Rectangle Block::GetRect() const { return rect; }
bool Block::IsActive() const { return active; }