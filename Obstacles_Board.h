#pragma once
#pragma once
#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

class Obstacles_Board : public Board<char> {
private:
    char empty_symbol = '.';
    char obstacle_symbol = '#';
    int moves_counter = 0; // count moves to add obstacles every 2 moves

public:
    Obstacles_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void add_obstacles();             // add 2 obstacles
    bool is_cell_empty(int x, int y) const;
};
