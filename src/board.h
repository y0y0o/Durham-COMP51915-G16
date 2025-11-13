#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

// Represents a cell on the board:
//   Empty: '.'
//   Black: 'X'
//   White: 'O'
enum class Cell : char { Empty = '.', Black = 'X', White = 'O' };

// Record of a move (row, column, color)
struct Move {
  int r, c;
  Cell color;
};

// The Board class manages the state of the game grid,
// move history, and victory checking.
class Board {
public:
  explicit Board(int n = 15);
  void reset();                      // Clear the board
  bool inBounds(int r, int c) const; // Check if a coordinate is within bounds
  bool place(int r, int c, Cell color); // Place a piece at (r,c)
  bool undo();                          // Undo the last move
  bool full() const;                    // Check if the board is full
  bool isWin(int r, int c) const;       // Check if the move at (r,c) wins
  void print(std::ostream &os) const;   // Print the current board to console

  int size() const { return n; }
  const std::vector<std::vector<Cell>> &cells() const { return grid; }
  const std::vector<Move> &history() const { return moves; }

private:
  int n;                               // Board size (default 15)
  std::vector<std::vector<Cell>> grid; // 2D board representation
  std::vector<Move> moves;             // Move history (for undo)

  int countLine(int r, int c, int dr, int dc, Cell me) const;
  // Helper: count consecutive pieces along direction (dr,dc)
};

#endif
