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
/// @brief Misere Tic-Tac-Toe game board class
class Misere_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< @brief Symbol representing empty cell

public:
    /// @brief Constructor
    Misere_TicTacToe_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;
};

/// @brief Obstacles Tic-Tac-Toe game board class
class Obstacles_TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< @brief Symbol representing empty cell
    char obstacle_symbol = '#'; ///< @brief Symbol representing obstacle

public:
    /// @brief Constructor
    Obstacles_TicTacToe_Board();

    /// @brief Adds random obstacles to the board
    void add_random_obstacles();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player)override;
};

/// @brief 5x5 Tic-Tac-Toe game board class
class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol; ///< @brief Symbol representing empty cell

public:
    /// @brief Constructor
    TicTacToe5x5_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Counts the number of 3-in-a-row sequences
    int count_3_in_row(char sym);

    /// @brief Checks if the player has won
    bool is_win(Player<char>*) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>*) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>*) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>*) override;
};

/// @brief 4x4 Tic-Tac-Toe game board class
class TicTacToe4x4_Board : public Board<char> {
public:
    /// @brief Constructor
    TicTacToe4x4_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* p) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Checks if a specific cell is empty
    bool is_cell_empty(int x, int y) const {
        return get_value(x, y) == '.';
    }

    /// @brief Gets the value of a specific cell
    virtual char get_value(int x, int y) const {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            return board[x][y];
        return '.';
    }

    /// @brief Sets the value of a specific cell
    void set_value(int x, int y, char val) {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
            board[x][y] = val;
    }
};
/// @brief Numerical Tic-Tac-Toe game board class
class Numerical_TicTacToe_Board : public Board<int> {
public:
    /// @brief Constructor
    Numerical_TicTacToe_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<int>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<int>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<int>* p) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<int>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<int>* player) override;

    /// @brief Checks if a specific cell is empty
    bool is_cell_empty(int x, int y) const { return this->get_value(x, y) == 0; }
};

/// @brief SUS Tic-Tac-Toe game board class
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< @brief Symbol representing empty cell

public:
    /// @brief Constructor
    SUS_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Displays the scores
    void display_scores();

    /// @brief Counts SUS sequences for a symbol
    int count_SUS_sequences(char symbol);
};

/// @brief Diamond Tic-Tac-Toe game board class
class Diamond_Board : public Board<char> {
private:
    char blank = '.'; ///< @brief Symbol representing empty cell
    char blocked = '#'; ///< @brief Symbol representing blocked cell

public:
    /// @brief Constructor
    Diamond_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Checks if a cell is inside the diamond
    bool inside_diamond(int x, int y) const;

    /// @brief Checks if a specific cell is empty
    bool is_cell_empty(int x, int y) const;

    /// @brief Checks if there is a line of 3 for a symbol
    bool has_line_of_3(char sym);

    /// @brief Checks if there is a line of 4 for a symbol
    bool has_line_of_4(char sym);

private:
    /// @brief Helper to check lines of specific length
    bool has_line(Player<char>* player, int length);
};

/// @brief Ultimate Tic-Tac-Toe game board class
class Ultimate_Board : public Board<char> {
private:
    vector<vector<Board<char>*>> subBoards; ///< @brief 2D vector of sub-boards
    vector<vector<char>> main_board_status; ///< @brief Main board status
    char blank = '.'; ///< @brief Symbol representing empty cell
    int last_x = -1; ///< @brief Last move row
    int last_y = -1; ///< @brief Last move column
    string current_playrer_name; ///< @brief Current player name

public:
    /// @brief Constructor
    Ultimate_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Checks if a sub-board is full
    bool is_sub_board_full(int sx, int sy);

    /// @brief Checks if player can play anywhere
    bool force_anywhere() const;

    /// @brief Accessor for sub-boards
    vector<vector<Board<char>*>>& access_subBoards();

    /// @brief Gets the required sub-board for next move
    pair<int, int> get_required_subboard() const { return { last_x, last_y }; }

    /// @brief Displays the main board
    void display_board();

    /// @brief Checks if main board has winning symbol
    bool main_board_win(char sym);

    /// @brief Sets current player name
    void set_current_player_name(const string& n) { current_playrer_name = n; };
};

/// @brief Infinity Tic-Tac-Toe game board class
class InfinityTicTacToe_Board : public Board<char> {
private:
    std::deque<std::pair<std::pair<int, int>, char>> move_history; ///< @brief History of moves

    /// @brief Checks if current symbol has winning condition
    bool check_current_win(char sym) const;

public:
    /// @brief Constructor
    InfinityTicTacToe_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Displays the board
    void display_board() const;
};

/// @brief Memory Tic-Tac-Toe game board class
class Memory_TicTacToe_Board : public Board<char> {
public:
    /// @brief Constructor
    Memory_TicTacToe_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Checks if a cell is empty
    bool is_empty_cell(int r, int c);
};

/// @brief Pyramid Tic-Tac-Toe game board class
class Pyramid_TicTacToe_Board : public Board<char> {
public:
    /// @brief Constructor
    Pyramid_TicTacToe_Board();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* p) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;
};



/// @brief Four in a Row game board class
class FourInARowBoard : public Board<char> {
private:
    static const int ROWS = 6; ///< @brief Number of rows
    static const int COLS = 7; ///< @brief Number of columns

public:
    /// @brief Constructor
    FourInARowBoard();

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override;

    /// @brief Checks if the player has won
    bool is_win(Player<char>* player) override;

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>* player) override;

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>* player) override;

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>* player) override;

    /// @brief Checks if a column is full
    bool isColumnFull(int col) const;

    /// @brief Drops a symbol to the bottom of a column
    int dropToBottom(int col, char symbol);

    /// @brief Checks for four in a row
    bool checkFour(char symbol) const;

    /// @brief Evaluates a window of the board
    int evaluate_window(const std::vector<char>& window, char symbol) const;

    /// @brief Evaluates the board for a symbol
    int evaluate_board(char symbol) const;

    /// @brief Minimax algorithm for AI
    int minimax(int depth, bool isMaximizing, char aiSymbol, char humanSymbol, int alpha = -1000000, int beta = 1000000);

    /// @brief Gets the best move for AI
    int get_best_move(char aiSymbol, int maxDepth = 7);
};


/// @brief Word Tic-Tac-Toe game board class
class Word_TicTacToe_Board : public Board<char> {
private:
    std::set<std::string> dictionary; ///< @brief Set of valid 3-letter words
    int moves_count = 0;  ///< @brief Number of moves made 

    /// @brief Loads dictionary from file or default words
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

    /// @brief Checks if there is a valid word on the board
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
    /// @brief Constructor
    Word_TicTacToe_Board() : Board<char>(3, 3) {
        load_dictionary();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' ';
    }

    /// @brief Updates the board with a move
    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = toupper(move->get_symbol());
        moves_count++;
        return true;
    }

    /// @brief Checks if the player has won
    bool is_win(Player<char>*) override { return has_valid_word(); }

    /// @brief Checks if the player has lost
    bool is_lose(Player<char>*) override { return false; }

    /// @brief Checks if the game is draw
    bool is_draw(Player<char>*) override { return moves_count == 9 && !has_valid_word(); }

    /// @brief Checks if the game is over
    bool game_is_over(Player<char>*) override { return is_win(nullptr) || is_draw(nullptr); }

    /// @brief Displays the board
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

    /// @brief Returns number of moves made
    int get_moves_count() const { return moves_count; }
};






