#ifndef CONSTANTS_H
#define CONSTANTS_H

// ============================================================================
// Game Constants
// ============================================================================
const int PLAYER_HEIGHT = 5;
const int PLAYER_WIDTH = 8;
const int ENEMY_HEIGHT = 5;
const int ENEMY_WIDTH = 8;
const int BOARD_HEIGHT = 36;
const int BOARD_WIDTH = 90;
const int FRAME_DELAY_MS = 30;
const int MAX_HIGH_SCORES = 5;

// Legacy constants (aliased for compatibility)
const int playerHeight = PLAYER_HEIGHT;
const int playerWidth = PLAYER_WIDTH;
const int enemyHeight = ENEMY_HEIGHT;
const int enemyWidth = ENEMY_WIDTH;
const int boardHeight = BOARD_HEIGHT;
const int boardWidth = BOARD_WIDTH;

// ============================================================================
// Enums
// ============================================================================
enum Color {
    COLOR_BLACK = 0, COLOR_BLUE = 1, COLOR_GREEN = 2, COLOR_CYAN = 3,
    COLOR_RED = 4, COLOR_MAGENTA = 5, COLOR_BROWN = 6, COLOR_LIGHTWHITE = 7,
    COLOR_DARKWHITE = 8, COLOR_LIGHTBLUE = 9, COLOR_LIGHTGREEN = 10,
    COLOR_LIGHTCYAN = 11, COLOR_LIGHTRED = 12, COLOR_LIGHTMAGENTA = 13,
    COLOR_YELLOW = 14, COLOR_WHITE = 15
};

enum Direction { DIR_LEFT, DIR_RIGHT };

enum GameScreen { 
    MAIN_MENU, PLAY_GAME, SET_DIFFICULTY, HIGH_SCORE, 
    INSTRUCTIONS, EXIT_GAME, GAME_OVER, LEVEL_COMPLETE, GAME_WON 
};

// Legacy color constants
const int black = 0, blue = 1, green = 2, cyan = 3, red = 4, magenta = 5;
const int brown = 6, lightwhite = 7, darkwhite = 8, lightblue = 9;
const int lightgreen = 10, lightcyan = 11, lightred = 12, lightmagenta = 13;
const int yellow = 14, white = 15;

#endif // CONSTANTS_H
