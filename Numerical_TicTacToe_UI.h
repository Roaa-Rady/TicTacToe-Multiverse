#pragma once
#pragma once
#include "BoardGame_Classes.h"
#include "Numerical_TicTacToe_Board.h"
#include <string>
using namespace std;

class Numerical_TicTacToe_UI : public UI<int> {
public:
    Numerical_TicTacToe_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    Move<int>* get_move(Player<int>* player) override;
};
