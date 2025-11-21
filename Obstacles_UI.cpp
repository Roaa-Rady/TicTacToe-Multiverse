#include "Obstacles_UI.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Obstacles_UI::Obstacles_UI()
    : UI<char>("Welcome to Obstacles Tic-Tac-Toe!", 3) {}

Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char>* Obstacles_UI::get_move(Player<char>* player) {
    int x, y;

    auto* board = player->get_board_ptr();

    // HUMAN
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " enter row and column: ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    // COMPUTER
    cout << player->get_name() << " (Computer) is thinking";
    Obstacles_Board* ob = dynamic_cast<Obstacles_Board*>(board);

    while (true) {
        x = rand() % 6;
        y = rand() % 6;
        cout << ".";

        if (ob && ob->is_cell_empty(x, y)) {
            cout << " -> (" << x << "," << y << ")\n";
            return new Move<char>(x, y, player->get_symbol());
        }
    }
}
