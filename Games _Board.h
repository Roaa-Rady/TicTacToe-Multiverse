#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
//misere game//
class Misere_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Misere_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_lose(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//obstacle game//
class Obstacles_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';

public:
    Obstacles_TicTacToe_Board();

    void add_random_obstacles();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//5x5 Tic-tac-Toe
class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol;

public:
    TicTacToe5x5_Board();  

    bool update_board(Move<char>* move) override;
    int count_3_in_row(char sym);
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
};

//4x4 TicTacToe
class TicTacToe4x4_Board : public Board<char> {
public:
    TicTacToe4x4_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_cell_empty(int x, int y) const {
        return get_value(x, y) == '.';
    }

    virtual char get_value(int x, int y) const {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            return board[x][y];
        return '.';
    }

    void set_value(int x, int y, char val) {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            board[x][y] = val;
    }
};

//Numerical TicTacToe
class Numerical_TicTacToe_Board : public Board<int> {
public:
    Numerical_TicTacToe_Board();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* p) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    bool is_cell_empty(int x, int y) const { return this->get_value(x, y) == 0; }

};

//Pyramid TicTacToe
class Pyramid_TicTacToe_Board : public Board<char> {
public:
    Pyramid_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

};






