#include <iostream>
#include <windows.h>   // for colors
#include <cstdlib>     // for clearing screen
#include <conio.h>     // for getch()
using namespace std;

// ---------- Color Codes ----------
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

// ---------- Function Declarations ----------
void setColor(int textColor, int bgColor);
void clearScreen();
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10]);
int showMenu();

// ---------- MAIN PROGRAM ----------
int main() {
    cout << "    ==================================\n\n";
    cout << "          WELCOME TO BATTLESHIP GAME        ";
    cout << "\n\n    ==================================\n";

    char board[10][10];
    initializeBoard(board);

    while (true) {
        int choice = showMenu();
        clearScreen();

        if (choice == 1) {
            cout << "\nStarting game...\n";
            // game logic will come later...
        }
        else if (choice == 2) {
            cout << "\nInstructions:\n";
            cout << "• Place your ships on the board.\n";
            cout << "• Try to hit enemy ships.\n";
            cout << "• X = Hit, O = Miss, ~ = Water.\n";
        }
        else if (choice == 3) {
            printBoard(board);
        }
        else if (choice == 4) {
            cout << "Thanks for playing!\n";
            break;
        }

        cout << "\nPress any key to return to menu...";
        getch();
        clearScreen();
    }

    return 0;
}

// ---------- FUNCTIONS ----------

// Set console color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

// Clear screen
void clearScreen() {
    system("CLS");
}

// Fill the board with '~'
void initializeBoard(char board[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}

// Print the board
void printBoard(char board[10][10]) {
    cout << "\n     0    1    2    3    4    5    6    7    8    9\n";
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";

    for (int r = 0; r < 10; r++) {
        cout << "  " << r << " ¦";

        for (int c = 0; c < 10; c++) {
            char cell = board[r][c];

            if (cell == 'X') { setColor(WHITE, RED); }
            else if (cell == 'O') { setColor(BLACK, GREEN); }
            else { setColor(WHITE, BLUE); }

            cout << "  " << cell << "  ";
            setColor(WHITE, BLACK);
            cout << "¦";
        }

        cout << "\n    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
    }
}

// Show Menu
int showMenu() {
    cout << "\n============== MAIN MENU ==============\n";
    cout << "1. Start Game\n";
    cout << "2. Instructions\n";
    cout << "3. Show Board\n";
    cout << "4. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > 4) {
        cout << "Invalid choice. Try again: ";
        cin >> choice;
    }
    return choice;
}

