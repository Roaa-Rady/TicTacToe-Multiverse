// Misere_UI.cpp
#include "Misere_UI.h"
#include"Misere_Board.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Misere_UI::Misere_UI() : UI<char>("Welcome to Misère Tic-Tac-Toe (avoid making 3-in-row)!", 3) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else { // COMPUTER: choose random empty
        Board<char>* b = player->get_board_ptr();
        do {
            x = rand() % b->get_rows();
            y = rand() % b->get_columns();
        } while (dynamic_cast<Misere_Board*>(b) == nullptr ? false : (((Misere_Board*)b)->get_board_matrix()[x][y] != '.'));
        cout << player->get_name() << " (Computer) plays: " << x << "," << y << endl;
    }
    return new Move<char>(x, y, player->get_symbol());
}
