#ifndef ENTITY_H
#define ENTITY_H

#include "constants.h"

// ============================================================================
// Generic Entity Functions
// ============================================================================

// Print/erase entities (sprite array uses WIDTH+1 for null terminator)
void printEntity(int x, int y, char sprite[][ENEMY_WIDTH + 1], int height, int width, int color);
void eraseEntity(int x, int y, int height, int width);

// Hitbox management
void createEnemyHitbox(int x, int y, char hitboxChar);
void eraseEnemyHitbox(int x, int y);

// Direction management
void changeEnemyDirection(int x, int y, char &direction);

// Generic enemy fire functions (legacy - use optimized versions below)
void initEnemyFire(int enemyX, int enemyY, int &fireX, int &fireY, char bulletChar);
void eraseEnemyFire(int fireY, char bulletChar);
void printEnemyFire(int fireY, char bulletChar, int color);
void moveEnemyFireGeneric(int &fireY, char bulletChar, int color,
                          bool &fireActive, bool &playerCollision, bool &playerHitByThis);

// Optimized enemy fire functions (use tracked position directly - O(1) instead of O(n))
void eraseEnemyFireDirect(int fireX, int fireY);
void printEnemyFireDirect(int fireX, int fireY, char bulletChar, int color);
void moveEnemyFireOptimized(int &fireX, int &fireY, char bulletChar, int color,
                            bool &fireActive, bool &playerCollision, bool &playerHitByThis);

// ============================================================================
// Player Functions
// ============================================================================
void erasePlayer();
void printPlayer();
void movePlayer(char direction);
void createPlayerHitbox();
void erasePlayerHitbox();

// Player fire
void playerFire();
void movePlayerFire();
void erasePlayerFire();
void printPlayerFire();

// ============================================================================
// Enemy 1 Functions
// ============================================================================
void eraseEnemy1();
void printEnemy1();
void changeDirectionEnemy1(char &direction);
void createEnemy1Hitbox();
void eraseEnemy1Hitbox();
void moveEnemy1(char direction);

// Enemy 1 fire
void enemy1Fire();
void moveEnemy1Fire();
void eraseEnemy1Fire();
void printEnemy1Fire();

// ============================================================================
// Enemy 2 Functions
// ============================================================================
void eraseEnemy2();
void printEnemy2();
void changeDirectionEnemy2(char &direction);
void createEnemy2Hitbox();
void eraseEnemy2Hitbox();
void moveEnemy2(char direction);

// Enemy 2 fire
void enemy2Fire();
void moveEnemy2Fire();
void eraseEnemy2Fire();
void printEnemy2Fire();

// ============================================================================
// Enemy 3 Functions
// ============================================================================
void eraseEnemy3();
void printEnemy3();
void changeDirectionEnemy3(char &direction);
void createEnemy3Hitbox();
void eraseEnemy3Hitbox();
void moveEnemy3(char direction);

// Enemy 3 fire
void enemy3Fire();
void moveEnemy3Fire();
void eraseEnemy3Fire();
void printEnemy3Fire();

#endif // ENTITY_H
