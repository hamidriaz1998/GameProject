#include "../include/ui.h"
#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/console.h"

// ============================================================================
// UI Functions Implementation
// ============================================================================

void printBanner()
{
    clearScreen();
    X = (getScreenWidth() - 67) / 2;
    Y = 2;
    setColor(cyan);
    gotoxy(X, Y++);
    printString("###############################################################");
    gotoxy(X, Y++);
    printString("#                                                             #");
    gotoxy(X, Y++);
    printString("#    _____                       __          __               #");
    gotoxy(X, Y++);
    printString("#   / ____|                      \\ \\        / /               #");
    gotoxy(X, Y++);
    printString("#  | (___  _ __   __ _  ___ ___   \\ \\  /\\  / /_ _ _ __ ___    #");
    gotoxy(X, Y++);
    printString("#   \\___ \\| '_ \\ / _` |/ __/ _ \\   \\ \\/  \\/ / _` | '__/ __|   #");
    gotoxy(X, Y++);
    printString("#   ____) | |_) | (_| | (_|  __/    \\  /\\  / (_| | |  \\__ \\   #");
    gotoxy(X, Y++);
    printString("#  |_____/| .__/ \\__,_|\\___\\___|     \\/  \\/ \\__,_|_|  |___/   #");
    gotoxy(X, Y++);
    printString("#         | |                                                 #");
    gotoxy(X, Y++);
    printString("#         |_|                                                 #");
    gotoxy(X, Y++);
    printString("#                                                             #");
    gotoxy(X, Y++);
    printString("###############################################################");
    setColor(white);
    Y++;
    refreshScreen();
}

void printMenu()
{
    setColor(blue);
    gotoxy(X, Y++);
    printString("1. Play Game");
    gotoxy(X, Y++);
    printString("2. Set difficulty");
    gotoxy(X, Y++);
    printString("3. High Score");
    gotoxy(X, Y++);
    printString("4. Instructions");
    gotoxy(X, Y++);
    printString("5. Exit");
    setColor(white);
    refreshScreen();
}

// ============================================================================
// Interactive Menu System
// ============================================================================

// Draw a single menu item with selection indicator
static void drawMenuItem(int x, int y, const char* text, bool selected)
{
    gotoxy(x, y);
    
    if (selected)
    {
        setColor(yellow);
        printString("> ");
        setColor(green);
        printString(text);
        setColor(yellow);
        printString(" <");
    }
    else
    {
        setColor(blue);
        printString("  ");
        printString(text);
        printString("  ");
    }
    setColor(white);
}

// Generic interactive menu
// Returns 0-based index of selected item, or -1 if cancelled (q/Escape)
int showMenu(const char* items[], int itemCount, int startY)
{
    int selected = 0;
    bool done = false;
    
    hideCursor();
    
    while (!done)
    {
        // Draw all menu items
        for (int i = 0; i < itemCount; i++)
        {
            drawMenuItem(X, startY + i, items[i], i == selected);
        }
        
        // Draw navigation hint
        gotoxy(X, startY + itemCount + 2);
        setColor(darkwhite);
        printString("[j/k or arrows to move, Enter/Space to select, q to quit]");
        setColor(white);
        
        refreshScreen();
        
        // Wait for input
        int key = waitForKey();
        
        // Handle navigation
        if (key == KEY_ARROW_UP || key == 'k' || key == 'K')
        {
            selected--;
            if (selected < 0) selected = itemCount - 1;  // Wrap to bottom
        }
        else if (key == KEY_ARROW_DOWN || key == 'j' || key == 'J')
        {
            selected++;
            if (selected >= itemCount) selected = 0;  // Wrap to top
        }
        else if (key == KEY_ENTER_KEY || key == KEY_SPACEBAR || key == '\n' || key == '\r')
        {
            done = true;
        }
        else if (key == KEY_ESCAPE_KEY || key == 'q' || key == 'Q')
        {
            selected = -1;  // Cancelled
            done = true;
        }
        // Number keys for quick selection (1-9)
        else if (key >= '1' && key <= '9')
        {
            int num = key - '1';  // Convert '1' to 0, '2' to 1, etc.
            if (num < itemCount)
            {
                selected = num;
                done = true;
            }
        }
    }
    
    showCursor();
    return selected;
}

// Main menu with predefined options
int showMainMenu()
{
    const char* items[] = {
        "Play Game",
        "Set Difficulty",
        "High Score",
        "Instructions",
        "Exit"
    };
    
    printBanner();
    return showMenu(items, 5, Y);
}

// Difficulty selection menu
int showDifficultyMenu()
{
    const char* items[] = {
        "Easy",
        "Medium",
        "Hard"
    };
    
    printBanner();
    gotoxy(X, Y++);
    setColor(lightblue);
    printString("Choose difficulty:");
    setColor(white);
    Y++;
    refreshScreen();
    
    return showMenu(items, 3, Y);
}

// ============================================================================
// Instructions Screen
// ============================================================================

void printInstructions()
{
    printBanner();
    gotoxy(X, Y++);
    setColor(lightblue);
    printString("Instructions");
    gotoxy(X, Y++);
    printString("- Use left and right arrow keys to move the player.");
    gotoxy(X, Y++);
    printString("- Press spacebar to fire.");
    gotoxy(X, Y++);
    printString("- You have to kill all the enemies to win.");
    gotoxy(X, Y++);
    printString("- You can collect coins to increase your score and health.");
    gotoxy(X, Y++);
    printString("- You can press escape to exit the game.");
    gotoxy(X, Y++);
    printString("- The game has three difficulty levels: Easy, Medium, and Hard.");
    gotoxy(X, Y++);
    printString("  - Easy: Enemies move slower and have less health.");
    gotoxy(X, Y++);
    printString("  - Medium: Enemies move at a moderate speed and have moderate health.");
    gotoxy(X, Y++);
    printString("  - Hard: Enemies move faster and have more health.");
    setColor(white);
    Y++;
    gotoxy(X, Y++);
    setColor(yellow);
    printString("  Press any key to go back to the main menu.");
    refreshScreen();
    waitForKey();
}

// ============================================================================
// In-Game Scoreboard
// ============================================================================

void printScoreBoard()
{
    setColor(magenta);
    gotoxy(100, 0);
    printString("##################################");
    gotoxy(100, 1);
    printString("#                                #");
    gotoxy(100, 2);
    printString("#        Difficulty: ");
    printInt(difficulty);
    printString("           #");
    gotoxy(100, 3);
    printString("#        Enemy 1 Health:         #");
    gotoxy(100, 4);
    printString("#        Enemy 2 Health:         #");
    gotoxy(100, 5);
    printString("#        Enemy 3 Health:         #");
    gotoxy(100, 6);
    printString("#        Player Health:          #");
    gotoxy(100, 7);
    printString("#        Score:                  #");
    gotoxy(100, 8);
    printString("#                                #");
    gotoxy(100, 9);
    printString("##################################");
    setColor(white);
}

void printScore()
{
    setColor(magenta);
    gotoxy(125, 3);
    printInt(e1Health);
    gotoxy(125, 4);
    printInt(e2Health);
    gotoxy(125, 5);
    printInt(e3Health);
    gotoxy(124, 6);
    printInt(pHealth);
    gotoxy(116, 7);
    printInt(score);
    setColor(white);
}
