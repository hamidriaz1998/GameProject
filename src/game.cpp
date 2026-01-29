#include "../include/game.h"
#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/console.h"
#include "../include/entity.h"
#include <string>
#include <cstdlib>
#include <cstring>

// ============================================================================
// Board Functions
// ============================================================================

void drawBoard()
{
    board[pX][pY] = 'p';
    board[e1X][e1Y] = 'X';
    board[e2X][e2Y] = 'Y';
    board[e3X][e3Y] = 'Z';
    printPlayer();
    printEnemy1();
    printEnemy2();
    printEnemy3();
    setColor(magenta);
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            gotoxy(j, i);
            printChar(board[i][j]);
        }
    }
    setColor(white);
}

void resetBoard()
{
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] != '#')
                board[i][j] = ' ';
        }
    }
}

// ============================================================================
// Coin Functions
// ============================================================================

void printCoin()
{
    setColor(yellow);
    gotoxy(coinY, coinX);
    printChar('$');
    setColor(white);
}

void eraseCoin()
{
    gotoxy(coinY, coinX);
    printChar(' ');
}

void generateCoin()
{
    // Safe range: rows 2-25 (above player area), columns 3-85 (away from walls)
    const int minRow = 2;
    const int maxRow = boardHeight - 11;  // Stay above player area
    const int minCol = 3;
    const int maxCol = boardWidth - 5;
    
    int attempts = 0;
    const int maxAttempts = 100;  // Prevent infinite loop
    
    while (attempts < maxAttempts)
    {
        coinX = minRow + (rand() % (maxRow - minRow + 1));
        coinY = minCol + (rand() % (maxCol - minCol + 1));
        
        if (coinX >= 0 && coinX < boardHeight && 
            coinY >= 0 && coinY < boardWidth && 
            isPositionEmpty(coinX, coinY))
        {
            break;
        }
        attempts++;
    }
}

void placeCoinInBoard()
{
    board[coinX][coinY] = '$';
}

bool isPositionEmpty(int x, int y)
{
    if (board[x][y] == ' ')
    {
        return true;
    }
    return false;
}

// ============================================================================
// Score Functions
// ============================================================================

void setHighScore()
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (score > highScore[i])
        {
            break;
        }
    }

    if (i < 5) // if score is greater than any of the high scores
    {
        for (int j = 4; j > i; j--)
        {
            highScore[j] = highScore[j - 1];
        }
        highScore[i] = score;
    }
}

// ============================================================================
// Difficulty Functions
// ============================================================================

void setHealth()
{
    if (difficulty == 1)
    {
        e1Health = 5;
        e2Health = 3;
        e3Health = 4;
        pHealth = 7;
    }
    else if (difficulty == 2)
    {
        e1Health = 7;
        e2Health = 5;
        e3Health = 6;
        pHealth = 6;
    }
    else
    {
        e1Health = 8;
        e2Health = 6;
        e3Health = 7;
        pHealth = 4;
    }
}

void setBarriers(bool &barrier1, bool &barrier3)
{
    if (difficulty == 1)
    {
        barrier1 = true;
        barrier3 = true;
    }
    else if (difficulty == 2)
    {
        barrier1 = true;
        barrier3 = false;
    }
    else
    {
        barrier1 = false;
        barrier3 = false;
    }
}

void printBarriers(bool barrier1, bool barrier3)
{
    if (barrier3)
    {
        for (int i = 43; i < boardWidth - 2; i++)
        {
            board[8][i] = '#';
        }
    }
    if (barrier1)
    {
        for (int i = 1; i < 44; i++)
        {
            board[8][i] = '#';
        }
    }
}

void eraseBarriers(bool barrier1, bool barrier3)
{
    if (!barrier3)
    {
        for (int i = 43; i < boardWidth - 2; i++)
        {
            board[8][i] = ' ';
            gotoxy(i, 8);
            printChar(' ');
        }
    }
    if (!barrier1)
    {
        for (int i = 1; i < 44; i++)
        {
            board[8][i] = ' ';
            gotoxy(i, 8);
            printChar(' ');
        }
    }
}

void setBarrierStatus(bool &barrier1, bool &barrier3)
{
    if (difficulty == 1 && e2Health <= 0 && !barrier3Erased)
    {
        barrier3 = false;
        eraseBarriers(barrier1, barrier3);
        barrier3Erased = true;
    }
    if (difficulty == 1 && e3Health <= 0 && !barrier1Erased)
    {
        barrier1 = false;
        eraseBarriers(barrier1, barrier3);
        barrier1Erased = true;
    }
    if (difficulty == 2 && e2Health <= 0 && e3Health <= 0 && !barrier1Erased)
    {
        barrier1 = false;
        eraseBarriers(barrier1, barrier3);
        barrier1Erased = true;
    }
}

// ============================================================================
// Utility Functions
// ============================================================================

// DEPRECATED: This function scans the entire board O(n*m) to find a character.
// For projectile tracking, use the direct position tracking in entity.cpp instead.
// Kept for backward compatibility with any code that still uses it.
bool inBoard(char c)
{
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == c)
            {
                return true;
            }
        }
    }
    return false;
}

void cleanChar(char character)
{
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == character)
            {
                board[i][j] = ' ';
            }
        }
    }
}

void resetAllValues()
{
    pX = 30;
    pY = 7;
    e1X = 2;
    e1Y = 9;
    e2X = 14;
    e2Y = 56;
    e3X = 2;
    e3Y = 45;
    pHealth = 5;
    e1Health = 5;
    e2Health = 5;
    e3Health = 5;
    score = 0;
    pFire = false;
    e1Fire = false;
    e2Fire = false;
    e3Fire = false;
    collision1 = false;
    collision2 = false;
    collision3 = false;
    pcollision = false;
    pCollsionByE1 = false;
    pCollsionByE2 = false;
    pCollsionByE3 = false;
    coin = false;
    coinCollision = false;
    barrier1Erased = false;
    barrier3Erased = false;
    gameOver = false;
}

// ============================================================================
// Input Validation
// ============================================================================

int getNum(const char* prompt)
{
    char num[32];
    while (true)
    {
        setColor(yellow);
        gotoxy(X, Y++);
        printString(prompt);
        refreshScreen();
        readString(num, sizeof(num));
        setColor(white);
        if (checkInt(num))
        {
            return strToInt(num);
        }
        else
        {
            setColor(red);
            gotoxy(X, Y++);
            printString("Invalid Input.");
            setColor(white);
            gotoxy(X, Y++);
            printString("Press any key to try again...................");
            refreshScreen();
            waitForKey();
        }
    }
}

bool checkInt(const char* num)
{
    size_t len = strlen(num);
    if (len == 0) return false;
    for (size_t i = 0; i < len; i++)
    {
        if (num[i] < '0' || num[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int strToInt(const char* num)
{
    int result = 0;
    size_t len = strlen(num);
    for (size_t i = 0; i < len; i++)
    {
        result = result * 10 + (num[i] - '0');
    }
    return result;
}
