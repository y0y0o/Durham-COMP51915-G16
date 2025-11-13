# Durham-COMP51915-G16
This repository is for Durham University course name COMP51915-Professional Skills of Group 16. We will collaborThe aim of this project is to collaboratively design and implement a **console-based Gomoku (Five-in-a-Row)** game using modern C++, while applying professional software engineering practices including:

- Git version control & collaboration  
- Unit testing  
- Coding standards & formatting  
- Continuous Integration (GitHub Actions)  
- Modular software design  

---

## 1. Project Overview

This project implements a modular, test-driven Gomoku (Five-in-a-Row) game in modern C++17 as part of the COMP51915 – Professional Skills module at Durham University. The objective of the assignment is not only to build a functioning game, but also to demonstrate competence in professional software engineering practices, including version control, collaborative development, modular system design, automated testing, and continuous integration.

**Gomoku** is a classical two-player board game in which players alternately place stones on a square grid. The goal is to achieve **five consecutive stones** horizontally, vertically, or diagonally. Although the rules are simple, implementing Gomoku in a clean and maintainable way requires careful separation of responsibilities and robust game-state management.

To meet these requirements, our implementation adopts a structured architecture that separates low-level board representation from high-level game flow. System correctness is supported by a comprehensive unit test suite, while development quality is enforced through automatic formatting (clang-format) and a GitHub Actions CI pipeline.

Key characteristics of the project include:

- a well-structured C++17 codebase with clear modular boundaries  
- separation of concerns between the `Board` and `Game` components  
- deterministic win-detection logic covering all directional cases  
- a terminal-based user interface for interactive gameplay  
- unit tests verifying both board behaviour and game mechanics  
- automated linting and CI checks to maintain code quality across the team

This combination of gameplay functionality and engineering workflow demonstrates our application of real-world development practices within the context of a collaborative coursework project.
---

## 2. Features

Our Gomoku implementation is designed not only to reproduce the rules of the game, but also to reflect good software engineering practice. The features of the project can be categorised into three domains: gameplay functionality, system architecture, and engineering workflow.

### Gameplay Features
- **Two-player interactive gameplay** with alternating turns.
- **Configurable board representation** (default 15×15) stored in a clean 2D structure.
- **Input validation** preventing illegal moves such as out-of-bounds coordinates or occupied positions.
- **Deterministic win-detection algorithm** capable of identifying horizontal, vertical, and diagonal five-in-a-row patterns.
- **Clear terminal-based user interface** providing real-time board updates.

### Architectural Features
- **Separation of concerns** through distinct `Board` and `Game` classes.
- `Board` handles:
  - stone placement  
  - grid boundaries  
  - directional win checks  
- `Game` manages:
  - turn order  
  - player interaction  
  - integration of board logic  
- **Maintainable, modular C++17 design**, facilitating readability and extensibility.

### Testing Features
- **Unit tests for the Board component**, covering:
  - placement rules  
  - boundary enforcement  
  - all directional win cases  
- **Unit tests for the Game component**, validating:
  - turn switching  
  - game flow logic  
  - end-game detection
- Tests provide confidence in correctness and guard against regressions.

### ⚙ Engineering Workflow Features
- **clang-format enforcement** ensuring consistent coding style across the team.
- **Makefile-based build system** supporting compilation, testing, and linting tasks.
- **GitHub Actions CI pipeline** that automatically:
  - compiles the project  
  - checks formatting compliance  
  - runs all unit tests
- This workflow mirrors industry-standard development pipelines and ensures stable collaboration.

---

## 3. Project Structure

The project follows a clean and modular directory layout that separates source code, test suites, build automation, and continuous integration configuration. This structure promotes maintainability, clarity, and scalability, aligning with standard practices in collaborative software development.



Durham-COMP51915-G16/
│
├── .github/workflows/ci.yml # CI pipeline
├── src/
│ ├── board.h # Board class header
│ ├── board.cpp # Board implementation
│ ├── game.h # Game logic header
│ ├── game.cpp # Game implementation
│ ├── main.cpp # Program entry point
│ └── gomoku # Built game executable
│
├── tests/
│ ├── test_board.cpp # Unit tests for Board
│ └── test_game.cpp # Unit tests for Game
│
├── Makefile # Build/test/lint rules
├── README.md # Documentation
└── compile_commands.json # (optional) clangd support

---

## 4. Build Instructions

The project uses a Makefile-based build system to ensure consistent compilation, testing, and formatting across all team members. The following instructions describe how to build and manage the project on a standard Linux-based development environment.

### Requirements
Ensure the following tools are installed:

- **g++** or **clang++** with C++17 support  
- **make** (build automation)  
- Linux / macOS / WSL environment  

These tools are readily available on most Unix-like systems and are standard in C++ development workflows.

---

### Build the Project

To compile the entire application, run:

```bash
make
```
this generates：
```bash
./test_board
./gomoku
./tets_game
```
Execute the full unit test suite:
make test

Code formatting compliance
make lint-check


## 5.Running the Game

After building the project, the Gomoku game can be launched directly from the terminal.

### Start the Game

```bash
./gomoku
```
Players alternate by entering coordinates like:
Enter row and column: 7 8
The board updates automatically until a player wins.

## 6.Running Tests

The project includes a dedicated unit test suite that validates the correctness of both the Board and Game components. All tests are executed through the Makefile to ensure a consistent and automated workflow.

### ▶ Run the Entire Test Suite

```bash
make test
```
If needed, individual test executables can be run manually:
```bash
./test_board
./test_game
```
These tests verify:
valid and invalid stone placement
boundary handling
horizontal, vertical, and diagonal win detection
turn switching and game-state transitions

## 7.Code Style Checking

To maintain a consistent and professional coding style across the entire project, the repository enforces formatting rules using **clang-format**. All formatting-related operations are integrated into the Makefile and validated through the CI pipeline.

### 8.Check Formatting Compliance

```bash
make lint-check
```
## Continuous Integration (CI)

This project uses GitHub Actions to ensure that every commit and pull request is automatically validated for build correctness, code style compliance, and test success.

The CI workflow is defined in:
github/workflows/ci.yml


### What the CI Pipeline Checks

The automated workflow performs the following steps:

- Checks out the repository  
- Installs the required C++ toolchain  
- uilds all executables using the Makefile  
- Runs the full unit test suite  
- Verifiescode formatting via `make lint-check`  
- Reports failures directly on GitHub  

---

Using CI ensures:

- consistent build environments  
- early detection of errors  
- guaranteed formatting compliance  
- stable collaboration between team members  
- improved software quality and reliability  

The CI pipeline runs automatically for every push and pull request, ensuring the project remains in a verified working state at all times.


## 9. Team Members & Contributions

This project was collaboratively developed by four members of Group 16.  
Each member contributed to different aspects of the implementation, testing, documentation, and engineering workflow.

| Name | Contributions |
|------|--------------|
| **Waston Wan** | Implemented core game logic in `game.cpp` and `game.h`, designed the win-detection algorithm (horizontal, vertical, diagonal), integrated the main gameplay loop in `main.cpp`, configured the Makefile build workflow, set up the GitHub Actions CI pipeline, and contributed major sections of the project documentation (README). |
| **Ethan** | Developed and maintained the Game test suite in `test_game.cpp`, validating turn switching, gameplay flow, and integrated win-detection. Assisted in debugging cross-module interactions and improving error handling in gameplay logic. |
| **Chen** | Wrote the Board unit tests in `test_board.cpp`, covering boundary checks, stone placement validation, and directional win cases. Contributed to improving the readability and robustness of the Board component through feedback and code review. |
| **Zhenting** | Implemented the Board module (`board.cpp`, `board.h`), including board initialisation, board representation, move validation, and directional scanning functionality. Provided fixes and refinements ensuring compatibility with the Game controller. |

---

### Collaboration Summary

- All members participated in discussions, design decisions, and pair-programming sessions.  
- Each member reviewed code written by others to ensure correctness and consistency.  
- Git history reflects active contributions in implementation, testing, debugging, formatting, and documentation.

10. Acknowledgements

This project is part of the COMP51915 – Professional Skills module at Durham University.
We thank the teaching team for guidance in:

version control best practices

modular code design

automated testing

continuous integration workflows
