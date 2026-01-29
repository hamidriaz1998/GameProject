#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

// ============================================================================
// Structs
// ============================================================================
struct Projectile {
    int x;
    int y;
    bool active;
    char bulletChar;
    
    void reset() {
        x = 0;
        y = 0;
        active = false;
    }
};

struct Entity {
    int x;
    int y;
    int health;
    int maxHealth;
    int damage;              // Damage dealt to player
    Color color;
    char identifier;         // Character used to identify in board ('p', 'X', 'Y', 'Z')
    char hitboxChar;         // Character used for hitbox ('.', ',', ';', '~')
    Direction direction;
    Projectile projectile;
    bool collision;          // Did this entity get hit?
    bool hitPlayer;          // Did this entity's projectile hit the player?
    
    void reset(int startX, int startY, int startHealth) {
        x = startX;
        y = startY;
        health = startHealth;
        maxHealth = startHealth;
        direction = DIR_RIGHT;
        collision = false;
        hitPlayer = false;
        projectile.reset();
    }
};

struct GameState {
    int score;
    int difficulty;
    bool gameOver;
    bool coin;
    bool coinCollision;
    int coinX;
    int coinY;
    bool barrier1Erased;
    bool barrier3Erased;
    int highScores[MAX_HIGH_SCORES];
    
    void reset() {
        score = 0;
        gameOver = false;
        coin = false;
        coinCollision = false;
        coinX = 0;
        coinY = 0;
        barrier1Erased = false;
        barrier3Erased = false;
    }
};

#endif // TYPES_H
