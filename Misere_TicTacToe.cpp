#include"games_Board.h"
#include"games_UI.h"
#include <cstdlib> using namespace std;

// Board //

Misere_TicTacToe_Board::Misere_TicTacToe_Board() : Board<char>(3, 3) { for (auto& row : board) for (auto& c : row) c = blank_symbol; }

bool Misere_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x(); int y = move->get_y(); char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell already taken!\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    return true;

}

bool Misere_TicTacToe_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();

    auto line = [&](char a, char b, char c) {
        return (a == sym && b == sym && c == sym);
        };

    for (int i = 0; i < 3; i++)
        if (line(board[i][0], board[i][1], board[i][2]))
            return true;

    for (int j = 0; j < 3; j++)
        if (line(board[0][j], board[1][j], board[2][j]))
            return true;

    if (line(board[0][0], board[1][1], board[2][2])) return true;
    if (line(board[0][2], board[1][1], board[2][0])) return true;

    return false;

}

bool Misere_TicTacToe_Board::is_win(Player<char>*) { return false; }

bool Misere_TicTacToe_Board::is_draw(Player<char>* p) { return (n_moves == 9 && !is_lose(p)); }

bool Misere_TicTacToe_Board::game_is_over(Player<char>* p) { return is_lose(p) || is_draw(p); }

//UI//

Misere_TicTacToe_UI::Misere_TicTacToe_UI() : UI<char>("Welcome to Misère Tic Tac Toe!", 3) {}

Player<char>* Misere_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) { return new Player<char>(name, symbol, type); }

Move<char>* Misere_TicTacToe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " enter x y (0-2): ";
        cin >> x >> y;
    }
    else {
        Board<char>* board = player->get_board_ptr();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());

}
