#include <iostream>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);
// Board
void drawBoard();
// Player
void erasePlayer();
void printPlayer();
void movePlayer(char direction);
void createPlayerHitbox();
void playerFire();
void moveFire();
int pX = 0, pY = 0, pHealth = 5;
bool pFire = false;
// Enemies
void createEnemyHitbox();
// Enemy 1
void eraseEnemy1();
void printEnemy1();
void changeDirectionEnemy1(char &direction);
void moveEnemy1(char direction);
int e1X = 0, e1Y = 0, e1Health = 5;
bool e1Fire = false;
// Enemy 2
void eraseEnemy2();
void printEnemy2();
void changeDirectionEnemy2(char &direction);
void moveEnemy2(char direction);
int e2X = 0, e2Y = 0, e2Health = 5;
bool e2Fire = false;
// Enemy 3
void eraseEnemy3();
void printEnemy3();
void changeDirectionEnemy3(char &direction);
void moveEnemy3(char direction);
int e3X = 0, e3Y = 0, e3Health = 5;
bool e3Fire = false;

const int playerHeight = 5;
const int playerWidth = 9;
const int enemyHeight = 5;
const int enemyWidth = 9;
const int boardHeight = 36, boardWidth = 90;

char board[boardHeight][boardWidth] = {
    "#########################################################################################",
    "#                                     #                                                 #",
    "#                                     #                                                 #",
    "#                                     #                                                 #",
    "#                                     #                                                 #",
    "#        X                            #                 Z                               #",
    "#                                     #                                                 #",
    "#                                     #                                                 #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                            Y                                          #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#     p                                                                                 #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#                                                                                       #",
    "#########################################################################################"};

char player2D[playerHeight][playerWidth] = {
    "   /\\   ",
    "  /  \\  ",
    " / P  \\ ",
    "-------",
    "  ||||  "};
char enemy1[enemyHeight][enemyWidth] = {
    "  ||||  ",
    "-------",
    " \\ X  / ",
    "  \\  /  ",
    "   \\/   "};
char enemy2[enemyHeight][enemyWidth] = {
    "  ||||  ",
    "-------",
    " \\ Y  / ",
    "  \\  /  ",
    "   \\/   "};
char enemy3[enemyHeight][enemyWidth] = {
    "  ||||  ",
    "-------",
    " \\ Z  / ",
    "  \\  /  ",
    "   \\/   "};
int main()
{
    char dir1 = 'r';
    char dir2 = 'r';
    char dir3 = 'r';
    system("cls");
    drawBoard();
    printPlayer();
    printEnemy1();
    printEnemy2();
    printEnemy3();
    createPlayerHitbox();
    createEnemyHitbox();

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayer('l');
            // Testing
            // moveEnemy1(board, 'l');
            // moveEnemy2(board, 'l');
            // moveEnemy3(board, 'l');
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer('r');
            // Testing
            // moveEnemy1(board, 'r');
            // moveEnemy2(board, 'r');
            // moveEnemy3(board, 'r');
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            if (!pFire)
            {
                playerFire();
                pFire = true;
            }
        }
        createPlayerHitbox();
        if (e1Health != 0)
        {
            changeDirectionEnemy1(dir1);
            // moveEnemy1(dir1);
        }
        if (e2Health != 0)
        {
            changeDirectionEnemy2(dir2);
            moveEnemy2(dir2);
        }
        if (e3Health != 0)
        {
            changeDirectionEnemy3(dir3);
            moveEnemy3(dir3);
        }
        createEnemyHitbox();

        Sleep(100);
    }

    return 1;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void drawBoard()
{
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == 'p')
            {
                pX = i;
                pY = j;
                printPlayer();
            }
            else if (board[i][j] == 'X')
            {
                e1X = i;
                e1Y = j;
                printEnemy1();
            }
            else if (board[i][j] == 'Y')
            {
                e2X = i;
                e2Y = j;
                printEnemy2();
            }
            else if (board[i][j] == 'Z')
            {
                e3X = i;
                e3Y = j;
                printEnemy3();
            }
            else
            {
                gotoxy(j, i);
                cout << board[i][j];
            }
        }
    }
}

void erasePlayer()
{
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(pY + j, pX + i);
            cout << " ";
        }
    }
}
void printPlayer()
{
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(pY + j, pX + i);
            cout << player2D[i][j];
        }
    }
}
void movePlayer(char direction)
{
    erasePlayer();
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
}
void createPlayerHitbox(){
    for (int i = 0; i < 6; i++)
    {
        board[pX][pY + i] = '.';
    }
}
void playerFire()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (board[i][j] == 'p')
            {
                board[i-1][j] = '|';
            }
        }
    }
}
void moveFire() { // the idea for collsion detection is to create a function that checks if in surrounding cells there is an enemy character
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 21; j++) {
            if (board[i][j] == '|') {
                if (board[i-1][j] != '#') { // If the cell above is not a wall
                    if (board[i-1][j] == 'e') { // If the cell above is an enemy
                        // Remove the enemy and the fire
                        board[i][j] = ' ';
                        board[i-1][j] = ' ';
                    } else {
                        // Move the fire up
                        board[i][j] = ' ';
                        board[i-1][j] = '|';
                    }
                } else {
                    // Remove the fire if it hits a wall
                    board[i][j] = ' ';
                }
            }
        }
    }
}
void createEnemyHitbox()
{
    for (int i = 0; i < 6; i++)
    {
        board[e1X + 4][e1Y + i] = '.';
        board[e2X + 4][e2Y + i] = '.';
        board[e3X + 4][e3Y + i] = '.';
    }
}
void printEnemy1()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e1Y + j, e1X + i);
            cout << enemy1[i][j];
        }
    }
}
void eraseEnemy1()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e1Y + j, e1X + i);
            cout << " ";
        }
    }
}
void changeDirectionEnemy1(char &direction)
{
    if (direction == 'l' && board[e1X][e1Y - 1] == '#')
    {
        direction = 'r';
    }
    else if (direction == 'r' && board[e1X][e1Y + 9] == '#')
    {
        direction = 'l';
    }
}
void moveEnemy1(char direction)
{
    eraseEnemy1();
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
}

void printEnemy2()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e2Y + j, e2X + i);
            cout << enemy2[i][j];
        }
    }
}
void eraseEnemy2()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e2Y + j, e2X + i);
            cout << " ";
        }
    }
}
void changeDirectionEnemy2(char &direction)
{
    if (direction == 'l' && board[e2X][e2Y - 1] == '#')
    {
        direction = 'r';
    }
    else if (direction == 'r' && board[e2X][e2Y + 9] == '#')
    {
        direction = 'l';
    }
}
void moveEnemy2(char direction)
{
    eraseEnemy2();
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
}
void printEnemy3()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e3Y + j, e3X + i);
            cout << enemy3[i][j];
        }
    }
}
void eraseEnemy3()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(e3Y + j, e3X + i);
            cout << " ";
        }
    }
}
void changeDirectionEnemy3(char &direction)
{
    if (direction == 'l' && board[e3X][e3Y - 1] == '#')
    {
        direction = 'r';
    }
    else if (direction == 'r' && board[e3X][e3Y + 9] == '#')
    {
        direction = 'l';
    }
}
void moveEnemy3(char direction)
{
    eraseEnemy3();
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
}
