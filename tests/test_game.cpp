#include <iostream>
#include "../src/game.h"
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

void testEqualsIgnoreCase() {
    Game g;
    check(g.equalsIgnoreCase("Quit", "quit"), "equalsIgnoreCase - same word different case");
    check(!g.equalsIgnoreCase("Undo", "und0"), "equalsIgnoreCase - different word");
}

void testIsQuit() {
    Game g;
    check(g.isQuit("Q"), "isQuit - single letter");
    check(g.isQuit("quit"), "isQuit - full word lowercase");
    check(!g.isQuit("play"), "isQuit - invalid word");
}

void testIsUndo() {
    Game g;
    check(g.isUndo("u"), "isUndo - single letter");
    check(g.isUndo("UNDO"), "isUndo - uppercase");
    check(!g.isUndo("move"), "isUndo - invalid word");
}

void testParseMove() {
    Game g;
    int row, col;
    bool ok;

    ok = g.parseMove("H 8", row, col);
    check(ok && row == 7 && col == 7, "parseMove - letter space number");

    ok = g.parseMove("j10", row, col);
    check(ok && row == 9 && col == 9, "parseMove - letter+number together");

    ok = g.parseMove("8 8", row, col);
    check(ok && row == 7 && col == 7, "parseMove - number space number");

    ok = g.parseMove("A", row, col);
    check(ok && col == 0, "parseMove - single letter");

    ok = g.parseMove("@@", row, col);
    check(!ok, "parseMove - invalid format");
}

int main() {
    testEqualsIgnoreCase();
    testIsQuit();
    testIsUndo();
    testParseMove();

    cout << "Passed " << passed << " of " << total << " tests." << endl;
    return (passed == total) ? 0 : 1;
}