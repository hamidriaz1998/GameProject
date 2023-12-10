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
void erasePlayerHitbox();
const int pX = 30;
int pY = 0, pHealth = 5;
// Player Fire
void playerFire();
void movePlayerFire();
void erasePlayerFire();
void printPlayerFire();
int pFireX = 0, pFireY = 0;
bool pFire = false, pcollision = false;
// Enemies
// Enemy 1
void eraseEnemy1();
void printEnemy1();
void changeDirectionEnemy1(char &direction);
void createEnemy1Hitbox();
void eraseEnemy1Hitbox();
void moveEnemy1(char direction);
int e1X = 0, e1Y = 0, e1Health = 5;
// Enemy 1 Fire
void enemy1Fire();
void moveEnemy1Fire();
void eraseEnemy1Fire();
void printEnemy1Fire();
int e1FireX = 0, e1FireY = 0;
bool e1Fire = false, collision1 = false;
// Enemy 2
void eraseEnemy2();
void printEnemy2();
void changeDirectionEnemy2(char &direction);
void createEnemy2Hitbox();
void eraseEnemy2Hitbox();
void moveEnemy2(char direction);
int e2X = 0, e2Y = 0, e2Health = 5;
// Enemy 2 Fire
void enemy2Fire();
void moveEnemy2Fire();
void eraseEnemy2Fire();
void printEnemy2Fire();
int e2FireX = 0, e2FireY = 0;
bool e2Fire = false, collision2 = false;
// Enemy 3
void eraseEnemy3();
void printEnemy3();
void changeDirectionEnemy3(char &direction);
void createEnemy3Hitbox();
void eraseEnemy3Hitbox();
void moveEnemy3(char direction);
int e3X = 0, e3Y = 0, e3Health = 5;
// Enemy 3 Fire
void enemy3Fire();
void moveEnemy3Fire();
void eraseEnemy3Fire();
void printEnemy3Fire();
int e3FireX = 0, e3FireY = 0;
bool e3Fire = false, collision3 = false;
// Error Handling
bool inBoard(char);

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

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayer('l');
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer('r');
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            if (!pFire)
            {
                playerFire();
                pFire = true;
            }
        }
        if (!(e1Health <= 0))
        {
            changeDirectionEnemy1(dir1);
            moveEnemy1(dir1);
        }
        if (!(e2Health <= 0))
        {
            changeDirectionEnemy2(dir2);
            moveEnemy2(dir2);
        }
        if (!(e3Health <= 0))
        {
            changeDirectionEnemy3(dir3);
            moveEnemy3(dir3);
        }
        gotoxy(100, 0);
        cout << "Enemy 1 Health: " << e1Health << "   ";
        gotoxy(100, 1);
        cout << "Enemy 2 Health: " << e2Health << "   ";
        gotoxy(100, 2);
        cout << "Enemy 3 Health: " << e3Health << "   ";
        gotoxy(100, 3);
        cout << "Player Health: " << pHealth << "   ";

        if (pFire)
        {
            if (!inBoard('|')) // Handling the error, When bullet disapper and cannot be fired again
            {
                playerFire();
            }
            movePlayerFire();
        }
        if (collision1)
        {
            eraseEnemy1();
            if (e1Health != 0)
                e1Health--;
            collision1 = false;
        }
        else if (collision2)
        {
            eraseEnemy2();
            if (e2Health != 0)
                e2Health--;
            collision2 = false;
        }
        else if (collision3)
        {
            eraseEnemy3();
            if (e3Health != 0) // Sometimes some hitboxes remain and the health goes to -1 and beyond
                e3Health--;
            collision3 = false;
        }
        if (!e1Fire && !(e1Health <= 0))
        {
            enemy1Fire();
            e1Fire = true;
        }
        if (e1Fire)
        {
            if (!inBoard('!')) // Handling the error, When bullet disapper and cannot be fired again
            {
                enemy1Fire();
            }
            moveEnemy1Fire();
        }
        if (!e2Fire && !(e2Health <= 0))
        {
            enemy2Fire();
            e2Fire = true;
        }
        if (e2Fire)
        {
            if (!inBoard('I')) // Handling the error, When bullet disapper and cannot be fired again
            {
                enemy2Fire();
            }
            moveEnemy2Fire();
        }
        if (!e3Fire && !(e3Health <= 0))
        {
            enemy3Fire();
            e3Fire = true;
        }
        if (e3Fire)
        {
            if (!inBoard('[')) // Handling the error, When bullet disapper and cannot be fired again
            {
                enemy3Fire();
            }
            moveEnemy3Fire();
            if (pcollision)
            {
                erasePlayer();
                if (pHealth != 0)
                    pHealth--;
                pcollision = false;
            }
        }
        Sleep(50);
        if (pHealth == 0 || (e1Health == 0 && e2Health == 0 && e3Health == 0))
        {
            break;
        }
    }
    if (pHealth == 0)
    {
        system("cls");
        gotoxy(0, 0);
        cout << "Game Over";
    }
    else
    {
        system("cls");
        gotoxy(0, 0);
        cout << "You Win";
    }
    return 0;
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
    pFireY = pY;
    board[pFireX][pFireY] = '|';
}
void movePlayerFire()
{
    bool foundFire = false;
    erasePlayerFire();
    for (int i = 1; i < boardHeight; i++)
    {
        if (board[i][pFireY] == '|')
        {
            foundFire = true;
            if (board[i - 1][pFireY] != '#')
            {
                if (board[i - 1][pFireY] == 'X' || board[i - 1][pFireY] == ',' || board[i][pFireY + 1] == ',' || board[i][pFireY - 1] == ',' || board[i][pFireY + 1] == 'X' || board[i][pFireY - 1] == 'X')
                { // Enemy 1
                    collision1 = true;
                    board[i][pFireY] = ' ';
                    board[i - 1][pFireY] = ' ';
                    pFire = false;
                }
                else if (board[i - 1][pFireY] == 'Y' || board[i - 1][pFireY] == ';' || board[i][pFireY + 1] == ';' || board[i][pFireY - 1] == ';' || board[i][pFireY + 1] == 'Y' || board[i][pFireY - 1] == 'Y') // Checks left, right and top of the bullet
                {                                                                                                                                                                                                // Enemy 2
                    collision2 = true;
                    board[i][pFireY] = ' ';
                    board[i - 1][pFireY] = ' ';
                    pFire = false;
                }
                else if (board[i - 1][pFireY] == 'Z' || board[i - 1][pFireY] == '~' || board[i][pFireY + 1] == '~' || board[i][pFireY - 1] == '~' || board[i][pFireY + 1] == 'Z' || board[i][pFireY - 1] == 'Z')
                { // Enemy 3
                    collision3 = true;
                    board[i][pFireY] = ' ';
                    board[i - 1][pFireY] = ' ';
                    pFire = false;
                }
                else
                {
                    // Move the fire up
                    board[i][pFireY] = ' ';
                    board[i - 1][pFireY] = '|';
                }
            }
            else
            {
                // Remove the fire if it hits a wall
                board[i][pFireY] = ' ';
                pFire = false;
            }
            break;
        }
    }
    printPlayerFire();
}
void erasePlayerFire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][pFireY] == '|')
        {
            gotoxy(pFireY, i);
            cout << " ";
            break;
        }
    }
}
void printPlayerFire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][pFireY] == '|')
        {
            gotoxy(pFireY, i);
            cout << board[i][pFireY];
            break;
        }
    }
}
void createEnemy1Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e1X + i][e1Y] = ',';
            board[e1X + i][e1Y + 5] = ',';
        }
        if (i < 6)
        {
            board[e1X + 4][e1Y + i] = ',';
        }
    }
}
void eraseEnemy1Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e1X + i][e1Y] = ' ';
            board[e1X + i][e1Y + 5] = ' ';
        }
        if (i < 6)
        {
            board[e1X + 4][e1Y + i] = ' ';
        }
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
// Enemy 1 Fire
void enemy1Fire()
{
    e1FireX = e1X + 4;
    e1FireY = e1Y;
    board[e1FireX][e1FireY] = '!';
}
void moveEnemy1Fire()
{
    bool foundFire = false;
    eraseEnemy1Fire();
    for (int i = 1; i <= boardHeight; i++)
    {
        if (board[i][e1FireY] == '!')
        {
            foundFire = true;
            if (board[i + 1][e1FireY] != '#')
            {
                if (board[i + 1][e1FireY] == 'p' || board[i + 1][e1FireY] == '.' || board[i][e1FireY + 1] == '.' || board[i][e1FireY - 1] == '.' || board[i][e1FireY + 1] == 'p' || board[i][e1FireY - 1] == 'p')
                {
                    pcollision = true;
                    board[i][e1FireY] = ' ';
                    board[i + 1][e1FireY] = ' ';
                    e1Fire = false;
                }
                else
                {
                    // Move the fire up
                    board[i][e1FireY] = ' ';
                    board[i + 1][e1FireY] = '!';
                }
            }
            else
            {
                // Remove the fire if it hits a wall
                board[i][e1FireY] = ' ';
                e1Fire = false;
            }
            break;
        }
    }
    printEnemy1Fire();
}
void eraseEnemy1Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e1FireY] == '!')
        {
            gotoxy(e1FireY, i);
            cout << " ";
            break;
        }
    }
}
void printEnemy1Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e1FireY] == '!')
        {
            gotoxy(e1FireY, i);
            cout << board[i][e1FireY];
            break;
        }
    }
}
// Enemy 2 Functions/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createEnemy2Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e2X + i][e2Y] = ';';
            board[e2X + i][e2Y + 5] = ';';
        }
        if (i < 6)
        {
            board[e2X + 4][e2Y + i] = ';';
        }
    }
}
void eraseEnemy2Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e2X + i][e2Y] = ' ';
            board[e2X + i][e2Y + 5] = ' ';
        }
        if (i < 6)
        {
            board[e2X + 4][e2Y + i] = ' ';
        }
    }
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
// Enemy 2 Fire
void enemy2Fire()
{
    e2FireX = e2X + 4;
    e2FireY = e2Y;
    board[e2FireX][e2FireY] = 'I';
}
void moveEnemy2Fire()
{
    bool foundFire = false;
    eraseEnemy2Fire();
    for (int i = 1; i <= boardHeight; i++)
    {
        if (board[i][e2FireY] == 'I')
        {
            foundFire = true;
            if (board[i + 1][e2FireY] != '#')
            {
                if (board[i + 1][e2FireY] == 'p' || board[i + 1][e2FireY] == '.' || board[i][e2FireY + 1] == '.' || board[i][e2FireY - 1] == '.' || board[i][e2FireY + 1] == 'p' || board[i][e2FireY - 1] == 'p')
                {
                    pcollision = true;
                    board[i][e2FireY] = ' ';
                    board[i + 1][e2FireY] = ' ';
                    e2Fire = false;
                }
                else
                {
                    // Move the fire up
                    board[i][e2FireY] = ' ';
                    board[i + 1][e2FireY] = 'I';
                }
            }
            else
            {
                // Remove the fire if it hits a wall
                board[i][e2FireY] = ' ';
                e2Fire = false;
            }
            break;
        }
    }
    printEnemy2Fire();
}
void eraseEnemy2Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e2FireY] == 'I')
        {
            gotoxy(e2FireY, i);
            cout << " ";
            break;
        }
    }
}
void printEnemy2Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e2FireY] == 'I')
        {
            gotoxy(e2FireY, i);
            cout << board[i][e2FireY];
            break;
        }
    }
}
// Enemy 3 Functions/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createEnemy3Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e3X + i][e3Y] = '~';
            board[e3X + i][e3Y + 5] = '~';
        }
        if (i < 6)
        {
            board[e3X + 4][e3Y + i] = '~';
        }
    }
}
void eraseEnemy3Hitbox()
{
    for (int i = 0; i < 6; i++)
    {
        if (i < 4)
        {
            board[e3X + i][e3Y] = ' ';
            board[e3X + i][e3Y + 5] = ' ';
        }
        if (i < 6)
        {
            board[e3X + 4][e3Y + i] = ' ';
        }
    }
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
// Enemy 3 Fire
void enemy3Fire()
{
    e3FireX = e3X + 4;
    e3FireY = e3Y;
    board[e3FireX][e3FireY] = '[';
}
void moveEnemy3Fire()
{
    bool foundFire = false;
    eraseEnemy3Fire();
    for (int i = 1; i <= boardHeight; i++)
    {
        if (board[i][e3FireY] == '[')
        {
            foundFire = true;
            if (board[i + 1][e3FireY] != '#')
            {
                if (board[i + 1][e3FireY] == 'p' || board[i + 1][e3FireY] == '.' || board[i][e3FireY + 1] == '.' || board[i][e3FireY - 1] == '.' || board[i][e3FireY + 1] == 'p' || board[i][e3FireY - 1] == 'p')
                {
                    pcollision = true;
                    board[i][e3FireY] = ' ';
                    board[i + 1][e3FireY] = ' ';
                    e3Fire = false;
                }
                else
                {
                    // Move the fire up
                    board[i][e3FireY] = ' ';
                    board[i + 1][e3FireY] = '[';
                }
            }
            else
            {
                // Remove the fire if it hits a wall
                board[i][e3FireY] = ' ';
                e3Fire = false;
            }
            break;
        }
    }
    printEnemy3Fire();
}
void eraseEnemy3Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e3FireY] == '[')
        {
            gotoxy(e3FireY, i);
            cout << " ";
            break;
        }
    }
}
void printEnemy3Fire()
{
    for (int i = 0; i < boardHeight; i++)
    {
        if (board[i][e3FireY] == '[')
        {
            gotoxy(e3FireY, i);
            cout << board[i][e3FireY];
            break;
        }
    }
}
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
}