#include "../include/console.h"
#include "../include/constants.h"

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <conio.h>
#else
    #include <ncurses.h>
    #include <unistd.h>
#endif

#include <cstdio>
#include <cstring>

// ============================================================================
// Cross-Platform Key Constants
// ============================================================================

#ifdef PLATFORM_WINDOWS
    const int KEY_ARROW_LEFT = VK_LEFT;
    const int KEY_ARROW_RIGHT = VK_RIGHT;
    const int KEY_ARROW_UP = VK_UP;
    const int KEY_ARROW_DOWN = VK_DOWN;
    const int KEY_SPACEBAR = VK_SPACE;
    const int KEY_ESCAPE_KEY = VK_ESCAPE;
    const int KEY_ENTER_KEY = VK_RETURN;
    const int KEY_NONE = -1;
#else
    // Note: KEY_LEFT, KEY_RIGHT, etc. are ncurses macros
    const int KEY_ARROW_LEFT = KEY_LEFT;
    const int KEY_ARROW_RIGHT = KEY_RIGHT;
    const int KEY_ARROW_UP = KEY_UP;
    const int KEY_ARROW_DOWN = KEY_DOWN;
    const int KEY_SPACEBAR = ' ';
    const int KEY_ESCAPE_KEY = 27;
    const int KEY_ENTER_KEY = '\n';  // Renamed to avoid conflict with ncurses KEY_ENTER
    const int KEY_NONE = -1;
#endif

// ============================================================================
// Color Pair Mapping (for ncurses)
// ============================================================================

#ifdef PLATFORM_LINUX
// Map game color constants to ncurses color pairs
// We'll initialize 16 color pairs in initConsole()
static bool colorsInitialized = false;

static void initColorPairs()
{
    if (colorsInitialized) return;
    
    start_color();
    use_default_colors();
    
    // Initialize color pairs (pair number = foreground color index)
    // COLOR_BLACK=0, COLOR_RED=1, COLOR_GREEN=2, COLOR_YELLOW=3,
    // COLOR_BLUE=4, COLOR_MAGENTA=5, COLOR_CYAN=6, COLOR_WHITE=7
    
    // Map Windows colors to ncurses colors
    // Windows: 0=black, 1=blue, 2=green, 3=cyan, 4=red, 5=magenta, 6=brown, 7=lightwhite
    //          8=darkwhite, 9=lightblue, 10=lightgreen, 11=lightcyan, 12=lightred,
    //          13=lightmagenta, 14=yellow, 15=white
    
    // Basic colors (non-bold)
    init_pair(1, COLOR_BLUE, -1);      // blue
    init_pair(2, COLOR_GREEN, -1);     // green
    init_pair(3, COLOR_CYAN, -1);      // cyan
    init_pair(4, COLOR_RED, -1);       // red
    init_pair(5, COLOR_MAGENTA, -1);   // magenta
    init_pair(6, COLOR_YELLOW, -1);    // brown/yellow
    init_pair(7, COLOR_WHITE, -1);     // light white
    
    // Bright colors (we'll use bold attribute for these)
    init_pair(8, COLOR_WHITE, -1);     // dark white (gray)
    init_pair(9, COLOR_BLUE, -1);      // light blue
    init_pair(10, COLOR_GREEN, -1);    // light green
    init_pair(11, COLOR_CYAN, -1);     // light cyan
    init_pair(12, COLOR_RED, -1);      // light red
    init_pair(13, COLOR_MAGENTA, -1);  // light magenta
    init_pair(14, COLOR_YELLOW, -1);   // yellow
    init_pair(15, COLOR_WHITE, -1);    // white
    
    colorsInitialized = true;
}
#endif

// ============================================================================
// Initialization and Cleanup
// ============================================================================

void initConsole()
{
#ifdef PLATFORM_WINDOWS
    // Windows: Enable virtual terminal processing for ANSI codes if needed
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#else
    // Linux: Initialize ncurses
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    keypad(stdscr, TRUE);   // Enable function keys (arrows, etc.)
    nodelay(stdscr, TRUE);  // Non-blocking getch()
    curs_set(0);            // Hide cursor by default
    
    initColorPairs();
#endif
}

void cleanupConsole()
{
#ifdef PLATFORM_WINDOWS
    // Windows: Nothing special needed
    showCursor();
#else
    // Linux: End ncurses mode
    endwin();
#endif
}

// ============================================================================
// Cursor and Screen Control
// ============================================================================

void gotoxy(int x, int y)
{
#ifdef PLATFORM_WINDOWS
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
#else
    move(y, x);  // ncurses uses (row, col) order
#endif
}

void hideCursor()
{
#ifdef PLATFORM_WINDOWS
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    curs_set(0);
#endif
}

void showCursor()
{
#ifdef PLATFORM_WINDOWS
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    curs_set(1);
#endif
}

void clearScreen()
{
#ifdef PLATFORM_WINDOWS
    system("cls");
#else
    clear();
    refresh();
#endif
}

void refreshScreen()
{
#ifdef PLATFORM_WINDOWS
    // Windows: stdout is usually unbuffered for console, nothing needed
#else
    refresh();
#endif
}

int getScreenWidth()
{
#ifdef PLATFORM_WINDOWS
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    return getmaxx(stdscr);
#endif
}

int getScreenHeight()
{
#ifdef PLATFORM_WINDOWS
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    return getmaxy(stdscr);
#endif
}

// ============================================================================
// Color Control
// ============================================================================

void setColor(unsigned short color)
{
#ifdef PLATFORM_WINDOWS
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
#else
    // Turn off all attributes first
    attroff(A_BOLD);
    attroff(A_DIM);
    
    if (color == 0) {
        // Black - use default
        attron(COLOR_PAIR(0));
    } else if (color <= 7) {
        // Normal colors
        attron(COLOR_PAIR(color));
    } else {
        // Bright colors (8-15) - use bold
        attron(COLOR_PAIR(color) | A_BOLD);
    }
#endif
}

// ============================================================================
// Output Functions
// ============================================================================

void printChar(char c)
{
#ifdef PLATFORM_WINDOWS
    putchar(c);
#else
    addch(c);
#endif
}

void printString(const char* s)
{
#ifdef PLATFORM_WINDOWS
    printf("%s", s);
#else
    addstr(s);
#endif
}

void printCharAt(int x, int y, char c, unsigned short color)
{
    gotoxy(x, y);
    setColor(color);
    printChar(c);
}

void printStringAt(int x, int y, const char* s, unsigned short color)
{
    gotoxy(x, y);
    setColor(color);
    printString(s);
}

void printInt(int value)
{
#ifdef PLATFORM_WINDOWS
    printf("%d", value);
#else
    printw("%d", value);
#endif
}

// ============================================================================
// Input Functions
// ============================================================================

int getKeyNonBlocking()
{
#ifdef PLATFORM_WINDOWS
    // Check for key press without blocking
    if (_kbhit()) {
        int ch = _getch();
        // Handle extended keys (arrow keys, etc.)
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch) {
                case 75: return VK_LEFT;
                case 77: return VK_RIGHT;
                case 72: return VK_UP;
                case 80: return VK_DOWN;
                default: return ch;
            }
        }
        if (ch == 27) return VK_ESCAPE;
        if (ch == 32) return VK_SPACE;
        if (ch == 13) return VK_RETURN;
        return ch;
    }
    return KEY_NONE;
#else
    int ch = getch();
    if (ch == ERR) return KEY_NONE;
    return ch;
#endif
}

int waitForKey()
{
#ifdef PLATFORM_WINDOWS
    int ch = _getch();
    // Handle extended keys
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 75: return VK_LEFT;
            case 77: return VK_RIGHT;
            case 72: return VK_UP;
            case 80: return VK_DOWN;
            default: return ch;
        }
    }
    return ch;
#else
    nodelay(stdscr, FALSE);  // Temporarily enable blocking
    int ch = getch();
    nodelay(stdscr, TRUE);   // Back to non-blocking
    return ch;
#endif
}

void readString(char* buffer, int maxLen)
{
#ifdef PLATFORM_WINDOWS
    // Simple Windows implementation using standard input
    fgets(buffer, maxLen, stdin);
    // Remove newline if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
#else
    // For ncurses, we need to temporarily enable echo and blocking
    echo();                     // Show what user types
    nodelay(stdscr, FALSE);     // Enable blocking
    curs_set(1);                // Show cursor
    
    getnstr(buffer, maxLen - 1);
    
    noecho();                   // Back to no echo
    nodelay(stdscr, TRUE);      // Back to non-blocking
    curs_set(0);                // Hide cursor
#endif
}
