#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "PowerUps.h"
#include <vector>

class Game {
private:
    GameState state;
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Block> blocks;
    std::vector<PowerUp> powerups;

    int score;
    int lives;
    int powerupsCollected;

    void InitLevel();
    void CheckCollisions();

public:
    Game();
    void Update(float deltaTime);
    void Draw() const;
};
