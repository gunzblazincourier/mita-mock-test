#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>

#include "Coordinate.h"
#include "Exceptions.h"

/**
 * The colours for the sides in the game.
 */
enum class Colour : char { WHITE = 'W', BLACK = 'B', NONE = 'N' };

class Piece {
 public:
  /**
   * A game piece.
   * @param colour The side of the piece.
   */
  Piece(Colour colour) : side{colour} {}

  virtual ~Piece() {}

  /**
   * Check that a move is valid.
   *   @param start The coordinate of the piece to move.
   *   @param destination The coordinate of where to move the piece.
   *   @return true if the move is valid, false otherwise.
   *   @throw invalid_location_error Thrown if one of the locations is
   *       off the board.
   *   @throw invalid_piece_error Thrown if the player tries moving the
   *       other player's piece.
   *   @throw no_piece_error The player selected a square that has no piece.
   */
  virtual bool isValidMove(Coordinate* start, Coordinate* destination,
                           std::vector<std::vector<Piece*>>* board) {
    return false;
  }

  /**
   * @return The side of the piece.
   */
  Colour getSide() const { return Colour::NONE; }

  /**
   * Check if a given game piece is equivilant ot this one.
   * @param p The piece to compare.
   * @return true if the two pieces are equal, false otherwise.
   */
  bool operator==(const Piece& p) const { return false; }

  /**
   * Output a string representation of the piece.
   * @param output Output stream.
   * @return p Piece to represent.
   */
  friend std::ostream& operator<<(std::ostream& output, const Piece& p) {
    output << p.getSymbol();
    return output;
  }

  /**
   * Update the location of a piece.
   * @param c The new coordinate of the piece.
   */
  virtual void updateLocation(Coordinate* c) { location = c; }

  const Colour side;

 protected:
  virtual char getSymbol() const { return ' '; }

 private:
  Coordinate* location;
};

#endif  // PIECE_H
