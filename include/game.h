#ifndef GAME_H
#define GAME_H

// ============================================================================
// Board Functions
// ============================================================================
void drawBoard();
void resetBoard();

// ============================================================================
// Coin Functions
// ============================================================================
void printCoin();
void eraseCoin();
void generateCoin();
void placeCoinInBoard();
bool isPositionEmpty(int x, int y);

// ============================================================================
// Score Functions
// ============================================================================
void setHighScore();

// ============================================================================
// Difficulty Functions
// ============================================================================
void setHealth();
void setBarriers(bool &barrier1, bool &barrier3);
void printBarriers(bool barrier1, bool barrier3);
void eraseBarriers(bool barrier1, bool barrier3);
void setBarrierStatus(bool &barrier1, bool &barrier3);

// ============================================================================
// Utility Functions
// ============================================================================
bool inBoard(char c);
void cleanChar(char character);
void resetAllValues();

// ============================================================================
// Input Validation
// ============================================================================
int getNum(const char* prompt);
bool checkInt(const char* num);
int strToInt(const char* num);

#endif // GAME_H
