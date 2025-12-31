#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>

#include "Board.h"
#include "ChessUI.h"
#include "Coordinate.h"
#include "Exceptions.h"

class Chess {
 public:
  Chess(ChessUI* ui, Board* b);
  virtual ~Chess();

  /**
   * Start the game.
   */
  void playGame();

  Board* getBoard() { return board; }

 private:
  /**
   * Place the pieces in their starting positions on the board.
   */
  void setup();

  const unsigned int BOARD_SIZE = 5;
  Board* board;
  ChessUI* ui;
  std::vector<Piece*> whitePieces;
  std::vector<Piece*> blackPieces;
};
#endif  // CHESS_H
