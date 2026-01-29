#include "../include/entity.h"
#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/console.h"

// ============================================================================
// Generic Entity Functions
// ============================================================================

void printEntity(int x, int y, char sprite[][ENEMY_WIDTH + 1], int height, int width, int color)
{
    setColor(color);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gotoxy(y + j, x + i);
            printChar(sprite[i][j]);
        }
    }
    setColor(white);
}

void eraseEntity(int x, int y, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gotoxy(y + j, x + i);
            printChar(' ');
        }
    }
}

void createEnemyHitbox(int x, int y, char hitboxChar)
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[x + i][y] = hitboxChar;
            board[x + i][y + 5] = hitboxChar;
        }
        if (i < 6)
        {
            board[x + 4][y + i] = hitboxChar;
        }
    }
}

void eraseEnemyHitbox(int x, int y)
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[x + i][y] = ' ';
            board[x + i][y + 5] = ' ';
        }
        if (i < 6)
        {
            board[x + 4][y + i] = ' ';
        }
    }
}

void changeEnemyDirection(int x, int y, char &direction)
{
    if (direction == 'l' && board[x][y - 1] == '#')
    {
        direction = 'r';
    }
    else if (direction == 'r' && board[x][y + 9] == '#')
    {
        direction = 'l';
    }
}

void initEnemyFire(int enemyX, int enemyY, int &fireX, int &fireY, char bulletChar)
{
    fireX = enemyX + 4;
    fireY = enemyY + 3;
    board[fireX][fireY] = bulletChar;
}

// Optimized: Use tracked position directly instead of scanning board
void eraseEnemyFireDirect(int fireX, int fireY)
{
    gotoxy(fireY, fireX);
    printChar(' ');
}

// Optimized: Use tracked position directly instead of scanning board
void printEnemyFireDirect(int fireX, int fireY, char bulletChar, int color)
{
    if (board[fireX][fireY] == bulletChar)
    {
        setColor(color);
        gotoxy(fireY, fireX);
        printChar(bulletChar);
        setColor(white);
    }
}

// Legacy functions kept for compatibility (can be removed later)
void eraseEnemyFire(int fireY, char bulletChar)
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][fireY] == bulletChar)
        {
            gotoxy(fireY, i);
            printChar(' ');
            break;
        }
    }
}

void printEnemyFire(int fireY, char bulletChar, int color)
{
    setColor(color);
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][fireY] == bulletChar)
        {
            gotoxy(fireY, i);
            printChar(board[i][fireY]);
            break;
        }
    }
    setColor(white);
}

// Optimized: Use tracked position directly instead of scanning board
void moveEnemyFireOptimized(int &fireX, int &fireY, char bulletChar, int color,
                            bool &fireActive, bool &playerCollision, bool &playerHitByThis)
{
    // Erase at current position
    eraseEnemyFireDirect(fireX, fireY);
    
    if (board[fireX + 1][fireY] != '#')
    {
        // Check for player collision
        if (board[fireX + 1][fireY] == 'p' || board[fireX + 1][fireY] == '.' ||
            board[fireX][fireY + 1] == '.' || board[fireX][fireY - 1] == '.' ||
            board[fireX][fireY + 1] == 'p' || board[fireX][fireY - 1] == 'p')
        {
            playerCollision = true;
            playerHitByThis = true;
            board[fireX][fireY] = ' ';
            board[fireX + 1][fireY] = ' ';
            fireActive = false;
        }
        else
        {
            // Move the fire down
            board[fireX][fireY] = ' ';
            fireX++;
            board[fireX][fireY] = bulletChar;
        }
    }
    else
    {
        // Remove the fire if it hits a wall
        board[fireX][fireY] = ' ';
        fireActive = false;
    }
    
    // Print at new position
    if (fireActive)
    {
        printEnemyFireDirect(fireX, fireY, bulletChar, color);
    }
}

// Legacy function kept for compatibility
void moveEnemyFireGeneric(int &fireY, char bulletChar, int color,
                          bool &fireActive, bool &playerCollision, bool &playerHitByThis)
{
    eraseEnemyFire(fireY, bulletChar);
    for (int i = 1; i <= boardHeight; i++)
    {
        if (board[i][fireY] == bulletChar)
        {
            if (board[i + 1][fireY] != '#')
            {
                // Check for player collision
                if (board[i + 1][fireY] == 'p' || board[i + 1][fireY] == '.' ||
                    board[i][fireY + 1] == '.' || board[i][fireY - 1] == '.' ||
                    board[i][fireY + 1] == 'p' || board[i][fireY - 1] == 'p')
                {
                    playerCollision = true;
                    playerHitByThis = true;
                    board[i][fireY] = ' ';
                    board[i + 1][fireY] = ' ';
                    fireActive = false;
                }
                else
                {
                    // Move the fire down
                    board[i][fireY] = ' ';
                    board[i + 1][fireY] = bulletChar;
                }
            }
            else
            {
                // Remove the fire if it hits a wall
                board[i][fireY] = ' ';
                fireActive = false;
            }
            break;
        }
    }
    printEnemyFire(fireY, bulletChar, color);
}

// ============================================================================
// Player Functions
// ============================================================================

void erasePlayer()
{
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(pY + j, pX + i);
            printChar(' ');
        }
    }
}

void printPlayer()
{
    setColor(green);
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(pY + j, pX + i);
            printChar(player2D[i][j]);
        }
    }
    setColor(white);
}

void movePlayer(char direction)
{
    erasePlayer();
    erasePlayerHitbox();
    board[pX][pY] = ' ';
    if (direction == 'l' && board[pX][pY - 1] != '#') // Boards left end
    {
        pY = pY - 1;
    }
    else if (direction == 'r' && board[pX][pY + 10] != '#') // Boards right end
    {
        pY = pY + 1;
    }
    board[pX][pY] = 'p';
    printPlayer();
    createPlayerHitbox();
}

void createPlayerHitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 6)
        {
            board[pX][pY + i] = '.';
        }
        if (i < 4)
        {
            board[pX + i][pY] = '.';
            board[pX + i][pY + 5] = '.';
        }
    }
}

void erasePlayerHitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 6)
        {
            board[pX][pY + i] = ' ';
        }
        if (i < 4)
        {
            board[pX + i][pY] = ' ';
            board[pX + i][pY + 5] = ' ';
        }
    }
}

void playerFire()
{
    pFireX = pX - 1;
    pFireY = pY + 3;
    board[pFireX][pFireY] = '|';
}

// Optimized: Use tracked pFireX position directly instead of scanning board
void movePlayerFire()
{
    // Erase at current position
    gotoxy(pFireY, pFireX);
    printChar(' ');
    
    if (board[pFireX - 1][pFireY] != '#')
    {
        // Check for enemy 1 collision
        if (board[pFireX - 1][pFireY] == 'X' || board[pFireX - 1][pFireY] == ',' || 
            board[pFireX][pFireY + 1] == ',' || board[pFireX][pFireY - 1] == ',' || 
            board[pFireX][pFireY + 1] == 'X' || board[pFireX][pFireY - 1] == 'X')
        {
            collision1 = true;
            board[pFireX][pFireY] = ' ';
            board[pFireX - 1][pFireY] = ' ';
            pFire = false;
        }
        // Check for enemy 2 collision
        else if (board[pFireX - 1][pFireY] == 'Y' || board[pFireX - 1][pFireY] == ';' || 
                 board[pFireX][pFireY + 1] == ';' || board[pFireX][pFireY - 1] == ';' || 
                 board[pFireX][pFireY + 1] == 'Y' || board[pFireX][pFireY - 1] == 'Y')
        {
            collision2 = true;
            board[pFireX][pFireY] = ' ';
            board[pFireX - 1][pFireY] = ' ';
            pFire = false;
        }
        // Check for enemy 3 collision
        else if (board[pFireX - 1][pFireY] == 'Z' || board[pFireX - 1][pFireY] == '~' || 
                 board[pFireX][pFireY + 1] == '~' || board[pFireX][pFireY - 1] == '~' || 
                 board[pFireX][pFireY + 1] == 'Z' || board[pFireX][pFireY - 1] == 'Z')
        {
            collision3 = true;
            board[pFireX][pFireY] = ' ';
            board[pFireX - 1][pFireY] = ' ';
            pFire = false;
        }
        // Check for coin collision
        else if (board[pFireX - 1][pFireY] == '$')
        {
            coinCollision = true;
            board[pFireX][pFireY] = ' ';
            board[pFireX - 1][pFireY] = ' ';
            pFire = false;
            coin = false;
        }
        else
        {
            // Move the fire up
            board[pFireX][pFireY] = ' ';
            pFireX--;
            board[pFireX][pFireY] = '|';
        }
    }
    else
    {
        // Remove the fire if it hits a wall
        board[pFireX][pFireY] = ' ';
        pFire = false;
    }
    
    // Print at new position
    if (pFire)
    {
        setColor(green);
        gotoxy(pFireY, pFireX);
        printChar('|');
        setColor(white);
    }
}

// Optimized: Use tracked position directly
void erasePlayerFire()
{
    gotoxy(pFireY, pFireX);
    printChar(' ');
}

// Optimized: Use tracked position directly
void printPlayerFire()
{
    if (pFire && board[pFireX][pFireY] == '|')
    {
        setColor(green);
        gotoxy(pFireY, pFireX);
        printChar('|');
        setColor(white);
    }
}

// ============================================================================
// Enemy 1 Functions
// ============================================================================

void createEnemy1Hitbox()
{
    createEnemyHitbox(e1X, e1Y, ',');
}

void eraseEnemy1Hitbox()
{
    eraseEnemyHitbox(e1X, e1Y);
}

void printEnemy1()
{
    printEntity(e1X, e1Y, enemy1, enemyHeight, enemyWidth, brown);
}

void eraseEnemy1()
{
    eraseEntity(e1X, e1Y, enemyHeight, enemyWidth);
}

void changeDirectionEnemy1(char &direction)
{
    changeEnemyDirection(e1X, e1Y, direction);
}

void moveEnemy1(char direction)
{
    eraseEnemy1();
    eraseEnemy1Hitbox();
    board[e1X][e1Y] = ' ';
    if (direction == 'l')
    {
        e1Y = e1Y - 1;
    }
    else if (direction == 'r')
    {
        e1Y = e1Y + 1;
    }
    board[e1X][e1Y] = 'X';
    printEnemy1();
    createEnemy1Hitbox();
}

void enemy1Fire()
{
    initEnemyFire(e1X, e1Y, e1FireX, e1FireY, '!');
}

void moveEnemy1Fire()
{
    moveEnemyFireOptimized(e1FireX, e1FireY, '!', brown, e1Fire, pcollision, pCollsionByE1);
}

void eraseEnemy1Fire()
{
    eraseEnemyFireDirect(e1FireX, e1FireY);
}

void printEnemy1Fire()
{
    printEnemyFireDirect(e1FireX, e1FireY, '!', brown);
}

// ============================================================================
// Enemy 2 Functions
// ============================================================================

void createEnemy2Hitbox()
{
    createEnemyHitbox(e2X, e2Y, ';');
}

void eraseEnemy2Hitbox()
{
    eraseEnemyHitbox(e2X, e2Y);
}

void printEnemy2()
{
    printEntity(e2X, e2Y, enemy2, enemyHeight, enemyWidth, lightred);
}

void eraseEnemy2()
{
    eraseEntity(e2X, e2Y, enemyHeight, enemyWidth);
}

void changeDirectionEnemy2(char &direction)
{
    changeEnemyDirection(e2X, e2Y, direction);
}

void moveEnemy2(char direction)
{
    eraseEnemy2();
    eraseEnemy2Hitbox();
    board[e2X][e2Y] = ' ';
    if (direction == 'l')
    {
        e2Y = e2Y - 1;
    }
    else if (direction == 'r')
    {
        e2Y = e2Y + 1;
    }
    board[e2X][e2Y] = 'Y';
    printEnemy2();
    createEnemy2Hitbox();
}

void enemy2Fire()
{
    initEnemyFire(e2X, e2Y, e2FireX, e2FireY, 'I');
}

void moveEnemy2Fire()
{
    moveEnemyFireOptimized(e2FireX, e2FireY, 'I', lightred, e2Fire, pcollision, pCollsionByE2);
}

void eraseEnemy2Fire()
{
    eraseEnemyFireDirect(e2FireX, e2FireY);
}

void printEnemy2Fire()
{
    printEnemyFireDirect(e2FireX, e2FireY, 'I', lightred);
}

// ============================================================================
// Enemy 3 Functions
// ============================================================================

void createEnemy3Hitbox()
{
    createEnemyHitbox(e3X, e3Y, '~');
}

void eraseEnemy3Hitbox()
{
    eraseEnemyHitbox(e3X, e3Y);
}

void printEnemy3()
{
    printEntity(e3X, e3Y, enemy3, enemyHeight, enemyWidth, lightblue);
}

void eraseEnemy3()
{
    eraseEntity(e3X, e3Y, enemyHeight, enemyWidth);
}

void changeDirectionEnemy3(char &direction)
{
    changeEnemyDirection(e3X, e3Y, direction);
}

void moveEnemy3(char direction)
{
    eraseEnemy3();
    eraseEnemy3Hitbox();
    board[e3X][e3Y] = ' ';
    if (direction == 'l')
    {
        e3Y = e3Y - 1;
    }
    else if (direction == 'r')
    {
        e3Y = e3Y + 1;
    }
    board[e3X][e3Y] = 'Z';
    printEnemy3();
    createEnemy3Hitbox();
}

void enemy3Fire()
{
    initEnemyFire(e3X, e3Y, e3FireX, e3FireY, '[');
}

void moveEnemy3Fire()
{
    moveEnemyFireOptimized(e3FireX, e3FireY, '[', lightblue, e3Fire, pcollision, pCollsionByE3);
}

void eraseEnemy3Fire()
{
    eraseEnemyFireDirect(e3FireX, e3FireY);
}

void printEnemy3Fire()
{
    printEnemyFireDirect(e3FireX, e3FireY, '[', lightblue);
}
