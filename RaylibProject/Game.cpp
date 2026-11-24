#include "Game.h"
#include "raylib.h"
Game::Game() {
    state = STATE_MENU;
    score = 0;
    lives = 3;
    powerupsCollected = 0;
}

void Game::InitLevel() {
    blocks.clear();
    powerups.clear();
    paddle.Reset();
    balls.clear();
    balls.push_back(Ball());
    powerupsCollected = 0;

    int rows = 8, cols = 10;
    float bw = 70.0f, bh = 25.0f, sx = 6.0f, sy = 6.0f;
    float startX = (SCREEN_WIDTH - (cols * bw + (cols - 1) * sx)) / 2;
    float startY = 60.0f;

    for (int r = 0; r < rows; r++) {
        int hp = (r <= 1) ? 3 : ((r <= 3) ? 2 : 1);
        for (int c = 0; c < cols; c++) {
            blocks.push_back(Block(startX + c * (bw + sx), startY + r * (bh + sy), bw, bh, hp));
        }
    }
}

void Game::Update(float deltaTime) {

    switch (state) {
    case STATE_MENU:
        if (IsKeyPressed(KEY_ENTER)) {
            score = 0; lives = 3;
            InitLevel();
            state = STATE_GAMEPLAY;
        }
        break;

    case STATE_GAMEPLAY: {
        paddle.Update(deltaTime);
        for (auto& ball : balls) ball.Update(deltaTime);
        for (auto& p : powerups) p.Update(deltaTime);

        for (int i = (int)balls.size() - 1; i >= 0; i--) {
            if (!balls[i].IsActive()) balls.erase(balls.begin() + i);
        }

        if (balls.empty()) {
            lives--;
            if (lives <= 0) state = STATE_GAMEOVER;
            else balls.push_back(Ball());
        }

        CheckCollisions();

        for (int i = (int)powerups.size() - 1; i >= 0; i--) {
            if (!powerups[i].IsActive()) powerups.erase(powerups.begin() + i);
        }

        bool allDestroyed = true;
        for (const auto& b : blocks) {
            if (b.IsActive()) { allDestroyed = false; break; }
        }
        if (allDestroyed) {
            state = STATE_VICTORY;
        }
        break;
    }
    case STATE_GAMEOVER:
    case STATE_VICTORY:
        if (IsKeyPressed(KEY_R)) {
            score = 0; lives = 3;
            InitLevel();
            state = STATE_GAMEPLAY;
        }
        if (IsKeyPressed(KEY_M)) state = STATE_MENU;
        break;
    }
}

void Game::CheckCollisions() {
    // 1. Проверяем столкновения МЯЧЕЙ
    for (auto& ball : balls) {
        ball.CollideWithPaddle(paddle.GetRect());

        for (auto& block : blocks) {
            if (block.IsActive() && ball.CollideWithBlock(block.GetRect())) {
                block.Hit();
                score += 10;


                if (!block.IsActive()) {
                    score += 20;
                    if (GetRandomValue(1, 100) <= 25) {
                        PowerUpType type = (PowerUpType)GetRandomValue(0, 2);
                        Vector2 pos = { block.GetRect().x + block.GetRect().width / 2, block.GetRect().y + block.GetRect().height / 2 };
                        powerups.push_back(PowerUp(pos, type));
                    }
                }
                break;
            }
        }
    }

    for (auto& p : powerups) {
        if (p.IsActive() && CheckCollisionCircleRec(p.GetPosition(), p.GetRadius(), paddle.GetRect())) {
            PowerUpType type = p.GetType();
            paddle.ApplyPowerUp(type);

            if (type == POWERUP_MULTIBALL) {
                Ball newBall;
                newBall.SetPosition({ paddle.GetRect().x + paddle.GetRect().width / 2, paddle.GetRect().y - 20 });
                newBall.SetSpeed({ 300.0f, -400.0f });
                balls.push_back(newBall);
            }
            else {
                for (auto& b : balls) b.ApplyPowerUp(type);
            }
            p.Deactivate();
            score += 50;
            powerupsCollected++;

        }
    }
}

void Game::Draw() const {
    BeginDrawing();
    ClearBackground({ 15, 15, 25, 255 });

    for (int i = 0; i < 50; i++) {
        DrawPixel((i * 123) % SCREEN_WIDTH, (i * 456) % SCREEN_HEIGHT, DARKGRAY);
    }

    switch (state) {
    case STATE_MENU:
        DrawText("ARCANOID", SCREEN_WIDTH / 2 - 150 + 2, 150 + 2, 60, DARKGRAY);
        DrawText("ARCANOID", SCREEN_WIDTH / 2 - 150, 150, 60, GOLD);
        DrawText("Use A/D or Arrow Keys to move paddle", SCREEN_WIDTH / 2 - 180, 280, 20, LIGHTGRAY);
        DrawText("Break all blocks to win!", SCREEN_WIDTH / 2 - 120, 310, 20, LIGHTGRAY);
        DrawText("[ ENTER ] - Start Game", SCREEN_WIDTH / 2 - 110, 400, 24, GREEN);
        DrawText("[ ESC ] - Exit", SCREEN_WIDTH / 2 - 70, 440, 20, RED);
        DrawText("Power-ups:", SCREEN_WIDTH / 2 - 50, 520, 18, WHITE);
        DrawText("W = Wide paddle | S = Slow ball | M = Multi-ball", SCREEN_WIDTH / 2 - 230, 545, 16, YELLOW);
        break;

    case STATE_GAMEPLAY:
        paddle.Draw();
        for (const auto& ball : balls) ball.Draw();
        for (const auto& b : blocks) b.Draw();
        for (const auto& p : powerups) p.Draw();

        DrawRectangle(0, 0, SCREEN_WIDTH, 30, DARKGRAY);
        DrawText(TextFormat("SCORE: %05i", score), 10, 5, 20, WHITE);
        DrawText(TextFormat("LIVES: %i", lives), 200, 5, 20, WHITE);
        DrawText(TextFormat("BALLS: %i", (int)balls.size()), 350, 5, 20, WHITE);
        DrawText("W=Wide S=Slow M=Multi", SCREEN_WIDTH - 200, 5, 16, YELLOW);

        break;

    case STATE_GAMEOVER:
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 180 });
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 150 + 3, 200 + 3, 50, BLACK);
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 150, 200, 50, RED);
        DrawText(TextFormat("Final Score: %i", score), SCREEN_WIDTH / 2 - 100, 280, 30, WHITE);
        DrawText("[ R ] - Restart", SCREEN_WIDTH / 2 - 70, 400, 24, GREEN);
        DrawText("[ M ] - Main Menu", SCREEN_WIDTH / 2 - 90, 440, 20, LIGHTGRAY);
        break;

    case STATE_VICTORY:
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 50, 40, 0, 180 });
        DrawText("VICTORY!", SCREEN_WIDTH / 2 - 130 + 3, 180 + 3, 60, BLACK);
        DrawText("VICTORY!", SCREEN_WIDTH / 2 - 130, 180, 60, GOLD);
        DrawText(TextFormat("Final Score: %i", score), SCREEN_WIDTH / 2 - 100, 270, 30, WHITE);
        DrawText("[ R ] - Play Again", SCREEN_WIDTH / 2 - 90, 400, 24, GREEN);
        DrawText("[ M ] - Main Menu", SCREEN_WIDTH / 2 - 90, 440, 20, LIGHTGRAY);
        break;
    }
    EndDrawing();
}