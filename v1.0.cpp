#include <iostream>
#include <windows.h>
#include <vector>

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

int main() {
    TicTacToe game;
    char again = 'y';
    
    showRules();
    
    while (again == 'y' || again == 'Y') {
        game.restart();
        bool finished = false;
        
        while (!finished) {
        	Sleep(3000);
        	system("cls");
            game.showBoard();
            int row, col;
            cout << "\nPlayer " << game.getPlayer() << "'s turn" << endl;
            
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
    }
    
    cout << "\nThanks for playing Tic-Tac-Toe!" << endl;
    
    return 0;

}
