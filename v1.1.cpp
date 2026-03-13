#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>   
#include <ctime>     

using namespace std;

class TicTacToe {
private:
    vector<vector<char> > board;
    char currentPlayer;
    int moves;

public:
    TicTacToe() {
        board = vector<vector<char> >(3, vector<char>(3, ' '));
        currentPlayer = 'X';
        moves = 0;
    }

    void showBoard() {
        cout << "\n   1   2   3" << endl;
        cout << "  --- --- ---" << endl;
        
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << "| ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << " |" << endl;
            
            if (i < 2) {
                cout << "  --- --- ---" << endl;
            }
        }
        cout << "  --- --- ---" << endl;
    }

    bool moveValid(int row, int col) {
        if (row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Error: Row and column must be 1-3!" << endl;
            return false;
        }
        
        if (board[row-1][col-1] != ' ') {
            cout << "Error: Position already taken!" << endl;
            return false;
        }
        
        return true;
    }

    bool placeMove(int row, int col) {
        if (!moveValid(row, col)) {
            return false;
        }
        
        board[row-1][col-1] = currentPlayer;
        moves++;
        return true;
    }

    char checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && 
                board[i][0] == board[i][1] && 
                board[i][1] == board[i][2]) {
                return board[i][0];
            }
        }
        
        for (int j = 0; j < 3; j++) {
            if (board[0][j] != ' ' && 
                board[0][j] == board[1][j] && 
                board[1][j] == board[2][j]) {
                return board[0][j];
            }
        }
        
        if (board[0][0] != ' ' && 
            board[0][0] == board[1][1] && 
            board[1][1] == board[2][2]) {
            return board[0][0];
        }
        
        if (board[0][2] != ' ' && 
            board[0][2] == board[1][1] && 
            board[1][1] == board[2][0]) {
            return board[0][2];
        }
        
        return ' ';
    }

    bool checkDraw() {
        return moves == 9;
    }

    void changePlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getPlayer() {
        return currentPlayer;
    }

    void restart() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
        currentPlayer = 'X';
        moves = 0;
    }
	
pair<int, int> findAttackOrDefensePosition(char mySymbol, char opponentSymbol) {
    char playerSymbol[2] = {mySymbol, opponentSymbol};
    
    for (int p = 0; p < 2; p++) {
        char symbol = playerSymbol[p];
        
        for (int row = 0; row < 3; row++) {
            int count = 0;
            int emptyCol = -1;
            
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == symbol) {
                    count++;
                } else if (board[row][col] == ' ') {
                    emptyCol = col;
                }
            }
            
            if (count == 2 && emptyCol != -1) {
                return make_pair(row, emptyCol);
            }
        }
        
        for (int col = 0; col < 3; col++) {
            int count = 0;
            int emptyRow = -1;
            
            for (int row = 0; row < 3; row++) {
                if (board[row][col] == symbol) {
                    count++;
                } else if (board[row][col] == ' ') {
                    emptyRow = row;
                }
            }
            
            if (count == 2 && emptyRow != -1) {
                return make_pair(emptyRow, col);
            }
        }
        
        int count = 0;
        int emptyPos = -1;
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == symbol) {
                count++;
            } else if (board[i][i] == ' ') {
                emptyPos = i;
            }
        }
        if (count == 2 && emptyPos != -1) {
            return make_pair(emptyPos, emptyPos);
        }
        
        count = 0;
        emptyPos = -1;
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i] == symbol) {
                count++;
            } else if (board[i][2-i] == ' ') {
                emptyPos = i;
            }
        }
        if (count == 2 && emptyPos != -1) {
            return make_pair(emptyPos, 2-emptyPos);
        }
    }
    
    return make_pair(-1, -1);   
}

bool aiMoveSmart() {
    pair<int, int> pos = findAttackOrDefensePosition('O', 'X');
    
    if (pos.first != -1) {
        int row = pos.first;
        int col = pos.second;
        board[row][col] = currentPlayer;   
        moves++;
        cout << "AI (Player " << currentPlayer << ") chose position: " 
             << row+1 << " " << col+1 << endl;
        return true;
    }
    return aiMoveRand();  
}

	
	
bool aiMoveRand() {
	vector<pair<int, int> > availableMoves;
        
    for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    availableMoves.push_back(make_pair(i, j));
                }
        }
    }
        
    if (availableMoves.empty()) {
        return false;  
    }
        
    int index = rand() % availableMoves.size();
    int row = availableMoves[index].first;
    int col = availableMoves[index].second;
        
    board[row][col] = currentPlayer;
    moves++;
        
    cout << "AI (Player " << currentPlayer << ") chose position: " 
        << row+1 << " " << col+1 << endl;
        
    return true;
    }
};

void showRules() {
    cout << "============ TIC-TAC-TOE ============" << endl;
    cout << "Rules:" << endl;
    cout << "1. Two players: X and O" << endl;
    cout << "2. Board is 3x3 grid" << endl;
    cout << "3. Enter row and column (1-3)" << endl;
    cout << "4. Get three in a row to win" << endl;
    cout << "=====================================" << endl << endl;
}

void showMenu() {
    cout << "========== GAME MODE ==========" << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs AI (Random)" << endl;
    cout << "================================" << endl << endl;
}

int main() {
    srand(time(NULL));   
    TicTacToe game;
    char again = 'y';
    int gameMode = 1;
    
    showRules();
    
    while (again == 'y' || again == 'Y') {
        showMenu();
        cout << "Select game mode (1 or 2): ";
        cin >> gameMode;
        
        while (gameMode != 1 && gameMode != 2) {
            cout << "Invalid choice! Please enter 1 or 2: ";
            cin >> gameMode;
        }
        
        game.restart();
        bool finished = false;
        while (!finished) {
            Sleep(3000);
            system("cls");
            game.showBoard();
            if (gameMode == 1) {
                cout << "\nPlayer " << game.getPlayer() << "'s turn" << endl;
                int row, col;
                
                while (true) {
                    cout << "Enter row and column (example: 1 2): ";
                    cin >> row >> col;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Error: Enter valid numbers!" << endl;
                        continue;
                    }
                    
                    if (game.placeMove(row, col)) {
                        break;
                    }
                }
            } else {
                if (game.getPlayer() == 'X') {
                    cout << "\nYour turn (Player " << game.getPlayer() << ")" << endl;
                    int row, col;
                    
                    while (true) {
                        cout << "Enter row and column (example: 1 2): ";
                        cin >> row >> col;
                        
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Error: Enter valid numbers!" << endl;
                            continue;
                        }
                        
                        if (game.placeMove(row, col)) {
                            break;
                        }
                    }
                } else {
                    cout << "\nAI's turn (Player " << game.getPlayer() << ")" << endl;
                    Sleep(1000);   
                    game.aiMoveSmart();
                }
            }
            
            char winner = game.checkWin();
            
            if (winner != ' ') {
                game.showBoard();
                cout << "\nPlayer " << winner << " wins!" << endl;
                finished = true;
            } else if (game.checkDraw()) {
                game.showBoard();
                cout << "\nDraw game!" << endl;
                finished = true;
            } else {
                game.changePlayer();
            }
        }
        
        cout << "\nPlay again? (y/n): ";
        cin >> again;
        
        if (again == 'y' || again == 'Y') {
            system("cls");
        }
    }
    
    cout << "\nThanks for playing Tic-Tac-Toe!" << endl;
    
    return 0;
}

