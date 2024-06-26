<div align="center">
 <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/93/Venus_globe_-_transparent_background.png/1200px-Venus_globe_-_transparent_background.png" 
  width="150" height="150">
  <h1>venus</h1>
  <p>a UCI-compliant chess engine written in C++</p>
  <p>current release: <a href="https://github.com/daviddoellstedt/venus_chess/releases">v1.0.0</a></p>
  <p>author: David Doellstedt</p>
</div>

# Background
This has been a personal side project, originally started during the 2020 
pandemic.

The chess engine does not provide it's own GUI. However, it is compatible with 
any UCI-compliant GUI. There are many free GUIs available for download/use; Stockfish
has compiled a nice list of them [here](https://github.com/official-stockfish/Stockfish/wiki/Download-and-usage#download-a-chess-gui).

# Project Structure

* [src/](https://github.com/daviddoellstedt/venus_chess/tree/master/src) : Subdirectory containing all source files
* [test/](https://github.com/daviddoellstedt/venus_chess/tree/master/test) : Subdirectory containing unit test files.
* venus_chess : The executable.

# Design Details
Game state is represented with bitboards (64-bit integers). Each bit represents a square on the chess board. 12 bitboards are used to fully represent the game, 1 bitboard per piece type per color. Move generation is accomplished using bitwise operations and [magic bitboards](https://www.chessprogramming.org/Magic_Bitboards). The AI agent uses the minimax algorithm with alpha/beta pruning to search deep in the game tree and select the best move. The evaluation function is fairly barebones, only based on material and position. The AI is able to look around 8 moves in the future, depending on the branching factor of the current game state. Tested on an Apple M1 chip, single threaded, performance details below:

|                                                 | NPS (nodes per second)|
| ------------------------------------------------|:---------------------:|
| [Perft](https://www.chessprogramming.org/Perft) | ~15M                  |
| Standard gameplay                               | ~1M                   |


# Further Improvement
There are many ways to further optimize the performance:

* Improve evalution function (piece position, pawn structure, king safety, end game, etc.)
* Opening book
* Move ordering
* Iterative deepening
* Memoization (Zobrist hashing)
* Multi-threading


# Licensing
Feel free to use and distribute this software as you please.
