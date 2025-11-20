#include <iostream>
#include <windows.h> // for colors
#include <cstdlib> // for clearing screen
#include <conio.h> //for getch();
using namespace std;

void setColor(int textColor, int bgColor);
void initializeBoard(char board[10][10]);
void clearScreen();

int main()
{
	cout << "    ==================================\n\n";
	cout << "          WELCOME TO BATTLESHIP GAME        ";
	cout << "\n\n    ==================================";
	cout << "\n\n\n              MAIN MENU\n    ----------------------------------\n";
	char board[10][10];
	initializeBoard(board);
	
	return 0;
}

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;
// Function to set console text and background color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void clearScreen() {
//    system("clear");  //For Mac /Linux;
		system("CLS"); //For Windows

}

void initializeBoard(char board[10][10]){
//	char board[10][10];

    // Initialize 10x10 board with water '~'
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';

//    board[2][3] = 'X'; 
//    board[7][8] = 'O'; 

    // Print column headers (hardcoded)
    cout << "     0    1    2    3    4    5    6    7    8    9  " << endl;

    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    // Row 0
    cout << "  0 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[0][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 1
    cout << "  1 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[1][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 2
    cout << "  2 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[2][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 3
    cout << "  3 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[3][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 4
    cout << "  4 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[4][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 5
    cout << "  5 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[5][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 6
    cout << "  6 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[6][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 7
    cout << "  7 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[7][i];
        if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 8
    cout << "  8 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[8][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 9
    cout << "  9 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[9][i];
        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "¦";
    }
    cout << endl;

    // Bottom border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}

