#include <iostream>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);
// Board
void drawBoard();
// Player
void erasePlayer();
void printPlayer();
void movePlayer(char board[][90], char direction);
int pX = 20, pY = 20, pHealth = 5;
// Enemies 
// Enemy 1
void eraseEnemy1();
void printEnemy1();
void moveEnemy1(char board[][90], char direction);
int e1X = 2, e1Y = 2, e1Health = 5;
// Enemy 2
void eraseEnemy2();
void printEnemy2();
void moveEnemy2(char board[][90], char direction);
int e2X = 2, e2Y = 2, e2Health = 5;
// Enemy 3
void eraseEnemy3();
void printEnemy3();
void moveEnemy3(char board[][90], char direction);
int e3X = 2, e3Y = 2, e3Health = 5;

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
    "#                p                                                                      #",
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
    system("cls");
    drawBoard();
    printPlayer();
    printEnemy1();
    printEnemy2();
    printEnemy3();

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayer(board, 'l');
            // Testing
            // moveEnemy1(board, 'l');
            // moveEnemy2(board, 'l');
            // moveEnemy3(board, 'l');
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer(board, 'r');
            // Testing
            // moveEnemy1(board, 'r');
            // moveEnemy2(board, 'r');
            // moveEnemy3(board, 'r');
        }

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
void movePlayer(char board[][90], char direction)
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
void moveEnemy1(char board[][90], char direction)
{
    eraseEnemy1();
    board[e1X][e1Y] = ' ';
    if (direction == 'l' && board[e1X][e1Y - 1] != '#') // Boards left end
    {
        e1Y = e1Y - 1;
    }
    else if (direction == 'r' && board[e1X][e1Y + 9] != '#') // Boards right end
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
void moveEnemy2(char board[][90], char direction)
{
    eraseEnemy2();
    board[e2X][e2Y] = ' ';
    if (direction == 'l' && board[e2X][e2Y - 1] != '#') // Boards left end
    {
        e2Y = e2Y - 1;
    }
    else if (direction == 'r' && board[e2X][e2Y + 9] != '#') // Boards right end
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
void moveEnemy3(char board[][90], char direction)
{
    eraseEnemy3();
    board[e3X][e3Y] = ' ';
    if (direction == 'l' && board[e3X][e3Y - 1] != '#') // Boards left end
    {
        e3Y = e3Y - 1;
    }
    else if (direction == 'r' && board[e3X][e3Y + 9] != '#') // Boards right end
    {
        e3Y = e3Y + 1;
    }
    board[e3X][e3Y] = 'Z';
    printEnemy3();
}
