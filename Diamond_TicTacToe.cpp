#include"Games_Board.h"
#include"Games_UI.h"
#include <cstdlib> using namespace std;
// Diamond_Board IMPLEMENTATION
Diamond_Board::Diamond_Board() : Board<char>(5, 5) {

    // fill all with '#'
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = '#';

    // playable diamond cells
    board[2][2] = blank;

    board[1][2] = blank;
    board[2][1] = blank;
    board[2][3] = blank;
    board[3][2] = blank;

    board[0][2] = blank;
    board[1][1] = blank;
    board[1][3] = blank;
    board[2][0] = blank;
    board[2][4] = blank;
    board[3][1] = blank;
    board[3][3] = blank;
    board[4][2] = blank;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
        return false;
    }

    if (board[x][y] == '#') {
        cout << "This cell is BLOCKED!\n";
        return false;
    }

    if (board[x][y] != blank) {
        cout << "Already taken!\n";
        return false;
    }

    board[x][y] = s;
    return true;
}
bool Diamond_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    // الاتجاهات الأربعة: رأسي، قطري نزول، أفقي، قطري طلوع
    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };

    bool has3[4] = { false };
    bool has4[4] = { false };

    // نمشي على كل الخلايا
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;

            // نجرب الاتجاهات الأربعة
            for (int d = 0; d < 4; d++) {

                int count = 1;
                int nx = x + dx[d];
                int ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }
                if (count >= 3) has3[d] = true;
                if (count >= 4) has4[d] = true;
            }
        }
    }
    // لازم يكون فيه اتجاه فيه 3 واتجاه تاني (مختلف) فيه 4
    for (int d1 = 0; d1 < 4; d1++) {
        if (!has3[d1]) continue;
        for (int d2 = 0; d2 < 4; d2++) {
            if (!has4[d2]) continue;
            if (d1 != d2)  // اتجاهين مختلفين = فوز
                return true;
        }
    }
    return false;
}

bool Diamond_Board::is_lose(Player<char>* player) {
    return false;
}

bool Diamond_Board::is_draw(Player<char>* player) {
    if (is_win(player)) return false;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == blank)
                return false;

    return true;
}

bool Diamond_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool Diamond_Board::has_line(Player<char>* player, int L) {
    char s = player->get_symbol();

    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;

            for (int d = 0; d < 4; d++) {
                int count = 1;

                int nx = x + dx[d];
                int ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }

                if (count >= L) return true;
            }
        }
    }
    return false;
}

bool Diamond_Board::inside_diamond(int x, int y) const {
    if (x < 0 || x >= 5 || y < 0 || y >= 5)
        return false;

    if (x == 0) return y == 2;
    if (x == 1) return y >= 1 && y <= 3;
    if (x == 2) return true;
    if (x == 3) return y >= 1 && y <= 3;
    if (x == 4) return y == 2;

    return false;
}

bool Diamond_Board::is_cell_empty(int x, int y) const {
    return board[x][y] == '.';
}




// Diamond_UI IMPLEMENTATION

Diamond_UI::Diamond_UI()
    : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 3) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name()
            << " enter row and column (0-2) : ";
        cin >> x >> y;

        return new Move<char>(x, y, player->get_symbol());
    }

    cout << player->get_name() << " (Computer) is choosing a move";

    Board<char>* board = player->get_board_ptr();
    Diamond_Board* dboard = dynamic_cast<Diamond_Board*>(board);

    while (true) {
        x = rand() % board->get_rows();
        y = rand() % board->get_columns();
        cout << ".";

        if (dboard && dboard->inside_diamond(x, y) && dboard->is_cell_empty(x, y)) {
            cout << " -> (" << x << "," << y << ")\n";
            return new Move<char>(x, y, player->get_symbol());
        }
    }
}
