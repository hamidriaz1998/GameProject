#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);
void hideCursor();
void showCursor();
// Starting Page
void printBanner();
void printMenu();
int getScreenWidth();
void printInstructions();
void printScoreBoard();
void printScore();
int X = 0, Y = 0;
// Input validation
int getNum(string);
bool checkInt(string);
int strToInt(string);
// Board
void drawBoard();
// Coin
void printCoin();
void eraseCoin();
void generateCoin();
void placeCoinInBoard();
bool isPositionEmpty(int x, int y);
bool coin = false, coinCollision = false;
int coinX = 0, coinY = 0;
// Player
void erasePlayer();
void printPlayer();
void movePlayer(char direction);
void createPlayerHitbox();
void erasePlayerHitbox();
int pX = 30;
int pY = 7, pHealth = 5;
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
int e1X = 6, e1Y = 9, e1Health = 5;
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
int e2X = 14, e2Y = 56, e2Health = 5;
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
int e3X = 6, e3Y = 45, e3Health = 5;
// Enemy 3 Fire
void enemy3Fire();
void moveEnemy3Fire();
void eraseEnemy3Fire();
void printEnemy3Fire();
int e3FireX = 0, e3FireY = 0;
bool e3Fire = false, collision3 = false;
// Score
int score = 0;
void setHighScore();
int highScore[5] = {0, 0, 0, 0, 0};
// Difficulty
int difficulty = 1;
// Error Handling
bool inBoard(char);
// File Handling
void storeData();
void readData();
// New Game
void resetAllValues();
void resetBoard();

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
    "#                                     #                                                 #",
    "#                                     #                                                 #",
    "#                                     #                                                 #",
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
    readData();
// Starting Page
mainMenu:
    printBanner();
    printMenu();
    int choice = getNum("Enter your choice: ");
    if (choice == 5)
    { // Exit
        storeData();
        return 0;
    }
    else if (choice == 2)
    {
        printBanner();
        gotoxy(X, Y++);
        cout << "Choose one of the following difficulties" << endl;
        gotoxy(X, Y++);
        cout << "1. Easy" << endl;
        gotoxy(X, Y++);
        cout << "2. Medium" << endl;
        gotoxy(X, Y++);
        cout << "3. Hard" << endl;
        difficulty = getNum("Enter your choice: ");
    }
    else if (choice == 3)
    {
        printBanner();
        gotoxy(X, Y++);
        cout << "High Score" << endl;
        for (int i = 0; i < 5; i++)
        {
            gotoxy(X, Y++);
            cout << i + 1 << ". " << highScore[i] << endl;
        }
        gotoxy(X, Y++);
        cout << "Press any key to return to the main menu....................";
        getch();
        goto mainMenu;
    }
    else if (choice == 4)
    { // Instructions
        printInstructions();
        goto mainMenu;
    }
    else if (choice == 1)
    {
        // Play Game
        char dir1 = 'r';
        char dir2 = 'r';
        char dir3 = 'r';
        system("cls");
        drawBoard();
        printScoreBoard();
        printPlayer();
        printEnemy1();
        printEnemy2();
        printEnemy3();
        hideCursor();
        int counter = 0;
        while (true)
        {
            int enemyToMove = counter % 3; // To move each enemy one by one to optimize the game
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
            if (!(e1Health <= 0) && enemyToMove == 0)
            {
                changeDirectionEnemy1(dir1);
                moveEnemy1(dir1);
            }
            if (!(e2Health <= 0) && enemyToMove == 1)
            {
                changeDirectionEnemy2(dir2);
                moveEnemy2(dir2);
            }
            if (!(e3Health <= 0) && enemyToMove == 2)
            {
                changeDirectionEnemy3(dir3);
                moveEnemy3(dir3);
            }

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
                score += 10;
                eraseEnemy1();
                if (e1Health != 0)
                    e1Health--;
                collision1 = false;
            }
            else if (collision2)
            {
                score += 10;
                eraseEnemy2();
                if (e2Health != 0)
                    e2Health--;
                collision2 = false;
            }
            else if (collision3)
            {
                score += 10;
                eraseEnemy3();
                if (e3Health != 0) // Sometimes some hitboxes remain and the health goes to -1 and beyond
                    e3Health--;
                collision3 = false;
            }
            if (!e1Fire && !(e1Health <= 0) && enemyToMove == 0)
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
            if (!e2Fire && !(e2Health <= 0) && enemyToMove == 1)
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
            if (!e3Fire && !(e3Health <= 0) && enemyToMove == 2)
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
                    score -= 10;
                    erasePlayer();
                    if (pHealth != 0)
                        pHealth--;
                    pcollision = false;
                }
            }
            if (score % 50 == 0 && score != 0)
            {
                if (!coin)
                {
                    generateCoin();
                    coin = true;
                }
            }
            if (coinCollision)
            {
                score += 20;
                pHealth++;
                eraseCoin();
                coinCollision = false;
            }
            if (coin) // To prevent coin from disapperaing
            {
                placeCoinInBoard();
                printCoin();
            }
            counter++;
            printScore();
            Sleep(50);
            if (pHealth == 0 || (e1Health == 0 && e2Health == 0 && e3Health == 0))
            {
                showCursor();
                setHighScore();
                break;
            }
        }
    }
    string temp;
    if (pHealth == 0)
    {
        printBanner();
        gotoxy(X, Y++);
        cout << "Game Over" << endl;
        gotoxy(X, Y++);
        cout << "Your Score is " << score << endl;
        gotoxy(X, Y++);
        cout << "Press Enter key to return to the main menu....................";
        cin >> temp;
        resetBoard();
        resetAllValues();
        goto mainMenu;
    }
    else
    {
        printBanner();
        gotoxy(X, Y++);
        cout << "You Win" << endl;
        gotoxy(X, Y++);
        cout << "Your Score is " << score << endl;
        gotoxy(X, Y++);
        cout << "Press Enter key to return to the main menu....................";
        cin >> temp;
        resetBoard();
        resetAllValues();
        goto mainMenu;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void showCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
// Starting Page
void printBanner()
{
    system("cls");
    X = (getScreenWidth() - 67) / 2;
    Y = 0;
    gotoxy(X, Y++);
    cout << "######################################################################" << endl;
    gotoxy(X, Y++);
    cout << "# #     #                                #####                       #" << endl;
    gotoxy(X, Y++);
    cout << "# ##   ## ###### #####   ##   #         #     # #      #    #  ####  #" << endl;
    gotoxy(X, Y++);
    cout << "# # # # # #        #    #  #  #         #       #      #    # #    # #" << endl;
    gotoxy(X, Y++);
    cout << "# #  #  # #####    #   #    # #          #####  #      #    # #      #" << endl;
    gotoxy(X, Y++);
    cout << "# #     # #        #   ###### #               # #      #    # #  ### #" << endl;
    gotoxy(X, Y++);
    cout << "# #     # #        #   #    # #         #     # #      #    # #    # #" << endl;
    gotoxy(X, Y++);
    cout << "# #     # ######   #   #    # ######     #####  ######  ####   ####  #" << endl;
    gotoxy(X, Y++);
    cout << "######################################################################" << endl;
    Y++;
}
void printMenu()
{
    gotoxy(X, Y++);
    cout << "1. Play Game" << endl;
    gotoxy(X, Y++);
    cout << "2. Set difficulty" << endl;
    gotoxy(X, Y++);
    cout << "3. High Score" << endl;
    gotoxy(X, Y++);
    cout << "4. Instructions" << endl;
    gotoxy(X, Y++);
    cout << "5. Exit" << endl;
}
void printInstructions()
{
    printBanner();
    gotoxy(X, Y++);
    cout << "Instructions" << endl;
    gotoxy(X, Y++);
    cout << "- Use left and right arrow keys to move the player." << endl;
    gotoxy(X, Y++);
    cout << "- Press spacebar to fire." << endl;
    gotoxy(X, Y++);
    cout << "- You have 5 lives." << endl;
    gotoxy(X, Y++);
    cout << "- You have to kill all the enemies to win." << endl;
    gotoxy(X, Y++);
    cout << "- You can collect coins to increase your score and health." << endl;
    gotoxy(X, Y++);
    cout << "- You can press escape to exit the game." << endl;
    gotoxy(X, Y++);
    cout << "  Press any key to go back to the main menu." << endl;
    getch();
}
void printScoreBoard()
{
    gotoxy(100, 0);
    cout << "##################################";
    gotoxy(100, 1);
    cout << "#                                #";
    gotoxy(100, 2);
    cout << "#        Enemy 1 Health:         #";
    gotoxy(100, 3);
    cout << "#        Enemy 2 Health:         #";
    gotoxy(100, 4);
    cout << "#        Enemy 3 Health:         #";
    gotoxy(100, 5);
    cout << "#        Player Health:          #";
    gotoxy(100, 6);
    cout << "#        Score:                  #";
    gotoxy(100, 7);
    cout << "#                                #";
    gotoxy(100, 8);
    cout << "##################################";
}
void printScore()
{
    gotoxy(125, 2);
    cout << e1Health;
    gotoxy(125, 3);
    cout << e2Health;
    gotoxy(125, 4);
    cout << e3Health;
    gotoxy(124, 5);
    cout << pHealth;
    gotoxy(116, 6);
    cout << score;
}
int getScreenWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return columns;
}
// Input Validation
int getNum(string prompt)
{
    string num;
    while (true)
    {
        // setcolor(yellow);
        gotoxy(X, Y++);
        cout << prompt;
        cin >> num;
        // setcolor(white);
        if (checkInt(num))
        {
            return strToInt(num);
        }
        else
        {
            // setcolor(red);
            gotoxy(X, Y++);
            cout << "Invalid Input." << endl;
            // setcolor(white);
            gotoxy(X, Y++);
            cout << "Press any key to try again..................." << endl;
            getch();
        }
    }
}
bool checkInt(string num)
{
    for (int i = 0; i < num.length(); i++)
    {
        if (num[i] < '0' || num[i] > '9')
        {
            return false;
        }
    }
    return true;
}
int strToInt(string num)
{
    int result = 0;
    for (int i = 0; i < num.length(); i++)
    {
        result = result * 10 + (num[i] - '0');
    }
    return result;
}
// Board
void drawBoard()
{
    board[pX][pY] = 'p';
    board[e1X][e1Y] = 'X';
    board[e2X][e2Y] = 'Y';
    board[e3X][e3Y] = 'Z';
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
                e1Y = j;
                printEnemy1();
            }
            else if (board[i][j] == 'Y')
            {
                e2Y = j;
                printEnemy2();
            }
            else if (board[i][j] == 'Z')
            {
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
// Coin Functions
void printCoin()
{
    gotoxy(coinY, coinX);
    cout << "$";
}
void eraseCoin()
{
    gotoxy(coinY, coinX);
    cout << " ";
}
void generateCoin()
{
    while (true)
    {
        coinX = rand() % boardHeight - 10;      // To prevent coin from appearing on or below the player
        coinY = (rand() % boardWidth - 10) + 3; // To prevent coin from appearing with walls
        if (isPositionEmpty(coinX, coinY))
        {
            break;
        }
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
// Player Functions
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
    pFireY = pY + 3;
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
                else if (board[i - 1][pFireY] == '$')
                {
                    coinCollision = true;
                    board[i][pFireY] = ' ';
                    board[i - 1][pFireY] = ' ';
                    pFire = false;
                    coin = false;
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
    e1FireY = e1Y + 3;
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
    e2FireY = e2Y + 3;
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
    e3FireY = e3Y + 3;
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
void setHighScore()
{
    for (int i = 0; i < 5; i++)
    {
        if (score == highScore[i])
            break;
        if (score > highScore[i])
        {
            highScore[i] = score;
            for (int j = 4; j > i; j--)
            {
                highScore[j] = highScore[j - 1];
            }
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
// File Handling
void storeData()
{ // First line contains difficulty, next 5 lines contain high scores
    fstream f;
    f.open("gameData.txt", ios::out);
    f << difficulty << endl;
    for (int i = 0; i < 5; i++)
    {
        f << highScore[i];
        if (i != 4)
        {
            f << endl;
        }
    }
    f.close();
}
void readData()
{
    fstream f;
    f.open("gameData.txt", ios::in);
    string temp;
    getline(f, temp);
    difficulty = strToInt(temp);
    for (int i = 0; i < 5; i++)
    {
        getline(f, temp);
        highScore[i] = strToInt(temp);
    }
    f.close();
}
void resetAllValues()
{
    pX = 30;
    pY = 7;
    e1X = 6;
    e1Y = 9;
    e2X = 14;
    e2Y = 56;
    e3X = 6;
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
    coin = false;
    coinCollision = false;
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