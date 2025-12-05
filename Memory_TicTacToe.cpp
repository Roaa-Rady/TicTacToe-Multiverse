#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
using namespace std;

//Board
Memory_TicTacToe_Board::Memory_TicTacToe_Board()
    : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

bool Memory_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (!is_empty_cell(x, y)) return false;

    board[x][y] = s;
    n_moves++;
    return true;
}

bool Memory_TicTacToe_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    // Rows & columns
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == s && board[i][1] == s && board[i][2] == s) ||
            (board[0][i] == s && board[1][i] == s && board[2][i] == s))
            return true;
    // Diagonals
    if ((board[0][0] == s && board[1][1] == s && board[2][2] == s) ||
        (board[0][2] == s && board[1][1] == s && board[2][0] == s))
        return true;

    return false;
}

bool Memory_TicTacToe_Board::is_lose(Player<char>* player) { return false; }

bool Memory_TicTacToe_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && !is_win(player);
}

bool Memory_TicTacToe_Board::is_empty_cell(int r, int c) {
    return board[r][c] == ' ';
}

bool Memory_TicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//UI

Memory_TicTacToe_UI::Memory_TicTacToe_UI()
    : UI<char>("Welcome to Memory Tic-Tac-Toe!", 3) {}

Player<char>* Memory_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}


void Memory_TicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    char occupied_symbol = '*';
    cout << "    0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " |";
        for (int j = 0; j < 3; j++) {
            char c = (matrix[i][j] == ' ') ? ' ' : occupied_symbol;
            cout << " " << c << " |";
        }
        cout << "\n   -----------\n";
    }
}

Move<char>* Memory_TicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    auto* board = dynamic_cast<Memory_TicTacToe_Board*>(player->get_board_ptr());
//Human
    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << player->get_name() << " enter row and column (0-2): ";
            cin >> x >> y;
            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "Invalid input! Try again.\n";
                continue;
            }
            if (!board->is_empty_cell(x, y)) {
                cout << "Cell already taken! Try again.\n";
                continue;
            }
            cout << "You placed at (" << x << "," << y << ")\n";
            return new Move<char>(x, y, player->get_symbol());
        }
    }
    // Computer
    else { 
        cout << player->get_name() << " (computer) is thinking\n";
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (!board->is_empty_cell(x, y));

        cout << player->get_name() << " chose: (" << x << "," << y << ")\n";
        return new Move<char>(x, y, player->get_symbol());
    }
}

