//#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class Misere_TicTacToe_UI : public UI<char> {

public:

    Misere_TicTacToe_UI() : UI<char>("Welcome to Misère Tic Tac Toe!", 3) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) override {
        int x, y;

        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " enter x y (0-2): ";
            cin >> x >> y;
        }
        else {
            // RANDOM COMPUTER MOVE
            Board<char>* board = player->get_board_ptr();
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (board->get_board_matrix()[x][y] != '.');

            cout << player->get_name() << " (Computer) played (" << x << ", " << y << ")\n";
        }

        return new Move<char>(x, y, player->get_symbol());
    }
};
