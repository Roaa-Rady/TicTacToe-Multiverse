#include "Obstacles_Board.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Obstacles_Board::Obstacles_Board() : Board<char>(6, 6) {
    for (auto& row : board)
        for (auto& c : row)
            c = empty_symbol;
}

bool Obstacles_Board::is_cell_empty(int x, int y) const {
    return board[x][y] == empty_symbol;
}
// Update board (place X or O)
bool Obstacles_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
        return false;
    }
    if (!is_cell_empty(x, y)) {
        cout << "Cell is not empty!\n";
        return false;
    }

    board[x][y] = symbol;
    moves_counter++;

    // After every 2 moves → add 2 obstacles
    if (moves_counter % 2 == 0) {
        add_obstacles();
    }

    return true;
}
// Add 2 random obstacles
void Obstacles_Board::add_obstacles() {
    int added = 0;
    while (added < 2) {
        int x = rand() % 6;
        int y = rand() % 6;

        if (is_cell_empty(x, y)) {
            board[x][y] = obstacle_symbol;
            added++;
        }
    }
}
// Check win (4 in a row)
bool Obstacles_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Horizontal
    for (int i = 0; i < 6; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == sym && board[i][j + 1] == sym &&
                board[i][j + 2] == sym && board[i][j + 3] == sym)
                return true;

    // Vertical
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j < 6; j++)
            if (board[i][j] == sym && board[i + 1][j] == sym &&
                board[i + 2][j] == sym && board[i + 3][j] == sym)
                return true;

    // Diagonal 
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym)
                return true;

    // Diagonal 
    for (int i = 0; i <= 2; i++)
        for (int j = 3; j < 6; j++)
            if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym)
                return true;

    return false;
}

bool Obstacles_Board::is_draw(Player<char>* player) {
    // If no empty spaces except obstacles and no win
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (board[i][j] == empty_symbol)
                return false;
    return !is_win(player);
}

bool Obstacles_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
