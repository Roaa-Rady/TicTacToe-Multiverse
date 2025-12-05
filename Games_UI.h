#pragma once
#include "BoardGame_Classes.h"
#include"Games_Board.h"
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
class Numerical_TicTacToe_UI : public UI<char> {
public:
    Numerical_TicTacToe_UI();
    
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

//Pyramid TicTacToe
class Pyramid_TicTacToe_UI : public UI<char> {
public:
    Pyramid_TicTacToe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};


// SUS Game //
class SUS_UI : public UI<char> {
public:
    SUS_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_final_result(Player<char>* p1, Player<char>* p2); 
    Player<char>** setup_players() override;
};


// FourInARow Game //
class FourInARowUI : public UI<char> {
public:
    FourInARowUI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_final_result(Player<char>* p1, Player<char>* p2);

    Player<char>** setup_players() override;
};


// Infinity Tic-Tac-Toe //
class InfinityTicTacToe_UI : public UI<char> {
public:
    InfinityTicTacToe_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_final_result(Player<char>* p1, Player<char>* p2);
    Player<char>** setup_players() override;
};

//Word Tic-Tac-Toe
class Word_TicTacToe_UI : public UI<char> {
public:
    Word_TicTacToe_UI();
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void show_result(const Word_TicTacToe_Board* board, Player<char>* winner) const;
};

/Diamond game//
class Diamond_UI : public UI<char> {
public:
    Diamond_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;
};

//Memory TicTacToe
class Memory_TicTacToe_UI : public UI<char> {
public:
	Memory_TicTacToe_UI();
    Move<char>* get_move(Player<char>*) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    void display_board_matrix(const vector<vector<char>>& matrix) const override;

};
