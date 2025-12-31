#include "gmock/gmock.h"
#include "Chess.h"
#include "Board.h"
#include "ChessUI.h"
#include "Coordinate.h"
#include <stdexcept>
#include <string>

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

// Mock classes for Board and ChessUI
class MockBoard : public Board
{
public:
	MOCK_METHOD(bool, movePiece, (Colour, Coordinate *, Coordinate *), (override));
	MOCK_METHOD(void, placePiece, (Piece *, Coordinate *), (override));
	MOCK_METHOD(bool, isWinner, (Colour), (override));
	MOCK_METHOD(void, draw, (), (override));
};

class MockChessUI : public ChessUI
{
public:
	MOCK_METHOD(std::string, getLocation, (Colour, const std::string), (override));
	MOCK_METHOD(void, invalidMove, (const std::runtime_error &), (override));
	MOCK_METHOD(void, gameOver, (Colour), (override));
};

// Tests chess.playGame()
TEST(ChessTest, CanPlayGame) {
	MockBoard board;
	MockChessUI ui;

	// Empty error message to use as argument for runtime_error
	const char* e = "";

	EXPECT_CALL(board, placePiece)
		.Times(10);

	EXPECT_CALL(board, draw())
		.Times(17);

	EXPECT_CALL(ui, getLocation)
		.Times(34)

		// White moves
		.WillOnce(Return("A1"))
		.WillOnce(Return("A2"))

		// Black moves
		.WillOnce(Return("B5"))
		.WillOnce(Return("B3"))

		// White moves; Black captured
		.WillOnce(Return("A2"))
		.WillOnce(Return("B3"))

		// Invalid White move; throws runtime_error
		.WillOnce(Return("A6"))
		.WillOnce(Return("B3"))

		// Black moves
		.WillOnce(Return("C5"))
		.WillOnce(Return("C4"))

		// White moves; Black captured
		.WillOnce(Return("B3"))
		.WillOnce(Return("C4"))

		// Black moves; White captured
		.WillOnce(Return("D5"))
		.WillOnce(Return("C4"))

		// White moves
		.WillOnce(Return("D1"))
		.WillOnce(Return("D3"))

		// Invalid Black move
		.WillOnce(Return("E5"))
		.WillOnce(Return("B3"))

		// Black moves
		.WillOnce(Return("E5"))
		.WillOnce(Return("E3"))

		// White moves; Black captured en passant
		.WillOnce(Return("D3"))
		.WillOnce(Return("E4"))

		// Black moves
		.WillOnce(Return("A5"))
		.WillOnce(Return("A3"))

		// White moves
		.WillOnce(Return("B1"))
		.WillOnce(Return("B3"))

		// Black moves; White captured en passant
		.WillOnce(Return("A3"))
		.WillOnce(Return("B2"))

		// White moves; Black captured
		.WillOnce(Return("C1"))
		.WillOnce(Return("B2"))

		// Black moves
		.WillOnce(Return("C4"))
		.WillOnce(Return("C3"))

		// White moves; Black captured
		.WillOnce(Return("B2"))
		.WillOnce(Return("C3"));

	EXPECT_CALL(board, movePiece)
		.Times(17)
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Throw(std::runtime_error(e)))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Throw(std::runtime_error(e)))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true));

	EXPECT_CALL(ui, invalidMove)
		.Times(2);

	EXPECT_CALL(board, isWinner)
		.Times(15)
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(false))

		// White wins
		.WillOnce(Return(true));

	EXPECT_CALL(ui, gameOver);

	Chess chess(&ui, &board);
	chess.playGame();
}