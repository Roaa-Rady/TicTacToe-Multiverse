#include "Numerical_TicTacToe_Board.h"
#include <iostream>
using namespace std;


Numerical_TicTacToe_Board::Numerical_TicTacToe_Board() : Board<int>(3, 3) {}


bool Numerical_TicTacToe_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int val = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Invalid position! Must be 0-2.\n";
        return false;
    }
    if (get_value(x, y) != 0) {
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
bool Numerical_TicTacToe_Board::is_win(Player<int>* player) {

    for (int i = 0; i < 3; i++) {
        int sum = get_value(i, 0) + get_value(i, 1) + get_value(i, 2);
        if (sum == 15 && get_value(i, 0) != 0) return true;
    }

    for (int j = 0; j < 3; j++) {
        int sum = get_value(0, j) + get_value(1, j) + get_value(2, j);
        if (sum == 15 && get_value(0, j) != 0) return true;
    }

    if (get_value(0, 0) + get_value(1, 1) + get_value(2, 2) == 15 && get_value(0, 0) != 0) return true;

    if (get_value(0, 2) + get_value(1, 1) + get_value(2, 0) == 15 && get_value(0, 2) != 0) return true;

    return false;
}
bool Numerical_TicTacToe_Board::is_lose(Player<int>* player) {
    Player<int>* opponent = new Player<int>("", (player->get_symbol() == 'X') ? 'O' : 'X', PlayerType::HUMAN);
    opponent->set_board_ptr(this);
    bool result = is_win(opponent);
    delete opponent;
    return result;
}


bool Numerical_TicTacToe_Board::is_draw(Player<int>* p) {

    int empty_cells = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (get_value(i, j) == 0) empty_cells++;

    return empty_cells == 0 && !is_win(p);
}
bool Numerical_TicTacToe_Board::game_is_over(Player<int>* p) {
    return is_win(p) || is_draw(p);
}
