//#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class Misere_TicTacToe_Board : public Board<char> {

private:
    char blank_symbol = '.';

public:

    Misere_TicTacToe_Board() : Board<char>(3, 3) {
        // Fill board with dots
        for (auto& row : board)
            for (auto& c : row)
                c = blank_symbol;
    }
    // UPDATE BOARD
    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char mark = move->get_symbol();

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
    // Player LOSES if they make 3-in-a-row
    bool is_lose(Player<char>* player) override {
        char sym = player->get_symbol();

        auto line = [&](char a, char b, char c) {
            return (a == sym && b == sym && c == sym);
            };

        // Rows
        for (int i = 0; i < 3; i++)
            if (line(board[i][0], board[i][1], board[i][2]))
                return true;

        // Columns
        for (int j = 0; j < 3; j++)
            if (line(board[0][j], board[1][j], board[2][j]))
                return true;

        // Diagonals
        if (line(board[0][0], board[1][1], board[2][2])) return true;
        if (line(board[0][2], board[1][1], board[2][0])) return true;

        return false;
    }
    // In Misère: no "win", only lose
    bool is_win(Player<char>*) override {
        return false;
    }
    // DRAW = board full AND nobody lost
    bool is_draw(Player<char>* p) override {
        return (n_moves == 9 && !is_lose(p));
    }

   
    bool game_is_over(Player<char>* p) override {
        return is_lose(p) || is_draw(p);
    }
};
