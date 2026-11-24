#pragma once
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

enum GameState {
    STATE_MENU,
    STATE_GAMEPLAY,
    STATE_GAMEOVER,
    STATE_VICTORY
};

enum PowerUpType {
    POWERUP_WIDEN,
    POWERUP_SPEEDY,
    POWERUP_MULTIBALL
};