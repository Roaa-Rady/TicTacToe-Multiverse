#include"Games _Board.h"
#include"Games_UI.h"
#include <iostream>
#include <cstdlib>
using namespace std;
//Board//
Obstacles_TicTacToe_Board::Obstacles_TicTacToe_Board() : Board<char>(6, 6) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

void Obstacles_TicTacToe_Board::add_random_obstacles() {
    int placed = 0;

    while (placed < 2) {
        int x = rand() % 6;
        int y = rand() % 6;

        if (board[x][y] == blank_symbol) {
            board[x][y] = obstacle_symbol;
            placed++;
        }
    }

    cout << "\nTwo obstacles added!\n";
}

bool Obstacles_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
        return false;
    }

    if (board[x][y] == obstacle_symbol) {
        cout << "This cell is blocked!\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell already taken!\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;

    if (n_moves % 2 == 0)
        add_random_obstacles();

    return true;
}

bool Obstacles_TicTacToe_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j <= 6 - 4; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym)
                return true;

            if (board[j][i] == sym && board[j + 1][i] == sym &&
                board[j + 2][i] == sym && board[j + 3][i] == sym)
                return true;
        }
    }

    for (int i = 0; i <= 6 - 4; i++) {
        for (int j = 0; j <= 6 - 4; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym)
                return true;

            if (board[i + 3][j] == sym && board[i + 2][j + 1] == sym &&
                board[i + 1][j + 2] == sym && board[i][j + 3] == sym)
                return true;
        }
    }

    return false;
}

bool Obstacles_TicTacToe_Board::is_lose(Player<char>*) {
    return false;
}

bool Obstacles_TicTacToe_Board::is_draw(Player<char>* p) {
    if (is_win(p)) return false;
    return n_moves >= 36;
}

bool Obstacles_TicTacToe_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

//UI//

Obstacles_TicTacToe_UI::Obstacles_TicTacToe_UI()
    : UI<char>("Welcome to Obstacles Tic Tac Toe!", 2) {}

Player<char>* Obstacles_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_TicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " enter x y (0-5): ";
        cin >> x >> y;
    }
    else {
        do {
            x = rand() % 6;
            y = rand() % 6;
        } while (b->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << "," << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}
