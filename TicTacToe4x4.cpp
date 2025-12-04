#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib> // rand, srand
using namespace std;

//Board implementation
TicTacToe4x4_Board::TicTacToe4x4_Board() : Board<char>(4, 4) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = '.';
}

bool TicTacToe4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
   char symbol = move->get_symbol(); 

    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        cout << "Invalid position!\n";
        return false;
    }

    if (this->get_value(x, y) != '.') {
        cout << "This cell is already taken!\n";
        return false;
    }

    set_value(x, y, symbol);
    n_moves++;
    return true;
}
    
bool TicTacToe4x4_Board::is_win(Player<char>* player) {
    int s = player->get_symbol();
    //check rows
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c <=1; c++) {
            if (board[r][c] == s &&
                board[r][c + 1] == s &&
                board[r][c + 2] == s)
                return true;
        }
    }
    //check columns
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r <= 1; r++) {
            if (board[r][c] == s &&
                board[r + 1][c] == s &&
                board[r + 2][c] == s)
                return true;
        }
    }
      // check diagonals from top left to bottom right
  for (int r = 0; r <= 1; ++r) {
    for (int c = 0; c <= 1; ++c) {
        if (board[r][c] == s &&
            board[r + 1][c + 1] == s &&
            board[r + 2][c + 2] == s)
            return true;
    }
}

    //check diagonals from top right to bottom left
for (int r = 0; r <= 1; ++r) {
    for (int c = 0; c <= 1; ++c) {
        if (board[r][c + 2] == s &&
            board[r + 1][c + 1] == s &&
            board[r + 2][c] == s)
            return true;
    }
}

    return false;

}
bool TicTacToe4x4_Board::is_lose(Player<char>* player)
{
    char other = (player->get_symbol() == 'X' ? 'O' : 'X');
    Player<char> temp("temp", other, PlayerType::HUMAN);
    return is_win(&temp);
}
bool TicTacToe4x4_Board::is_draw(Player<char>* player)
{
    return n_moves == 16 && !is_win(player);
}
bool TicTacToe4x4_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_lose(player) || is_draw(player);
}
//UI implementation
TicTacToe4x4_UI::TicTacToe4x4_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 3) {
      srand(static_cast<unsigned int>(std::time(nullptr)));
}

Player<char>* TicTacToe4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating player: " << name << endl;
    return new Player<char>(name, symbol, type);
}

//AI algorithm
int evaluateSimple(Board<char>* b, char aiSymbol) {
    char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';
    Player<char> aiTmp("ai", aiSymbol, PlayerType::COMPUTER);
    Player<char> huTmp("hu", humanSymbol, PlayerType::HUMAN);
    if (b->is_win(&aiTmp)) return 1000;
    if (b->is_win(&huTmp)) return -1000;
    return 0;
}


bool movesLeftSimple(Board<char>* b) {
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            if (b->get_value(r, c) == '.') return true;
    return false;
}


int minimax_simple(Board<char>* b, int depth, int maxDepth, int alpha, int beta, bool isMax, char aiSymbol) {
    int score = evaluateSimple(b, aiSymbol);

    
    if (score == 1000) return score - depth;   
    if (score == -1000) return score + depth; 
   
    if (depth >= maxDepth || !movesLeftSimple(b)) return 0;

    char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';

    if (isMax) {
        int best = std::numeric_limits<int>::min();
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (b->get_value(r, c) == '.') {
                    b->set_value(r, c, aiSymbol);
                    int val = minimax_simple(b, depth + 1, maxDepth, alpha, beta, false, aiSymbol);
                    b->set_value(r, c, '.'); 
                    best = std::max(best, val);
                    alpha = std::max(alpha, best);
                    if (alpha >= beta) return best; 
                }
            }
        }
        return best;
    }
    else {
        int best = std::numeric_limits<int>::max();
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (b->get_value(r, c) == '.') {
                    b->set_value(r, c, humanSymbol);
                    int val = minimax_simple(b, depth + 1, maxDepth, alpha, beta, true, aiSymbol);
                    b->set_value(r, c, '.'); 
                    best = std::min(best, val);
                    beta = std::min(beta, best);
                    if (alpha >= beta) return best; 
                }
            }
        }
        return best;
    }
}


std::pair<int, int> findBestMove(Board<char>* b, char aiSymbol) {
    std::pair<int, int> bestMove = { -1,-1 };
    int bestVal = std::numeric_limits<int>::min();

    const int MAX_DEPTH = 6; 
    
    std::vector<std::pair<int, int>> moves;
    for (int r = 0; r < 4; ++r) for (int c = 0; c < 4; ++c)
        if (b->get_value(r, c) == '.') moves.push_back({ r,c });

 
    std::sort(moves.begin(), moves.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        int scoreA = (a.first == 1 || a.first == 2) + (a.second == 1 || a.second == 2);
        int scoreB = (b.first == 1 || b.first == 2) + (b.second == 1 || b.second == 2);
        return scoreA > scoreB;
        });

    for (auto mv : moves) {
        int r = mv.first, c = mv.second;
        b->set_value(r, c, aiSymbol);
        int moveVal = minimax_simple(b, 0, MAX_DEPTH, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false, aiSymbol);
        b->set_value(r, c, '.');
        if (moveVal > bestVal) {
            bestVal = moveVal;
            bestMove = { r,c };
        }
    }

    return bestMove;
}


Move<char>* TicTacToe4x4_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* board = player->get_board_ptr();
//Human
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
         //AI
    else {
        cout << player->get_name() << " AI is thinking";

       char AiSymbol = player->get_symbol();
auto mv = findBestMove(board, AiSymbol);
if (mv.first == -1) {
    while (true) {
        cout << ".";

        x = rand() % 4;
        y = rand() % 4;


        if (board->get_value(x, y) == '.') {

            cout << " -> (" << x << "," << y
                << ") with " << AiSymbol << endl;

            return new Move<char>(x, y, AiSymbol);
         }
      }
   }
   else {
      cout << " -> (" << mv.first << "," << mv.second << ") with " << AiSymbol << endl;
      return new Move<char>(mv.first, mv.second, AiSymbol);
    }
  }
}
