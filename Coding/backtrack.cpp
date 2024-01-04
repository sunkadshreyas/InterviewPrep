#include<bits/stdc++.h>

using namespace std;

bool isQueenPlacementValid(vector<vector<char>> board, int row, int col) {
    // check no other queens in the row
    for(int c=0; c < col; c++) {
        if(board[row][c] == 'Q') {
            return false;
        }
    }
    // check no other queens in the column
    for(int r=0; r < row; r++) {
        if(board[r][col] == 'Q') {
            return false;
        }
    }
    // check no other queens in the left diagonal
    int r = row-1;
    int c = col-1;
    while(r >= 0 and c >= 0) {
        if(board[r][c] == 'Q'){
            return false;
        }
        r--;
        c--;
    }
    // check no other queens in the right diagonal
    r = row-1;
    c = col+1;
    while(r >= 0 and c < board.size()) {
        if(board[r][c] == 'Q') {
            return false;
        }
        r--;
        c++;
    }
    return true;
}

void nQueensSolver(vector<vector<char>> &board, int row) {
    if(row == board.size()) {
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board.size(); j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        return;
    }
    for(int c = 0; c < board.size(); c++) {
        board[row][c] = 'Q';
        if (isQueenPlacementValid(board, row, c)) {
            // in 1 row there can be max 1 queen, so go to next row
            nQueensSolver(board, row+1);
        }
        board[row][c] = '.';
    }
}

int main(int argc, char const *argv[]) {
    int n;
    cout << "Enter the size of the board : ";
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n, '.'));
    nQueensSolver(board, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
