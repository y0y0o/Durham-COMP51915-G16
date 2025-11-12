#include "board.h"
#include <iomanip>
#include <algorithm>

Board::Board(int n): n(n), grid(n, std::vector<Cell>(n, Cell::Empty)) {}

// Reset the board to empty
void Board::reset() {
    for (auto &row : grid) std::fill(row.begin(), row.end(), Cell::Empty);
    moves.clear();
}

bool Board::inBounds(int r, int c) const {
    return r >= 0 && r < n && c >= 0 && c < n;
}

// Try to place a stone at (r,c)
bool Board::place(int r, int c, Cell color) {
    if (!inBounds(r,c) || grid[r][c] != Cell::Empty) return false;
    grid[r][c] = color;
    moves.push_back({r,c,color});
    return true;
}

// Undo the last move
bool Board::undo() {
    if (moves.empty()) return false;
    auto m = moves.back();
    moves.pop_back();
    grid[m.r][m.c] = Cell::Empty;
    return true;
}

// Check if the board is full (draw)
bool Board::full() const {
    for (auto &row : grid)
        for (auto x : row)
            if (x == Cell::Empty) return false;
    return true;
}

// Check if there are 5 in a row including (r,c)
bool Board::isWin(int r, int c) const {
    if (!inBounds(r,c)) return false;
    Cell me = grid[r][c];
    if (me == Cell::Empty) return false;

    // Directions: vertical, horizontal, and two diagonals
    static const int dirs[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    for (auto &d : dirs) {
        int cnt = 1;
        cnt += countLine(r, c, d[0], d[1], me);
        cnt += countLine(r, c, -d[0], -d[1], me);
        if (cnt >= 5) return true;
    }
    return false;
}

// Count consecutive stones in a direction (dr,dc)
int Board::countLine(int r, int c, int dr, int dc, Cell me) const {
    int i = 1, cnt = 0;
    while (true) {
        int nr = r + dr*i, nc = c + dc*i;
        if (!inBounds(nr, nc) || grid[nr][nc] != me) break;
        ++cnt; ++i;
    }
    return cnt;
}

// Print the current board nicely
void Board::print(std::ostream& os) const {
    os << "    ";
    for (int c=0;c<n;++c) os << std::setw(2) << char('A'+c) << ' ';
    os << "\n";
    os << "   +" << std::string(n*3, '-') << "+\n";
    for (int r=0;r<n;++r) {
        os << std::setw(2) << r+1 << " |";
        for (int c=0;c<n;++c)
            os << ' ' << char(grid[r][c]) << ' ';
        os << "|\n";
    }
    os << "   +" << std::string(n*3, '-') << "+\n";
    os << "   Total moves: " << moves.size() << "\n";
}

