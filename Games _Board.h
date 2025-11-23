#pragma once
#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
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





