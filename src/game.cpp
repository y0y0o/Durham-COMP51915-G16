#include "game.h"
#include <algorithm>
#include <cctype>
#include <iostream>

Game::Game()
    : board(15), current(Cell::Black), againstAI(false), aiPlayer(nullptr) {}

// ---------------------- GAME LOOP ----------------------
void Game::loop() {
  printHelp();

  // Ask if AI mode
  std::cout << "Play against AI? (y/n): ";
  std::string aiAns;
  std::getline(std::cin, aiAns);
  trim(aiAns);
  againstAI = (!aiAns.empty() && (aiAns[0] == 'y' || aiAns[0] == 'Y'));

  if (againstAI) {
    aiPlayer = new AI(Cell::White); // Player = Black
    std::cout << "AI enabled. You play as Black (X).\n";
  }

  while (true) {
    board.reset();
    current = Cell::Black;
    bool gameOver = false;

    while (!gameOver) {
      board.print(std::cout);

      // ---------------- AI Move ----------------
      if (againstAI && current == Cell::White) {
        auto [r, c] = aiPlayer->chooseMove(board);

        board.place(r, c, Cell::White);
        std::cout << "AI plays: " << char('A' + c) << (r + 1) << "\n";

        if (board.isWin(r, c)) {
          board.print(std::cout);
          std::cout << "[WIN] AI wins!\n";
          gameOver = true;
        } else if (board.full()) {
          board.print(std::cout);
          std::cout << "Draw!\n";
          gameOver = true;
        } else {
          switchPlayer();
        }
        continue;
      }

      // ---------------- Player Move ----------------
      std::cout << playerName(current)
                << "'s turn. Enter your move (H 8 / j10), "
                   "'u' to undo, 'q' to quit: ";

      std::string line;
      if (!std::getline(std::cin, line))
        return;
      trim(line);
      if (line.empty())
        continue;

      if (isQuit(line)) {
        std::cout << "Game exited.\n";
        return;
      }
      if (isUndo(line)) {
        if (!doUndo())
          std::cout << "No moves to undo.\n";
        continue;
      }
      if (equalsIgnoreCase(line, "help")) {
        printHelp();
        continue;
      }

      int r = -1, c = -1;
      if (!parseMove(line, r, c)) {
        std::cout << "Invalid input. Please enter a valid move.\n";
        continue;
      }

      if (!board.place(r, c, current)) {
        std::cout << "Invalid move. Try again.\n";
        continue;
      }

      if (board.isWin(r, c)) {
        board.print(std::cout);
        std::cout << "[WIN] " << playerName(current) << " wins!\n";
        gameOver = true;
      } else if (board.full()) {
        board.print(std::cout);
        std::cout << "Draw!\n";
        gameOver = true;
      } else {
        switchPlayer();
      }
    }

    // ---------------- Replay? ----------------
    while (true) {
      std::cout << "Play again? (y/n): ";
      std::string ans;
      std::getline(std::cin, ans);
      trim(ans);
      if (ans.empty())
        continue;

      char ch = std::tolower(ans[0]);
      if (ch == 'y')
        break;
      if (ch == 'n') {
        std::cout << "Thanks for playing!\n";
        return;
      }
      std::cout << "Invalid input.\n";
    }
  }
}

// -------------------------------------------------------

void Game::switchPlayer() {
  current = (current == Cell::Black ? Cell::White : Cell::Black);
}

std::string Game::playerName(Cell p) const {
  return (p == Cell::Black ? "Black (X)" : "White (O)");
}

bool Game::doUndo() {
  bool ok1 = board.undo();
  bool ok2 = board.undo();
  if (ok1 && ok2)
    return true;
  if (ok1)
    switchPlayer();
  return ok1;
}

void Game::trim(std::string &s) {
  auto ns = [](int ch) { return !std::isspace(ch); };
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), ns));
  s.erase(std::find_if(s.rbegin(), s.rend(), ns).base(), s.end());
}

bool Game::equalsIgnoreCase(const std::string &a, const std::string &b) {
  if (a.size() != b.size())
    return false;
  for (size_t i = 0; i < a.size(); i++)
    if (std::tolower(a[i]) != std::tolower(b[i]))
      return false;
  return true;
}

bool Game::isQuit(const std::string &s) {
  static const std::vector<std::string> qs = {"q", "quit", "exit"};
  for (auto &t : qs)
    if (equalsIgnoreCase(s, t))
      return true;
  return false;
}

bool Game::isUndo(const std::string &s) {
  static const std::vector<std::string> us = {"u", "undo"};
  for (auto &t : us)
    if (equalsIgnoreCase(s, t))
      return true;
  return false;
}

bool Game::parseMove(const std::string &s, int &r, int &c) const {
  std::string A, B;

  for (char ch : s) {
    if (isalpha((unsigned char)ch))
      A.push_back(ch);
    else if (isdigit((unsigned char)ch))
      B.push_back(ch);
    else if (isspace((unsigned char)ch))
      continue;
    else
      return false; // invalid character
  }

  // Must have exactly 1 letter + at least 1 digit
  if (A.size() != 1 || B.empty())
    return false;

  // Convert row (letter)
  r = toupper(A[0]) - 'A';
  if (r < 0 || r >= 15)
    return false;

  // Convert column (number)
  int col = std::stoi(B);
  if (col < 1 || col > 15)
    return false;

  c = col - 1;

  return board.inBounds(r, c);
}

void Game::printHelp() const {
  std::cout << "================ Gomoku ================\n"
               "Board: 15x15\n"
               "Black (X) goes first\n"
               "Examples: H 8, j10, 8 8\n"
               "Commands:\n"
               "  u, undo  - Undo last round\n"
               "  q, quit  - Quit the game\n"
               "========================================\n";
}
