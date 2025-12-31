#ifndef CHESSUI_H
#define CHESSUI_H

#include <stdexcept>
#include <string>

#include "Piece.h"

class ChessUI {
 public:
  /**
   * Ask the player for a location on the chess board.
   * @param side The player's colour.
   * @param desc A description of the location (e.g. "of the piece to move.")
   * @return A chess board coodinate in chess notation (e.g. B3).
   */
  virtual std::string getLocation(Colour side, const std::string desc) {
    return "";
  }

  /**
   * Display the error message of an exception.
   * @param e The runtime error.
   */
  virtual void invalidMove(const std::runtime_error& e) {}

  /**
   * Display an end of game message.
   * @param The side that has lost.
   */
  virtual void gameOver(Colour side) {}
};

#endif
