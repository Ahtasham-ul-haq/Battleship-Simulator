#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // for colors
#include <conio.h>   // for getch()
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
const int GRAY = 8;
const int LIGHT_RED = 12;
const int PINK = 13;
const int LIGHT_BLUE = 9;

// Function to set console text and background color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}


// Clear the console screen
void clearScreen() {
    system("CLS"); // For Windows
}

// Initialize the board with '~' in every cell
void initializeBoard(char board[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = '~';
        }
    }
}

// Display the board with colors (optionally hide ships)
void printBoard(char board[10][10], bool hideShips) {
    // Print column headers
    cout << "     0    1    2    3    4    5    6    7    8    9  " << endl;
    
    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    
    // Print each row
    for (int row = 0; row < 10; row++) {
        // Row number
        cout << "  " << row << " |";
        
        // Print each cell in the row
        for (int col = 0; col < 10; col++) {
            char cell = board[row][col];
            
            // Determine what to display and what color
            if (cell == 'X') {
                // HIT - Red background with white X
                setColor(WHITE, RED);
                cout << "  X  ";
                setColor(WHITE, BLACK);
            }
            else if (cell == 'O') {
                // MISS - Gray background with black O
                setColor(BLACK, GRAY);
                cout << "  O  ";
                setColor(WHITE, BLACK);
            }
            else if (cell == 'S') {
                // SUNK SHIP - Pink background
                setColor(WHITE, PINK);
                cout << "  S  ";
                setColor(WHITE, BLACK);
            }
            else if (cell >= '1' && cell <= '5') {
                // SHIP - if hideShips is true, show as water
                if (hideShips) {
                    setColor(WHITE, BLUE);
                    cout << "  ~  ";
                    setColor(WHITE, BLACK);
                } else {
                    // Show ship with color (can choose different colors for ships)
                    setColor(BLACK, YELLOW);
                    cout << "  " << cell << "  ";
                    setColor(WHITE, BLACK);
                }
            }
            else {
                // WATER - Blue background with white ~
                setColor(WHITE, BLUE);
                cout << "  ~  ";
                setColor(WHITE, BLACK);
            }
            
            cout << "|";
        }
        cout << endl;
        
        // Border between rows
        if (row < 9) {
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        }
    }
    
    // Bottom border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}

// Show Leaderboard - reads from file and displays top 10 scores
void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers) {
    setColor(YELLOW, BLACK);
    cout << "\n========== LEADERBOARD ==========" << endl;
    setColor(WHITE, BLACK);
    cout << "Rank\tPlayer Name\tScore" << endl;
    cout << "=================================" << endl;
    
    if (totalPlayers == 0) {
        setColor(RED, BLACK);
        cout << "No scores yet!" << endl;
        setColor(WHITE, BLACK);
    } else {
        for (int i = 0; i < totalPlayers && i < 10; i++) {
            if (i < 3) {
                setColor(YELLOW, BLACK); // Top 3 in gold
            } else {
                setColor(WHITE, BLACK);
            }
            cout << (i + 1) << "\t" << playerNames[i] << "\t\t" << scores[i] << endl;
        }
        setColor(WHITE, BLACK);
    }
    cout << "=================================" << endl;
}

// Load leaderboard from file
int loadLeaderboard(string playerNames[], int scores[]) {
    ifstream file("highscores.txt");
    int count = 0;
    
    if (file.is_open()) {
        while (count < 10 && file >> playerNames[count] >> scores[count]) {
            count++;
        }
        file.close();
    }
    return count;
}

// Save leaderboard to file
void saveLeaderboard(const string playerNames[], const int scores[], int totalPlayers) {
    ofstream file("highscores.txt");
    
    if (file.is_open()) {
        for (int i = 0; i < totalPlayers && i < 10; i++) {
            file << playerNames[i] << " " << scores[i] << endl;
        }
        file.close();
    }
}

// Update leaderboard with new score
void updateLeaderboard(string newPlayerName, int newScore) {
    string playerNames[11];
    int scores[11];
    int totalPlayers = loadLeaderboard(playerNames, scores);
    
    // Add new score
    playerNames[totalPlayers] = newPlayerName;
    scores[totalPlayers] = newScore;
    totalPlayers++;
    
    // Sort in descending order (bubble sort)
    for (int i = 0; i < totalPlayers - 1; i++) {
        for (int j = 0; j < totalPlayers - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                // Swap scores
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;
                
                // Swap names
                string tempName = playerNames[j];
                playerNames[j] = playerNames[j + 1];
                playerNames[j + 1] = tempName;
            }
        }
    }
    
    // Keep only top 10
    if (totalPlayers > 10) {
        totalPlayers = 10;
    }
    
    saveLeaderboard(playerNames, scores, totalPlayers);
}

// Display game instructions
void displayInstructions() {
    clearScreen();
    setColor(CYAN, BLACK);
    cout << "\n========== BATTLESHIP INSTRUCTIONS ==========" << endl;
    setColor(WHITE, BLACK);
    
    cout << "\n1. OBJECTIVE:" << endl;
    cout << "   - Sink all of your opponent's ships before they sink yours!" << endl;
    
    setColor(YELLOW, BLACK);
    cout << "\n2. SHIPS:" << endl;
    setColor(WHITE, BLACK);
    cout << "   - Aircraft Carrier (5 blocks)" << endl;
    cout << "   - Battleship (4 blocks)" << endl;
    cout << "   - Destroyer (3 blocks)" << endl;
    cout << "   - Submarine (3 blocks)" << endl;
    cout << "   - Patrol Boat (2 blocks)" << endl;
    
    setColor(GREEN, BLACK);
    cout << "\n3. SETUP:" << endl;
    setColor(WHITE, BLACK);
    cout << "   - Place your 5 ships on the 10x10 grid" << endl;
    cout << "   - Ships can be placed horizontally or vertically" << endl;
    cout << "   - Ships cannot overlap or go outside the grid" << endl;
    
    setColor(LIGHT_BLUE, BLACK);
    cout << "\n4. GAMEPLAY:" << endl;
    setColor(WHITE, BLACK);
    cout << "   - Players take turns attacking coordinates" << endl;
    cout << "   - Enter row and column to attack (0-9)" << endl;
    cout << "   - "; setColor(WHITE, RED); cout << " X "; setColor(WHITE, BLACK); 
    cout << " marks a HIT (Red), "; setColor(BLACK, GRAY); cout << " O "; setColor(WHITE, BLACK);
    cout << " marks a MISS (Grey)" << endl;
    cout << "   - When all cells of a ship are hit, it sinks "; 
    setColor(WHITE, PINK); cout << "(Pink)"; setColor(WHITE, BLACK); cout << endl;
    
    setColor(YELLOW, BLACK);
    cout << "\n5. SCORING:" << endl;
    setColor(WHITE, BLACK);
    cout << "   - Each HIT: +10 points" << endl;
    cout << "   - Each MISS: -1 point" << endl;
    cout << "   - First to sink all enemy ships wins!" << endl;
    
    setColor(CYAN, BLACK);
    cout << "\n=============================================" << endl;
    setColor(WHITE, BLACK);
    cout << "\nPress any key to continue...";
    getch();
}

// Main menu
void showMainMenu() {
    clearScreen();
    setColor(CYAN, BLACK);
    cout << "\n========================================" << endl;
    cout << "       BATTLESHIP SIMULATOR GAME        " << endl;
    cout << "========================================" << endl;
    setColor(GREEN, BLACK);
    cout << "1. Start New Game" << endl;
    setColor(YELLOW, BLACK);
    cout << "2. Instructions" << endl;
    setColor(LIGHT_BLUE, BLACK);
    cout << "3. View Leaderboard" << endl;
    setColor(RED, BLACK);
    cout << "4. Exit" << endl;
    setColor(CYAN, BLACK);
    cout << "========================================" << endl;
    setColor(WHITE, BLACK);
    cout << "Enter your choice: ";
}

// Display ship selection sidebar
void displayShipInfo() {
    setColor(YELLOW, BLACK);
    cout << "\n===== SHIPS TO PLACE =====" << endl;
    setColor(WHITE, BLACK);
    cout << "1. Aircraft Carrier (5)" << endl;
    cout << "2. Battleship (4)" << endl;
    cout << "3. Destroyer (3)" << endl;
    cout << "4. Submarine (3)" << endl;
    cout << "5. Patrol Boat (2)" << endl;
    setColor(YELLOW, BLACK);
    cout << "==========================" << endl;
    setColor(WHITE, BLACK);
}


// Student 1 Functions
void setRandomShips(char board[10][10]);
void vsComputer(char playerBoard[10][10], char computerBoard[10][10]);
void computerAttack(char playerBoard[10][10], int &computerScore);

// Student 2 Functions 
void setPlayerShips(char board[10][10], string playerName);
void vsPlayer(char board1[10][10], char board2[10][10]);
void playerAttack(char opponentBoard[10][10], int &playerScore, string playerName);
void clearBoard(char board[10][10]);
void updateScore(int &score, bool isHit);
void showGameMenu();
void displayResult(int player1Score, int player2Score, string player1Name, string player2Name);
//void testBoardDisplay();

int main() {
    int choice;
    string playerNames[10];
    int scores[10];
//    testBoardDisplay();
    
    do {
        showMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Start New Game
                clearScreen();
                setColor(GREEN, BLACK);
                cout << "\n===== GAME MODE SELECTION =====" << endl;
                setColor(WHITE, BLACK);
                cout << "1. Player vs Computer" << endl;
                cout << "2. Player vs Player" << endl;
                cout << "Enter your choice: ";
                
                int gameMode;
                cin >> gameMode;
                
                if (gameMode == 1) {
                    // Player vs Computer
                    char playerBoard[10][10];
                    char computerBoard[10][10];
                    
                    cout << "\nStarting Player vs Computer mode..." << endl;
                    
                    // Initialize boards
                    initializeBoard(playerBoard);
                    initializeBoard(computerBoard);
                    
                    
                } else if (gameMode == 2) {
                    // Player vs Player
                    char board1[10][10];
                    char board2[10][10];
                    
                    cout << "\nStarting Player vs Player mode..." << endl;
                    
                    // Initialize boards
                    initializeBoard(board1);
                    initializeBoard(board2);
                    
                    // Call vsPlayer function (to be implemented by Student 2)
                    // vsPlayer(board1, board2);
                    
                } else {
                    setColor(RED, BLACK);
                    cout << "\nInvalid choice!" << endl;
                    setColor(WHITE, BLACK);
                }
                
                cout << "\nPress any key to continue...";
                	setColor(WHITE, BLACK);
                getch();
                break;
            }
                
            case 2:
                displayInstructions();
                break;
                
            case 3: {
                clearScreen();
                int totalPlayers = loadLeaderboard(playerNames, scores);
                showLeaderboard(playerNames, scores, totalPlayers);
                cout << "\nPress any key to continue...";
                getch();
                break;
            }
                
            case 4:
                clearScreen();
                setColor(GREEN, BLACK);
                cout << "\nThank you for playing Battleship!" << endl;
                break;
                
            default:
                setColor(RED, BLACK);
                cout << "\nInvalid choice! Please try again." << endl;
                setColor(WHITE, BLACK);
                cout << "Press any key to continue...";
                getch();
        }
        
    } while (choice != 4);
    
    return 0;
}

// ==================== TEST FUNCTION ====================
// Uncomment this to test the board display with colors

void testBoardDisplay() {
    char testBoard[10][10];
    initializeBoard(testBoard);
    
    // Place some test items
    testBoard[0][0] = '5'; // Ship
    testBoard[0][1] = '5';
    testBoard[2][3] = 'X'; // Hit
    testBoard[7][8] = 'O'; // Miss
    testBoard[5][5] = 'S'; // Sunk ship
    
    cout << "\n===== YOUR BOARD (Ships Visible) =====" << endl;
    printBoard(testBoard, false);
    
    cout << "\n\n===== OPPONENT BOARD (Ships Hidden) =====" << endl;
    printBoard(testBoard, true);
    
    getch();
}

