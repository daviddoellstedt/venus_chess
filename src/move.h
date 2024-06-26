#pragma once

#include "helper_functions.h"
#include <stdint.h>
#include <string>

// Masks for reading/writing to move.
const uint16_t X_INITIAL_MASK = 0x7;
const uint16_t Y_INITIAL_MASK = 0x38;
const uint16_t X_FINAL_MASK = 0x1C0;
const uint16_t Y_FINAL_MASK = 0xE00;
const uint16_t MOVE_TYPE_MASK = 0xF000;

enum MoveType : uint8_t {
  NONE = 0,
  CASTLE_KINGSIDE = 1,
  CASTLE_QUEENSIDE = 2,
  PROMOTION_QUEEN = 3,
  PROMOTION_ROOK = 4,
  PROMOTION_KNIGHT = 5,
  PROMOTION_BISHOP = 6,
  PAWN_PUSH_2 = 7,
};

class Move {
private:
  /**Moves are stored as a 16-bit integer. Kept as lightweight as possible to
   * allow deeper search. Bits: 0 - 2:   Initial x position 3 - 5:   Initial y
   * position 6 - 8:   Final x position 9 - 11:  Final y position 12 - 15:
   * move type (see MoveType enum).
   */
  uint16_t data = 0;
  void setX1(uint8_t x1) { data |= x1; }
  void setY1(uint8_t y1) { data |= y1 << 3; }
  void setX2(uint8_t x2) { data |= x2 << 6; }
  void setY2(uint8_t y2) { data |= y2 << 9; }
  std::string moveTypeToString(void) {
    switch (getMoveType()) {
    case NONE:
    case PAWN_PUSH_2:
      return "";
    case PROMOTION_QUEEN:
      return "q";
    case PROMOTION_ROOK:
      return "r";
    case PROMOTION_KNIGHT:
      return "n";
    case PROMOTION_BISHOP:
      return "b";
    default:
      return "";
    }
  }

public:
  uint8_t getX1(void) { return data & X_INITIAL_MASK; }
  uint8_t getY1(void) { return (data & Y_INITIAL_MASK) >> 3; }
  uint8_t getX2(void) { return (data & X_FINAL_MASK) >> 6; }
  uint8_t getY2(void) { return (data & Y_FINAL_MASK) >> 9; }
  uint64_t getInitialBitboard(void) { return 1ULL << (getX1() * 8 + getY1()); }
  uint64_t getFinalBitboard(void) { return 1ULL << (getX2() * 8 + getY2()); }
  MoveType getMoveType(void) {
    return (MoveType)((data & MOVE_TYPE_MASK) >> 12);
  }
  void setMoveType(MoveType move_type) {
    data &= ~MOVE_TYPE_MASK;
    data |= move_type << 12;
  }
  std::string toString(void) {
    return (char)('a' + getY1()) + std::to_string(getX1() + 1) +
           (char)('a' + getY2()) + std::to_string(getX2() + 1) +
           moveTypeToString();
  }
  Move() {};
  Move(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, MoveType move_type) {
    setX1(x1);
    setY1(y1);
    setX2(x2);
    setY2(y2);
    setMoveType(move_type);
  }
  Move(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    setX1(x1);
    setY1(y1);
    setX2(x2);
    setY2(y2);
  }
};
