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
