#include <iostream>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);
// Board
void drawBoard();
// Player
void erasePlayer();
void printPlayer();
void movePlayer(char board[][80], char direction);
int pX = 20, pY = 20;
// Enemies 
void moveEnemy(char board[][80], char direction,char enemyType);
// Enemy X
void eraseEnemy1();
void printEnemy1();
int e1X = 2, e1Y = 2;

const int playerHeight = 5;
const int playerWidth = 9;
const int enemyHeight = 5;
const int enemyWidth = 9;
const int boardHeight = 26, boardWidth = 80;

char board[boardHeight][boardWidth] = {
    "###############################################################################",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#        X                                                                    #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                p                                                            #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "#                                                                             #",
    "###############################################################################"};

char player2D[playerHeight][playerWidth] = {
    "   /\\   ",
    "  /  \\  ",
    " / P  \\ ",
    "-------",
    "  ||||  "};
char enemyX[enemyHeight][enemyWidth] = {
    "  ||||  ",
    "-------",
    " \\ X  / ",
    "  \\  /  ",
    "   \\/   "};

int main()
{
    system("cls");
    drawBoard();
    printPlayer();

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayer(board, 'l');
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer(board, 'r');
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
void movePlayer(char board[][80], char direction)
{
    erasePlayer();
    board[pX][pY] = ' ';
    if (direction == 'l' && board[pX][pY - 1] != '#') // Boards left end
    {
        pY = pY - 1;
    }
    else if (direction == 'r' && board[pX][pY + 12] != '#') // Boards right end
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
            cout << enemyX[i][j];
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
void moveEnemy(char board[][80], char direction, char enemyType)
{
    eraseEnemy1();
    board[e1X][e1Y] = ' ';
    if (direction == 'l' && board[e1X][e1Y - 1] != '#') // Boards left end
    {
        e1Y = e1Y - 1;
    }
    else if (direction == 'r' && board[e1X][e1Y - 1] != '#') // Boards right end
    {
        e1Y = e1Y + 1;
    }
    board[e1X][e1Y] = enemyType;
    printEnemy1();
}