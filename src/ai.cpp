#include "ai.h"
#include <limits>

AI::AI(Cell aiColor) : me(aiColor) {
    enemy = (me == Cell::Black ? Cell::White : Cell::Black);
}

// Check if placing a move here wins immediately
bool AI::isWinningMove(const Board& board, int r, int c, Cell color) const {
    Board temp = board;
    if (!temp.place(r, c, color)) return false;
    return temp.isWin(r, c);
}

// Simple heuristic scoring
int AI::evaluatePoint(const Board& board, int r, int c, Cell color) const {
    int score = 0;

    // +- simple patterns
    static const int dirs[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    for (auto& d : dirs) {
        int count = 1; // self
        int dr = d[0], dc = d[1];
        // forward direction
        int rr = r + dr, cc = c + dc;
        while (board.inBounds(rr, cc) && board.cells()[rr][cc] == color) {
            count++; rr += dr; cc += dc;
        }
        // backward direction
        rr = r - dr; cc = c - dc;
        while (board.inBounds(rr, cc) && board.cells()[rr][cc] == color) {
            count++; rr -= dr; cc -= dc;
        }

        // weight score
        if (count >= 4) score += 1000;
        else if (count == 3) score += 200;
        else if (count == 2) score += 50;
        else score += 10;
    }

    return score;
}

std::pair<int,int> AI::chooseMove(const Board& board) {
    int n = board.size();
    int bestScore = -1;
    int bestR = n/2, bestC = n/2; // default: center

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board.cells()[r][c] != Cell::Empty) continue;

            // 1. If AI can win here, do it
            if (isWinningMove(board, r, c, me)) {
                return {r, c};
            }

            // 2. If opponent wins here, block it
            if (isWinningMove(board, r, c, enemy)) {
                return {r, c};
            }

            // 3. Evaluate move
            int score = evaluatePoint(board, r, c, me) +
                        evaluatePoint(board, r, c, enemy);

            // 4. Slight preference for center
            int dist = abs(r - n/2) + abs(c - n/2);
            score -= dist;

            if (score > bestScore) {
                bestScore = score;
                bestR = r;
                bestC = c;
            }
        }
    }

    return {bestR, bestC};
}
