#pragma once
#include "BoardGame_Classes.h"

class Numerical_TicTacToe_Board : public Board<int> {
public:
    Numerical_TicTacToe_Board();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* p) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    bool is_cell_empty(int x, int y) const { return get_value(x, y) == 0; }
    int get_value(int x, int y) const {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            return board[x][y];
        return -1;
    }
    void set_value(int x, int y, int val) {
        if (x >= 0 && x < rows && y >= 0 && y < columns) board[x][y] = val;
    }
};
