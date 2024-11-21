#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

struct termios oldt;

// Restore terminal settings on program exit or interruption
void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void handle_signal(int signal) {
    restore_terminal();
    printf("\nProgram interrupted. Terminal restored.\n");
    _exit(0);
}

// Function to read a single character without pressing Enter
char getch() {
    struct termios newt;
    char ch;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    ch = getchar();

    // Restore the old settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
