#pragma once

#include "move.h"
#include <stdint.h>
#include <string>

class ColorState {
public:
  uint64_t rook = 0;
  uint64_t knight = 0;
  uint64_t bishop = 0;
  uint64_t queen = 0;
  uint64_t king = 0;
  uint64_t pawn = 0;
  bool can_king_side_castle = false;
  bool can_queen_side_castle = false;

  uint64_t getOccupiedBitboard(void) {
    return pawn | rook | knight | bishop | queen | king;
  }
};

class GameState {
public:
  // State of the white pieces.
  ColorState white;

  // State of the black pieces.
  ColorState black;

  // If true -> white's turn, false -> black's turn.
  bool whites_turn = true;

  // The bit of the possible en passant. -1 denotes no en passant available.
  int8_t en_passant = -1;

  uint64_t getWhiteOccupiedBitboard(void) {
    return white.getOccupiedBitboard();
  }
  uint64_t getBlackOccupiedBitboard(void) {
    return black.getOccupiedBitboard();
  }
};

/** Prints board to std out.
 *
 * @param game_state: Game state.
 */
void printBoard(const GameState &game_state);

/** Converts a FEN string to a game state.
 *
 * @param fen: FEN string.
 * @param game_state: Game state.
 */
void fenToGameState(const std::string fen, GameState &game_state);

/** Updates the game state according to the move.
 *
 * @param move: Move.
 * @param game_state: Game state.
 */
void applyMove(Move move, GameState &game_state);
