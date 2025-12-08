#pragma once
#include "BoardGame_Classes.h"
#include"Games_Board.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
/// @brief Misere Tic-Tac-Toe UI class
class Misere_TicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    Misere_TicTacToe_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;
};

/// @brief Obstacles Tic-Tac-Toe UI class
class Obstacles_TicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    Obstacles_TicTacToe_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;
};

/// @brief 5x5 Tic-Tac-Toe UI class
class TicTacToe5x5_UI : public UI<char> {
public:
    /// @brief Constructor
    TicTacToe5x5_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Displays the final result of the game
    void display_final_result(TicTacToe5x5_Board* board, Player<char>* p1, Player<char>* p2);
};

/// @brief 4x4 Tic-Tac-Toe UI class
class TicTacToe4x4_UI : public UI<char> {
public:
    /// @brief Constructor
    TicTacToe4x4_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;
};

/// @brief Numerical Tic-Tac-Toe UI class
class Numerical_TicTacToe_UI : public UI<int> {
public:
    /// @brief Constructor
    Numerical_TicTacToe_UI();

    /// @brief Creates a player for the game
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<int>* get_move(Player<int>* player) override;
};

/// @brief SUS Tic-Tac-Toe UI class
class SUS_UI : public UI<char> {
public:
    /// @brief Constructor
    SUS_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Sets up the players
    Player<char>** setup_players() override;
};

/// @brief Diamond Tic-Tac-Toe UI class
class Diamond_UI : public UI<char> {
public:
    /// @brief Constructor
    Diamond_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;
};

/// @brief Ultimate Tic-Tac-Toe UI class
class Ultimate_UI : public UI<char> {
public:
    /// @brief Constructor
    Ultimate_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;
};

/// @brief Infinity Tic-Tac-Toe UI class
class InfinityTicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    InfinityTicTacToe_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Displays the final result of the game
    void display_final_result(Player<char>* p1, Player<char>* p2);

    /// @brief Sets up the players
    Player<char>** setup_players() override;
};

/// @brief Memory Tic-Tac-Toe UI class
class Memory_TicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    Memory_TicTacToe_UI();

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>*) override;

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Displays the board matrix
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

/// @brief Word Tic-Tac-Toe UI class
class Word_TicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    Word_TicTacToe_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Shows the result of the game
    void show_result(const Word_TicTacToe_Board* board, Player<char>* winner) const;
};

/// @brief Four-in-a-Row UI class
class FourInARowUI : public UI<char> {
public:
    /// @brief Constructor
    FourInARowUI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Displays the final result of the game
    void display_final_result(Player<char>* p1, Player<char>* p2);

    /// @brief Sets up the players
    Player<char>** setup_players() override;
};

/// @brief Pyramid Tic-Tac-Toe UI class
class Pyramid_TicTacToe_UI : public UI<char> {
public:
    /// @brief Constructor
    Pyramid_TicTacToe_UI();

    /// @brief Creates a player for the game
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Gets a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// @brief Displays the board matrix
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};
