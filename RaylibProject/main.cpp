#include "raylib.h"
#include "Game.h"
#include "Constants.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arcanoid!!!");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        game.Update(deltaTime);
        game.Draw();
    }

    CloseWindow();
    return 0;
}