#include "../include/constants.h"
#include "../include/types.h"
#include "../include/globals.h"
#include "../include/console.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/fileio.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <thread>
#include <chrono>

// ============================================================================
// Cross-Platform Sleep Function
// ============================================================================

static void sleepMs(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// ============================================================================
// Main Function
// ============================================================================

int main()
{
    // Initialize console/terminal
    initConsole();
    
    // Seed the random number generator for coin placement
    srand(static_cast<unsigned int>(time(nullptr)));
    
    loadBoard();
    if (!readData())
    {
        difficulty = 1;
        for (int i = 0; i < 5; i++)
        {
            highScore[i] = 50 - i;
        }
    }
    
    GameScreen currentScreen = MAIN_MENU;
    bool barrier1 = false;
    bool barrier3 = false;
    bool exitedGame = false;
    
    while (currentScreen != EXIT_GAME)
    {
        switch (currentScreen)
        {
        case MAIN_MENU:
        {
            int choice = showMainMenu();
            
            if (choice == 0) currentScreen = PLAY_GAME;
            else if (choice == 1) currentScreen = SET_DIFFICULTY;
            else if (choice == 2) currentScreen = HIGH_SCORE;
            else if (choice == 3) currentScreen = INSTRUCTIONS;
            else if (choice == 4 || choice == -1) currentScreen = EXIT_GAME;
            break;
        }
        
        case SET_DIFFICULTY:
        {
            int diffChoice = showDifficultyMenu();
            // diffChoice: 0=Easy, 1=Medium, 2=Hard, -1=cancelled
            if (diffChoice >= 0 && diffChoice <= 2)
            {
                difficulty = diffChoice + 1;  // Convert 0-based to 1-based
            }
            currentScreen = MAIN_MENU;
            break;
        }
        
        case HIGH_SCORE:
        {
            printBanner();
            gotoxy(X, Y++);
            setColor(lightblue);
            printString("High Score");
            for (int i = 0; i < 5; i++)
            {
                gotoxy(X, Y++);
                printInt(i + 1);
                printString(". ");
                printInt(highScore[i]);
            }
            setColor(white);
            gotoxy(X, Y++);
            setColor(yellow);
            printString("Press any key to return to the main menu....................");
            refreshScreen();
            waitForKey();
            currentScreen = MAIN_MENU;
            break;
        }
        
        case INSTRUCTIONS:
        {
            printInstructions();
            currentScreen = MAIN_MENU;
            break;
        }
        
        case PLAY_GAME:
        {
            setBarriers(barrier1, barrier3);
            setHealth();
            char dir1 = 'r';
            char dir2 = 'r';
            char dir3 = 'r';
            clearScreen();
            printBarriers(barrier1, barrier3);
            drawBoard();
            printScoreBoard();
            printPlayer();
            printEnemy1();
            printEnemy2();
            printEnemy3();
            hideCursor();
            refreshScreen();
            int counter = 0;
            exitedGame = false;
            
            while (true) // Game Loop
            {
                int enemyToMove = counter % 6;
                
                // Player Controls - non-blocking input
                int key = getKeyNonBlocking();
                if (key == KEY_ARROW_LEFT)
                {
                    movePlayer('l');
                }
                else if (key == KEY_ARROW_RIGHT)
                {
                    movePlayer('r');
                }
                else if (key == KEY_SPACEBAR)
                {
                    if (!pFire)
                    {
                        playerFire();
                        pFire = true;
                    }
                }
                else if (key == KEY_ESCAPE_KEY)
                {
                    showCursor();
                    setHighScore();
                    exitedGame = true;
                    break;
                }
                
                // Enemy Movement
                if (!(e1Health <= 0) && (enemyToMove == 0 || enemyToMove == 2 || enemyToMove == 4) && !barrier1)
                {
                    changeDirectionEnemy1(dir1);
                    moveEnemy1(dir1);
                }
                if (!(e2Health <= 0) && enemyToMove == 1)
                {
                    changeDirectionEnemy2(dir2);
                    moveEnemy2(dir2);
                }
                if (!(e3Health <= 0) && (enemyToMove == 3 || enemyToMove == 5) && !barrier3)
                {
                    changeDirectionEnemy3(dir3);
                    moveEnemy3(dir3);
                }

                if (pFire)
                {
                    movePlayerFire();
                }
                
                // Player Fire Collision Detections
                if (collision1)
                {
                    eraseEnemy1();
                    if (e1Health != 0)
                    {
                        score += 10;
                        e1Health--;
                    }
                    if (e1Health == 0)
                    {
                        cleanChar(',');
                        cleanChar('X');
                    }
                    collision1 = false;
                }
                else if (collision2)
                {
                    eraseEnemy2();
                    if (e2Health != 0)
                    {
                        score += 10;
                        e2Health--;
                    }
                    if (e2Health == 0)
                    {
                        cleanChar(';');
                        cleanChar('Y');
                    }
                    collision2 = false;
                }
                else if (collision3)
                {
                    eraseEnemy3();
                    if (e3Health != 0)
                    {
                        score += 10;
                        e3Health--;
                    }
                    if (e3Health == 0)
                    {
                        cleanChar('~');
                        cleanChar('Z');
                    }
                    collision3 = false;
                }
                
                // Enemy Fire
                if (!e1Fire && !(e1Health <= 0) && enemyToMove == 0 && !barrier1)
                {
                    enemy1Fire();
                    e1Fire = true;
                }
                if (e1Fire)
                {
                    moveEnemy1Fire();
                }
                if (!e2Fire && !(e2Health <= 0) && enemyToMove == 1)
                {
                    enemy2Fire();
                    e2Fire = true;
                }
                if (e2Fire)
                {
                    moveEnemy2Fire();
                }
                if (!e3Fire && !(e3Health <= 0) && enemyToMove == 2 && !barrier3)
                {
                    enemy3Fire();
                    e3Fire = true;
                }
                if (e3Fire)
                {
                    moveEnemy3Fire();
                }
                
                // Enemy Fire Collision Detections
                if (pcollision)
                {
                    if (score != 0)
                        score -= 10;
                    erasePlayer();
                }
                if (pHealth != 0)
                {
                    if (pCollsionByE1)
                    {
                        pHealth -= 3;
                        pCollsionByE1 = false;
                    }
                    else if (pCollsionByE2)
                    {
                        pHealth -= 1;
                        pCollsionByE2 = false;
                    }
                    else if (pCollsionByE3)
                    {
                        pHealth -= 2;
                        pCollsionByE3 = false;
                    }
                }
                pcollision = false;
                
                // Coin Collision
                if (coinCollision)
                {
                    score += 20;
                    pHealth++;
                    eraseCoin();
                    coinCollision = false;
                }
                
                // Coin Generation
                if (score % 50 == 0 && score != 0)
                {
                    if (!coin)
                    {
                        generateCoin();
                        coin = true;
                    }
                }
                if (coin)
                {
                    placeCoinInBoard();
                    printCoin();
                }
                
                counter++;
                printScore();
                setBarrierStatus(barrier1, barrier3);
                refreshScreen();
                
                // Game Over
                if (pHealth <= 0)
                {
                    gameOver = true;
                    showCursor();
                    setHighScore();
                    break;
                }
                if (e1Health <= 0 && e2Health <= 0 && e3Health <= 0)
                {
                    showCursor();
                    setHighScore();
                    difficulty++;
                    break;
                }
                sleepMs(30);
            }
            
            // Determine next screen based on game result
            if (exitedGame)
            {
                printBanner();
                gotoxy(X, Y++);
                printString("You exited the game.");
                gotoxy(X, Y++);
                printString("Your Score is: ");
                printInt(score);
                gotoxy(X, Y++);
                printString("Press any key to return to the main menu....................");
                refreshScreen();
                waitForKey();
                resetBoard();
                resetAllValues();
                currentScreen = MAIN_MENU;
            }
            else if (gameOver)
            {
                currentScreen = GAME_OVER;
            }
            else if (difficulty == 4)
            {
                currentScreen = GAME_WON;
            }
            else
            {
                if (difficulty == 2)
                    barrier1Erased = false;
                currentScreen = LEVEL_COMPLETE;
            }
            break;
        }
        
        case GAME_OVER:
        {
            printBanner();
            gotoxy(X, Y++);
            printString("Game Over");
            gotoxy(X, Y++);
            printString("Your Score is ");
            printInt(score);
            gotoxy(X, Y++);
            printString("Press any key to return to the main menu....................");
            refreshScreen();
            waitForKey();
            resetBoard();
            resetAllValues();
            difficulty = 1;
            currentScreen = MAIN_MENU;
            break;
        }
        
        case LEVEL_COMPLETE:
        {
            printBanner();
            gotoxy(X, Y++);
            printString("Congrats! You have completed this difficulty level.");
            gotoxy(X, Y++);
            printString("Your current score is: ");
            printInt(score);
            gotoxy(X, Y++);
            printString("Press any key to continue to the next difficulty level....................");
            refreshScreen();
            waitForKey();
            currentScreen = PLAY_GAME;
            break;
        }
        
        case GAME_WON:
        {
            printBanner();
            gotoxy(X, Y++);
            printString("You Win");
            gotoxy(X, Y++);
            printString("Your Score is ");
            printInt(score);
            gotoxy(X, Y++);
            printString("Press any key to return to the main menu....................");
            refreshScreen();
            waitForKey();
            resetBoard();
            resetAllValues();
            currentScreen = MAIN_MENU;
            break;
        }
        
        case EXIT_GAME:
            break;
        }
    }
    
    storeData();
    cleanupConsole();
    return 0;
}
