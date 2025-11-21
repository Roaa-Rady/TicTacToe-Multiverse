#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Obstacles_TicTacToe_Board : public Board<char> {

private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';

public:
    Obstacles_TicTacToe_Board() : Board<char>(6, 6) {
        // Initialize empty board
        for (auto& row : board)
            for (auto& c : row)
                c = blank_symbol;
    }
    // Add two obstacles every time BOTH players played once
    void add_random_obstacles() {
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
    bool update_board(Move<char>* move) override {
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

        // After every 2 moves (one round)
        if (n_moves % 2 == 0) add_random_obstacles();

        return true;
    }
    bool is_win(Player<char>* player) override {
        char sym = player->get_symbol();

        // Check 4 in a row horizontally & vertically
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j <= 6 - 4; j++) {
                // horizontal
                if (board[i][j] == sym && board[i][j + 1] == sym &&
                    board[i][j + 2] == sym && board[i][j + 3] == sym)
                    return true;

                // vertical
                if (board[j][i] == sym && board[j + 1][i] == sym &&
                    board[j + 2][i] == sym && board[j + 3][i] == sym)
                    return true;
            }
        }

        // Diagonals
        for (int i = 0; i <= 6 - 4; i++) {
            for (int j = 0; j <= 6 - 4; j++) {
                // diagonal ? right
                if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                    board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym)
                    return true;

                // diagonal ? right
                if (board[i + 3][j] == sym && board[i + 2][j + 1] == sym &&
                    board[i + 1][j + 2] == sym && board[i][j + 3] == sym)
                    return true;
            }
        }

        return false;
    }
    bool is_lose(Player<char>*) override {
        return false;
    }

    bool is_draw(Player<char>* p) override {
        if (is_win(p)) return false;
        return n_moves >= 36;
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }
};
