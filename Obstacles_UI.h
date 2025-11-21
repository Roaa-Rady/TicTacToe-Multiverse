#pragma once
#pragma once
#include "BoardGame_Classes.h"
#include "Obstacles_Board.h"
#include <string>
using namespace std;

class Obstacles_UI : public UI<char> {
public:
    Obstacles_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
