#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"
#include "types.h"

// ============================================================================
// Global Variables (extern declarations)
// ============================================================================

// Game board
extern char board[BOARD_HEIGHT][BOARD_WIDTH];

// Player sprite (WIDTH+1 for null terminator storage)
extern char playerSprite[PLAYER_HEIGHT][PLAYER_WIDTH + 1];

// Enemy sprites
extern char enemySprites[3][ENEMY_HEIGHT][ENEMY_WIDTH + 1];

// Game state instance
extern GameState gameState;

// Entity instances
extern Entity player;
extern Entity enemies[3];

// Screen positioning (for menu rendering)
extern int screenX, screenY;

// Legacy sprite aliases (WIDTH+1 for null terminator)
extern char (&player2D)[PLAYER_HEIGHT][PLAYER_WIDTH + 1];
extern char (&enemy1)[ENEMY_HEIGHT][ENEMY_WIDTH + 1];
extern char (&enemy2)[ENEMY_HEIGHT][ENEMY_WIDTH + 1];
extern char (&enemy3)[ENEMY_HEIGHT][ENEMY_WIDTH + 1];

// ============================================================================
// Legacy Variables (kept for compatibility during refactoring)
// ============================================================================

// Screen positioning
extern int X, Y;

// Coin state
extern bool coin, coinCollision;
extern int coinX, coinY;

// Player state
extern int pX, pY, pHealth;

// Player fire state
extern int pFireX, pFireY;
extern bool pFire, pcollision;

// Enemy 1 state
extern int e1X, e1Y, e1Health;
extern int e1FireX, e1FireY;
extern bool e1Fire, collision1, pCollsionByE1;

// Enemy 2 state
extern int e2X, e2Y, e2Health;
extern int e2FireX, e2FireY;
extern bool e2Fire, collision2, pCollsionByE2;

// Enemy 3 state
extern int e3X, e3Y, e3Health;
extern int e3FireX, e3FireY;
extern bool e3Fire, collision3, pCollsionByE3;

// Score and difficulty
extern int score;
extern int highScore[5];
extern int difficulty;

// Barrier state
extern bool barrier1Erased, barrier3Erased;

// Game state
extern bool gameOver;

#endif // GLOBALS_H
