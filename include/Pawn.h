#ifndef PAWN_H
#define PAWN_H

#include <Piece.h>

#include <vector>

class Pawn : public Piece {
 public:
  Pawn(Colour colour) : Piece(colour) {
    canPromote = false;
    enPassantState = false;
    enPassantCoord = new Coordinate(0, 0);
  }

  virtual ~Pawn() { delete enPassantCoord; }

  bool isValidMove(Coordinate* start, Coordinate* destination,
                   std::vector<std::vector<Piece*>>* board) {
    return false;
  }

  /**
   * @return The coordinate for a successful "enpassnat" move.
   */
  Coordinate* getEnPassantCoord() { return nullptr; }

  /**
   * @return true if the pawn can be promoted to another piece.
   */
  bool promotable() { return false; }

  /**
   * @return true if the pawn can perform an "enpassant" move,
   *    false otherwise.
   */
  bool canEnpassant() { return false; }

  char getSymbol() const {
    if (side == Colour::WHITE) {
      return 'p';
    } else {
      return 'P';
    }
  }

 private:
  bool enPassant(Coordinate* start, Coordinate* destination,
                 std::vector<std::vector<Piece*>> board);

  bool canPromote;
  bool enPassantState;
  Coordinate* enPassantCoord;
};

#endif  // PAWN_H
