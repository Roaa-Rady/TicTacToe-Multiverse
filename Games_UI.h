#pragma once
#include "BoardGame_Classes.h"
#include "TicTacToe4x4_Board.h"
#include "Numerical_TicTacToe_Board.h"
#include <iostream>
#include <string>
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

// 4x4TicTacToe
class TicTacToe4x4_UI : public UI<char> {
public:
    TicTacToe4x4_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

//Numerical TicTacToe
class Numerical_TicTacToe_UI : public UI<int> {
public:
    Numerical_TicTacToe_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    Move<int>* get_move(Player<int>* player) override;
};

// SUS game //
class SUS_UI : public UI<char> {
public:
    SUS_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_final_result(Player<char>* p1, Player<char>* p2); 
    Player<char>** setup_players() override;
};
