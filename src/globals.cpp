#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/types.h"

// ============================================================================
// Global Variable Definitions
// ============================================================================

// Game board
char board[BOARD_HEIGHT][BOARD_WIDTH];

// Player sprite (each row is exactly 8 visible characters)
// Array size is [HEIGHT][WIDTH+1] to accommodate null terminator from string literals
char playerSprite[PLAYER_HEIGHT][PLAYER_WIDTH + 1] = {
    "   /\\   ",
    "  /  \\  ",
    " / P  \\ ",
    "--------",
    "  ||||  "
};

// Enemy sprites (each row is exactly 8 visible characters)
char enemySprites[3][ENEMY_HEIGHT][ENEMY_WIDTH + 1] = {
    {
        "  ||||  ",
        "--------",
        " \\ X  / ",
        "  \\  /  ",
        "   \\/   "
    },
    {
        "  ||||  ",
        "--------",
        " \\ Y  / ",
        "  \\  /  ",
        "   \\/   "
    },
    {
        "  ||||  ",
        "--------",
        " \\ Z  / ",
        "  \\  /  ",
        "   \\/   "
    }
};

// Game state instance
GameState gameState;

// Entity instances
Entity player;
Entity enemies[3];

// Screen positioning (for menu rendering)
int screenX = 0, screenY = 0;

// Legacy sprite aliases (WIDTH+1 for null terminator)
char (&player2D)[PLAYER_HEIGHT][PLAYER_WIDTH + 1] = playerSprite;
char (&enemy1)[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = enemySprites[0];
char (&enemy2)[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = enemySprites[1];
char (&enemy3)[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = enemySprites[2];

// ============================================================================
// Legacy Variables (kept for compatibility during refactoring)
// ============================================================================

// Screen positioning
int X = 0, Y = 0;

// Coin state
bool coin = false, coinCollision = false;
int coinX = 0, coinY = 0;

// Player state
int pX = 30;
int pY = 7, pHealth = 5;

// Player fire state
int pFireX = 0, pFireY = 0;
bool pFire = false, pcollision = false;

// Enemy 1 state
int e1X = 2, e1Y = 9, e1Health = 5;
int e1FireX = 0, e1FireY = 0;
bool e1Fire = false, collision1 = false, pCollsionByE1 = false;

// Enemy 2 state
int e2X = 14, e2Y = 56, e2Health = 5;
int e2FireX = 0, e2FireY = 0;
bool e2Fire = false, collision2 = false, pCollsionByE2 = false;

// Enemy 3 state
int e3X = 2, e3Y = 45, e3Health = 5;
int e3FireX = 0, e3FireY = 0;
bool e3Fire = false, collision3 = false, pCollsionByE3 = false;

// Score and difficulty
int score = 0;
int highScore[5] = {0, 0, 0, 0, 0};
int difficulty = 1;

// Barrier state
bool barrier1Erased = false, barrier3Erased = false;

// Game state
bool gameOver = false;
