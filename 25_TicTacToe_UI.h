#pragma once
#include "BoardGame_Classes.h"
#include "25_TicTacToe_Board.h"
#include <iostream>
using namespace std;

class TicTacToe5x5_UI : public UI<char> {
public:
    TicTacToe5x5_UI() : UI<char>("Welcome to 5x5 Tic Tac Toe!", 2) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        Board<char>* b = player->get_board_ptr();

        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " enter x y (0-4): ";
            cin >> x >> y;
        }
        else {
            do {
                x = rand() % 5;
                y = rand() % 5;
            } while (b->get_board_matrix()[x][y] != '.');

            cout << player->get_name() << " (Computer) played (" << x << "," << y << ")\n";
        }

        return new Move<char>(x, y, player->get_symbol());
    }

    void display_final_result(TicTacToe5x5_Board* board, Player<char>* p1, Player<char>* p2) {
        int p1_count = board->count_3_in_row(p1->get_symbol());
        int p2_count = board->count_3_in_row(p2->get_symbol());

        cout << "\nGame Over!\n";
        cout << p1->get_name() << " has " << p1_count << " sets of 3-in-row.\n";
        cout << p2->get_name() << " has " << p2_count << " sets of 3-in-row.\n";

        if (p1_count > p2_count) cout << p1->get_name() << " wins!\n";
        else if (p2_count > p1_count) cout << p2->get_name() << " wins!\n";
        else cout << "It's a tie!\n";
    }
};
