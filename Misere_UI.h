#pragma once
// Misere_UI.h
#pragma once
#include "BoardGame_Classes.h"
#include <string>
using namespace std;

class Misere_UI : public UI<char> {
public:
    Misere_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
