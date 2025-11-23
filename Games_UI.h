#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
using namespace std;
//Misere game//
class Misere_TicTacToe_UI : public UI<char> {
public:
    Misere_TicTacToe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
//Obstacles game//
class Obstacles_TicTacToe_UI : public UI<char> {
public:
    Obstacles_TicTacToe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
//5x5 Tic-tac-Toe
class TicTacToe5x5_UI : public UI<char> {
public:
    TicTacToe5x5_UI();  // Constructor

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_final_result(TicTacToe5x5_Board* board, Player<char>* p1, Player<char>* p2);
};

