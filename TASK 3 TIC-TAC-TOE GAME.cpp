#include <iostream>
#include <vector>

namespace TicTacToe {

    using namespace std;

    // Define a type alias for the game board
    using Board = vector<vector<char>>;

    // Function to display the game board
    void displayBoard(const Board& board) {
        cout << "  1 2 3" << endl;
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Function to check if a player has won
    bool checkWin(const Board& board, char player) {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }
        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
                return true;
            }
        }
        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }
        return false;
    }

    // Function to check if the game is a draw
    bool checkDraw(const Board& board) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false; // There's an empty cell, game is not a draw
                }
            }
        }
        return true; // All cells are filled, game is a draw
    }

    // Function to prompt the current player to enter their move
    void promptPlayer(char currentPlayer, Board& board) {
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row column): ";
        cin >> row >> col;

        // Check if the move is valid
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            cout << "Invalid move! Please try again." << endl;
            promptPlayer(currentPlayer, board); // Recursive call to prompt again
        } else {
            board[row - 1][col - 1] = currentPlayer; // Update the board with the player's move
        }
    }

    // Function to play the game
    void playGame() {
        Board board(3, vector<char>(3, ' '));
        char currentPlayer = 'X';
        bool gameOver = false;

        cout << "Welcome to Tic-Tac-Toe!" << endl;

        while (!gameOver) {
            displayBoard(board); // Display the board
            promptPlayer(currentPlayer, board); // Prompt the current player to enter their move

            // Check for win
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameOver = true;
            } else if (checkDraw(board)) { // Check for draw
                displayBoard(board);
                cout << "It's a draw!" << endl;
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
            }
        }

        cout << "Thanks for playing Tic-Tac-Toe!" << endl;
    }

} // namespace TicTacToe

int main() {
    using namespace TicTacToe;

    playGame(); // Start the game

    return 0;
}
