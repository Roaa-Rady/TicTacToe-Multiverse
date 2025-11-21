#pragma once
// Misere_Board.h
#pragma once
#include "BoardGame_Classes.h"

class Misere_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    Misere_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;   // For GameManager: returns true if opponent has lost (so current wins)
    bool is_lose(Player<char>* player) override;  // returns true if THIS player made a 3-in-row (so he loses)
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};
