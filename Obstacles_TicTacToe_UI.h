//#pragma once
#include "BoardGame_Classes.h"
#include"C:\Users\dell\source\repos\Asss3.opp\Asss3\Obstacles_TicTacToe_Board.h"
#include <iostream>
using namespace std;

class Obstacles_TicTacToe_UI : public UI<char> {

public:

    Obstacles_TicTacToe_UI() : UI<char>("Welcome to Obstacles Tic Tac Toe!", 2) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        Board<char>* b = player->get_board_ptr();

        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " enter x y (0-5): ";
            cin >> x >> y;
        }
        else {
            // Random computer move
            do {
                x = rand() % 6;
                y = rand() % 6;
            } while (b->get_board_matrix()[x][y] != '.');

            cout << player->get_name() << " (Computer) played (" << x << "," << y << ")\n";
        }

        return new Move<char>(x, y, player->get_symbol());
    }
};
