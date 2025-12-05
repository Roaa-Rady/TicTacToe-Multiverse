#include "Games_Board.h"
#include "Games_UI.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

//Board implementation
Numerical_TicTacToe_Board::Numerical_TicTacToe_Board() : Board<char>(3, 3) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            set_value(i, j, ' ');
}


bool Numerical_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char val = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Invalid position! Must be 0-2.\n";
        return false;
    }
    if (get_value(x, y) !=' ') {
        cout << "This cell is already taken!\n";
        return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (get_value(i, j) == val) {
                cout << "Number " << val << " is already used!\n";
                return false;
            }
        }
    }

    set_value(x, y, val);
    return true;  
}
bool Numerical_TicTacToe_Board::is_win(Player<char>* player) {
    auto check_line = [&](char a, char b, char c) {
        return a != ' ' && b != ' ' && c != ' ' &&
            (stoi(string(1, a)) + stoi(string(1, b)) + stoi(string(1, c)) == 15);
        };

    for (int i = 0; i < 3; i++) {
        if (check_line(get_value(i, 0), get_value(i, 1), get_value(i, 2))) return true;
    }
    
    for (int j = 0; j < 3; j++) {
        if (check_line(get_value(0, j), get_value(1, j), get_value(2, j))) return true;
    }
   
    if (check_line(get_value(0, 0), get_value(1, 1), get_value(2, 2))) return true;
    if (check_line(get_value(0, 2), get_value(1, 1), get_value(2, 0))) return true;

    return false;
}
bool Numerical_TicTacToe_Board::is_lose(Player<char>* player) {
    char opp_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char>* opponent = new Player<char>("Opponent", opp_symbol, PlayerType::HUMAN);
    opponent->set_board_ptr(this);
    bool result = is_win(opponent);
    delete opponent;
    return result;
}

bool Numerical_TicTacToe_Board::is_draw(Player<char>* p) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (get_value(i, j) == ' ') return false;

    return !is_win(p);
}
bool Numerical_TicTacToe_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}
//UI implementation
Numerical_TicTacToe_UI::Numerical_TicTacToe_UI()
    : UI<char>("Welcome to Numerical Tic-Tac-Toe!", 3) {}

Player<char>* Numerical_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating player: " << name << endl;
    return new Player<char>(name, symbol, type);
}


Move<char>* Numerical_TicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    char num;
    auto* board = dynamic_cast<Numerical_TicTacToe_Board*>(player->get_board_ptr());

    //Human
    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << player->get_name() << " enter row and column (0-2): ";
            cin >> x >> y;
            cout << "Enter your number (1-9): ";
            cin >> num;

            vector<char> allowed_numbers = (player->get_symbol() == 'X') ?
                vector<char>{'1', '3', '5', '7', '9'} : vector<char>{'2', '4', '4', '8'};

            if (find(allowed_numbers.begin(), allowed_numbers.end(), num) == allowed_numbers.end()) {
                cout << "You can only use: ";
                for (auto& n : allowed_numbers) cout << n << " ";
                cout << "\n";
                continue;
            }

            return new Move<char>(x, y, num);
        }
    }

      // Computer
    else {
        cout << player->get_name() << " computer is thinking";
        vector<char> allowed_numbers = (player->get_symbol() == 'X') ?
            vector<char>{'1', '3', '5', '7', '9'} : vector<char>{ '2', '4', '4', '8' };

        while (true) {
            x = rand() % 3;
            y = rand() % 3;
            num = allowed_numbers[rand() % allowed_numbers.size()];
            cout << ".";

            if (board->get_value(x, y) == ' ') {
                bool used = false;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        if (board->get_value(i, j) == num) used = true;

                if (!used) {
                    cout << " -> (" << x << "," << y << ") with " << num << endl;
                    return new Move<char>(x, y, num); // بدون set_value
                }
            }
        }
    }
}
