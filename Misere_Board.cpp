// Misere_Board.cpp
#include "Misere_Board.h"
#include <cctype>

Misere_Board::Misere_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    n_moves = 0;
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    if (board[x][y] != blank_symbol) return false;

    board[x][y] = std::toupper(mark);
    n_moves++;
    return true;
}

// helper to check whether a given symbol has any 3-in-row
static bool has_three_in_row(const std::vector<std::vector<char>>& b, char sym, char blank_symbol) {
    auto all_equal = [&](char a, char b2, char c) { return a == b2 && b2 == c && a != blank_symbol; };

    // rows
    for (int i = 0; i < 3; i++)
        if (all_equal(b[i][0], b[i][1], b[i][2]) && b[i][0] == sym) return true;
    // cols
    for (int j = 0; j < 3; j++)
        if (all_equal(b[0][j], b[1][j], b[2][j]) && b[0][j] == sym) return true;
    // diags
    if (all_equal(b[0][0], b[1][1], b[2][2]) && b[1][1] == sym) return true;
    if (all_equal(b[0][2], b[1][1], b[2][0]) && b[1][1] == sym) return true;
    return false;
}

bool Misere_Board::is_lose(Player<char>* player) {
    // Player loses if he has formed a 3-in-row with his symbol
    char sym = player->get_symbol();
    return has_three_in_row(board, sym, blank_symbol);
}

bool Misere_Board::is_win(Player<char>* player) {
    // For GameManager semantics: current player "wins" if opponent has lost (i.e., opponent created 3-in-row)
    // find opponent symbol (assume X and O)
    char sym = player->get_symbol();
    char opp = (std::toupper(sym) == 'X') ? 'O' : 'X';
    return has_three_in_row(board, opp, blank_symbol);
}

bool Misere_Board::is_draw(Player<char>* player) {
    // draw if board full and no one made 3-in-row
    if (n_moves < 9) return false;
    // if neither player has 3-in-row -> draw
    bool x_three = has_three_in_row(board, 'X', blank_symbol);
    bool o_three = has_three_in_row(board, 'O', blank_symbol);
    return !x_three && !o_three;
}

bool Misere_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}
