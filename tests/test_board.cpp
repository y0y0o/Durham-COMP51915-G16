#include "../src/board.h"
#include <iostream>
using namespace std;

int total = 0;
int passed = 0;

void check(bool condition, const string &name) {
  total++;
  if (condition) {
    cout << "[PASS] " << name << endl;
    passed++;
  } else {
    cout << "[FAIL] " << name << endl;
  }
}

void testInitialization() {
  Board b(15);
  check(!b.full(), "Initialization - board not full");
}

void testPlaceAndDuplicate() {
  Board b(15);
  bool ok1 = b.place(7, 7, Cell::Black);
  bool ok2 = b.place(7, 7, Cell::White); // should fail
  check(ok1 && !ok2, "Place and duplicate");
}

void testUndo() {
  Board b(15);
  b.place(7, 7, Cell::Black);
  bool undone = b.undo();
  check(undone, "Undo move");
}

void testHorizontalWin() {
  Board b(15);
  for (int i = 0; i < 5; ++i)
    b.place(7, 3 + i, Cell::Black);
  check(b.isWin(7, 7), "Horizontal win");
}

void testVerticalWin() {
  Board b(15);
  for (int i = 0; i < 5; ++i)
    b.place(3 + i, 7, Cell::White);
  check(b.isWin(7, 7), "Vertical win");
}

void testDiagonalWin() {
  Board b(15);
  for (int i = 0; i < 5; ++i)
    b.place(3 + i, 3 + i, Cell::Black);
  check(b.isWin(7, 7), "Diagonal win");
}

void testFullBoard() {
  Board b(3);
  for (int r = 0; r < 3; ++r)
    for (int c = 0; c < 3; ++c)
      b.place(r, c, Cell::Black);
  check(b.full(), "Full board");
}

int main() {
  testInitialization();
  testPlaceAndDuplicate();
  testUndo();
  testHorizontalWin();
  testVerticalWin();
  testDiagonalWin();
  testFullBoard();

  cout << "Passed " << passed << " of " << total << " tests." << endl;
  return (passed == total) ? 0 : 1;
}