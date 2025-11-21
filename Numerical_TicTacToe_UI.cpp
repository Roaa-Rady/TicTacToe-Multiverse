#include "Numerical_TicTacToe_UI.h"
#include "Numerical_TicTacToe_Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Numerical_TicTacToe_UI::Numerical_TicTacToe_UI()
    : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 3) {}

Player<int>* Numerical_TicTacToe_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating player: " << name << endl;
    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_TicTacToe_UI::get_move(Player<int>* player) {
    int x, y, num;
    auto* board = dynamic_cast<Numerical_TicTacToe_Board*>(player->get_board_ptr());


    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << player->get_name() << " enter row and column (0-2): ";
            cin >> x >> y;
            cout << "Enter your number (1-9): ";
            cin >> num;

            vector<int> allowed_numbers = (player->get_symbol() == 'X') ?
                vector<int>{1, 3, 5, 7, 9} : vector<int>{ 2, 4, 6, 8 };

            if (find(allowed_numbers.begin(), allowed_numbers.end(), num) == allowed_numbers.end()) {
                cout << "You can only use: ";
                for (int n : allowed_numbers) cout << n << " ";
                cout << "\n";
                continue;
            }

            return new Move<int>(x, y, num);
        }
    }

    // الجزء الخاص بالكمبيوتر
    else {
        cout << player->get_name() << " (Computer) is thinking";
        vector<int> allowed_numbers = (player->get_symbol() == 'X') ?
            vector<int>{1, 3, 5, 7, 9} : vector<int>{ 2, 4, 6, 8 };

        while (true) {
            x = rand() % 3;
            y = rand() % 3;
            num = allowed_numbers[rand() % allowed_numbers.size()];
            cout << ".";

            if (board->get_value(x, y) == 0) {
                bool used = false;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        if (board->get_value(i, j) == num) used = true;

                if (!used) {
                    cout << " -> (" << x << "," << y << ") with " << num << endl;
                    return new Move<int>(x, y, num); // بدون set_value
                }
            }
        }
    }
}
