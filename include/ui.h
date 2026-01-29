#ifndef UI_H
#define UI_H

// ============================================================================
// UI Functions
// ============================================================================

// Banner and menus
void printBanner();
void printMenu();
void printInstructions();

// Interactive menu system
// Returns the 0-based index of the selected option
// Controls: Up/Down/j/k to navigate, Enter/Space to select, q/Escape to quit (returns -1)
int showMenu(const char* items[], int itemCount, int startY);

// Convenience functions for common menus
int showMainMenu();      // Returns: 0=Play, 1=Difficulty, 2=HighScore, 3=Instructions, 4=Exit
int showDifficultyMenu(); // Returns: 0=Easy, 1=Medium, 2=Hard, -1=cancelled

// Scoreboard
void printScoreBoard();
void printScore();

#endif // UI_H
