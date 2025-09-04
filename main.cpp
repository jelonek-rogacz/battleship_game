#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class BattleshipGame {
    int N;        //board size
    int ships;
    vector<vector<int>> board;
    int hits;
    int moves;
public:
    BattleshipGame(int size, int num_ships) {
        N = size;
        ships = num_ships;
        board.assign(N, vector<int>(N, 0));
        hits = 0;
        moves = 0;
        place_ships();
    }

    void place_ships() {
        int placed = 0;
        while (placed < ships) {
            int x = rand() % N;
            int y = rand() % N;
            if (board[x][y] == 0) {
                board[x][y] = 1;
                placed++;
            }
        }
    }

    void print_board(bool reveal=false) {
        cout << "  ";
        for (int i=0; i<N; i++) cout << i << " ";
        cout << "\n";
        for (int i=0; i<N; i++) {
            cout << i << " ";
            for (int j=0; j<N; j++) {
                if (board[i][j] == 2) cout << "X ";       // hit
                else if (board[i][j] == 3) cout << "o ";  // missed
                else if (board[i][j] == 1 && reveal) cout << "S "; //ship
                else cout << "~ ";
            }
            cout << "\n";
        }
    }
    bool game_over() {
        return hits == ships;
    }

    void shooting(int x, int y) {
        moves++;
        if (x < 0 || x >= N || y < 0 || y >= N) {
            cout << "Wrong coordinates!\n";
            return;
        }

        if (board[x][y] == 1) {
            board[x][y] = 2;
            hits++;
            cout << "Hit!\n";
        } else if (board[x][y] == 0) {
            board[x][y] = 3;
            cout << "Missed!\n";
        } else {
            cout << "Can't fire there twice!\n";
        }
    }

    int get_moves() { return moves; }
};
int main() {
        srand(time(0));

        BattleshipGame game(6, 4);
        cout << "=== Battleship Game ===\n";

        while (!game.game_over()) {
            game.print_board();
            int x, y;
            cout << "Where is the ship? (row number <enter> column number): ";
            cin >> x >> y;
            game.shooting(x, y);
        }

        cout << "\nCongratulations! You've sunk all the ships in " << game.get_moves() << " moves!\n";
        cout << "The final battlefield:\n";
        game.print_board(true);
        return 0;
    }