#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Pawn.h"
#include "Piece.h"

class Board {
 public:
  Board() {}
  virtual ~Board() {}

  /**
   *   Move a piece on the board.
   *   @param side Colour of the side moving the piece.
   *   @param start The coordinate of the piece to move.
   *   @param destination The coordinate of where to move the piece.
   *   @return true if the move is valid, false otherwise.
   *   @throw invalid_location_error One of the locations is
   *       off of the board.
   *   @throw invalid_piece_error The player tried to move the
   *       other player's piece.
   *   @throw no_piece_error The player selected a board location that has no
   * piece.
   */
  virtual bool movePiece(Colour side, Coordinate* start,
                         Coordinate* destination) {
    return false;
  }

  /**
   * Place a piece at a location on the board.
   * @param p The piece.
   * @param c A coordinate on the board.
   */
  virtual void placePiece(Piece* p, Coordinate* c) {}

  /**
   * Clear a location on the board.
   * @param c A coordinate on the board.
   */
  virtual void emptySpace(Coordinate* c) {}

  /**
   * Get the piece at location c.
   * @param c A location on the chessboard.
   */
  virtual Piece* getPiece(Coordinate* c) { return nullptr; }

  /**
   * Check if a player has captured all the opponent's pieces.
   * @param side The player to check.
   */
  virtual bool isWinner(Colour side) { return false; }

  /**
   * Draw the board.
   */
  virtual void draw() {}

  virtual std::vector<std::vector<Piece*>>* getBoard() { return nullptr; }
};

#endif  // BOARD_H
