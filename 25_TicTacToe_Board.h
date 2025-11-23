#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    TicTacToe5x5_Board() : Board<char>(5, 5) {
        for (auto& row : board)
            for (auto& c : row)
                c = blank_symbol;
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char mark = move->get_symbol();

        if (x < 0 || x >= 5 || y < 0 || y >= 5) {
            cout << "Invalid position! Row and column must be 0-4.\n";
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

    int count_3_in_row(char sym) {
        int count = 0;

        // Rows
        for (int i = 0; i < 5; i++)
            for (int j = 0; j <= 2; j++)
                if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                    count++;

        // Columns
        for (int j = 0; j < 5; j++)
            for (int i = 0; i <= 2; i++)
                if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                    count++;

        // Diagonals
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++) {
                if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                    count++;
                if (board[i + 2][j] == sym && board[i + 1][j + 1] == sym && board[i][j + 2] == sym)
                    count++;
            }

        return count;
    }

    bool is_win(Player<char>*) override { return false; }

    bool is_lose(Player<char>*) override { return false; }

    bool is_draw(Player<char>*) override { return n_moves >= 25; }

    bool game_is_over(Player<char>*) override { return n_moves >= 25; }
};
