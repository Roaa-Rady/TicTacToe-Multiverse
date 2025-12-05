#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <deque>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>


using namespace std;
//misere game//
class Misere_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Misere_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_lose(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//obstacle game//
class Obstacles_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';

public:
    Obstacles_TicTacToe_Board();

    void add_random_obstacles();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//5x5 Tic-tac-Toe
class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol;

public:
    TicTacToe5x5_Board();  

    bool update_board(Move<char>* move) override;
    int count_3_in_row(char sym);
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
};

//4x4 TicTacToe
class TicTacToe4x4_Board : public Board<char> {
public:
    TicTacToe4x4_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_cell_empty(int x, int y) const {
        return get_value(x, y) == '.';
    }

    virtual char get_value(int x, int y) const {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            return board[x][y];
        return '.';
    }

    void set_value(int x, int y, char val) {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            board[x][y] = val;
    }
};

//Numerical TicTacToe
class Numerical_TicTacToe_Board : public Board<char> {
public:
    Numerical_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_cell_empty(int x, int y) const { return this->get_value(x, y) == ' '; }
   
};

// SUS game //
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    SUS_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;     
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void display_scores();
    int count_SUS_sequences(char symbol);
};


// FourInARow Game //
class FourInARowBoard : public Board<char> {
private:
    static const int ROWS = 6;
    static const int COLS = 7;

public:
    FourInARowBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool isColumnFull(int col) const;
    int dropToBottom(int col, char symbol);
    bool checkFour(char symbol) const;
};


// Infinity Tic-Tac-Toe //
class InfinityTicTacToe_Board : public Board<char> {
private:
    std::deque<std::pair<std::pair<int, int>, char>> move_history;
    void remove_oldest_move();
    bool check_current_win(char sym) const;

public:
    InfinityTicTacToe_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void display_board() const;
};

//Word Tic-Tac-Toe
class Word_TicTacToe_Board : public Board<char> {
private:
    std::set<std::string> dictionary;
    int moves_count = 0;  // بديل n_moves

    void load_dictionary() {
        std::ifstream file("dic.txt");
        if (file.is_open()) {
            std::string word;
            while (file >> word) {
                if (word.length() == 3) {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    dictionary.insert(word);
                }
            }
            file.close();
        }
        // if the player does not have the file dic.txt
        if (dictionary.empty()) {
            const std::string words[] = { "cat","dog","bat","rat","pat","sat","hat","bit","fit","hit",
                                         "kit","lit","pit","sit","car","bar","far","jar","man","fan",
                                         "run","sun","win","bin","ant","art","act","add","age","air" };
            for (const auto& w : words) dictionary.insert(w);
        }
    }

    bool has_valid_word() const {
        auto check = [this](int r, int c, int dr, int dc) -> bool {
            std::string s;
            for (int i = 0; i < 3; ++i) {
                char ch = board[r][c];
                if (ch == ' ') return false;
                s += tolower(ch);
                r += dr; c += dc;
            }
            return dictionary.count(s);
            };

        for (int i = 0; i < 3; ++i)
            if (check(i, 0, 0, 1) || check(0, i, 1, 0)) return true;
        return check(0, 0, 1, 1) || check(0, 2, 1, -1);
    }

public:
    Word_TicTacToe_Board() : Board<char>(3, 3) {
        load_dictionary();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' ';
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = toupper(move->get_symbol());
        moves_count++;
        return true;
    }

    bool is_win(Player<char>*) override { return has_valid_word(); }
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>*) override { return moves_count == 9 && !has_valid_word(); }
    bool game_is_over(Player<char>*) override { return is_win(nullptr) || is_draw(nullptr); }

    void display() const {
        cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << "  ";
            for (int j = 0; j < 3; ++j) {
                char c = board[i][j];
                cout << (c == ' ' ? '.' : c);
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "  ---+---+---\n";
        }
        cout << "\n";
    }

    int get_moves_count() const { return moves_count; }
};

//Pyramid TicTacToe
class Pyramid_TicTacToe_Board : public Board<char> {
public:
    Pyramid_TicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

};

/Diamond game//
class Diamond_Board : public Board<char> {
private:
    char blank = '.';
    char blocked = '#';

public:
    Diamond_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool inside_diamond(int x, int y) const;
    bool is_cell_empty(int x, int y) const;
    bool has_line_of_3(char sym);
    bool has_line_of_4(char sym);

private:
    bool has_line(Player<char>* player, int length);
};
//Memory TicTacToe
class Memory_TicTacToe_Board : public Board<char> {
     public:
         Memory_TicTacToe_Board();

         bool update_board(Move<char>* move) override;
         bool is_win(Player<char>* player) override;
         bool is_lose(Player<char>* player) override;
         bool is_draw(Player<char>* player) override;
         bool game_is_over(Player<char>* player) override;
         bool is_empty_cell(int r, int c);
};

class Ultimate_Board : public Board<char> {
private:
    vector<vector<Board<char>*>> subBoards; // كل Sub-board حجمه 3×3
    vector<vector<char>> main_board_status; // حالة الفوز لكل sub-board
    char blank = '.';
    int last_x = -1;
    int last_y = -1;
    string current_playrer_name;
public:
    Ultimate_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_sub_board_full(int sx, int sy);
    bool force_anywhere() const;
    vector<vector<Board<char>*>>& access_subBoards();
    pair<int, int> get_required_subboard() const { return { last_x, last_y }; }
    void display_board(); // 
    bool main_board_win(char sym);
void set_current_player_name(const string& n) { current_playrer_name = n; };
};
