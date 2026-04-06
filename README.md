# 🏏 Smart Squad Selection System

A robust, C-based command-line application built to effectively manage player rosters and automatically select the optimal "Playing XI" for a cricket match based on dynamic pitch conditions. 

This project was built fundamentally to demonstrate a strong command of **Data Structures and Algorithms (DSA)** and manual memory management in C. It serves as an excellent demonstration of modular architecture, pointers, and memory allocation.

---

## ✨ Features

- **Player Management:** Add, search, filter, and view cricket players securely stored in an in-memory database.
- **Dynamic "Playing XI" Generator:** Automatically select the best 11 players tailored for a specific pitch type:
  - 🏏 **Batting Pitch:** Focuses heavily on top-rated Batsmen.
  - 🥎 **Bowling Pitch:** Prioritizes top-rated Bowlers.
  - ⚖️ **Balanced Pitch:** Selects a well-rounded mix of Batsmen, Bowlers, and All-rounders.
- **Player Rankings:** View dynamically sorted leaderboards based on player ratings.
- **Persistent Data:** Loads and saves the entire player roster automatically to a disk-based `.txt` file so you never lose data on exit.

---

## 🧠 Data Structure & Algorithm Implementations

To ensure lightning-fast operations and optimized memory, the system leverages three core Data Structures and Algorithms:

### 1. Linked List (`linkedlist.c`)
- **Use Case:** Serves as the primary dynamic in-memory database for all loaded players.
- **Why:** Since the total number of players is typically unknown beforehand, linked lists allow for dynamic and continuous `O(1)` memory growth without reallocation overhead.

### 2. Max Heap (`heap.c`)
- **Use Case:** Used exclusively for selecting the top candidates when generating the Playing XI.
- **Why:** By building a Max Heap in `O(n log n)` time and extracting the root via `extractMax()` 11 times, we retrieve the absolute highest-rated players in `O(k log n)` time without needing to fully sort the entire 40+ player database. 

### 3. Quick Sort (`sort.c`)
- **Use Case:** Generating overall player rankings.
- **Why:** An efficient, in-place `O(n log n)` sorting algorithm that's highly performant. 
- *Pro-tip:* Sorting swaps **pointers (8-bytes)** rather than full Player Structs (86-bytes) to massively lower memory access traffic!

---

## 🧩 System Architecture

The codebase is split into modular translation units (`.c` files) connected via shared headers to maintain a strict separation of concerns.

| Component / Layer | Role / Description | Uses |
| :--- | :--- | :--- |
| `main.c` | **App Controller.** Handles the User Interface (CLI), routing commands to the right modules. | All DSAs |
| `player.h` | **Data Model.** Blueprint of the `Player` struct and constants. | — |
| `utils.h/c` | **Shared Helper Services.** Functions to calculate ratings, print, etc. | — |
| `linkedlist.h/c` | **Storage Layer.** The primary data structure holding all loaded players. | Linked List |
| `heap.h/c` | **Business Logic 1.** Specialized module for extracting the best players for the Squad. | Max Heap |
| `sort.h/c` | **Business Logic 2.** Specialized module for generating ordered leaderboards. | Quick Sort |

---

## 🚀 How to Run

### Compilation
Make sure you have GCC installed. Compile the files into a single `.exe` object using:
```bash
gcc -o squad.exe main.c utils.c linkedlist.c heap.c sort.c -Wall
```

### Execution
Run the compiled executable! Note that the application will automatically load data from (and save it to) `players.txt`.
```bash
./squad.exe
```
