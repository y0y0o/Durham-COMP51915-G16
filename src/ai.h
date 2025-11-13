#ifndef AI_H
#define AI_H

#include "board.h"

// Simple AI for Gomoku.
// Strategy priority:
// 1. Win immediately if possible
// 2. Block opponent winning move
// 3. Extend own lines (3 or 2 in a row)
// 4. Place near existing stones
// 5. Otherwise place in the center

class AI {
public:
  explicit AI(Cell aiColor);

  // Decide next move for the AI
  // Returns a pair (row, col)
  std::pair<int, int> chooseMove(const Board &board);

private:
  Cell me;    // AI's own color
  Cell enemy; // Opponent's color

  bool isWinningMove(const Board &board, int r, int c, Cell color) const;
  int evaluatePoint(const Board &board, int r, int c, Cell color) const;
};

#endif
